//============================================
//
//	spawn.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "spawn.h"
#include "enemy.h"
#include "objectX.h"
#include "game.h"
#include "player.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "indication.h"
#include "boss.h"
#include "hp.h"
#include "sound.h"
#include "warning.h"

//============================================
// 静的メンバ変数宣言
//============================================
CBoss *CSpawn::m_pBoss = nullptr;

//============================================
// コンストラクタ
//============================================
CSpawn::CSpawn()
{
	//============================================
	// メンバ変数のクリア
	//============================================
}

//============================================
// デストラクタ
//============================================
CSpawn::~CSpawn()
{
	//何も書かない
}

//============================================
// 量産の初期化処理
//============================================
HRESULT CSpawn::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_EnemyCreateTime = 0;
	m_RandNumber = 0;
	m_EnemyCount = 0;
	m_WaveTime = 0;
	m_BossAppearTime = 0;
	m_RandFlag = false;
	m_MaxEnemyFlag = false;
	m_IndicationFlag = false;
	m_BossFlag = false;

	return S_OK;
}

//============================================
// 量産の終了処理
//============================================
void CSpawn::Uninit(void)
{
	//破棄処理
	Release();
}

//============================================
// 量産の更新処理
//============================================
void CSpawn::Update(void)
{
	if (CPlayer::GetBullet() != nullptr)
	{
		m_EnemyCount = CPlayer::GetBullet()->GetTotalEnemy();
	}

	if (m_EnemyCount < MAX_ENEMY_1 && m_EnemyCreateTime == ENEMY_CREATE_TIME_WAVE_1)
	{
		m_MaxEnemyFlag = false;
	}
	if (m_EnemyCount < MAX_ENEMY_2 && m_EnemyCreateTime == ENEMY_CREATE_TIME_WAVE_2)
	{
		m_MaxEnemyFlag = false;
	}

	if (m_MaxEnemyFlag == false)
	{
		//敵の量産処理の関数呼び出し
		EnemySpawn();
	}
}

//============================================
// 量産の描画処理
//============================================
void CSpawn::Draw(void)
{

}

//============================================
// 量産の生成処理
//============================================
CSpawn *CSpawn::Create()
{
	CSpawn *pSpawn = nullptr;

	// 量産クラスの生成
	pSpawn = new CSpawn;				// 量産インスタンス生成

	// nullptrチェック
	if (pSpawn != nullptr)
	{
		// 初期化処理
		pSpawn->Init();
	}
	else
	{
		assert(false);
	}
	return pSpawn;
}

//============================================
// ボスのインスタンスの設定処理
//============================================
void CSpawn::SetBoss(CBoss *boss)
{
	m_pBoss = boss;
}

//============================================
// 敵の量産処理
//============================================
void CSpawn::EnemySpawn(void)
{
	//敵が生成されるまでの時間を減らしていく
	m_EnemyCreateTime--;
	m_WaveTime++;
	m_BossAppearTime++;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	if (m_EnemyCreateTime <= 0 && m_RandFlag == false && m_MaxEnemyFlag == false)
	{
		m_RandNumber = 1;								//ランダムな数値を決める
		x = rand() % (1000 - (-135 + 1)) + (-135);		//xの範囲にランダム
		y = 0.0f;										//yは0.0fに固定
		z = rand() % (150 - (-1050 + 1)) + (-1050);		//zの範囲にランダム
		m_EnemySpawnType = rand() % 3 + 1;				//ゾンビの種類ランダム
		m_RandFlag = true;								//ランダムな数値を決め終わった
	}
	//ウェーブ1
	if (m_EnemyCreateTime <= 0 && m_WaveTime <= WAVE_TIME)
	{	
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_1;	//時間を初期化

		if (m_EnemyCount >= MAX_ENEMY_1)
		{
			m_MaxEnemyFlag = true;
		}
	}
	//ウェーブ2
	if (m_EnemyCreateTime <= 0 && m_WaveTime >= WAVE_TIME)
	{
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_2;	//時間を初期化

		if (m_IndicationFlag == false)
		{
			CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE2);	//表示の生成
			m_IndicationFlag = true;
		}

		if (m_EnemyCount >= MAX_ENEMY_2)
		{
			m_MaxEnemyFlag = true;
		}
	}
	//ウェーブ3
	if (m_EnemyCreateTime <= 0 && m_WaveTime >= WAVE_TIME)
	{
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_2;	//時間を初期化

		if (m_IndicationFlag == false)
		{
			CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE2);	//表示の生成
			m_IndicationFlag = true;
		}

		if (m_EnemyCount >= MAX_ENEMY_2)
		{
			m_MaxEnemyFlag = true;
		}
	}
	if (m_RandNumber == 1 && m_RandFlag == true)
	{
		CEnemy::Create(D3DXVECTOR3(x, y, z), CEnemy::ENEMYTYPE_HUMAN);
		if (m_EnemySpawnType == 1 && m_WaveTime >= WAVE_TIME)
		{
			CEnemy::Create(D3DXVECTOR3(x, y, z), CEnemy::ENEMYTYPE_DOG);
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DOG_VOICE);
		}
		if (m_BossAppearTime >= WAVE_TIME2 && m_BossFlag == false && m_pBoss == nullptr)
		{
			m_pBoss = CBoss::Create(D3DXVECTOR3(555.0f,0.0f, -200.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));		//ボスの生成
			CHp::Create(CHp::HPTYPE_BOSS);																//ボスの体力生成
			CWarning::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CWarning::WARNINGTYPE_SCREEN);	//Warningの生成
			m_BossAppearTime = WAVE_TIME2;
			m_BossFlag = true;
		}
		m_EnemyCount++;
		m_RandFlag = false;
	}

	//if (m_EnemyCount >= 1)
	//{
	//	m_MaxEnemyFlag = true;
	//}
}

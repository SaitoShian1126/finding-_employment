//============================================
//
//	game.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "object3d.h"
#include "objectX.h"
#include "game.h"
#include "player.h"
#include "billboard.h"
#include "meshfield.h"
#include "sphere.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "number.h"
#include "score.h"
#include "objectbase.h"
#include "enemy.h"
#include "model.h"
#include "particle.h"
#include "boss.h"
#include "gasolene_gimmick.h"
#include "bullet.h"
#include "explosion.h"
#include "spawn.h"
#include "particle.h"
#include "camera.h"
#include "rock_gimmick.h"
#include "skybox.h"
#include "wall.h"
#include "sound.h"
#include "hp.h"
#include "fire.h"
#include "indication.h"
#include "item.h"
#include "ui.h"
#include "reticle.h"
#include "warning.h"

//============================================
// 静的メンバ変数宣言
//============================================
CMeshField *CGame::m_pMeshField = nullptr;
CScore *CGame::m_pScore = nullptr;
CGasolene_Gimmick *CGame::m_pGasoleneGimmick[MAX_GASOLENE] = {};
CModel *CGame::m_Model = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CSpawn *CGame::m_pSpawn = nullptr;
CParticle *CGame::m_pParticle[MAX_PARTICLE] = {};
CRock_gimmick *CGame::m_pRockGimmick[MAX_ROCK] = {};
CBoss *CGame::m_pBoss = nullptr;
CIndication *CGame::m_pIndication = nullptr;
CItem *CGame::m_pItem = nullptr;
CUi *CGame::m_pUi[MAX_UI] = {};

//============================================
// ゲームのコンストラクタ
//============================================
CGame::CGame()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// ゲームのデストラクタ
//============================================
CGame::~CGame()
{
	//何も書かない
}

//============================================
// ゲームの初期化処理
//============================================
HRESULT CGame::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_ParticleCreateTime = PARTICLE_TIME;
	m_ItemSpawnTime = 100;
	m_ItemGetFlag = false;
	m_BGMFlag = false;

	//============================================
	//	テクスチャ読み込み
	//============================================
	CNumber::Load();		//ナンバーテクスチャの読み込み
	CWall::Load();			//壁のテクスチャ読み込み
	CParticle::Load();		//パーティクルのテクスチャ読み込み
	CFire::Load();			//炎のテクスチャ読み込み
	CIndication::Load();	//表示のテクスチャ読み込み
	CItem::Load();			//アイテムのテクスチャ読み込み
	CUi::Load();			//UIのテクスチャ読み込み
	CReticle::Load();		//レティクルのテクスチャ読み込み
	CWarning::Load();		//Warningのテクスチャ読み込み

	//============================================
	//	オブジェクトの生成
	//============================================
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));													//メッシュフィールドの生成
	m_Model = CModel::Create();																							//モデルの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));															//プレイヤーの生成
	m_pSpawn = CSpawn::Create();																						//敵の生成
	CSkyBox::Create(D3DXVECTOR3(400.0f, 0.0f, -460.0f));																//スカイボックスの生成
	CFire::Create(D3DXVECTOR3(400.0f, 35.0f, -100.0f),D3DXVECTOR3(50.0f,75.0f,0.0f));									//炎の生成
	CFire::Create(D3DXVECTOR3(630.0f, 90.0f, -400.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f));								//炎の生成
	CFire::Create(D3DXVECTOR3(170, 20.0f, -460.0f), D3DXVECTOR3(35.0f, 55.0f, 0.0f));									//炎の生成

	//============================================
	//	UIの生成
	//============================================																							
	m_pScore = CScore::Create();																						//スコアの生成
	CHp::Create(CHp::HPTYPE_PLAYER);																					//プレイヤーの体力生成
	m_pIndication = CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE1);	//表示の生成
	m_pUi[0] = CUi::Create(D3DXVECTOR3(-750.0f, 650.0f, 0.0f), CUi::UITYPE_NUMBER);										//UIの生成
	m_pUi[1] = CUi::Create(D3DXVECTOR3(450.0f, 675.0f, 0.0f), CUi::UITYPE_BOMB);										//UIの生成

	//============================================
	//	アイテムの生成
	//============================================			
	m_pItem = CItem::Create(D3DXVECTOR3(480.0f,20.0f,-980.0f), D3DXVECTOR3(3.0f, 3.0f, 0.0f));

	//============================================
	//　ギミックの生成
	//============================================
	//ガソリン
	m_pGasoleneGimmick[0] = CGasolene_Gimmick::Create(D3DXVECTOR3(230.0f, 0.0f, -420.0f));									
	m_pGasoleneGimmick[1] = CGasolene_Gimmick::Create(D3DXVECTOR3(250.0f, 0.0f, -640.0f));
	m_pGasoleneGimmick[2] = CGasolene_Gimmick::Create(D3DXVECTOR3(510.0f, 0.0f, -800.0f));
	m_pGasoleneGimmick[3] = CGasolene_Gimmick::Create(D3DXVECTOR3(490.0f, 0.0f, -20.0f));
	//岩
	m_pRockGimmick[0] = CRock_gimmick::Create(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), CRock_gimmick::MODELTYPE_SUPPORTBAR);
	m_pRockGimmick[1] = CRock_gimmick::Create(D3DXVECTOR3(1000.0f, 120.0f, -520.0f), CRock_gimmick::MODELTYPE_ROCK);
	m_pRockGimmick[2] = CRock_gimmick::Create(D3DXVECTOR3(-90.0f, 0.0f, -975.0f), CRock_gimmick::MODELTYPE_SUPPORTBAR);
	m_pRockGimmick[3] = CRock_gimmick::Create(D3DXVECTOR3(-90.0f, 120.0f, -990), CRock_gimmick::MODELTYPE_ROCK);

	//============================================
	//　壁の生成
	//============================================
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-50.0f + 200.0f * nCnt, 40.0f, 150.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI, D3DX_PI));			//奥の内側の壁
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-50.0f + 200.0f * nCnt, 40.0f, -1050.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, D3DX_PI));			//手前の内側の壁
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(1050.0f, 40.0f, 50.0f - 200.0f * nCnt), D3DXVECTOR3(-D3DX_PI / 2, -D3DX_PI / 2, D3DX_PI));	//右の内側の壁
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-150, 40.0f, 50.0f - 200.0f * nCnt), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI, D3DX_PI / 2));		//左の内側の壁
	}

	return S_OK;
}

//============================================
// ゲームの終了処理
//============================================
void CGame::Uninit(void)
{
	//============================================
	// サウンドの停止
	//============================================
	StopSound();

	//============================================
	//	テクスチャ破棄
	//============================================
	CNumber::Unload();			//ナンバーテクスチャの破棄
	CWall::Unload();			//壁のテクスチャ破棄
	CParticle::Unload();		//パーティクルのテクスチャ破棄
	CFire::Unload();			//炎のテクスチャ破棄
	CIndication::Unload();		//表示のテクスチャ破棄
	CItem::Unload();			//アイテムのテクスチャ破棄
	CUi::Unload();				//UIのテクスチャ破棄
	CReticle::Unload();			//レティクルのテクスチャ破棄
	CWarning::Unload();			//Warningのテクスチャ破棄

	CObject::Release();
}

//============================================
// ゲームの更新処理
//============================================
void CGame::Update()
{
	//============================================
	// サウンドの再生
	//============================================
	if (m_BGMFlag == false)
	{
		PlaySound(SOUND_LABEL_SOUND);
		m_BGMFlag = true;
	}
	m_ParticleCreateTime--;
	if (m_ParticleCreateTime <= 0)
	{
		for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
		{
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(400.0f, 10.0f, -100.0f), 80, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(630.0f, 90.0f, -410.0f), 30, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(170, 10.0f, -460.0f), 40, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, D3DXVECTOR3(615.0f, 40.0f, 20.0f), PARTICLE_TIME, D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));
		}
	}
	if (m_ParticleCreateTime <= 0)
	{
		m_ParticleCreateTime = PARTICLE_TIME / 2;
	}

	/*if (m_ItemGetFlag == false && CGame::GetItem() == nullptr)
	{
		m_ItemSpawnTime--;
		if (m_ItemSpawnTime <= 0)
		{
			m_pItem = CItem::Create(D3DXVECTOR3(480.0f, 20.0f, -980.0f), D3DXVECTOR3(3.0f, 3.0f, 0.0f));
			m_ItemSpawnTime = 100;
			m_ItemGetFlag = true;
		}
	}*/
}

//============================================
// ゲームの描画処理
//============================================
void CGame::Draw()
{

}

//============================================
// プレイヤーの設定処理
//============================================
void CGame::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}

//============================================
// アイテムの設定処理
//============================================
void CGame::SetItem(CItem * item)
{
	m_pItem = item;
}

//============================================
// ゲームの生成
//============================================
CGame *CGame::Create()
{
	CGame *pgame = nullptr;

	//クラスの生成
	pgame = new CGame;				//ゲームのインスタンス生成

	//nullチェック
	if (pgame != nullptr)
	{
		//初期化処理
		pgame->Init();
	}
	else
	{
		assert(false);
	}

	return pgame;
}
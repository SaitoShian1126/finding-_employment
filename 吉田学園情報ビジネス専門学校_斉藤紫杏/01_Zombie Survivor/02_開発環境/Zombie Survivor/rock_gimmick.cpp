//============================================
//
//	rock_gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "rock_gimmick.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "spawn.h"
#include "enemy.h"
#include "score.h"
#include "input.h"
#include "application.h"
#include "particle.h"
#include "shadow.h"
#include "object2D.h"
#include "application.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"
#include "sound.h"
#include "camera.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// ギミックのコンストラクタ
//============================================
CRock_gimmick::CRock_gimmick()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PushCount = 0;
}

//============================================
// ギミックのデストラクタ
//============================================
CRock_gimmick::~CRock_gimmick()
{
	//何も書かない
}

//============================================
// ギミックの初期化処理
//============================================
HRESULT CRock_gimmick::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PushCount = 0;
	m_PushCountFlag = false;
	m_UninitFlag = false;

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/!.png",
		&m_pTexture);

	switch (m_type)
	{
	case CRock_gimmick::MODELTYPE_ROCK:
		CGimmick::SetModel("data/XMODEL/rock.x");
		break;
	case CRock_gimmick::MODELTYPE_SUPPORTBAR:
		CGimmick::SetModel("data/XMODEL/supportbar.x");
		break;
	default:
		break;
	}

	//オブジェクト基礎の初期化処理
	CGimmick::Init();

	return S_OK;
}

//============================================
// ギミックの終了処理
//============================================
void CRock_gimmick::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CGimmick::Uninit();
}

//============================================
// ギミックの更新処理
//============================================
void CRock_gimmick::Update(void)
{
	//操作処理
	Operation();

	//オブジェクト基礎の更新処理
	CGimmick::Update();
}

//============================================
// ギミックの描画処理
//============================================
void CRock_gimmick::Draw(void)
{
	//オブジェクト基礎の描画処理
	CGimmick::Draw();
}

//============================================
// 爆発した時の当たり判定
//============================================
void CRock_gimmick::HitDamage()
{
	D3DXVECTOR3 GimmickPos = CGimmick::GetPos();

	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			//敵の位置の取得
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			int EnemyLife = pEnemy->GetLife();

			if (EnemyPos.x <= GimmickPos.x + 50.0f && EnemyPos.x >= GimmickPos.x - 50.0f
				&& EnemyPos.z <= GimmickPos.z + 50.0f && EnemyPos.z >= GimmickPos.z - 50.0f)
			{
				EnemyLife = 0;
				if (EnemyLife <= 0)
				{
					CGame::GetScore()->AddScore(300);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
			}
		}
		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//============================================
// ギミック操作処理
//============================================
void CRock_gimmick::Operation()
{
	// インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();
	//カメラの情報を取得
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 GimmickPos = CGimmick::GetPos();
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPlayerPos();

	if (GimmickPos.x + 50.0f >= PlayerPos.x && GimmickPos.x - 50.0f <= PlayerPos.x
		&& PlayerPos.z <= GimmickPos.z + 50.0f && PlayerPos.z >= GimmickPos.z - 50.0f)
	{
		if (pInput->GetKeyboardTrigger(DIK_SPACE) == true
			|| pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B))
		{
			m_PushCount++;
			if (m_PushCount >= MAX_PUSH)
			{
				m_PushCountFlag = true;
			}
		}
	}

	if (m_type == MODELTYPE_ROCK)
	{
		//位置の更新
		GimmickPos += m_move;

		if (m_PushCountFlag == true)
		{
			GimmickPos.y -= 2.0f;
			if (GimmickPos.y <= 0.0f)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_ROCKGIMMICK);

				//カメラを揺らす
				pCamera->SetShakeCamera(50, 3);

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_SPLINTER, D3DXVECTOR3(GimmickPos.x, 5.0f, GimmickPos.z), PARTICLE_TIME, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
				}
				HitDamage();
				Uninit();
				return;
			}

			//移動量減衰
			GimmickPos.x += (0.0f - m_move.x) * 0.1f;
			GimmickPos.y += (0.0f - m_move.y) * 0.1f;
			GimmickPos.z += (0.0f - m_move.z) * 0.1f;
			SetPosition(GimmickPos);
		}
	}
}

//============================================
// モデルの種類の設定
//============================================
void CRock_gimmick::SetModelType(MODELTYPE type)
{
	m_type = type;
}

//============================================
// 生成
//============================================
CRock_gimmick * CRock_gimmick::Create(D3DXVECTOR3 pos, MODELTYPE type)
{
	CRock_gimmick *pRock = nullptr;

	//岩ギミックの生成
	pRock = new CRock_gimmick;				//岩ギミックのインスタンス生成

	//nullチェック
	if (pRock != nullptr)
	{
		pRock->SetModelType(type);
		//初期化処理
		pRock->Init();
		pRock->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pRock;
}

//============================================
//
//	gasolene_gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "gasolene_gimmick.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "spawn.h"
#include "enemy.h"
#include "score.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// ギミックのコンストラクタ
//============================================
CGasolene_Gimmick::CGasolene_Gimmick()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================================
// ギミックのデストラクタ
//============================================
CGasolene_Gimmick::~CGasolene_Gimmick()
{
	//何も書かない
}

//============================================
// ギミックの初期化処理
//============================================
HRESULT CGasolene_Gimmick::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	m_nLife = 1;

	//オブジェクト基礎の初期化処理
	CGimmick::Init();
	CGimmick::SetModel("data/XMODEL/gasolene.x");

	return S_OK;
}

//============================================
// ギミックの終了処理
//============================================
void CGasolene_Gimmick::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CGimmick::Uninit();
}

//============================================
// ギミックの更新処理
//============================================
void CGasolene_Gimmick::Update(void)
{
	//オブジェクト基礎の更新処理
	CGimmick::Update();
}

//============================================
// ギミックの描画処理
//============================================
void CGasolene_Gimmick::Draw(void)
{
	//オブジェクト基礎の描画処理
	CGimmick::Draw();
}

//============================================
// 爆発した時の当たり判定
//============================================
void CGasolene_Gimmick::HitDamage()
{
	CObject *pObject = GetTop(PRIORITY_LEVEL0);
	D3DXVECTOR3 GasolinePos = CGimmick::GetPos();

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			//敵の位置の取得
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			D3DXVECTOR3 EnemySize = pEnemy->GetEnemySize();
			int EnemyLife = pEnemy->GetLife();

			if (GasolinePos.x + 100.0f >= EnemyPos.x - EnemySize.x / 2 && GasolinePos.x - 100.0f <= EnemyPos.x + EnemySize.x / 2
				&& EnemyPos.z - EnemySize.z / 2 <= GasolinePos.z + 100.0f && EnemyPos.z + EnemySize.z / 2 >= GasolinePos.z - 100.0f)
			{
				EnemyLife--;
				if (EnemyLife <= 0)
				{
					CGame::GetScore()->AddScore(300);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
				else
				{
					pEnemy->SetLife(EnemyLife);
				}
			}
		}
		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//============================================
// 生成
//============================================
CGasolene_Gimmick * CGasolene_Gimmick::Create(D3DXVECTOR3 pos)
{
	CGasolene_Gimmick *pGasolene = nullptr;

	//3Dオブジェクトクラスの生成
	pGasolene = new CGasolene_Gimmick;				//3Dオブジェクトのインスタンス生成

	//nullチェック
	if (pGasolene != nullptr)
	{
		//初期化処理
		pGasolene->Init();
		pGasolene->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pGasolene;
}

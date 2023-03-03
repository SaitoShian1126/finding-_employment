//============================================
//
//	explosion.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "explosion.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion = nullptr;
D3DXVECTOR3 CExplosion::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//============================================
// 爆発のコンストラクタ
//============================================
CExplosion::CExplosion()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_nCounterAnimExplosion = 0;						//カウントアニメーションのクリア
	m_nPatternAnimExplosion = 0;						//パターンアニメーションのクリア
	m_nPatternAnimExplosionY = 0;						//Yパターンアニメーションのクリア
}

//============================================
// 爆発のデストラクタ
//============================================
CExplosion::~CExplosion()
{
}

//============================================
// 爆発の初期化処理
//============================================
HRESULT CExplosion::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_nCounterAnimExplosion = 0;						//カウントアニメーションの初期化
	m_nPatternAnimExplosion = 0;						//パターンアニメーションの初期化
	m_nPatternAnimExplosionY = 0;						//Yパターンアニメーションの初期化

	//オブジェクト基礎の初期化処理
	CObjectBase::Init();

	SetTexture("data/TEXTURE/爆発.png");
	SetTextureY(8.0f, 0.0f, 2.0f, 0.0f);

	return S_OK;
}

//============================================
// 爆発の終了処理
//============================================
void CExplosion::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CObjectBase::Uninit();
}

//============================================
// 爆発の更新処理
//============================================
void CExplosion::Update(void)
{
	//============================================
	//	爆発のアニメーション
	//============================================
	//objectbaseの更新処理関数呼び出し
	CObjectBase::Update();

	//アニメーションカウンターをインクリメント
	m_nCounterAnimExplosion++;

	if (m_nCounterAnimExplosion % 5 == 0)
	{
		//テクスチャの設定
		SetTextureY(8.0f, (float)m_nPatternAnimExplosion, 2.0f, (float)m_nPatternAnimExplosionY);

		//アニメーションパターンのインクリメン
		m_nPatternAnimExplosion++;
	}

	//アニメーションパターンが最後まで行ったら終了
	else if (m_nPatternAnimExplosion == 8.0f)
	{
		m_nPatternAnimExplosion = 0;
		m_nPatternAnimExplosionY++;
		m_nPatternAnimExplosion++;
		if (m_nPatternAnimExplosionY == 2.0f)
		{
			Uninit();	//使用されてない
			return;
		}
	}
}

//============================================
// 爆発の描画処理
//============================================
void CExplosion::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObjectBase::Draw();
}

//============================================
// 爆発の生成
//============================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pexplosion = nullptr;

	//爆発の生成
	pexplosion = new CExplosion;				//爆発のインスタンス生成

	//nullチェック
	if (pexplosion != nullptr)
	{
		//初期化処理
		pexplosion->Init();
		pexplosion->SetPosition(pos);
		pexplosion->SetSize(size);
	}
	else
	{
		assert(false);
	}
	return pexplosion;
}
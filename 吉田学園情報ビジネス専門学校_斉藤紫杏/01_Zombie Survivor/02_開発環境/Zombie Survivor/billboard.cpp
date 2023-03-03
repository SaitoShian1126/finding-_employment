//============================================
//
//	billboard.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "billboard.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// ビルボードのコンストラクタ
//============================================
CBillboard::CBillboard()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// ビルボードのデストラクタ
//============================================
CBillboard::~CBillboard()
{
}
//============================================
// ビルボードの初期化処理
//============================================
HRESULT CBillboard::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//オブジェクト基礎の初期化処理
	CObjectBase::Init();

	//ビルボードのテクスチャの設定
	SetTexture("data/TEXTURE/レティクル.png");

	return S_OK;
}

//============================================
// ビルボードの終了処理
//============================================
void CBillboard::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CObjectBase::Uninit();
}

//============================================
// ビルボードの更新処理
//============================================
void CBillboard::Update(void)
{
	//位置の設定
	SetPosition(m_pos);
}

//============================================
// ビルボードの描画処理
//============================================
void CBillboard::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObjectBase::Draw();
}

//============================================
// ビルボードの生成
//============================================
CBillboard * CBillboard::Create()
{
	CBillboard *pBillboard = nullptr;

	//ビルボードの生成
	pBillboard = new CBillboard;		//ビルボードのインスタンス生成

	//nullチェック
	if (pBillboard != nullptr)
	{
		pBillboard->Init();				//初期化処理
	}
	else
	{
		assert(false);
	}

	return pBillboard;
}
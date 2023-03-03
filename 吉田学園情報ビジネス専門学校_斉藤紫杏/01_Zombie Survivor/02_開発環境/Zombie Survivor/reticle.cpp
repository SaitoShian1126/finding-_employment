//============================================
//
//	reticle.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "reticle.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CReticle::m_pTexture = nullptr;

//============================================
// レティクルのコンストラクタ
//============================================
CReticle::CReticle() : CObject2D(PRIORITY_LEVEL5)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//色のクリア
}

//============================================
// レティクルのデストラクタ
//============================================
CReticle::~CReticle()
{
	//何も書かない
}

//============================================
// レティクルの初期化処理
//============================================
HRESULT CReticle::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//色の初期化

	//テクスチャの反映
	BindTexture(m_pTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//============================================
// レティクルの終了処理
//============================================
void CReticle::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//============================================
// レティクルの更新処理
//============================================
void CReticle::Update()
{

}

//============================================
// レティクルの描画処理
//============================================
void CReticle::Draw()
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//============================================
// レティクルの生成
//============================================
CReticle *CReticle::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size)
{
	CReticle *pReticle = nullptr;

	//クラスの生成
	pReticle = new CReticle;				//レティクルのインスタンス生成

	//nullチェック
	if (pReticle != nullptr)
	{
		pReticle->Init();					//初期化処理
		pReticle->SetPosition(pos);			//位置の設定
		pReticle->SetSize(size);			//サイズの設定
	}
	else
	{
		assert(false);
	}

	return pReticle;
}

//============================================
// テクスチャの読み込み
//============================================
HRESULT CReticle::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/レティクル.png",
		&m_pTexture);
	return S_OK;
}

//============================================
// テクスチャの破棄
//============================================
void CReticle::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
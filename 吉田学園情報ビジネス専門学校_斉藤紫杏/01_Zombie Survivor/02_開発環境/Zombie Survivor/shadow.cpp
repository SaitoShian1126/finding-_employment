//============================================
//
//	shadow.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "objectX.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "shadow.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// 影のコンストラクタ
//============================================
CShadow::CShadow()
{
	//============================================
	//メンバ変数のクリア
	//============================================ 
}

//============================================
// 影のデストラクタ
//============================================
CShadow::~CShadow()
{
}

//============================================
// 影の初期化処理
//============================================
HRESULT CShadow::Init(void)
{
	CObject3D::Init();

	//============================================
	//メンバ変数の初期化
	//============================================

	//テクスチャの使用をfalseにする
	m_Texture = false;
	//テクスチャの設定
	SetTexture("data/TEXTURE/shadow000.jpg");

	return S_OK;
}

//============================================
// 影の終了処理
//============================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//============================================
// 影の更新処理
//============================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//============================================
// 影の描画処理
//============================================
void CShadow::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	//減算合成の設定
	//============================================
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//============================================
	//減算合成を元に戻す
	//============================================
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================
// 影のテクスチャの設定
//============================================
CShadow * CShadow::SetTexture(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureShadow);

	BindTexture(m_pTextureShadow);

	m_Texture = true;

	return S_OK;
}

//============================================
// 影の生成
//============================================
CShadow * CShadow::Create(const D3DXVECTOR3 & pos)
{
	CShadow *pShadow = nullptr;

	//3Dオブジェクトクラスの生成
	pShadow = new CShadow;				//3Dオブジェクトのインスタンス生成

	//nullチェック
	if (pShadow != nullptr)
	{
		//初期化処理
		pShadow->Init();
		//設定処理
		pShadow->SetPosition(pos);
		pShadow->SetSize(D3DXVECTOR3(100.0f, 1.0f, 100.0f));
	}
	else
	{
		assert(false);
	}
	return pShadow;
}

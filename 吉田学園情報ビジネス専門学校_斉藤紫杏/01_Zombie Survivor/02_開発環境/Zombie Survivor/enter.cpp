//============================================
//
//	enter.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "enter.h"
#include "application.h"
#include "renderer.h"
#include "explosion.h"
#include "fade.h"
#include "input.h"
#include "player.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CEnter::m_pTextureenter = {};

//============================================
// enterのコンストラクタ
//============================================
CEnter::CEnter() : CObject2D(4)
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// enterのデストラクタ
//============================================
CEnter::~CEnter()
{
	//何も書かない
}

//============================================
// enterの初期化処理
//============================================
HRESULT CEnter::Init(void)
{
	CObject2D::Init();

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PRESS ENTER1.png",
		&m_pTextureenter);

	//============================================
	//メンバ変数の初期化
	//============================================
	m_nCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nType = TYPE_IN;
	m_nCount = 50;

	BindTexture(m_pTextureenter);
	return S_OK;
}

//============================================
// enterの終了処理
//============================================
void CEnter::Uninit(void)
{
	CObject2D::Uninit();
}

//============================================
// enterの更新処理
//============================================
void CEnter::Update()
{
	m_nCount--;
	if (m_nType == TYPE_IN && m_nCount <= 0)
	{
		m_nCol.a = 0.0f;
		m_nType = TYPE_OUT; 
		m_nCount = 50;
	}
	else if (m_nType == TYPE_OUT && m_nCount <= 0)
	{
		m_nCol.a = 1.0f;
		m_nType = TYPE_IN;
		m_nCount = 50;
	}
	SetColor(m_nCol.r, m_nCol.g, m_nCol.b, m_nCol.a);
}

//============================================
// enterの描画処理
//============================================
void CEnter::Draw()
{
	CObject2D::Draw();
}

//============================================
// スポーンの生成
//============================================
CEnter *CEnter::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size)
{
	CEnter *penter = nullptr;

	//クラスの生成
	penter = new CEnter;				//2Dオブジェクトのインスタンス生成

								//nullチェック
	if (penter != nullptr)
	{
		//初期化処理
		penter->Init();
		//設定処理
		penter->SetPosition(pos);
		penter->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return penter;
}

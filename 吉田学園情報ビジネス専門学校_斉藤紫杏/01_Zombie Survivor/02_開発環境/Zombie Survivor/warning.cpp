//============================================
//
//	warning.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "warning.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CWarning::m_pTexture[MAX_TEXTURE] = {};

//============================================
// Warningのコンストラクタ
//============================================
CWarning::CWarning() : CObject2D(PRIORITY_LEVEL5)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//色のクリア
}

//============================================
// Warningのデストラクタ
//============================================
CWarning::~CWarning()
{
	//何も書かない
}

//============================================
// Warningの初期化処理
//============================================
HRESULT CWarning::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//色の初期化
	m_nUninitTimer = RELEASE_TIME;					//破棄するまでの時間の初期化
	m_flag = false;									//フラグの初期化

	//============================================
	// Warningの種類
	//============================================
	switch (m_type)
	{
	case CWarning::WARNINGTYPE_UI:
		BindTexture(m_pTexture[0]);
		break;
	case CWarning::WARNINGTYPE_SCREEN:
		BindTexture(m_pTexture[1]);
		break;
	case CWarning::WARNINGTYPE_MAX:
		break;
	default:
		break;
	}

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//============================================
// Warningの終了処理
//============================================
void CWarning::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//============================================
// Warningの更新処理
//============================================
void CWarning::Update()
{
	//============================================
	// ボス出現のWarning
	//============================================
	if (m_type == WARNINGTYPE_UI)
	{
		m_nUninitTimer--;
		if (m_flag == false)
		{
			m_col.a += 0.001f;
		}

		if (m_col.a >= 1.0f)
		{
			m_flag = true;
		}
		if (m_flag == true)
		{
			m_col.a -= 0.001f;
			if (m_col.a <= 0.5f)
			{
				m_flag = false;
			}
		}
		if (m_nUninitTimer <= 0)
		{
			Uninit();
			return;
		}

		//色の設定
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}

	if (m_type == WARNINGTYPE_SCREEN)
	{
		m_nUninitTimer--;
		if (m_flag == false)
		{
			m_col.a += 0.025f;
		}

		if (m_col.a >= 0.5f)
		{
			m_flag = true;
		}
		if (m_flag == true)
		{
			m_col.a -= 0.025f;
			if (m_col.a <= 0.0f)
			{
				m_flag = false;
			}
		}
		if (m_nUninitTimer <= 0)
		{
			Uninit();
			return;
		}

		//色の設定
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}
}

//============================================
// Warningの描画処理
//============================================
void CWarning::Draw()
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//============================================
// Warningの生成
//============================================
CWarning *CWarning::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, WARNINGTYPE type)
{
	CWarning *pwarning = nullptr;

	//クラスの生成
	pwarning = new CWarning;				//Warningのインスタンス生成

	//nullチェック
	if (pwarning != nullptr)
	{
		pwarning->SetWarningType(type);		//Warningの種類の設定処理
		pwarning->Init();					//初期化処理
		pwarning->SetPosition(pos);			//位置の設定
		pwarning->SetSize(size);			//サイズの設定
	}
	else
	{
		assert(false);
	}

	return pwarning;
}

//============================================
// テクスチャの読み込み
//============================================
HRESULT CWarning::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/warning.png",
		&m_pTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/警告1.png",
		&m_pTexture[1]);

	return S_OK;
}

//============================================
// テクスチャの破棄
//============================================
void CWarning::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//============================================
// Warningの設定
//============================================
void CWarning::SetWarningType(WARNINGTYPE type)
{
	m_type = type;
}
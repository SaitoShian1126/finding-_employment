//============================================
//
//	indication.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "indication.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CIndication::m_pTexture[MAX_TEXTURE] = {};

//============================================
// 表示のコンストラクタ
//============================================
CIndication::CIndication() : CObject2D(PRIORITY_LEVEL4)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//色のクリア
	m_nUninitTimer = 0;								//破棄するまでの時間のクリア
	m_flag = false;									//フラグのクリア
	m_ColorFlag = false;							//色のフラグのクリア
	m_BloodFlag = false;							//血のフラグのクリア
}

//============================================
// 表示のデストラクタ
//============================================
CIndication::~CIndication()
{
	//何も書かない
}

//============================================
// 表示の初期化処理
//============================================
HRESULT CIndication::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//色の初期化
	m_nUninitTimer = RELEASE_TIME;					//破棄するまでの時間の初期化
	m_flag = false;									//フラグの初期化
	m_ColorFlag = false;							//色のフラグの初期化
	m_BloodFlag = false;							//血のフラグの初期化

	//============================================
	// 表示の種類
	//============================================
	switch (m_nType)
	{
	case INDICATIONTYPE_WAVE1:
		//テクスチャ反映
		BindTexture(m_pTexture[0]);		//wave1のテクスチャ
		break;
	case INDICATIONTYPE_WAVE2:
		//テクスチャ反映
		BindTexture(m_pTexture[1]);		//wave2のテクスチャ
		break;
	case INDICATIONTYPE_BLOOD:
		//テクスチャ反映
		BindTexture(m_pTexture[2]);		//血のテクスチャ
		break;
	default:
		break;
	}

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	return S_OK;
}

//============================================
// 表示の終了処理
//============================================
void CIndication::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//============================================
// 表示の更新処理
//============================================
void CIndication::Update()
{
	//ジョイパッドのインスタンス
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	//============================================
	// wave1とwave2の表示
	//============================================
	if (m_nType == INDICATIONTYPE_WAVE1 || m_nType == INDICATIONTYPE_WAVE2)
	{
		if (m_flag == false)
		{
			m_col.a += 0.01f;
		}

		if (m_col.a >= 1.0f)
		{
			m_flag = true;
			m_nUninitTimer--;
		}
		if (m_nUninitTimer <= 0 && m_flag == true)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				Uninit();
				return;
			}
		}

		//色の設定
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}

	//============================================
	// 血の表示
	//============================================
	if (m_nType == INDICATIONTYPE_BLOOD)
	{
		if (m_ColorFlag == false)
		{
			m_col.a = 1.0f;
			m_ColorFlag = true;
		}
		m_nUninitTimer--;
		if (m_nUninitTimer <= 0 && m_ColorFlag == true)
		{
			m_col.a -= 0.005f;
			if (m_col.a <= 0.0f)
			{
				Uninit();
				return;
			}
		}
		//色の設定
		SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));
	}
}

//============================================
// 表示の描画処理
//============================================
void CIndication::Draw()
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//============================================
// 表示の生成
//============================================
CIndication *CIndication::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, INDICATIONTYPE type)
{
	CIndication *pIndication = nullptr;

	//クラスの生成
	pIndication = new CIndication;				//表示のインスタンス生成

	//nullチェック
	if (pIndication != nullptr)
	{
		pIndication->SetIndicationType(type);	//表示の種類の設定処理
		pIndication->Init();					//初期化処理
		pIndication->SetPosition(pos);			//位置の設定
		pIndication->SetSize(size);				//サイズの設定
	}
	else
	{
		assert(false);
	}

	return pIndication;
}

//============================================
// テクスチャの読み込み
//============================================
HRESULT CIndication::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wave1.png",
		&m_pTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wave2.png",
		&m_pTexture[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/blood.png",
		&m_pTexture[2]);

	return S_OK;
}

//============================================
// テクスチャの破棄
//============================================
void CIndication::Unload(void)
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
// 表示の設定
//============================================
void CIndication::SetIndicationType(INDICATIONTYPE type)
{
	m_nType = type;
}
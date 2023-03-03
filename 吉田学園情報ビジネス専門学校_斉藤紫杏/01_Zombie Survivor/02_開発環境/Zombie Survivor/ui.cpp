//============================================
//
//	ui.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "ui.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture = nullptr;

//============================================
// 表示のコンストラクタ
//============================================
CUi::CUi() : CObject2D(PRIORITY_LEVEL3)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_nUninitTimer = 100;
	m_flag = false;
	m_ColorFlag = false;
	m_BloodFlag = false;
}

//============================================
// 表示のデストラクタ
//============================================
CUi::~CUi()
{
	//何も書かない
}

//============================================
// 表示の初期化処理
//============================================
HRESULT CUi::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_size = D3DXVECTOR3(55.0f, 35.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nUninitTimer = 100;
	m_Bomb = 3;
	m_flag = false;
	m_ColorFlag = false;
	m_BloodFlag = false;
	m_apNumber = nullptr;

	switch (m_type)
	{
	case CUi::UITYPE_NUMBER:
		m_apNumber = CNumber::Create(D3DXVECTOR3(570.0f, 670.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CNumber::NUMBERTYPE_BOMB);		//ナンバーの生成
		break;
	case CUi::UITYPE_BOMB:
		BindTexture(m_pTexture);
		break;
	case CUi::UITYPE_MAX:
		break;
	default:
		break;
	}
	
	//オブジェクト2Dの初期化処理
	CObject2D::Init();
	SetSize(m_size);

	return S_OK;
}

//============================================
// 表示の終了処理
//============================================
void CUi::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//============================================
// 表示の更新処理
//============================================
void CUi::Update()
{

}

//============================================
// 表示の描画処理
//============================================
void CUi::Draw()
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//============================================
// スポーンの生成
//============================================
CUi *CUi::Create(const D3DXVECTOR3 &pos, UITYPE type)
{
	CUi *pScene = nullptr;

	//クラスの生成
	pScene = new CUi;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pScene != nullptr)
	{
		pScene->SetUiType(type);
		//初期化処理
		pScene->Init();
		//設定処理
		pScene->SetPosition(pos);
	}
	else
	{
		assert(false);
	}

	return pScene;
}

//============================================
// テクスチャの読み込み
//============================================
HRESULT CUi::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/爆弾1.png",
		&m_pTexture);

	return S_OK;
}

//============================================
// テクスチャの破棄
//============================================
void CUi::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//============================================
// 残りの爆弾の設定
//============================================
void CUi::SetBomb(int bomb)
{
	int aPosTexU = m_Bomb;	//各桁の爆弾の数を格納
	m_Bomb = bomb;

	aPosTexU = m_Bomb % 10 / 1;

	//分割数,何番目か
	m_apNumber->SetTexture(10.0f, (float)aPosTexU, 1.0f, 0.0f);
}

//============================================
// 爆弾の数の加算処理
//============================================
void CUi::AddBomb(int nValue)
{
	//メンバ変数にスコアを加算
	SetBomb(m_Bomb + nValue);
}

//============================================
// 爆弾の数の減算処理
//============================================
void CUi::SubBomb(int nSubtract)
{
	//メンバ変数にスコアを減算
	SetBomb(m_Bomb - nSubtract);
}

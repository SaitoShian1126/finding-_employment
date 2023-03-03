//============================================
//
//	number.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "number.h"
#include "application.h"
#include "renderer.h" 

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CNumber::m_pTextureNumber = nullptr;

//============================================
// 数字のコンストラクタ
//============================================
CNumber::CNumber() : CObject2D(4)
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// 数字のデストラクタ
//============================================
CNumber::~CNumber()
{
	//何も書かない
}

//============================================
// 数字の初期化処理
//============================================
HRESULT CNumber::Init(void)
{
	CObject2D::Init();

	//============================================
	//メンバ変数の初期化
	//============================================

	switch (m_type)
	{
	case CNumber::NUMBERTYPE_SCORE:
		SetTexture(10.0f, 0.0f, 1.0f, 0.0f);
		BindTexture(m_pTextureNumber);
		break;
	case CNumber::NUMBERTYPE_BOMB:
		SetTexture(10.0f, 3.0f, 1.0f, 0.0f);
		BindTexture(m_pTextureNumber);
		break;
	case CNumber::NUMBERTYPE_MAX:
		break;
	default:
		break;
	}

	return S_OK;
}

//============================================
// 数字の終了処理
//============================================
void CNumber::Uninit(void)
{
	CObject2D::Uninit();
}

//============================================
// 数字の更新処理
//============================================
void CNumber::Update()
{
	D3DXVECTOR3 NumberPos = GetPos();

	//位置の設定
	SetPosition(NumberPos);
	CObject2D::Update();
}

//============================================
// 数字の描画処理
//============================================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//============================================
// 数字の生成
//============================================
CNumber *CNumber::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, NUMBERTYPE type)
{
	CNumber *pNumber = nullptr;

	//クラスの生成
	pNumber = new CNumber;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pNumber != nullptr)
	{
		pNumber->SetType(type);
		//初期化処理
		pNumber->Init();
		//設定処理
		pNumber->SetPosition(pos);
		pNumber->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pNumber;
}

//============================================
// テクスチャの読み込み
//============================================
HRESULT CNumber::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number.png",
		&m_pTextureNumber);

	return S_OK;
}

//============================================
// テクスチャの破棄
//============================================
void CNumber::Unload(void)
{
	//テクスチャの破棄
	if (m_pTextureNumber != nullptr)
	{
		m_pTextureNumber->Release();
		m_pTextureNumber = nullptr;
	}
}

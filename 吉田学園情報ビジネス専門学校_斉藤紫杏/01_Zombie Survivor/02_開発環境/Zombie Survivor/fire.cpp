//============================================
//
//	fire.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "fire.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CFire::m_pTexturefire = nullptr;
D3DXVECTOR3 CFire::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//============================================
// 炎のコンストラクタ
//============================================
CFire::CFire()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_nCounterAnimfire = 0;						//カウントアニメーションのクリア
	m_nPatternAnimfire = 0;						//パターンアニメーションのクリア
	m_nPatternAnimfireY = 0;					//Yパターンアニメーションのクリア
}

//============================================
// 炎のデストラクタ
//============================================
CFire::~CFire()
{
}

//============================================
// 炎の初期化処理
//============================================
HRESULT CFire::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_nCounterAnimfire = 0;						//カウントアニメーションの初期化
	m_nPatternAnimfire = 0;						//パターンアニメーションの初期化
	m_nPatternAnimfireY = 0;					//Yパターンアニメーションの初期化

	//オブジェクト基礎の初期化処理
	CObjectBase::Init();

	BindTexture(m_pTexturefire);
	SetTextureY(5.0f, 0.0f, 4.0f, 0.0f);

	return S_OK;
}

//============================================
// 炎の終了処理
//============================================
void CFire::Uninit(void)
{
	if (m_pTexturefire != nullptr)
	{
		//オブジェクト基礎の終了処理
		CObjectBase::Uninit();
	}
}

//============================================
// 炎の更新処理
//============================================
void CFire::Update(void)
{
	//============================================
	//	炎のアニメーション
	//============================================
	//objectbaseの更新処理関数呼び出し
	CObjectBase::Update();

	//アニメーションカウンターをインクリメント
	m_nCounterAnimfire++;

	if (m_nCounterAnimfire % 10 == 0)
	{
		//テクスチャの設定
		SetTextureY(5.0f, (float)m_nPatternAnimfire, 4.0f, (float)m_nPatternAnimfireY);

		//アニメーションパターンのインクリメン
		m_nPatternAnimfire++;
	}

	//アニメーションパターンが最後まで行ったらループ
	else if (m_nPatternAnimfire == 5.0f)
	{
		m_nPatternAnimfire = 0;
		m_nPatternAnimfireY++;
		m_nPatternAnimfire++;
		if (m_nPatternAnimfireY == 4.0f)
		{
			m_nPatternAnimfireY = 0.0f;
		}
	}
}

//============================================
// 炎の描画処理
//============================================
void CFire::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObjectBase::Draw();
}

//============================================
// 炎のテクスチャ読み込み
//============================================
HRESULT CFire::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/炎.png",
		&m_pTexturefire);

	return S_OK;
}

//============================================
// 炎のテクスチャ破棄
//============================================
void CFire::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexturefire != nullptr)
	{
		m_pTexturefire->Release();
		m_pTexturefire = nullptr;
	}
}

//============================================
// 炎の生成
//============================================
CFire * CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFire *pfire = nullptr;

	//炎の生成
	pfire = new CFire;				//炎のインスタンス生成

	//nullチェック
	if (pfire != nullptr)
	{
		//初期化処理
		pfire->Init();
		pfire->SetPosition(pos);
		pfire->SetSize(size);
	}
	else
	{
		assert(false);
	}
	return pfire;
}
//============================================
//
//	application.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"
#include "input.h"
#include "debug.h"
#include "player.h"
#include "tutorial.h"

//============================================
// 静的メンバ変数宣言
//============================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInput = nullptr;
CJoyPad *CApplication::m_pJoyPad = nullptr;
CMode *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CDebugProc *CApplication::m_pDebug = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//============================================
// アプリケーションのコンストラクタ
//============================================
CApplication::CApplication()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pRenderer = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//アプリケーションのデストラクタ
CApplication::~CApplication()
{
	//何も書かない
}

//アプリケーションの初期化処理
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_pRenderer = nullptr;
	m_pInput = nullptr;
	m_pJoyPad = nullptr;
	m_pMode = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pDebug = nullptr;
	m_mode = MODE_TITLE;

	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	//カメラクラスの生成
	m_pCamera = new CCamera;
	//ライトクラスの生成
	m_pLight = new CLight;
	//インプットのインスタンス生成
	m_pInput = new CInput;
	//ジョイパッドのインスタンス生成
	m_pJoyPad = new CJoyPad;
	//デバッグ表示のインスタンス生成
	m_pDebug = new CDebugProc;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//キーボードの初期化処理
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pCamera->Init();
	m_pLight->Init();
	m_pDebug->Init();

	CFade::Create(MODE_GAME);

	return S_OK;
}

//============================================
// アプリケーションの終了処理
//============================================
void CApplication::Uninit(void)
{
	//キーボードの破棄
	if (m_pInput != nullptr)
	{
		//キーボードの終了処理
		m_pInput->Uninit();

		delete m_pInput;
		m_pInput = nullptr;
	}

	//ジョイパッドの破棄
	if (m_pJoyPad != nullptr)
	{
		//ジョイパッドの終了処理
		m_pJoyPad->Uninit();

		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//レンダリングの破棄
	if (m_pRenderer != nullptr)
	{
		//レンダリングの終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//カメラの破棄
	if (m_pCamera != nullptr)
	{
		//カメラの終了処理
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//デバッグ表示の破棄
	if (m_pDebug != nullptr)
	{
		//デバッグ表示の終了処理
		m_pDebug->Uninit();

		delete m_pDebug;
		m_pDebug = nullptr;
	}
	//オブジェクトの破棄処理
	CObject::ReleaseAll();
}

//============================================
// アプリケーションの更新処理
//============================================
void CApplication::Update(void)
{
	//============================================
	//	更新処理
	//============================================
	if (m_pInput != nullptr)
	{
		//キーボードの更新処理
		m_pInput->Update();
	}

	if (m_pJoyPad != nullptr)
	{
		//ジョイパッドの更新処理
		m_pJoyPad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//レンダリングの更新処理
		m_pRenderer->Update();
	}

	if (m_pCamera != nullptr)
	{
		//モードの更新処理
		m_pCamera->Update();
	}

	if (m_pMode != nullptr)
	{
		//モードの更新処理
		m_pMode->Update();
	}
}

//============================================
// アプリケーションの描画処理
//============================================
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダリングの描画処理
		m_pRenderer->Draw();
	}
}

//============================================
// レンダリングのインスタンス取得処理
//============================================
CRenderer *CApplication::GetRenderer (void)
{
	return m_pRenderer;
}

//============================================
// モードの設定処理
//============================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}
	
	CObject::ModeRelease();

	m_mode = mode;

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case CApplication::MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;
	case CApplication::MODE_GAME:
		m_pMode = CGame::Create();
		break;
	case CApplication::MODE_RESULT:
		m_pMode = CResult::Create();
		break;
	case CApplication::MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
		break;
	case CApplication::MODE_MAX:
		break;
	default:
		break;
	}
}



//============================================
//
//	renderer.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "object3D.h"
#include "object.h"
#include "application.h"
#include "debug.h"
#include "input.h"

//============================================
// レンダリングのコンストラクタ
//============================================
CRenderer::CRenderer()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pD3D = nullptr;						//Direct3Dオブジェクトをクリア
	m_pD3DDevice = nullptr;					//Deviceオブジェクトをクリア
}

//============================================
// レンダリングのデストラクタ
//============================================
CRenderer::~CRenderer()
{
	//何も書かない
}

//============================================
// レンダリングの初期化処理
//============================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pD3DDevice = nullptr;					//Deviceオブジェクトを初期化

	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// 生成失敗
		return E_FAIL;
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//フォグの有効設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//フォグカラー
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//フォグのモード(範囲指定:D3DFOG_LINEAR,密度指定:D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);

	////範囲指定(※LINEAR時に指定)
	//int fFogStartPos = 100;
	//int fFogEndPos = 1000;
	//m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	//m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	//密度指定(※EXP時に指定)
	float fFogDensity = 0.001f;
	m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//============================================
// レンダリングの終了処理
//============================================
void CRenderer::Uninit(void)
{
	CObject3D::ReleaseAll();

	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//============================================
// レンダリングの更新処理
//============================================
void CRenderer::Update(void)
{
	// インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();

	//============================================
	//	ワイヤーフレーム
	//============================================
	//F1キーでワイヤーフレームを表示
	if (pInput->GetKeyboardPress(DIK_F1) == true)
	{//F1キーが押された
	 //ワイヤーフレームモードの設定
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	//F1キーを放したらワイヤーフレーム非表示
	else if (pInput->GetKeyboardPress(DIK_F1) == false)
	{
		//ワイヤーフレームモードの設定
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
	}

	//すべての更新処理
	CObject3D::UpdateAll();
}

//============================================
// レンダリングの描画処理
//============================================
void CRenderer::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	CApplication::GetCamera()->SetCamera();

	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),	//画面クリア時の色(背景色)
		1.0f,
		0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開示が成功した場合

		//すべての描画処理
		CObject3D::DrawAll();

#ifdef _DEBUG

		//デバッグ表示
		CDebugProc::Draw();

#endif // _DEBUG

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//============================================
// デバイスの取得処理
//============================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
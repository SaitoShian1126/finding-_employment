//============================================
//
//	line.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "line.h"

//============================================
// 静的メンバ変数宣言
//============================================
D3DXVECTOR3 CLine::m_start = {};
D3DXVECTOR3 CLine::m_end = {};

//============================================
// ライン表示のコンストラクタ
//============================================
CLine::CLine()
{
	//============================================
	// メンバ変数のクリア
	//============================================
	m_pVtxBuffLine = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		m_aLine[nCnt] = nullptr;
	}
}

//============================================
// ライン表示のデストラクタ
//============================================
CLine::~CLine()
{
	//何も書かない
}

//============================================
// ライン表示の初期化処理
//============================================
HRESULT CLine::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_pVtxBuffLine = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_mtxWorld = {};
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		m_aLine[nCnt] = nullptr;
	}

	return S_OK;
}

//============================================
// ライン表示の終了処理
//============================================
void CLine::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffLine != NULL)
	{
		m_pVtxBuffLine->Release();
		m_pVtxBuffLine = NULL;
	}
}

//============================================
// ライン表示の更新処理
//============================================
void CLine::Update(void)
{
}

//============================================
// ライン表示の描画処理
//============================================
void CLine::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;					//計算用マトリックス

	//ライトを無効化にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワルドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワルドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffLine, 0, sizeof(VERTEX_LINE));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_LINE);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================
// ライン表示の位置設定
//============================================
void CLine::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// ライン表示の生成処理
//============================================
CLine *CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	CLine *pLine = nullptr;

	//プレイヤークラスの生成
	pLine = new CLine;				//3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pLine != nullptr)
	{
		// 初期化処理
		pLine->Init();
		pLine->SetPosition(pos);
		pLine->m_rot = rot;
		pLine->m_start = start;
		pLine->m_end = end;
		pLine->SetLine();
	}
	else
	{
		assert(false);
	}
	return pLine;
}

//============================================
// ライン表示の頂点座標設定
//============================================
void CLine::SetLine(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_LINE) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_LINE,
		D3DPOOL_MANAGED,
		&m_pVtxBuffLine,
		NULL);

	//頂点情報へのポインタ
	VERTEX_LINE*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_end;

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	//頂点バッファのアンロック
	m_pVtxBuffLine->Unlock();
}

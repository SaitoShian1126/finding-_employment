//============================================
//
//	wall.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "wall.h"
#include "player.h"
#include "game.h"
#include "mode.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CWall::m_pTexture = nullptr;

//============================================
// コンストラクタ
//============================================
CWall::CWall()
{
}

//============================================
// デストラクタ
//============================================
CWall::~CWall()
{
}

//============================================
// 初期化
//============================================
HRESULT CWall::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	// メンバ変数の初期化
	//============================================
	m_size = D3DXVECTOR3(100.0f,0.0f,40.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, -m_size.z);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// 終了
//============================================
void CWall::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//破棄処理
	Release();
}

//============================================
// 更新
//============================================
void CWall::Update()
{

}

//============================================
// 描画
//============================================
void CWall::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);										//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);				//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);	//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);					//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);						//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//============================================
// 位置の設定処理
//============================================
void CWall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// 移動の設定処理
//============================================
void CWall::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// サイズの設定処理
//============================================
void CWall::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// 向きの設定処理
//============================================
void CWall::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// テクスチャ反映
//============================================
void CWall::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//============================================
// 生成
//============================================
CWall *CWall::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 rot)
{
	CWall *pWall;
	pWall = new CWall;

	if (pWall != nullptr)
	{
		pWall->Init();
		pWall->SetPosition(pos);
		pWall->SetRot(rot);
	}
	else
	{
		assert(false);
	}

	return pWall;
}

//============================================
//テクスチャ読み込み
//============================================
HRESULT CWall::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall.jpg",
		&m_pTexture);

	return S_OK;
}

//============================================
//テクスチャ破棄
//============================================
void CWall::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}


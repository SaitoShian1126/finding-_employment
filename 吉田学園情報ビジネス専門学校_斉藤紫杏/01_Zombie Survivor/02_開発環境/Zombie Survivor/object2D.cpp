//============================================
//
//	object2D.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "object2D.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"

//============================================
// オブジェクトのコンストラクタ
//============================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pVtxBuff = nullptr;						//バッファのクリア
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//位置のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動のクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転のクリア
	m_fWidth = 0.0f;							//幅のクリア
	m_fHeight = 0.0f;							//高さのクリア
	m_fLength = 0;								//拡大縮小のスケールのクリア
	m_fAngle = 0;								//角度のクリア
	m_nTimer = 0;								//時間のクリア
}

//============================================
// オブジェクトのデストラクタ
//============================================
CObject2D::~CObject2D()
{
	//何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CObject2D::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pVtxBuff = nullptr;														//バッファの初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//位置の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//移動の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//回転の初期化
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);									//色の初期化
	m_size = D3DXVECTOR3(50.0f, 50.0f,0.0f);									//サイズ
	m_fWidth = 25.0f;															//幅の初期化
	m_fHeight = 25.0f;															//高さの初期化
	m_fLength = sqrtf(((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_fWidth, m_fHeight);										//角度の初期化
	m_nTimer = 0;																//時間の初期化

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ddd",
		&m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CObject2D::Update(void)
{

}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CObject2D::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,											//頂点情報の先頭アドレス
		2);											//プリミティブの数

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//============================================
// ポリゴンの設定処理
//============================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	m_pos = pos;

	//頂点バッファをロックし、頂点情報へのポインタを取得
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の更新
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================
// ポリゴンの移動
//============================================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// ポリゴンのサイズの設定処理
//============================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	m_size = size;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の更新
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================
// ポリゴンの色の設定処理
//============================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================
//	回転の設定
//============================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================
// 長さの設定
//============================================
void CObject2D::SetLength(float length)
{
	m_fLength = length;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================
// 生成
//============================================
CObject2D *CObject2D::Create(const D3DXVECTOR3 &pos)
{
	CObject2D *pObject2D = nullptr;

	//2Dオブジェクトクラスの生成
	pObject2D = new CObject2D;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pObject2D != nullptr)
	{
		//初期化処理
		pObject2D->Init();
		//設定処理
		pObject2D->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pObject2D;
}

//============================================
// テクスチャ反映
//============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//============================================
// 縦テクスチャ画像の設定
//============================================
void CObject2D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//頂点座標へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//============================================
// 色の設定
//============================================
void CObject2D::SetColor(float Red, float Green, float Blue, float α)
{
	VERTEX_2D*pVtx;				//頂点情報へのポインタ

	m_col = D3DXCOLOR(Red, Green, Blue, α);

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(Red,Green,Blue,α);
	pVtx[1].col = D3DXCOLOR(Red,Green,Blue,α);
	pVtx[2].col = D3DXCOLOR(Red,Green,Blue,α);
	pVtx[3].col = D3DXCOLOR(Red,Green,Blue,α);

	//頂点バッファをアンロックする
	Buffer->Unlock();
}

//============================================
//
//	object3D.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "object3d.h"
#include "renderer.h"
#include "object.h"
#include "application.h"

//============================================
// オブジェクトのコンストラクタ
//============================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pVtxBuffMeshPolygon = nullptr;			//バッファのクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動のクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転のクリア
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色のクリア
	m_fWidth = 0.0f;							//幅のクリア
	m_fHeight = 0.0f;							//高さのクリア
	m_fLength = 0;								//拡大縮小のスケールのクリア
	m_fAngle = 0;								//角度のクリア
	m_nTimer = 0;								//時間のクリア
}

//============================================
// オブジェクトのデストラクタ
//============================================
CObject3D::~CObject3D()
{
	//何も書かない
}
//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CObject3D::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pVtxBuffMeshPolygon = nullptr;											//バッファの初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//位置の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//移動の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//回転の初期化
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);									//色の初期化
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//サイズ
	m_fWidth = 25.0f;															//幅の初期化
	m_fHeight = 25.0f;															//高さの初期化
	m_fLength = sqrtf(((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_fWidth, m_fHeight);										//角度の初期化
	m_nTimer = 0;																//時間の初期化

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの使用をfalseにする
	m_Texture = false;
	//テクスチャの設定
	SetTexture("data/TEXTURE/field001.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMeshPolygon,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffMeshPolygon->Unlock();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffMeshPolygon != NULL)
	{
		m_pVtxBuffMeshPolygon->Release();
		m_pVtxBuffMeshPolygon = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuffMeshPolygon != NULL)
	{	
		m_pIdxBuffMeshPolygon->Release();
		m_pIdxBuffMeshPolygon = NULL;
	}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CObject3D::Update(void)
{
	SetPosition(m_pos);
	SetSize(m_size);
}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CObject3D::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshPolygon);										//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);				//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorldMeshPolygon, &m_mtxWorldMeshPolygon, &mtxRot);	//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);					//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorldMeshPolygon, &m_mtxWorldMeshPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshPolygon);						//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffMeshPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureMeshPolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//============================================
// ポリゴンの設定処理
//============================================
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// ポリゴンの移動
//============================================
void CObject3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// ポリゴンのサイズの設定処理
//============================================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;		//頂点情報へのポインタ

	m_size = size;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の更新
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//頂点バッファをアンロックする
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// ポリゴンの回転の設定処理
//============================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	VERTEX_3D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// ポリゴンの長さの設定処理
//============================================
void CObject3D::SetLength(float length)
{
	m_fLength = length;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//拡大縮小のスケールの初期化
	m_fAngle = atan2f(m_size.y, m_size.x);									//角度の初期化

	VERTEX_3D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// 生成
//============================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 &pos)
{
	CObject3D *pObject3D = nullptr;

	//3Dオブジェクトクラスの生成
	pObject3D = new CObject3D;				//3Dオブジェクトのインスタンス生成

	//nullチェック
	if (pObject3D != nullptr)
	{
		//初期化処理
		pObject3D->Init();
		//設定処理
		pObject3D->SetPosition(pos);
		pObject3D->SetSize(D3DXVECTOR3(100.0f, 0.5f, 100.0f));
		pObject3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		assert(false);
	}
	return pObject3D;
}

//============================================
// テクスチャの設定
//============================================
CObject3D * CObject3D::SetTexture(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureMeshPolygon);

	m_Texture = true;

	return S_OK;
}

//============================================
// テクスチャ反映
//============================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTextureMeshPolygon = pTexture;
}

//============================================
// 縦テクスチャ画像の設定
//============================================
void CObject3D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//頂点座標へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//頂点バッファをアンロック
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// 色の設定
//============================================
void CObject3D::SetColor(float Red, float Green, float Blue, float α)
{
	VERTEX_3D*pVtx;				//頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[1].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[2].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[3].col = D3DXCOLOR(Red, Green, Blue, α);

	//頂点バッファをアンロックする
	Buffer->Unlock();
}

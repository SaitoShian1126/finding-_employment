//============================================
//
//	ObjectBase.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "objectbase.h"
#include "application.h"
#include "renderer.h" 
#include "object2d.h"
#include "fade.h"
#include "input.h"
#include "player.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// オブジェクト基礎コンストラクタ
//============================================
CObjectBase::CObjectBase()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pVtxBuffObjectBase = nullptr;
	m_pTextureObjectBase = nullptr;
	m_ObjectBasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBasemtxWorld = {};
	m_fLength = 0.0f;
}

//============================================
// オブジェクト基礎デストラクタ
//============================================
CObjectBase::~CObjectBase()
{
	//何も書かない
}

//============================================
// オブジェクト基礎初期化処理
//============================================
HRESULT CObjectBase::Init(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	//メンバ変数の初期化
	//============================================
	m_pVtxBuffObjectBase = nullptr;
	m_pTextureObjectBase = nullptr;
	m_ObjectBasemtxWorld = {};
	m_ObjectBasePos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_ObjectBaseRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_Radius = 0.0f;
	m_Life = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffObjectBase,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
	pVtx[0].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_ObjectBaseCol;
	pVtx[1].col = m_ObjectBaseCol;
	pVtx[2].col = m_ObjectBaseCol;
	pVtx[3].col = m_ObjectBaseCol;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffObjectBase->Unlock();

	//サイズの設定
	SetSize(m_ObjectBaseSize);

	return S_OK;
}

//============================================
// オブジェクト基礎終了処理
//============================================
void CObjectBase::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffObjectBase != nullptr)
	{			  
		m_pVtxBuffObjectBase->Release();
		m_pVtxBuffObjectBase = nullptr;
	}

	//テクスチャの破棄
	if (m_pTextureObjectBase != nullptr)
	{
		m_pTextureObjectBase->Release();
		m_pTextureObjectBase = nullptr;
	}

	//破棄処理
	CObject::Release();
}

//============================================
// オブジェクト基礎更新処理
//============================================
void CObjectBase::Update()
{

}

//============================================
// オブジェクト基礎描画処理
//============================================
void CObjectBase::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_ObjectBasemtxWorld);//行列初期化関数(第一引数の行列を単位行列に初期化)

	 //ビューマトリックスを取得
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定	(2付くやつを消せばビルボードが上に向かない)
	m_ObjectBasemtxWorld._11 = mtxView._11;
	m_ObjectBasemtxWorld._12 = mtxView._21;
	m_ObjectBasemtxWorld._13 = mtxView._31;
	m_ObjectBasemtxWorld._21 = mtxView._12;
	m_ObjectBasemtxWorld._22 = mtxView._22;
	m_ObjectBasemtxWorld._23 = mtxView._32;
	m_ObjectBasemtxWorld._31 = mtxView._13;
	m_ObjectBasemtxWorld._32 = mtxView._23;
	m_ObjectBasemtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_ObjectBasePos.x, m_ObjectBasePos.y, m_ObjectBasePos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_ObjectBasemtxWorld, &m_ObjectBasemtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_ObjectBasemtxWorld);	//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffObjectBase, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//zバッファ
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureObjectBase);

	//ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================
// テクスチャの設定
//============================================
CObjectBase * CObjectBase::SetTexture(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureObjectBase);

	m_ObjectBaseTexture = true;

	return S_OK;
}

//============================================
//縦テクスチャ画像の設定
//============================================
void CObjectBase::SetTextureY(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//頂点座標へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//頂点バッファをアンロック
	m_pVtxBuffObjectBase->Unlock();
}

//============================================
// 位置の設定
//============================================
void CObjectBase::SetPosition(D3DXVECTOR3 pos)
{
	m_ObjectBasePos = pos;
}

//============================================
// 移動の設定
//============================================
void CObjectBase::SetMove(D3DXVECTOR3 move)
{
	m_ObjectBaseMove = move;
}

//============================================
// サイズの設定
//============================================
void CObjectBase::SetSize(D3DXVECTOR3 size)
{
	m_ObjectBaseSize = size;

	//頂点情報へのポインタ
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
	pVtx[0].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuffObjectBase->Unlock();
}

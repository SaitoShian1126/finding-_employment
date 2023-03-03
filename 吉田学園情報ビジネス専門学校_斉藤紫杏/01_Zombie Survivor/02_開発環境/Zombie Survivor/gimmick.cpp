//============================================
//
//	gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "gimmick.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "gasolene_gimmick.h"
#include "application.h"
#include "renderer.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// ギミックのコンストラクタ
//============================================
CGimmick::CGimmick()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// ギミックのデストラクタ
//============================================
CGimmick::~CGimmick()
{
	//何も書かない
}

//============================================
// ギミックの初期化処理
//============================================
HRESULT CGimmick::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モデルタイプ
	SetType(OBJTYPE_GIMMICK);

	return S_OK;
}

//============================================
// ギミックの終了処理
//============================================
void CGimmick::Uninit(void)
{
	//メッシュの破棄
	if (m_Mesh != nullptr)
	{
		m_Mesh->Release();
		m_Mesh = nullptr;
	}
	//マテリアルの破棄
	if (m_BuffMat != nullptr)
	{
		m_BuffMat->Release();
		m_BuffMat = nullptr;
	}

	//破棄処理
	Release();
}

//============================================
// ギミックの更新処理
//============================================
void CGimmick::Update(void)
{
	SetPosition(m_pos);
	SetMove(m_move);
}

//============================================
// ギミックの描画処理
//============================================
void CGimmick::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL * pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);									//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ShadowDraw();	//影の描画

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);					//ワールド座標行列の設定

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_Mesh->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//============================================
// 影の描画
//============================================
void CGimmick::ShadowDraw(void)
{
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL * pMat;				//マテリアルデータへのポインタ
	D3DMATERIAL9 Material;

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//影マトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(-1.0f, 1.0f, 0.5f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);	//法線と平面の1点から平面を作成
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);	//ライトと平面から影行列を作成

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);					//ワールド座標行列の設定

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//マテリアルの保存
		Material = pMat[nCntMat].MatD3D;

		//色を黒にする
		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetMaterial(&Material);

		//モデルパーツの描画
		m_Mesh->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//============================================
// モデルの設定
//============================================
CGimmick * CGimmick::SetModel(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&m_Mesh);

	return S_OK;
}

//============================================
// 位置の設定
//============================================
void CGimmick::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// 移動の設定
//============================================
void CGimmick::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// 位置の取得処理
//============================================
D3DXVECTOR3 CGimmick::GetPos(void)
{
	return m_pos;
}

//============================================
// サイズの取得処理
//============================================
D3DXVECTOR3 CGimmick::GetSize(void)
{
	return m_size;
}

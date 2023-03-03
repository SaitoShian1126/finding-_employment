//============================================
//
//	objectX.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "objectX.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "player.h"
#include "camera.h"

//============================================
// オブジェクトのコンストラクタ
//============================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// オブジェクトのデストラクタ
//============================================
CObjectX::~CObjectX()
{
	//何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CObjectX::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_nNumMat = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//向きの初期設定

	//モデルの使用をfalseにする
	m_Model = false;
	//SetModel("data/XMODEL/car.x");
	
	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CObjectX::Uninit(void)
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

	//モデルの破棄
	if (m_Model == true)
	{
		m_Model = false;
	}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CObjectX::Update(void)
{
}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CObjectX::Draw(void)
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

	ShadowDraw();

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
// 生成
//============================================
CObjectX * CObjectX::Create(const D3DXVECTOR3 & pos)
{
	CObjectX *pObjectX = nullptr;

	//3Dオブジェクトクラスの生成
	pObjectX = new CObjectX;				//3Dオブジェクトのインスタンス生成

	//nullチェック
	if (pObjectX != nullptr)
	{
		//初期化処理
		pObjectX->Init();
		//設定処理
		pObjectX->SetPosition(pos);
		pObjectX->SetSize(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	}
	else
	{
		assert(false);
	}
	return pObjectX;
}

//============================================
// モデルの設定
//============================================
CObjectX * CObjectX::SetModel(char * pFile)
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

	m_Model = true;

	return S_OK;
}

//============================================
// ポリゴンの設定処理
//============================================
void CObjectX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// オブジェクトxの回転の設定処理
//============================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// 影の描画
//============================================
void CObjectX::ShadowDraw(void)
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

//============================================
//
//	modelparts.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include <stdio.h>
#include "modelparts.h"
#include "application.h"
#include "renderer.h"
#include "line.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// モデルパーツのコンストラクタ
//============================================
CModelParts::CModelParts()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pMesh = {};
	m_pBuffMat = {};
	m_pNumMat = {};
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	nIdxModelParent = 0;
}

//============================================
// モデルパーツのデストラクタ
//============================================
CModelParts::~CModelParts()
{
	//何も書かない
}

//============================================
// モデルパーツの初期化処理
//============================================
HRESULT CModelParts::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_pMesh = {};
	m_pBuffMat = {};
	m_pNumMat = {};
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	nIdxModelParent = 0;
	m_LineUseFlag = false;
	return S_OK;
}

//============================================
// モデルパーツの終了処理
//============================================
void CModelParts::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{	  
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{	  
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	////テクスチャの破棄
	//for (int nCnt = 0; nCnt < (int)m_pNumMat; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != nullptr)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = nullptr;
	//	}
	//}

	//if (m_pTexture != nullptr)
	//{
	//	delete[] m_pTexture;
	//	m_pTexture = nullptr;
	//}
}

//============================================
// モデルパーツの更新処理
//============================================
void CModelParts::Update(void)
{
	if (m_LineUseFlag == false)
	{
		//下の線
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));

		//上の線							  							 																				 			   				
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z));

		//縦の線						  						 														 									   				
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		m_LineUseFlag = true;
	}
}

//============================================
// モデルパーツの描画処理
//============================================
void CModelParts::DrawFile(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL * pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_pmtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);							//ワールド座標行列の設定

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		//pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef); 

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//============================================
// マトリックスの取得
//============================================
D3DXMATRIX * CModelParts::GetMatrix(void)
{
	return &m_mtxWorld;
}

//============================================
// メッシュの取得
//============================================
LPD3DXMESH CModelParts::GetMesh(void)
{
	return m_pMesh;
}

//============================================
// マトリックスの設定
//============================================
void CModelParts::SetMatrix(D3DXMATRIX * matrixparent)
{
	m_pmtxParent = matrixparent;
}

//============================================
// 位置の取得
//============================================
D3DXVECTOR3 CModelParts::GetPos(void)
{
	return m_pos;
}

//============================================
// 最大の取得
//============================================
D3DXVECTOR3 CModelParts::GetVtxMax(void)
{
	return m_VtxMaxModel;
}

//============================================
// 最小の取得
//============================================
D3DXVECTOR3 CModelParts::GetVtxMin(void)
{
	return m_VtxMinModel;
}

//============================================
// 位置の設定
//============================================
void CModelParts::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// 向きの取得
//============================================
D3DXVECTOR3 CModelParts::GetRot(void)
{
	return m_rot;
}

//============================================
// 向きの設定
//============================================
void CModelParts::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// 最大の設定
//============================================
void CModelParts::SetVtxMax(D3DXVECTOR3 max)
{
	m_VtxMaxModel = max;
}

//============================================
// 最小の設定
//============================================
void CModelParts::SetVtxMin(D3DXVECTOR3 min)
{
	m_VtxMinModel = min;
}

//============================================
// 生成
//============================================
CModelParts * CModelParts::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelParts *pModelParts = nullptr;

	// 3Dオブジェクトクラスの生成
	pModelParts = new CModelParts;				// 3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pModelParts != nullptr)
	{
		// 初期化処理
		pModelParts->Init();
		pModelParts->m_pos = pos;
		pModelParts->m_rot = rot;
	}
	else
	{
		assert(false);
	}
	return pModelParts;
}

//============================================
// モデルの設定
//============================================
void CModelParts::SetModel(char * pFile)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_pNumMat,
		&m_pMesh);

	//// テクスチャ
	//m_pTexture = new LPDIRECT3DTEXTURE9[m_pNumMat];

	////情報が入ってなかったら
	//assert(m_pTexture != nullptr);

	//// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	//D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//// 各メッシュのマテリアル情報を取得する
	//for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	//{
	//	//情報の初期化
	//	m_pTexture[nCntMat] = nullptr;

	//	//ポリゴンに貼り付けるテクスチャの読み込み
	//	D3DXCreateTextureFromFile(pDevice,
	//		pMat[nCntMat].pTextureFilename,
	//		&m_pTexture[nCntMat]);
	//}
}

//============================================
// モデルの当たり判定
//============================================
void CModelParts::ModelCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size)
{
	//左の当たり判定
	if (pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z
		&&pPosOld->x + size.x / 2.0f <= m_pos.x + m_VtxMinModel.x
		&&pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x)
	{
		pPos->x = m_pos.x + m_VtxMinModel.x - size.x / 2.0f;
	}
	//右の当たり判定
	if (pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z
		&&pPosOld->x - size.x / 2.0f >= m_pos.x + m_VtxMaxModel.x
		&&pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x)
	{
		pPos->x = m_pos.x + m_VtxMaxModel.x + size.x / 2.0f;
	}
	//手前の当たり判定
	if (pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x
		&&pPosOld->z + size.z / 2.0f <= m_pos.z + m_VtxMinModel.z
		&&pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z)
	{
		pPos->z = m_pos.z + m_VtxMinModel.z - size.z / 2.0f;
	}

	//奥の当たり判定
	if (pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x
		&&pPosOld->z - size.z / 2.0f >= m_pos.z + m_VtxMaxModel.z
		&&pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z)
	{
		pPos->z = m_pos.z + m_VtxMaxModel.z + size.z / 2.0f;
	}
}

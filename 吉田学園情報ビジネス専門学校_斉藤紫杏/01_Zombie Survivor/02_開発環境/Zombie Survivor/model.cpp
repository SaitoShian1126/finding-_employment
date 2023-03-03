//============================================
// 
// 	model.cpp
// 	Author: saito shian
// 
//============================================

//============================================
// インクルード
//============================================
#include <stdio.h>
#include <assert.h>
#include "model.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"
#include "modelparts.h"
#include "keyset.h"
#include "key.h"
#include "motionset.h"
#include "score.h"
#include "line.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// モデルのコンストラクタ
//============================================
CModel::CModel()
{
	//============================================
	// メンバ変数のクリア
	//============================================
}

//============================================
// モデルのデストラクタ
//============================================
CModel::~CModel()
{
	// 何も書かない
}

//============================================
// モデル(ポリゴン)の初期化処理
//============================================
HRESULT CModel::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountModel = 0;
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	//モデルのファイル読み込み
	LoadModel();

	//頂点の最大最小
	Vtx();

	return S_OK;
}

//============================================
// モデル(ポリゴン)の終了処理
//============================================
void CModel::Uninit(void)
{
	//モデルパーツの終了処理
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//============================================
// モデル(ポリゴン)の更新処理
//============================================
void CModel::Update(void)
{
	/*for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt])
		{
			m_apModel[nCnt]->Update();
		}
	}*/
}

//============================================
// モデル(ポリゴン)の描画処理
//============================================
void CModel::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//ローカルマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//モデルパーツのfor文
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->DrawFile();
		}
	}
}

//============================================
// 生成
//============================================
CModel * CModel::Create()
{
	CModel *pModel = nullptr;

	// 3Dモデルクラスの生成
	pModel = new CModel;				// 3Dモデルのインスタンス生成

	// nullptrチェック
	if (pModel != nullptr)
	{
		// 初期化処理
		pModel->Init();
	}
	else
	{
		assert(false);
	}
	return pModel;
}

//============================================
// 外部ファイル読み込み
//============================================
void CModel::LoadModel()
{
	int nNumParts;
	char aText[2000];						//文字列を格納する配列
	char FileName[NUMBER_OF_MODELS][2000];		//2次元配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data/XMODEL/model.txt", "r");

	aText[0] = '\0';	//文字列なし

	if (pFile != nullptr)
	{//ファイルが開けた場合
	 //ファイルに入力したデータを書き出す処理
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_MODEL_WORD, pFile);        //一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_MODEL_WORD, pFile);        //一行ごと読み込む
				continue;
			}

			//ファイルネームを複数個入力する
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);        // = を読み込む
				fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0番目から読み込まれる

				//モデルパーツの生成
				m_apModel[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nCountModel++;
			}

			if (strcmp(&aText[0], "MODELSET") == 0)
			{
				D3DXVECTOR3 pos, rot;
				int Ind = 0;

				while (strcmp(&aText[0], "END_MODELSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_MODEL_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = を読み込む
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%d", &Ind);

						m_ModelNumber = Ind;
					}

					else if (strcmp(&aText[0], "POS") == 0)
					{
						float x = 0.0f;
						float y = 0.0f;
						float z = 0.0f;
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &x);
						fscanf(pFile, "%f", &y);
						fscanf(pFile, "%f", &z);
						pos = D3DXVECTOR3(x, y, z);
					}

					else if (strcmp(&aText[0], "ROT") == 0)
					{
						float x = 0.0f;
						float y = 0.0f;
						float z = 0.0f;
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &x);
						fscanf(pFile, "%f", &y);
						fscanf(pFile, "%f", &z);
						rot = D3DXVECTOR3(x, y, z);
					}
				}

				//モデルパーツの生成
				m_apModel[Ind] = CModelParts::Create(pos,rot);

				//モデルパーツの読み込み
				m_apModel[Ind]->SetModel(&FileName[Ind][0]);

				//モデルパーツのマトリックスの設定
				m_apModel[Ind]->SetMatrix(&m_mtxWorld);
			}
		}
	}
}

//============================================
// 頂点の最大最小
//============================================
void CModel::Vtx(void)
{
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = m_apModel[nCnt]->GetMesh()->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_apModel[nCnt]->GetMesh()->GetFVF());

		//頂点バッファのロック
		m_apModel[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		D3DXVECTOR3 min = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		D3DXVECTOR3 max = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値、最大値を取得
			//xの比較
			if (vtx.x < min.x)
			{
				min.x = vtx.x;
			}
			if (vtx.x > max.x)
			{
				max.x = vtx.x;
			}

			//yの比較(最小値)
			if (vtx.y < min.y)
			{
				min.y = vtx.y;
			}
			if (vtx.y > max.y)
			{
				max.y = vtx.y;
			}

			//zの比較(最小値)
			if (vtx.z < min.z)
			{
				min.z = vtx.z;
			}
			if (vtx.z > max.z)
			{
				max.z = vtx.z;
			}
			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		m_apModel[nCnt]->GetMesh()->UnlockVertexBuffer();

		m_apModel[nCnt]->SetVtxMin(min);
		m_apModel[nCnt]->SetVtxMax(max);

	}
}

//============================================
// 配列モデルパーツの取得
//============================================
CModelParts ** CModel::GetModelParts(void)
{
	return m_apModel;
}

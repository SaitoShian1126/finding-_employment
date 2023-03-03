//============================================
//
//	meshfield.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include <time.h>
#include "meshfield.h"
#include "renderer.h"
#include "object.h"
#include "application.h"

//============================================
// オブジェクトのコンストラクタ
//============================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_pVtxBuffMeshField = nullptr;				//バッファのクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動のクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転のクリア
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色のクリア
	m_fWidth = 0.0f;							//幅のクリア
	m_fHeight = 0.0f;							//高さのクリア
	m_fLength = 0;								//拡大縮小のスケールのクリア
	m_fAngle = 0;								//角度のクリア
	m_nTimer = 0;								//時間のクリア
	m_RandFlag = false;							//ランダムのクリア
	m_fRotMove = 0;								//向きのクリア
}

//============================================
// オブジェクトのデストラクタ
//============================================
CMeshField::~CMeshField()
{
	//何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CMeshField::Init(void)
{
	//乱数
	srand((unsigned int)time(nullptr));											//起動時に一回だけ行うため初期化に書く	
	//============================================
	// メンバ変数の初期化
	//============================================
	m_pVtxBuffMeshField = nullptr;												//バッファの初期化
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
	m_RandFlag = false;															//ランダムフラグをfalse
	m_fRotMove = 5.0f;															//向きのクリア

	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの使用をfalseにする
	m_Texture = false;
	//テクスチャの設定
	SetTexture("data/TEXTURE/床.jpeg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMeshField,
		nullptr);

	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;

	//頂点バッファをロック
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファの読み込み
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,	//インデックス数の計算マクロ定義
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffMeshField,
		nullptr);

	//z方向の繰り返し
	for (int nCntMeshFieldZ = 0; nCntMeshFieldZ < MESHFIELD_Z_BLOCK + 1; nCntMeshFieldZ++)
	{
		//x方向の繰り返し
		for (int nCntMeshFieldX = 0; nCntMeshFieldX < MESHFIELD_X_BLOCK + 1; nCntMeshFieldX++)
		{
			//m_nVtxRand = (float)sin(nCntMeshFieldX * 0.5f) * 60;
			m_nVtxRand = rand() % 40 + 0;
			//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-150.0f + (nCntMeshFieldX * 15.0f), 0.0f, 150.0f - (nCntMeshFieldZ * 15.0f));
			//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//頂点カラーの設定						
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標の設定				  
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCntMeshFieldX, (float)nCntMeshFieldZ);
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);
	int nCntMeshFieldX = 0;

	//インデックスの設定
	//z方向の繰り返し
	for (int nCntMeshFieldZ = 0; nCntMeshFieldZ < MESHFIELD_Z_BLOCK; nCntMeshFieldZ++)
	{
		//x方向の繰り返し
		for (nCntMeshFieldX = 0; nCntMeshFieldX < MESHFIELD_X_BLOCK + 1; nCntMeshFieldX++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCntMeshFieldX + nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCntMeshFieldX + nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);
			pIdx += 2;	//pIdxを2加算する
		}
		//縮退ポリゴンの設定
		if (nCntMeshFieldZ != MESHFIELD_Z_BLOCK)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) * nCntMeshFieldZ + MESHFIELD_X_BLOCK;
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) * (nCntMeshFieldZ + 2);
			pIdx += 2;	//pIdxを2加算する
		}
	}
	//頂点バッファをアンロック
	m_pVtxBuffMeshField->Unlock();

	//頂点バッファをロック
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//インデックスバッファをロック
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE - 2; nCnt++)
	{
		//Idxのpos
		IdxPosNor[0] = pVtx[pIdx[nCnt]].pos;
		IdxPosNor[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPosNor[2] = pVtx[pIdx[nCnt + 2]].pos;

		//縮退ポリゴンの判定を無視する処理
		if (pIdx[nCnt] == pIdx[nCnt + 1] || pIdx[nCnt + 1] == pIdx[nCnt + 2] || pIdx[nCnt + 2] == pIdx[nCnt])
		{
			continue;
		}

		//3次元外積の計算
		Calculation3DNor[0] = IdxPosNor[1] - IdxPosNor[0];
		Calculation3DNor[1] = IdxPosNor[2] - IdxPosNor[0];
		D3DXVec3Cross(&VecAnswer, &Calculation3DNor[0], &Calculation3DNor[1]);

		//正規化
		D3DXVec3Normalize(&VecAnswer, &VecAnswer);

		if (nCnt % 2 == 1)
		{
			VecAnswer *= -1;
		}

		//保存用配列に法線ベクトルを保存
		SaveVtxNor[pIdx[nCnt]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 1]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 2]] += VecAnswer;

		//正規化
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt]], &SaveVtxNor[pIdx[nCnt]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 1]], &SaveVtxNor[pIdx[nCnt + 1]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 2]], &SaveVtxNor[pIdx[nCnt + 2]]);

		//法線
		pVtx[pIdx[nCnt]].nor = SaveVtxNor[pIdx[nCnt]];
		pVtx[pIdx[nCnt + 1]].nor = SaveVtxNor[pIdx[nCnt + 1]];
		pVtx[pIdx[nCnt + 2]].nor = SaveVtxNor[pIdx[nCnt + 2]];
	}

	//頂点バッファをアンロック
	m_pVtxBuffMeshField->Unlock();
	//インデックスバッファをアンロック
	m_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CMeshField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffMeshField != nullptr)
	{
		m_pVtxBuffMeshField->Release();
		m_pVtxBuffMeshField = nullptr;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuffMeshField != nullptr)
	{
		m_pIdxBuffMeshField->Release();
		m_pIdxBuffMeshField = nullptr;
	}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CMeshField::Update(void)
{

}
//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CMeshField::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshField);									//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);	//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);					//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureMeshField);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX, 0, MESHFIELD_PRIMITIVE);

	//テクスチャの解除
	pDevice->SetTexture(0, nullptr);
}

//============================================
// ポリゴンの設定処理
//============================================
void CMeshField::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// ポリゴンの移動
//============================================
void CMeshField::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//============================================
// ポリゴンのサイズの設定処理
//============================================
void CMeshField::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// ポリゴンの回転の設定処理
//============================================
void CMeshField::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//============================================
// ポリゴンの長さの設定処理
//============================================
void CMeshField::SetLength(float length)
{
	m_fLength = length;
}
//============================================
// 生成
//============================================
CMeshField *CMeshField::Create(const D3DXVECTOR3 &pos)
{
	CMeshField *pmeshfield = nullptr;

	//3Dオブジェクトクラスの生成
	pmeshfield = new CMeshField;				//3Dオブジェクトのインスタンス生成

	//nullptrチェック
	if (pmeshfield != nullptr)
	{
		//初期化処理
		pmeshfield->Init();
		//設定処理
		pmeshfield->SetPosition(pos);
		pmeshfield->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		assert(false);
	}
	return pmeshfield;
}

//============================================
// テクスチャの設定
//============================================
CMeshField * CMeshField::SetTexture(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureMeshField);

	m_Texture = true;

	return S_OK;
}

//============================================
// テクスチャ反映
//============================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTextureMeshField = pTexture;
}
//============================================
// 縦テクスチャ画像の設定
//============================================
void CMeshField::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//頂点座標へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//頂点バッファをアンロック
	m_pVtxBuffMeshField->Unlock();
}

//============================================
// 色の設定
//============================================
void CMeshField::SetColor(float Red, float Green, float Blue, float α)
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

//============================================
// プレイヤーとメッシュフィールドの当たり判定
//============================================
void CMeshField::GetMeshFieldCollision(D3DXVECTOR3 *PlayerPos)
{
	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;
	WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idxのpos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB
	D3DXVECTOR3 Calculation3D[2];		//3次元外積の計算結果
	float Calculation2D[3];				//2次元外積の計算結果
	D3DXVECTOR3 Answer;					//外積の計算結果
	D3DXVECTOR3 PlayerDist;				//プレイヤーと頂点の距離

	//頂点バッファをロック
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//インデックスバッファをロック
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE - 2; nCnt++)
	{
		//Idxのpos
		IdxPos[0] = pVtx[pIdx[nCnt]].pos;
		IdxPos[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPos[2] = pVtx[pIdx[nCnt + 2]].pos;

		//プレイヤーと頂点の距離の計算
		PlayerDist = *PlayerPos - IdxPos[0];
		D3DXVec3Length(&PlayerDist);

		//縮退ポリゴンの判定を無視する処理
		if (IdxPos[0] == IdxPos[1] || IdxPos[1] == IdxPos[2] || IdxPos[2] == IdxPos[0])
		{
			continue;
		}
		
		//距離が30.0f以下だったら最初から
		if (30.0f <= D3DXVec3Length(&PlayerDist))
		{
			continue;
		}

		//VecA
		VecA[0] = IdxPos[1] - IdxPos[0];
		VecA[1] = IdxPos[2] - IdxPos[1];
		VecA[2] = IdxPos[0] - IdxPos[2];

		//VecB
		VecB[0] = *PlayerPos - (IdxPos[0] + m_pos);
		VecB[1] = *PlayerPos - (IdxPos[1] + m_pos);
		VecB[2] = *PlayerPos - (IdxPos[2] + m_pos);

		//2次元外積の計算結果
		Calculation2D[0] = VecA[0].x *VecB[0].z - VecB[0].x * VecA[0].z;
		Calculation2D[1] = VecA[1].x *VecB[1].z - VecB[1].x * VecA[1].z;
		Calculation2D[2] = VecA[2].x *VecB[2].z - VecB[2].x * VecA[2].z;

		//プレイヤーの位置が全部-か+
		if ((Calculation2D[0] >= 0 && Calculation2D[1] >= 0 && Calculation2D[2] >= 0) || (Calculation2D[0] <= 0 && Calculation2D[1] <= 0 && Calculation2D[2] <= 0))
		{
			//3次元外積の計算
			Calculation3D[0] = IdxPos[1] - IdxPos[0];
			Calculation3D[1] = IdxPos[2] - IdxPos[0];
			D3DXVec3Cross(&Answer, &Calculation3D[0], &Calculation3D[1]);

			//正規化
			D3DXVec3Normalize(&Answer, &Answer);

			//内積の計算
			PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;
			break;
		}
	}
	//頂点バッファをアンロック
	m_pVtxBuffMeshField->Unlock();
	//頂点バッファをアンロック
	m_pIdxBuffMeshField->Unlock();
}

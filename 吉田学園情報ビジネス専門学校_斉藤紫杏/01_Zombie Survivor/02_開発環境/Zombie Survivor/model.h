//============================================
//
//	model.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MODEL_H_
#define _MODEL_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectx.h"

//============================================
// マクロ定義
//============================================
#define MAX_MODEL_WORD		(512)	//ワード数
#define NUMBER_OF_MODELS	(64)	//モデル数

//============================================
// 前方宣言
//============================================
class CModelParts;
class CLine;

//============================================
// モデルクラス
//============================================
class CModel : public CObjectX
{
public:

	CModel();										//コンストラクタ
	~CModel()override;								//デストラクタ

	HRESULT Init(void)override;						//モデルの初期化処理
	void Uninit(void)override;						//モデルの終了処理
	void Update(void)override;						//モデルの更新処理
	void Draw(void)override;						//モデルの描画処理

	void LoadModel();								//モデルの読み込み
	void Vtx(void);									//最大最小

	CModelParts **GetModelParts(void);

	static CModel *Create();						//生成
	
private:
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_rot;								//向き
	D3DXVECTOR3 m_size;								//サイズ
	CModelParts *m_apModel[NUMBER_OF_MODELS];		//モデルパーツ
	D3DXVECTOR3 m_posOld;							//目的の位置
	D3DXVECTOR3 m_rotDest;							//目的の向き
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	LPD3DXMESH m_pMesh;								//メッシュ
	LPD3DXBUFFER m_pBuffMat;						//バッファー
	DWORD m_nNumMat;								//マテリアル
	D3DXMATRIX *m_pmtxParent;						//親のマトリックス

	int m_nLife;									//体力
	int m_nCountModel;								//モデル数のカウント
	int m_ModelNumber;

	float m_PlayerHeightPos;						//モデルの高さの位置
};

#endif

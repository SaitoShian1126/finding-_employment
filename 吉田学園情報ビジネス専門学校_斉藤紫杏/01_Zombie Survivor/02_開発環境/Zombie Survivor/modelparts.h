//============================================
//
//	modelparts.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// モデルパーツクラス
//============================================
class CModelParts
{
public:
	CModelParts();					//コンストラクタ
	~CModelParts();					//デストラクタ

	HRESULT Init(void);				//モデルパーツの初期化処理
	void Uninit(void);				//モデルパーツの終了処理
	void Update(void);				//モデルパーツの更新処理
	void DrawFile(void);			//モデルパーツの描画処理

	//getter
	D3DXMATRIX *GetMatrix(void);				//マトリックスの取得
	LPD3DXMESH GetMesh(void);					//メッシュの取得
	D3DXVECTOR3 GetRot(void);					//向き
	D3DXVECTOR3 GetPos(void);					//位置の取得
	D3DXVECTOR3 GetVtxMax(void);				//最大の取得
	D3DXVECTOR3 GetVtxMin(void);				//最小の取得

	//setter
	void SetMatrix(D3DXMATRIX *matrixparent);	//マトリックスの設定
	void SetPos(D3DXVECTOR3 pos);				//位置の設定
	void SetRot(D3DXVECTOR3 rot);				//向きの設定
	void SetVtxMax(D3DXVECTOR3 max);			//最大の設定
	void SetVtxMin(D3DXVECTOR3 min);			
		
	void SetModel(char * pFile);				//モデルの設定
	void ModelCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//モデルの当たり判定

	static CModelParts *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);			//生成

private:
	LPDIRECT3DTEXTURE9 *m_pTexture;					//テクスチャへのポインタ
	LPD3DXBUFFER m_pBuffMat;						//バッファ
	LPD3DXMESH m_pMesh;								//メッシュ
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_rot;								//向き
	D3DXVECTOR3 m_VtxMinModel;						//最小
	D3DXVECTOR3 m_VtxMaxModel;						//最大
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	D3DXMATRIX *m_pmtxParent;						//親のマトリックス
	DWORD m_pNumMat;								//マテリアル

	int nIdxModelParent;							//親モデルのインデックス
	bool m_LineUseFlag;								//ラインが使用されたか
};

#endif
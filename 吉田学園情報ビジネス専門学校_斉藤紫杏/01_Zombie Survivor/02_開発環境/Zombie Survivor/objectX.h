//============================================
//
//	objectX.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// 前方宣言
//============================================

//============================================
// オブジェクトクラス
//============================================
class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = 3);			//オブジェクト優先順位
	~CObjectX();									//デストラクタ

	HRESULT Init(void)override;						//ポリゴンの初期化処理
	void Uninit(void)override;						//ポリゴンの終了処理
	void Update(void)override;						//ポリゴンの更新処理
	void Draw(void)override;						//ポリゴンの描画処理

	void SetPosition(D3DXVECTOR3 pos)override;					//ポリゴンの位置
	void SetMove(D3DXVECTOR3 move)override { move; }			//ポリゴンの移動
	void SetSize(D3DXVECTOR3 size) { size; }					//ポリゴンのサイズ
	void SetRot(D3DXVECTOR3 rot);								//回転
	void SetLength(float length) { length; }					//拡大縮小のスケール

	void ShadowDraw(void);										//影の描画

	D3DXVECTOR3 GetPos(void) override { return m_pos; }			//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }		//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_size; }		//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			//回転の取得

	float GetLength(void) override { return m_fLength; }		//拡大縮小のスケールの取得

	static CObjectX *Create(const D3DXVECTOR3 &pos);			//生成
	CObjectX *SetModel(char *pFile);

private:
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_move;							//位置
	D3DXVECTOR3 m_size;							//サイズ
	D3DXVECTOR3 m_VtxMinModel;					//最小
	D3DXVECTOR3 m_VtxMaxModel;					//最大
	LPD3DXBUFFER m_BuffMat;
	LPD3DXMESH m_Mesh;
	DWORD m_nNumMat;
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	CObjectX *m_pObjectX;						//オブジェクトXの情報

	int m_nIdxModelParent;						//親モデルのインデックス
	float m_fLength;					//拡大縮小のスケール
	bool m_Model;						//テクスチャを使用しているかどうか
};

#endif

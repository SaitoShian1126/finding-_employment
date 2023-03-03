//============================================
//
//	object2D.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// オブジェクトクラス
//============================================
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = 3);			//オブジェクト優先順位
	~CObject2D();									//デストラクタ

	HRESULT Init(void)override;						//ポリゴンの初期化処理
	void Uninit(void)override;						//ポリゴンの終了処理
	void Update(void)override;						//ポリゴンの更新処理
	void Draw(void)override;						//ポリゴンの描画処理

	void SetPosition(D3DXVECTOR3 pos)override;		//ポリゴンの位置
	void SetMove(D3DXVECTOR3 move)override;			//ポリゴンの移動
	void SetSize(D3DXVECTOR3 size);					//ポリゴンのサイズ
	void SetCol(D3DXCOLOR col);						//色
	void SetRot(D3DXVECTOR3 rot);					//回転
	void SetLength(float length);					//拡大縮小のスケール
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ反映
	void CObject2D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);		//テクスチャの設定
	void SetColor(float Red, float Green, float Blue, float α);									//色の設定

	float GetLength(void) override { return m_fLength; }		//拡大縮小のスケールの取得

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }	//バッファーの取得
	D3DXVECTOR3 GetPos(void) override{ return m_pos; }			//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }		//移動量の取得
	D3DXVECTOR3 GetSize(void) override{ return m_size; }		//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			//回転の取得

	static CObject2D *Create(const D3DXVECTOR3 &pos);			//生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	D3DXVECTOR3	m_pos;					//位置
	D3DXVECTOR3	m_move;					//移動
	D3DXVECTOR3 m_rot;					//回転
	D3DXVECTOR3 m_size;					//サイズ
	D3DXCOLOR m_col;					//色

	float m_fWidth;						//幅
	float m_fHeight;					//高さ
	float m_fAngle;						//角度
	float m_nTimer;						//時間
	float m_fLength;					//拡大縮小のスケール
};

#endif





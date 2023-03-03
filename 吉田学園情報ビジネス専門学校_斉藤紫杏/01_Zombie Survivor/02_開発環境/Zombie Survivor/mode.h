//============================================
//
//	mode.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MODE_H_
#define _MODE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// モードクラス
//============================================
class CMode : public CObject
{
public:
	CMode();
	virtual ~CMode();

	virtual HRESULT Init(void) { return S_OK; }						//ポリゴンの初期化処理
	virtual void Uninit(void) {} ;									//ポリゴンの終了処理
	virtual void Update(void) = 0;									//ポリゴンの更新処理

	void SetPosition(D3DXVECTOR3 pos)override { pos; }				//ポリゴンの位置
	void SetMove(D3DXVECTOR3 move)override { move; }				//ポリゴンの移動
	void SetLength(float length)override { length; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { pTexture; }		//テクスチャ反映

	float GetLength(void) override { return m_fLength; }			//拡大縮小のスケールの取得

	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }			//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_size; }			//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }				//回転の取得

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//バッファーの取得

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファのポインタ
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





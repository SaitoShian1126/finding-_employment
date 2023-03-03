//============================================
//
//	key.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _KEY_H_
#define _KEY_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// キークラス
//============================================
class CKey
{
public:
	CKey();						//コンストラクタ
	~CKey();					//デストラクタ

	HRESULT Init(void);			//キーの初期化処理
	void Uninit();				//キーの終了処理

	static CKey *Create();		//生成

	//getter
	D3DXVECTOR3 GetPos() { return m_pos; }	//位置の取得処理
	D3DXVECTOR3 GetRot() { return m_rot; }	//向きの取得処理

	//setter
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	//位置の設定処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	//向きの取得処理

private:
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
};

#endif

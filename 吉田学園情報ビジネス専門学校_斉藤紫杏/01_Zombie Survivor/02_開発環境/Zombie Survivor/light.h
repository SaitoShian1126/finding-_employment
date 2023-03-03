//============================================
//
//	light.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// マクロ定義
//============================================
#define LIGHT_SPEED	(0.1f)	//ライトの速度
#define MAX_LIGHT	(1)		//ライトの分割数

//============================================
// ライトクラス
//============================================
class CLight
{
public:
	CLight();						//コンストラクタ
	~CLight();						//デストラクタ

	HRESULT Init(void);				//ライトの初期化処理
	void Uninit(void);				//ライトの終了処理
	void Update(void);				//ライトの更新処理

private:
	D3DLIGHT9 m_nLight[5];			//ライトのポインタ
};

#endif

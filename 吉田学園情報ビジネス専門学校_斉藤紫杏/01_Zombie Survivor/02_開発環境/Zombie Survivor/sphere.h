//============================================
//
//	sphere.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectx.h"

//============================================
// マクロ定義
//============================================
#define SPHERE_MOVE	(1.0f)	//球の移動

//============================================
// オブジェクトクラス
//============================================
class CSphere : public CObjectX
{
public:
	CSphere();											//コンストラクタ
	~CSphere()override;									//デストラクタ

	HRESULT Init(void)override;							//球の初期化処理
	void Uninit(void)override;							//球の終了処理
	void Update(void)override;							//球の更新処理
	void Draw(void)override;							//球の描画処理

	static CSphere *Create(const D3DXVECTOR3 &pos);		//生成

private:
	D3DXVECTOR3 m_RotDest;		//目的の角度
	D3DXVECTOR3 m_Move;			//移動
};

#endif

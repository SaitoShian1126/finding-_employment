//============================================
//
//	reticle.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _RETICLE_H_
#define _RETICLE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================

//============================================
// 前方宣言
//============================================

//============================================
// 表示クラス
//============================================
class CReticle : public CObject2D
{
public:
	CReticle();								//コンストラクタ
	~CReticle()override;					//デストラクタ

	HRESULT Init(void)override;				//表示の初期化処理
	void Uninit(void)override;				//表示の終了処理
	void Update(void)override;				//表示の更新処理
	void Draw(void)override;				//表示の描画処理

	static CReticle *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size);	//生成

	static HRESULT Load(void);				//テクスチャの読み込み
	static void Unload(void);				//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXCOLOR m_col;						//色
};

#endif
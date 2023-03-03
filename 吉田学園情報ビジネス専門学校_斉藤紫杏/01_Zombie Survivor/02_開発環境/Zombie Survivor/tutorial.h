//============================================
//
//	tutorial.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "mode.h"

//============================================
// 前方宣言
//============================================
class CObject2D;
class CFade;

//============================================
// チュートリアルクラス
//============================================
class CTutorial : public CMode
{
public:
	CTutorial();				//コンストラクタ
	~CTutorial();				//デストラクタ

	HRESULT Init(void);			//チュートリアルの初期化処理
	void Uninit(void);			//チュートリアルの終了処理
	void Update(void);			//チュートリアルの更新処理
	void Draw(void);			//チュートリアルの描画処理

	static CTutorial *Create();	//生成

private:
	LPDIRECT3DTEXTURE9 m_pTextureTutorial;	//テクスチャへのポインタ
	CObject2D *m_pObject;					//オブジェクトのポインタ
	CFade *m_pFade;							//フェード
	bool m_BGMFlag;							//BGMフラグ
	bool m_flag;							//フラグ
};

#endif







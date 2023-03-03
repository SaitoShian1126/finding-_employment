//============================================
//
//	fade.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _FADE_H_
#define _FADE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2d.h"
#include "application.h"

//============================================
// マクロ定義
//============================================
#define  FADE_TIME	(60)	//フェードに掛かる時間

//============================================
// フェードクラス
//============================================
class CFade : public CObject2D
{
public:
	//============================================
	// フェード列挙型
	//============================================
	enum FADETYPE
	{
		FADETYPE_NONE = 0,	//何もしていない状態
		FADETYPE_IN,		//フェードin
		FADETYE_OUT,		//フェードout
		FADETYPE_MAX
	};

	CFade();												//コンストラクタ
	~CFade() override;										//デストラクタ

	HRESULT Init(CApplication::MODE modenext);				//フェードの初期化処理
	void Uninit(void) override;								//フェードの終了処理
	void Update(void) override;								//フェードの更新処理

	static FADETYPE GetFade() { return m_Fade; }			//フェードの取得処理
	static D3DXCOLOR GetFadeCol() { return m_FadeColor; }	//フェードカラーの取得処理

	static void SetFade(CApplication::MODE modenext);		//フェードの設定処理
	static CFade *Create(CApplication::MODE modenext);		//生成

private:
	static CFade::FADETYPE m_Fade;			//フェードの状態
	static D3DXCOLOR m_FadeColor;			//フェードの色
	static CApplication::MODE m_ModeNext;	//次の画面
	CObject2D *m_pObject;					//オブジェクトのポインタ
};

#endif








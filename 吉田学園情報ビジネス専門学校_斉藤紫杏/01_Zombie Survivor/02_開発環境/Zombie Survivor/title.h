//============================================
//
//	title.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _TITLE_H_
#define _TITLE_H_

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
// マクロ定義
//============================================

//============================================
// タイトルクラス
//============================================
class CTitle : public CMode
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_MAX
	};

	CTitle();				//コンストラクタ
	~CTitle() ;				//デストラクタ

	HRESULT Init(void);		//タイトルの初期化処理
	void Uninit(void);		//タイトルの終了処理
	void Update(void);		//タイトルの更新処理
	void Draw(void);		//タイトルの描画処理

	void SetColor(float Red, float Green, float Blue, float α);		//色の設定
	static CTitle *Create();			//生成

private:
	LPDIRECT3DTEXTURE9 m_pTextureTitle;		//テクスチャへのポインタ
	CObject2D *m_pObject;					//オブジェクトのポインタ
	CFade *m_pFade;							//フェード

	bool m_BGMFlag;							//BGMフラグ
	bool m_flag;							//フラグ
};

#endif







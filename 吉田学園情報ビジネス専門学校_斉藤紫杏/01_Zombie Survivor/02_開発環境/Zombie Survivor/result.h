//============================================
//
//	result.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _RESULT_H_
#define _RESULT_H_

//============================================
//インクルード
//============================================
#include "main.h"
#include "mode.h"

//============================================
// 前方宣言
//============================================
class CObject2D;
class CFade;

//============================================
// リザルトクラス
//============================================
class CResult : public CMode
{
public:
	//============================================
	// リザルトの種類
	//============================================
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_GAMEOVER,		//ゲームオーバー
		TYPE_GAMECLEAR,		//ゲームクリア
		TYPE_MAX
	};

	CResult();							//コンストラクタ
	~CResult();							//デストラクタ

	HRESULT Init(void);					//リザルトの初期化処理
	void Uninit(void);					//リザルトの終了処理
	void Update(void);					//リザルトの更新処理
	void Draw(void);					//リザルトの描画処理

	static void SetType(TYPE type);		//リザルトの種類の設定
	static CResult *Create();			//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTextureResult[2];	//テクスチャへのポインタ
	static TYPE m_TypeNumber;						//リザルトの種類
	CObject2D *m_pObject;							//オブジェクトのポインタ
	CFade *m_pFade;									//フェード

	bool m_BGMFlag;							//BGMフラグ
};

#endif







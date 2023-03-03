//============================================
//
//	application.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// 前方宣言
//============================================
class CMode;
class CCamera;
class CLight;
class CInput;
class CJoyPad;
class CDebugProc;

//============================================
// アプリケーションクラス
//============================================
class CApplication
{
public:
	//============================================
	//	モードの列挙型
	//============================================
	enum MODE
	{
		MODE_NONE = 0,	
		MODE_TITLE,		//タイトル
		MODE_TUTORIAL,	//チュートリアル
		MODE_GAME,		//ゲーム
		MODE_RESULT,	//リザルト
		MODE_RANKING,	//ランキング
		MODE_MAX
	 };

	CApplication();														//アプリケーションのコンストラクタ
	~CApplication();													//アプリケーションのデストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);			//アプリケーションの初期化処理
	void Uninit(void);													//アプリケーションの終了処理
	void Update(void);													//アプリケーションの更新処理
	void Draw(void);													//アプリケーションの描画処理

	static CRenderer *GetRenderer(void);								//レンダリングの取得処理
	static void SetMode(MODE mode);										//モードの設定
	static MODE GetModeType() { return m_mode; }						//モード種類の取得処理
	static CCamera *GetCamera(void) { return m_pCamera; }				//カメラの情報の取得処理
	static CInput *GetInput(void) { return m_pInput; }					//キーボードの取得処理
	static CJoyPad *GetJpyPad(void) { return m_pJoyPad; }				//ジョイパッドの取得処理
	
private:
	static CRenderer *m_pRenderer;			//レンダリングのポインタ
	static CMode *m_pMode;					//モードのポインタ
	static MODE m_mode;						//モード
	static CCamera *m_pCamera;				//カメラのポインタ
	static CLight *m_pLight;				//ライトのポインタ
	static CInput *m_pInput;				//インプットのポインタ
	static CJoyPad *m_pJoyPad;				//ジョイパッドのポインタ
	static CDebugProc *m_pDebug;			//デバッグ表示のポインタ	
};

#endif

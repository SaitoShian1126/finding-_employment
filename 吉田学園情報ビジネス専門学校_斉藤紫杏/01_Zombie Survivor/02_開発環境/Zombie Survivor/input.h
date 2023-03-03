//============================================
//
//	input.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _INPUT_H_
#define _INPUT_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// マクロ定義
//============================================
#define NUM_KEY_MAX	(256)		//キーの最大値

//============================================
// 入力クラス
//============================================
class CInput
{
public:
	CInput();	//コンストラクタ
	~CInput();	//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void Uninit(void);								//終了処理
	virtual void Update(void);								//更新処理
	bool GetKeyboardPress(int nKey);						//キーボードプレスの取得処理
	bool GetKeyboardTrigger(int nKey);						//キーボードトリガーの取得処理
	bool GetRelease(int nKey);								//キーボードリリースの取得処理

protected:
	BYTE m_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報
	LPDIRECTINPUTDEVICE8 m_pDevice;					//デバイス
	static LPDIRECTINPUT8 m_pInput;					//DirectInputオブジェクトへのポインタ
};

//============================================
// 入力クラス(ジョイパッド)
//============================================
class CJoyPad : public CInput
{
public:
	//============================================
	// ボタンの列挙型
	//============================================
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//十字ボタン上
		JOYKEY_DOWN,				//十字ボタン下
		JOYKEY_LEFT,				//十字ボタン左
		JOYKEY_RIGHT,				//十字ボタン右
		JOYKEY_START,				//スタートボタン
		JOYKEY_BACK,				//バックボタン
		JOYKEY_LEFT_THUMB,			//左スティック押込み
		JOYKEY_RIGHT_THUMB,			//右スティック押込み
		JOYKEY_LEFT_SHOULDER,		//L１ボタン
		JOYKEY_RIGHT_SHOULDER,		//R１ボタン
		JOYKEY_LEFT_TRIGGER,		//L２トリガー
		JOYKEY_RIGHT_TRIGGER,		//R２トリガー
		JOYKEY_A,					//Aボタン
		JOYKEY_B,					//Bボタン
		JOYKEY_X,					//Xボタン
		JOYKEY_Y,					//Yボタン
		JOYKEY_LEFT_STICK,			//左スティック
		JOYKEY_RIGHT_STICK,			//右スティック
		JOYKEY_MAX
	};

	CJoyPad();	//コンストラクタ
	~CJoyPad();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	//ジョイパッドの初期化処理
	void Uninit(void)override;								//ジョイパッドの終了処理
	void Update(void)override;								//ジョイパッドの更新処理

	D3DXVECTOR3 GetJoypadStick(JOYKEY Key);					//ジョイパッドスティック処理
	int GetJoypadTriggerPedal(JOYKEY Key);					//ジョイパッドトリガーペダル処理

	bool GetJoypadPress(JOYKEY key);						//ジョイパッドのプレスの取得処理
	bool GetJoypadTrigger(JOYKEY key);						//ジョイパッドのトリガー処理
	bool *GetUseJoypad(void);								//ジョイパッドの使用状況を取得

private:
	XINPUT_STATE m_JoykeyState;								//ジョイパッドのプレス情報
	XINPUT_STATE m_JoykeyStateTrigger;						//ジョイパッドのトリガー情報
	XINPUT_VIBRATION m_JoyMoter;							//ジョイパッドのモーター
	D3DXVECTOR3 m_JoyStickPos;								//ジョイスティックの傾き
	int m_aJoykeyStateTrigger;								//ジョイパッドのトリガー情報
	int m_aJoykeyStateRelese;								//ジョイパッドのリリース情報
	bool m_bUseJoypad;										//ジョイパッドを使用してるかどうか
};

#endif
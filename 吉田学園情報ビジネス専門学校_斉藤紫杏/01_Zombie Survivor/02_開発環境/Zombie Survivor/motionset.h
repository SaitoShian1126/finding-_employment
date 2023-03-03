//============================================
//
//	motionset.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MOTIONSET_H_
#define _MOTIONSET_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// マクロ定義
//============================================
#define KEY_NUMBER	(2)			//キー数

//============================================
// 前方宣言
//============================================
class CKeySet;

//============================================
// モーション設定クラス
//============================================
class CMotionSet
{
public:
	CMotionSet();					//コンストラクタ
	~CMotionSet();					//デストラクタ

	HRESULT Init(void);				//モーション設定の初期化処理
	void Uninit(void);				//モーション設定の終了処理

	//getter
	int GetLoop(void) { return m_Loop; }				//ループの取得処理
	int GetNumKey(void) {return m_Num_Key;}				//モーションの数の取得処理
	int GetNumParts(void) { return m_NumParts; }		//パーツの種類の取得処理
	CKeySet *GetKeySet(int keyset) { return m_apKeySet[keyset]; }

	//setter
	void SetLoop(int Loop) { m_Loop = Loop; }					//ループの設定処理
	void SetNumKey(int NumKey) { m_Num_Key = NumKey; }			//モーションの数の設定処理
	void SetNumParts(int NumParts) { m_NumParts = NumParts; }	//パーツの種類の設定処理

	static CMotionSet *Create();		//生成

private:
	int m_Loop;								//ループ
	int m_Num_Key;							//モーションの数
	int m_NumParts;							//パーツの種類
	CKeySet *m_apKeySet[KEY_NUMBER];	//KeySet構造体の配列
};

#endif


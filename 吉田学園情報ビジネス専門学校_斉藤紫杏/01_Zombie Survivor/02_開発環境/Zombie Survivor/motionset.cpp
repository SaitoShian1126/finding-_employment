//============================================
//
//	motionset.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include <stdio.h>
#include "motionset.h"
#include "application.h"
#include "renderer.h"
#include "keyset.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// モーション設定のコンストラクタ
//============================================
CMotionSet::CMotionSet()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_Loop = false;							//ループ
	m_Num_Key = 0;							//キーの数
	m_NumParts = 0;							//パーツの種類
	m_apKeySet[KEY_NUMBER] = {};		//KeySet構造体の配列
}

//============================================
// キーのデストラクタ
//============================================
CMotionSet::~CMotionSet()
{
	//何も書かない
}

//============================================
// キーの初期化処理
//============================================
HRESULT CMotionSet::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_Loop = 0;								//ループ
	m_Num_Key = 0;							//キーの数
	m_NumParts = 0;							//パーツの種類

	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		//キー設定の生成
		m_apKeySet[nCnt] = CKeySet::Create();
	}

	return S_OK;
}

//============================================
// キー設定の終了処理
//============================================
void CMotionSet::Uninit()
{
	//キーの終了処理
	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		if (m_apKeySet[nCnt] != nullptr)
		{
			m_apKeySet[nCnt]->Uninit();
			delete m_apKeySet[nCnt];
			m_apKeySet[nCnt] = nullptr;
		}
	}
}

//============================================
// 生成
//============================================
CMotionSet * CMotionSet::Create()
{
	CMotionSet *pMotionSet = nullptr;

	// 3Dオブジェクトクラスの生成
	pMotionSet = new CMotionSet;				// 3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pMotionSet != nullptr)
	{
		// 初期化処理
		pMotionSet->Init();
	}
	else
	{
		assert(false);
	}
	return pMotionSet;
}
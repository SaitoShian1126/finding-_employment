//********************************************
//
//	ranking.cpp
//	Author: saito shian
//
//********************************************

//インクルード
#include <stdio.h>
#include <assert.h>
#include "ranking.h"
#include "application.h"
#include "renderer.h" 
#include "input.h"
#include "object2D.h"
#include "fade.h"
#include "result.h"
#include "sound.h"

//静的メンバ変数宣言
CNumber *CRanking::m_pNumber[MAX_RANKINGRANK][SCORE_DIGIT] = {};
int CRanking::m_aData[5] = {};
int CRanking::m_aRanking = 0;

//ランキングのコンストラクタ
CRanking::CRanking()
{
	//********************************
	//メンバ変数のクリア
	//********************************
}

//ランキングのデストラクタ
CRanking::~CRanking()
{
	//何も書かない
}

//ランキングの初期化処理
HRESULT CRanking::Init(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking.png",
		&m_pTextureRanking[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number.png",
		&m_pTextureRanking[1]);

	//********************************
	//メンバ変数の初期化
	//********************************
	m_BGMFlag = false;

	m_pObject[0] = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject[0]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject[0]->BindTexture(m_pTextureRanking[0]);

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			m_pNumber[nCntRanking][nCnt] = CNumber::Create(D3DXVECTOR3(425.0f + 90.0f * nCnt, 260.0f + 75.0f * nCntRanking, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),CNumber::NUMBERTYPE_SCORE);
			m_pNumber[nCntRanking][nCnt]->BindTexture(m_pTextureRanking[1]);
		}
	}

	LoadRanking();
	return S_OK;
}

//ランキングの終了処理
void CRanking::Uninit(void)
{
	//サウンドの停止
	StopSound();

	CObject::Release();

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			if (m_pNumber[nCntRanking][nCnt] != nullptr)
			{
				m_pNumber[nCntRanking][nCnt]->Uninit();
			}
		}
	}
}

//ランキングの更新処理
void CRanking::Update()
{
	//インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B) && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_RANKING)
	{
		PlaySound(SOUND_LABEL_SE_BUTTOM);
		SaveRanking();
		CFade::SetFade(CApplication::MODE_TITLE);
	}

	//============================================
	// サウンドの再生
	//============================================
	if (m_BGMFlag == false)
	{
		PlaySound(SOUND_LABEL_RANKING);
		m_BGMFlag = true;
	}
}

//ランキングの描画処理
void CRanking::Draw()
{

}

//ランキングの生成
CRanking *CRanking::Create()
{
	CRanking *pRanking = nullptr;

	//クラスの生成
	pRanking = new CRanking;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pRanking != nullptr)
	{
		//初期化処理
		pRanking->Init();
	}
	else
	{
		assert(false);
	}

	return pRanking;
}

//ランキング読み込み
void CRanking::LoadRanking()
{
	FILE * pFile;	//ファイルポインタを宣言

	pFile = fopen("data/Save/ranking.txt", "r");

	if (pFile != nullptr)
	{
		//スコア5個分読み込む
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//ファイルから文字列を読み込む
			fscanf(pFile, "%d \n\n", &m_aData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

//ランキング保存
void CRanking::SaveRanking()
{
	FILE * pFile;	//ファイルポインタを宣言

	pFile = fopen("data/Save/ranking.txt", "w");

	if (pFile != nullptr)
	{
		//スコアを5個分書き出す
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//ファイルに書き出す
			fprintf(pFile, "%d\n", m_aData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

//ランキングの設定
void CRanking::SetRankingScore()
{
	int aPosTexU[5][SCORE_DIGIT];	//各桁の数字を格納

	//新しいスコアを古いスコアと比べる
	if (m_aRanking > m_aData[4])
	{
		m_aData[4] = m_aRanking;
	}
	//バブルソート(昇順)
	for (int nCount1 = 0; nCount1 < 4; nCount1++)
	{
		for (int nCount2 = nCount1 + 1; nCount2 < 5; nCount2++)
		{
			if (m_aData[nCount1] < m_aData[nCount2])
			{
				int tmp = m_aData[nCount1];
				m_aData[nCount1] = m_aData[nCount2];
				m_aData[nCount2] = tmp;
			}
		}
	}
	//8桁のランキングスコアが5回
	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		aPosTexU[nCntRanking][0] = m_aData[nCntRanking] % 10000000 / 1000000;
		aPosTexU[nCntRanking][1] = m_aData[nCntRanking] % 1000000 / 100000;
		aPosTexU[nCntRanking][2] = m_aData[nCntRanking] % 100000 / 10000;
		aPosTexU[nCntRanking][3] = m_aData[nCntRanking] % 10000 / 1000;
		aPosTexU[nCntRanking][4] = m_aData[nCntRanking] % 1000 / 100;
		aPosTexU[nCntRanking][5] = m_aData[nCntRanking] % 100 / 10;
		aPosTexU[nCntRanking][6] = m_aData[nCntRanking] % 10 / 1;
	}

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			//分割数,何番目か
			m_pNumber[nCntRanking][nCnt]->SetTexture(10.0f, (float)aPosTexU[nCntRanking][nCnt], 1.0f, 0.0f);
		}
	}
}

void CRanking::SetRanking(int Score)
{
	m_aRanking = Score;
}

//********************************************
//
//	ranking.h
//	Author: saito shian
//
//********************************************

//2重インクルードガード
#ifndef _RANKING_H_
#define _RANKING_H_

//インクルード
#include "main.h"
#include "mode.h"
#include "score.h"

//マクロ定義
#define MAX_RANKINGRANK	(5)

//前方宣言
class CObject2D;
class CFade;
class CNumber;

//ランキングクラス
class CRanking : public CMode
{
public:
	CRanking();							//コンストラクタ
	~CRanking();						//デストラクタ

	HRESULT Init(void);					//ランキングの初期化処理
	void Uninit(void);					//ランキングの終了処理
	void Update(void);					//ランキングの更新処理
	void Draw(void);					//ランキングの描画処理
	void LoadRanking(void);				//ランキング読み込み
	void SaveRanking(void);				//ランキング保存

	static void SetRankingScore(void);	//ランキングスコアの設定
	static void SetRanking(int Score);	//ランキングの設定
	static CRanking *Create();			//生成

private:
	static CNumber *m_pNumber[MAX_RANKINGRANK][SCORE_DIGIT];	//数字のポインタ
	static int m_aData[5];										//外部ファイルのデータ
	static int m_aRanking;										//取った得点
	LPDIRECT3DTEXTURE9 m_pTextureRanking[2] = {};				//テクスチャへのポインタ
	CObject2D *m_pObject[2];									//オブジェクトのポインタ
	CFade *m_pFade;												//フェード

	bool m_BGMFlag;							//BGMフラグ
};

#endif
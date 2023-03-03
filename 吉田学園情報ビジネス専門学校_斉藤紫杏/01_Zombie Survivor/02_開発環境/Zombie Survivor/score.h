//============================================
//
//	score.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _SCORE_H_
#define _SCORE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"
#include "number.h"

//============================================
// マクロ定義
//============================================
#define SCORE_SIZE_X		 (25.0f)	//スコアのxサイズ
#define SCORE_SIZE_Y		 (250.0f)	//スコアのyサイズ
#define SCORE_DIGIT			 (7)		//スコアの桁数

//============================================
// スコアクラス
//============================================
class CScore : public CObject
{
public:
	CScore();							//コンストラクタ
	~CScore()override;					//デストラクタ

	HRESULT Init(void)override;			//スコアの初期化処理
	void Uninit(void)override;			//スコアの終了処理
	void Update(void)override;			//スコアの更新処理
	void Draw(void)override;			//スコアの描画処理

	void SetScore(int nScore);			//スコアの設定処理
	void AddScore(int nValue);			//スコアの加算処理
	void SubScore(int nSubtract);		//スコアの減算処理
	void SetPosition(D3DXVECTOR3 pos)override { pos; }					//ポリゴンの位置処理
	void SetMove(D3DXVECTOR3 move)override { move; }					//ポリゴンの移動処理
	void SetLength(float length)override { length; }					//ポリゴンの長さ

	D3DXVECTOR3 GetPos(void)override { return D3DXVECTOR3(); }			//位置の取得処理
	D3DXVECTOR3 GetMove(void)override { return D3DXVECTOR3(); };		//移動量の取得
	D3DXVECTOR3 GetSize(void)override { return D3DXVECTOR3(); };		//サイズの取得処理
	D3DXVECTOR3 GetRot(void)override { return D3DXVECTOR3(); };			//回転の取得

	int GetScore(void) { return m_nScore; }								//スコアの取得処理
	float GetLength(void)override { return 0; }							//拡大縮小のスケールの取得

	static CScore *Create();											//生成

private:
	CNumber *m_apNumber[SCORE_DIGIT];		//スコアの数字(桁数)
	int m_nScore;							//スコア
};

#endif






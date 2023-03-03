//============================================
//
//	spawn.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _SPAWN_H_
#define _SPAWN_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectX.h"

//============================================
// マクロ定義
//============================================
#define ENEMY_CREATE_TIME_WAVE_1	(150)		//敵がウェーブ1に生成されるまでの時間
#define ENEMY_CREATE_TIME_WAVE_2	(100)		//敵がウェーブ2に生成されるまでの時間
#define MAX_ENEMY_1					(20)		//敵ウェーブ1の最大数
#define MAX_ENEMY_2					(40)		//敵ウェーブ2の最大数
#define WAVE_TIME					(2000)		//ウェーブ1から2のタイム
#define WAVE_TIME2					(400)		//ウェーブ2から3のタイム

//============================================
// 前方宣言
//============================================
class CBoss;									//ボスのクラス

//============================================
// 量産クラス
//============================================
class CSpawn : public CObject
{
public:
	CSpawn();						//コンストラクタ
	~CSpawn();						//デストラクタ

	HRESULT Init(void);				//量産の初期化処理
	void Uninit(void);				//量産の終了処理
	void Update(void);				//量産の更新処理
	void Draw(void);				//量産の描画処理

	void EnemySpawn(void);			//敵の量産処理
	
	//============================================
	// getter
	//============================================
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); }		//位置の取得処理
	D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3(); }		//移動量の取得
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(); }		//サイズの取得処理
	D3DXVECTOR3 GetRot(void) { return D3DXVECTOR3(); }		//回転の取得
	float GetLength(void) { return float(); }				//拡大縮小のスケールの取得
	int GetEnemyCount(void) { return m_EnemyCount; }		//敵の総数の取得処理
	static CBoss *GetBoss(void) { return m_pBoss;}			//ボスのインスタンスの取得処理
			
	//============================================
	// setter
	//============================================
	void SetPosition(D3DXVECTOR3 pos) {pos; }				//ギミックの位置処理
	void SetRot(D3DXVECTOR3 rot) {rot; }					//ギミックの回転処理
	void SetMove(D3DXVECTOR3 move) { move; }				//ギミックの移動処理
	void SetLength(float length) { length; }				//長さの設定処理
	void SetEnemyCount(int cnt) { m_EnemyCount = cnt; }		//敵の総数の設定処理
	static void SetBoss(CBoss *boss);						//ボスの設定処理

	static CSpawn *Create();								//生成処理

private:
	static CBoss *m_pBoss;									//ボスのインスタンス

	D3DXVECTOR3 m_pos;										//位置
	int m_EnemyCreateTime;									//敵が生成されるまでの時間
	int m_RandNumber;										//ランダムな値が入る変数
	int m_EnemyCount;										//敵の総数
	int m_EnemySpawnType;									//敵がスポーンする種類
	int m_WaveTime;											//ウェーブタイム
	int m_BossAppearTime;									//ボスが出現するまでの時間
	int m_BossCount;										//ボスのカウント

	bool m_RandFlag;										//敵のランダムフラグ
	bool m_MaxEnemyFlag;									//敵が最大値に達したのかのフラグ
	bool m_IndicationFlag;									//wave表示のフラグ
	bool m_BossFlag;										//ボスが出現したのかのフラグ

};
#endif
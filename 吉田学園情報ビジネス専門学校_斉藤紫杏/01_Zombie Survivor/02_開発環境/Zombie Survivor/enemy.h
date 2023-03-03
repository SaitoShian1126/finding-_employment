//============================================
//
//	enemy.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"
#include "model.h"
#include "spawn.h"

//============================================
// マクロ定義
//============================================
#define HUMAN_MOVE			(7.0f)		//人型敵の移動
#define DOG_MOVE			(10.0f)		//犬型敵の移動
#define MAX_ENEMY_WORD		(512)		//ワード数
#define MODEL_HUMAN_PARTS	(15)		//人型ゾンビモデルのパーツ数
#define MODEL_DOG_PARTS		(12)		//犬型ゾンビモデルのパーツ数
#define MOTION_ENEMY_NUMBER	(2)			//モーション数
#define ATTACK_COUNT		(40)		//攻撃するまでの時間

//============================================
// 前方宣言
//============================================
class CShadow;
class CModelParts;
class CMotionSet;
class CKeySet;
class CKey;

//============================================
// 敵クラス
//============================================
class CEnemy : public CObject
{
public:
	enum ENEMYTYPE
	{
		ENEMYTYPE_NONE = 0,
		ENEMYTYPE_HUMAN,	//人型の敵
		ENEMYTYPE_DOG,		//犬型の敵
		ENEMYTYPE_MAX
	};

	//============================================
	// モーションの種類
	//============================================
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,					//ニュートラルモーション
		MOTIONTYPE_MOVE,								//移動モーション
		MOTIONTYPE_ATTACK,								//攻撃モーション
		MOTIONTYPE_MAX
	};

	CEnemy();											//コンストラクタ
	~CEnemy()override;									//デストラクタ

	HRESULT Init(void)override;							//敵の初期化処理
	void Uninit(void)override;							//敵の終了処理
	void Update(void)override;							//敵の更新処理
	void Draw(void)override;							//敵の描画処理

	void LoadEnemy(char * pFileName);					//敵の読み込み
	void Vtx(void);										//最大最小
	void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//モデルとの当たり判定
	void EnemyMove(float speed);						//敵の移動処理

	//setter
	void SetPosition(D3DXVECTOR3 pos);					//敵の位置処理
	void SetRot(D3DXVECTOR3 rot);						//敵の回転処理
	void SetMove(D3DXVECTOR3 move);						//敵の移動処理
	void SetLength(float length);						//長さの設定処理
	void SetLife(int life);								//体力の設定処理
	void SetMotionType(MOTIONTYPE type);				//モーションの種類の設定処理
	void SetEnemyType(ENEMYTYPE type);					//敵の種類

	//getter
	D3DXVECTOR3 GetEnemyPos(void) { return m_pos; }		//敵の位置取得
	D3DXVECTOR3 GetEnemySize(void) { return m_size; }	//敵のサイズ取得
	D3DXVECTOR3 GetEnemyRot(void) { return m_rot; }		//敵の向きの取得
	D3DXVECTOR3 GetPos(void);							//位置の取得処理
	D3DXVECTOR3 GetMove(void);							//移動量の取得
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(); }	//サイズの取得処理
	D3DXVECTOR3 GetRot(void);							//回転の取得
	float GetLength(void);								//拡大縮小のスケールの取得
	int GetLife(void);									//体力の取得処理

	static CEnemy *Create(const D3DXVECTOR3 pos, ENEMYTYPE type);				//生成

private:
	//============================================
	// プライベート関数
	//============================================
	void MotionEnemyAnimation(void);					//モーション関数

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_size;									//サイズ
	D3DXVECTOR3 m_VtxMinModel;							//最小
	D3DXVECTOR3 m_VtxMaxModel;							//最大
	CModelParts *m_apModelHuman[MODEL_HUMAN_PARTS];		//人型モデルパーツ
	CModelParts *m_apModelDog[MODEL_DOG_PARTS];			//犬型モデルパーツ
	CMotionSet *m_MotionSet[MOTION_ENEMY_NUMBER];		//モーションセット
	CKeySet *m_KeySet;									//キーセット
	CKey *m_Key;										//キー
	D3DXVECTOR3 m_posOld;								//目的の位置
	D3DXVECTOR3 m_rotDest;								//目的の向き
	D3DXVECTOR3 m_FrameSpeedHuman[MODEL_HUMAN_PARTS];	//人型フレームの速さ
	D3DXVECTOR3 m_FrameSpeedDog[MODEL_DOG_PARTS];		//犬型フレームの速さ
	D3DXVECTOR3 m_RotSpeedHuman[MODEL_HUMAN_PARTS];		//人型回転の速さ
	D3DXVECTOR3 m_RotSpeedDog[MODEL_DOG_PARTS];			//犬型回転の速さ
	D3DXVECTOR3 m_move;									//移動
	D3DXMATRIX m_mtxWorld;								//ワールドマトリックス
	D3DXMATRIX *m_pmtxParent;							//親のマトリックス
	CShadow *m_pShadow;									//影

	MOTIONTYPE m_MotionType;							//モーションの種類
	ENEMYTYPE m_type;									//敵の種類

	int m_Frame;										//フレーム
	int m_PresentKeySet;								//現在のキーセット
	int m_nLife;										//体力
	int m_nCountModel;									//モデル数のカウント
	int m_EnemyNumber;									//敵の番号
	int m_AttackCount;									//攻撃するまでの時間
	int m_VoiceCount;									//声を発するまでの時間
	int m_VoiceRand;									//声を発するまでのランダムな時間
	int m_MoveRand;										//移動のランダム変数

	float m_PlayerHeightPos;							//敵の高さの位置
	float m_Length;										//長さ
	float m_Angle;										//角度

	bool m_PlayerDethFlag;								//プレイヤーが死んだのかフラグ
	bool m_VoiceFlag;									//声を発しているか
	bool m_RandFlag;									//ランダムフラグ
	bool m_MoveRandFlag;								//移動のランダムフラグ
};

#endif

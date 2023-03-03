//============================================
//
//	boss.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _BOSS_H_
#define _BOSS_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================
#define BOSS_MOVE			(1.0f)		//ボスの移動
#define MAX_BOSS_WORD		(512)		//ワード数
#define MODEL_BOSS_PARTS	(21)		//モデルのパーツ数
#define MOTION_BOSS_NUMBER	(1)			//モーション数

//============================================
// 前方宣言
//============================================
class CShadow;
class CModelParts;
class CMotionSet;
class CKeySet;
class CKey;
class CBullet;

//============================================
// ボスクラス
//============================================
class CBoss : public CObject
{
public:
	//============================================
	// モーションの種類
	//============================================
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,				//ニュートラルモーション
		MOTIONTYPE_MOVE,							//移動モーション
		MOTIONTYPE_MAX
	};

	CBoss();										//コンストラクタ
	~CBoss()override;								//デストラクタ

	HRESULT Init(void)override;						//ボスの初期化処理
	void Uninit(void)override;						//ボスの終了処理
	void Update(void)override;						//ボスの更新処理
	void Draw(void)override;						//ボスの描画処理

	void LoadBoss();								//ボスの読み込み
	void Vtx(void);									//最大最小
	void BossRot();									//ボスの向き
	void BossAttack();								//ボスの攻撃処理

	static D3DXVECTOR3 GetBossPos(void) { return m_pos; }		//ボスの位置取得
	static D3DXVECTOR3 GetBossSize(void) { return m_size; }		//ボスのサイズ取得
	static D3DXVECTOR3 GetBossRot(void) { return m_rot; }		//ボスの向きの取得
	static CBoss *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);				//生成

	void SetPosition(D3DXVECTOR3 pos);		//ボスの位置処理
	void SetRot(D3DXVECTOR3 rot);			//ボスの回転処理
	void SetMove(D3DXVECTOR3 move);			//ボスの移動処理
	void SetLength(float length);			//長さの設定処理
	void SetLife(int life);					//体力の設定処理
	void SetMotionType(MOTIONTYPE type);	//モーションの種類の設定処理
	void SetBossDeathFlag(bool flag);		//ボスが死んだのかの設定処理
	static void SetBullet(CBullet *bullet) { m_pBullet = bullet; }

	D3DXVECTOR3 GetPos(void);				//位置の取得処理
	D3DXVECTOR3 GetMove(void);				//移動量の取得
	D3DXVECTOR3 GetSize(void);				//サイズの取得処理
	D3DXVECTOR3 GetRot(void);				//回転の取得
	float GetLength(void);					//拡大縮小のスケールの取得
	int GetLife(void);						//体力の取得処理
	bool GetBossDethFlag(void);				//ボスが死んだのかフラグ
	static CBullet *GetBullet(void) { return m_pBullet; }

private:
	//============================================
	// プライベート関数
	//============================================
	void MotionBossAnimation(void);					//モーション関数

	static D3DXVECTOR3 m_pos;						//位置
	static D3DXVECTOR3 m_rot;						//向き
	static D3DXVECTOR3 m_size;						//サイズ
	CModelParts *m_apModel[MODEL_BOSS_PARTS];		//モデルパーツ
	CMotionSet *m_MotionSet[MOTION_BOSS_NUMBER];	//モーションセット
	CKeySet *m_KeySet;								//キーセット
	CKey *m_Key;									//キー
	static CBullet *m_pBullet;						//弾のインスタンス
	D3DXVECTOR3 m_posOld;							//目的の位置
	D3DXVECTOR3 m_rotDest;							//目的の向き
	D3DXVECTOR3 m_FrameSpeed[MODEL_BOSS_PARTS];		//フレームの速さ
	D3DXVECTOR3 m_RotSpeed[MODEL_BOSS_PARTS];		//回転の速さ
	D3DXVECTOR3 m_move;								//移動
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	D3DXMATRIX *m_pmtxParent;						//親のマトリックス
	CShadow *m_pShadow;								//影

	MOTIONTYPE m_MotionType;						//モーションの種類

	int m_Frame;									//フレーム
	int m_PresentKeySet;							//現在のキーセット
	int m_nLife;									//体力
	int m_nCountModel;								//モデル数のカウント
	int m_RandCount;								//ランダムカウント
	int m_EnemyCount;								//敵のカウント
	int m_BulletCount;								//弾のカウント

	float m_PlayerHeightPos;						//ボスの高さの位置
	float m_Length;									//長さ
	float m_Angle;									//角度

	bool m_MotionFlag;								//モーションフラグ
	bool m_RandFlag;								//ランダムフラグ
	bool m_BossDeathFlag;							//ボスが死んだのかフラグ
};

#endif

//============================================
//
//	player.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================
#define PLAYER_MOVE			(1.5f)		//プレイヤーの移動
#define PLAYER_DASH_MOVE	(2.5f)		//走っているときの移動
#define PLAYER__ADS_MOVE	(0.5f)		//プレイヤーのADS移動
#define MAX_WORD			(512)		//ワード数
#define MODEL_NUMBER		(20)		//モデルのパーツ数
#define MOTION_NUMBER		(6)			//モーション数
#define BULLET_TIME			(20)		//弾が生成されるまでの時間

//============================================
// 前方宣言
//============================================
class CModelParts;
class CMotionSet;
class CKeySet;
class CKey;
class CCamera;
class CBillboard;
class CBullet;
class CReticle;

//============================================
// プレイヤークラス
//============================================
class CPlayer : public CObject
{
public:
	//============================================
	// モーションの種類
	//============================================
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,				//ニュートラルモーション
		MOTIONTYPE_STANDBYATTACK,					//銃を構えるモーション
		MOTIONTYPE_ATTACK,							//攻撃モーション
		MOTIONTYPE_MOVE,							//移動モーション
		MOTIONTYPE_DASH,							//移動(走り)モーション
		MOTIONTYPE_THROW,							//投げるモーション
		MOTIONTYPE_NONE,
		MOTIONTYPE_MAX
	};

	CPlayer();										//コンストラクタ
	~CPlayer()override;								//デストラクタ

	HRESULT Init(void)override;						//プレイヤーの初期化処理
	void Uninit(void)override;						//プレイヤーの終了処理
	void Update(void)override;						//プレイヤーの更新処理
	void Draw(void)override;						//プレイヤーの描画処理

	void LoadPlayer();								//プレイヤーの読み込み
	void Vtx(void);									//最大最小
	void CollisionPlayer(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//モデルとの当たり判定
	void CollisionMaxModel();															//全部のモデルとの当たり判定

	static D3DXVECTOR3 GetPlayerPos(void) { return m_pos; }		//プレイヤーの位置取得
	static D3DXVECTOR3 GetPlayerRot(void) { return m_rot; }		//プレイヤーの向きの取得
	D3DXVECTOR3 GetPlayerSize(void) { return m_size; }			//プレイヤーのサイズの取得
	static CBullet *GetBullet(void) { return m_pBullet; }		//弾の情報の取得処理

	int GetLife(void) { return m_Life; }						//プレイヤーの体力の取得処理

	static CPlayer *Create(const D3DXVECTOR3 &pos);				//生成

	void SetPosition(D3DXVECTOR3 pos);			//プレイヤーの位置処理
	void SetRot(D3DXVECTOR3 rot);				//プレイヤーの向きの設定処理
	void SetMove(D3DXVECTOR3 move);				//プレイヤーの移動処理
	void SetLength(float length);				//プレイヤーの長さの設定処理
	void SetMotionType(MOTIONTYPE type);		//モーションの種類の設定処理
	void SetPlayerLife(int life);				//プレイヤーの体力の設定処理
	void SetBombUseCount(int usecnt);			//爆弾を何回使用したのかの設定処理
	void GetBombUseFlag(bool flag);				//爆弾を使用したのかの設定処理
	static void SetBullet(CBullet *bullet);		//ボスの設定処理

	void PlayerMove(void);						//プレイヤーの移動処理
	void PlayerAttack(void);					//プレイヤーの攻撃処理

	D3DXVECTOR3 GetPos(void);					//位置の取得処理
	D3DXVECTOR3 GetMove(void);					//移動量の取得
	D3DXVECTOR3 GetSize(void);					//サイズの取得処理
	D3DXVECTOR3 GetRot(void);					//回転の取得
	float GetLength(void);						//拡大縮小のスケールの取得
	int GetBombUseCount(void);					//爆弾を何回使用したのかの取得処理
	bool GetBombUseFlag(void);					//爆弾を使用したのかの取得処理

private:

	//============================================
	// プライベート関数
	//============================================
	void MotionAnimation(void);				//モーション関数

	//============================================
	// メンバ変数
	//============================================
	static D3DXVECTOR3 m_pos;				//位置
	static D3DXVECTOR3 m_rot;				//向き
	static CBullet *m_pBullet;				//弾のインスタンス
	
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_posOld;					//前回の位置
	D3DXVECTOR3 m_rotDest;					//目的の向き
	D3DXVECTOR3 m_ADSRotDest;				//エイム中の目的の向き
	D3DXVECTOR3 m_FrameSpeed[MODEL_NUMBER];	//フレームの速さ
	D3DXVECTOR3 m_RotSpeed[MODEL_NUMBER];	//回転の速さ
	D3DXVECTOR3 m_VtxMinModel;				//最小
	D3DXVECTOR3 m_VtxMaxModel;				//最大
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	D3DXMATRIX *m_pmtxParent;				//親のマトリックス	
	CModelParts *m_apModel[MODEL_NUMBER];	//モデルパーツ
	CMotionSet *m_MotionSet[MOTION_NUMBER];	//モーションセット
	CBillboard *m_pBillboard;				//ビルボードのインスタンス生成
	CObject *m_pObjectTarget;				//当たり判定対象のオブジェクト
	CReticle *m_pReticle;					//レティクルのインスタンス

	MOTIONTYPE m_MotionType;				//モーションの種類

	int m_Life;								//体力
	int m_Frame;							//フレーム
	int m_PresentKeySet;					//現在のキーセット
	int m_nCountModel;						//モデル数のカウント
	int m_BulletCreateTime;					//弾を生成するまでの時間
	int m_ThrowTime;						//投げるモーションが終わるまでの時間
	int m_BombUseCount;						//爆弾を何回使用したのか

	static bool m_PlayerAttackFlag;			//プレイヤーがエイムをしたのかフラグ

	float m_PlayerHeightPos;				//プレイヤーの高さの位置
	float m_Speed;							//移動速さ

	bool m_AnimationFlag;					//移動のアニメーションフラグ
	bool m_AttackAnimationFlag;				//攻撃体制のアニメーションのフラグ
	bool m_SoundRunFlag;					//走っているサウンドが使われているか
	bool m_SoundAttackFlag;					//攻撃のサウンドが使われているか	
	bool m_BulletCreateFlag;				//弾が生成されたかのフラグ
	bool m_ThrowFlag;						//投げるモーションフラグ
	bool m_BombUseCountFlag;				//爆弾を何回使用したのかフラグ
	bool m_DashFlag;						//走っているかフラグ
	bool m_DashAnimationFlag;				//走っている時のモーションフラグ
};

#endif

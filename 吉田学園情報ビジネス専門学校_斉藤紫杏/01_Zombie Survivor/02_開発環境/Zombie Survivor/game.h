//============================================
//
//	game.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _GAME_H_
#define _GAME_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "mode.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================
#define MAX_PARTICLE	(100)	//パーティクルの最大数
#define MAX_GASOLENE	(4)		//ガソリンの最大数
#define MAX_ROCK		(4)		//岩ギミックの最大数
#define PARTICLE_TIME	(125)	//パーティクルが消えるまでの時間
#define MAX_UI			(2)		//UIの最大数

//============================================
// 前方宣言
//============================================
class CMeshField;
class CEnemy;
class CFade;
class CScore;
class CGasolene_Gimmick;
class CModel;
class CHitBox;
class CPlayer;
class CSpawn;
class CParticle;
class CRock_gimmick;
class CBoss;
class CIndication;
class CItem;
class CUi;

//============================================
// ゲームクラス
//============================================
class CGame : public CMode
{
public:
	CGame();					//コンストラクタ
	~CGame();					//デストラクタ

	HRESULT Init(void);			//ゲームの初期化処理
	void Uninit(void);			//ゲームの終了処理
	void Update(void);			//ゲームの更新処理
	void Draw(void);			//ゲームの描画処理

	static CMeshField *GetMeshField(void) { return m_pMeshField; }								//メッシュフィールドの情報の取得処理
	static CScore *GetScore(void) { return m_pScore; }											//敵の情報の取得処理
	static CGasolene_Gimmick **GetGasoleneGimmick(void) { return m_pGasoleneGimmick; }			//ガソリンギミックの情報の取得処理
	static CModel *GetModel(void) { return m_Model; }											//モデルの取得処理
	static CPlayer *GetPlayer(void) { return m_pPlayer; }										//プレイヤー取得処理
	static CSpawn *GetSpawn(void) { return m_pSpawn; }											//スポーンの取得処理
	static CParticle **GetParticle(void) { return m_pParticle; }								//パーティクルの取得処理
	static CRock_gimmick **GetRockGimmick(void) { return m_pRockGimmick; }						//岩ギミックの取得処理
	static CBoss *GetBoss(void) { return m_pBoss; }												//ボスの取得処理
	static CIndication *GetIndication(void) { return m_pIndication; }							//表示の取得処理
	static CItem *GetItem(void) { return m_pItem; }												//アイテムの取得処理
	static CUi **GetUi(void) { return m_pUi; }													//UIの取得処理

	static void SetPlayer(CPlayer *player);														//プレイヤーの設定処理
	static void SetItem(CItem *item);															//アイテムの設定処理

	static CGame *Create();												//生成

private:
	static CMeshField *m_pMeshField;							//メッシュフィールドのインスタンス
	static CScore *m_pScore;									//スコアのインスタンス
	static CGasolene_Gimmick *m_pGasoleneGimmick[MAX_GASOLENE];	//ガソリンギミックのインスタンス
	static CModel *m_Model;										//モデルのインスタンス
	static CPlayer *m_pPlayer;									//プレイヤーのインスタンス
	static CSpawn *m_pSpawn;									//スポーンのインスタンス
	static CParticle *m_pParticle[MAX_PARTICLE];				//パーティクルのインスタンス
	static CRock_gimmick *m_pRockGimmick[MAX_ROCK];				//岩ギミックのインスタンス
	static CBoss *m_pBoss;										//ボスのインスタンス
	static CIndication *m_pIndication;							//表示のインスタンス
	static CItem *m_pItem;										//アイテムのインスタンス
	static CUi *m_pUi[MAX_UI];									//UIのインスタンス
	CFade *m_pFade;												//フェードのインスタンス

	int m_ParticleCreateTime;									//パーティクルの生成されるまでの時間
	int m_ItemSpawnTime;										//アイテムが再スポーンする時間
	bool m_ItemGetFlag;											//アイテムを取得したのかのフラグ
	bool m_BGMFlag;												//BGMが使用されているのかフラグ
	bool m_EnemyFlag;
};
#endif




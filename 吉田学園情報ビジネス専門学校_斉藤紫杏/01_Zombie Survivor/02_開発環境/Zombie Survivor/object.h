//=============================================================================
//
// オブジェクト処理
// Author : SAITO SHIAN
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CObject
{
public:

	struct VERTEX_LINE
	{
		D3DXVECTOR3 pos;			//xyz座標
		D3DCOLOR col;				//カーラー
	};

	//-------------------------------------------------------------------------
	// 列挙型
	//-------------------------------------------------------------------------
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PAUSE,		//ポーズ
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_BG,			//背景
		OBJTYPE_EFFECT,		//エフェクト
		OBJTYPE_MESH,		//メッシュ
		OBJTYPE_NUMBER,		//番号
		OBJTYPE_SCORE,		//スコア
		OBJTYPE_MODE,		//モード
		OBJTYPE_TITLEROGO,	//タイトルロゴ
		OBJTYPE_COUNTDOWN,	//カウントダウン
		OBJTYPE_MODEL,		//モデル
		OBJTYPE_GIMMICK,	//ギミック
		OBJTYPE_MAX,
		OBJTYPE_INVALID
	};

	enum EPRIORITY
	{
		PRIORITY_LEVEL0 = 0,
		PRIORITY_LEVEL1,
		PRIORITY_LEVEL2,
		PRIORITY_LEVEL3,
		PRIORITY_LEVEL4,
		PRIORITY_LEVEL5,
		PRIORITY_FADE,
		PRIORITY_LEVELMAX
	};

	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	virtual HRESULT Init() = 0;							// 初期化処理
	virtual void Uninit() = 0;							// 終了処理
	virtual void Update() = 0;							// 更新処理
	virtual void Draw() = 0;							// 描画処理
	virtual void VtxUpdate() {}							// 頂点座標更新処理

	virtual void SetPosition(D3DXVECTOR3 pos) = 0;		//ポリゴンの位置処理
	virtual void SetMove(D3DXVECTOR3 move) = 0;			//ポリゴンの移動処理
	virtual void SetLength(float length) = 0;

	virtual D3DXVECTOR3 GetPos(void) = 0;				//位置の取得処理
	virtual D3DXVECTOR3 GetMove(void) = 0;				//移動量の取得
	virtual D3DXVECTOR3 GetSize(void) = 0;				//サイズの取得処理
	virtual D3DXVECTOR3 GetRot(void) = 0;				//回転の取得
	virtual float GetLength(void) = 0;					//拡大縮小のスケールの取得

	virtual int GetLife(void) { return 0; }				//体力の取得
	virtual void SetLife(int nLife) { nLife; }			//体力の設定

	virtual void SetType(const EObjType type);			// タイプ設定処理
	virtual void SetCanPoseUpdate() { m_canPoseUpdate = true; }
	virtual EObjType GetObjType(void);								// オブジェクトのタイプ取得処理

	static void ReleaseAll(void);						// 全てのインスタンスの終了処理
	static void UpdateAll(void);						// 全てのインスタンスの更新処理
	static void DrawAll(void);							// 全てのインスタンスの描画処理
	static void ModeRelease();							// モード以外だったら破棄処理
	void Death(void);									// オブジェクト破棄処理

	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static CObject* GetCurrent(int nPriority) { return m_pCurrent[nPriority]; }
	CObject* GetNext() { return m_pNext; }

protected:
	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	void Release();										// インスタンスの解放処理

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	static int m_nNumAll;										// オブジェクトの総数
	int m_nID;													// 接続先の番号	
	int m_nPriority;											// プライオリティの保存
	EObjType m_objType;											// オブジェクトの種類

	// リスト構造
	static CObject *m_pTop[PRIORITY_LEVELMAX];					// 先頭のオブジェクトへのポインタ
	static CObject *m_pCurrent[PRIORITY_LEVELMAX];				// 現在(一番後ろ)のオブジェクトへのポインタ
	CObject *m_pPrev;											// 前のオブジェクトへのポインタ
	CObject *m_pNext;											// 次のオブジェクトへのポインタ

	bool m_bDeath;												// 死フラグ

	bool m_canPoseUpdate;	// ポーズ中の更新が出来るか
};

#endif
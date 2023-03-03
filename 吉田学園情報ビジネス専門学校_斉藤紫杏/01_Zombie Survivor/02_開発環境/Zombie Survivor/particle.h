//============================================
//
//	particle.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================

//============================================
// 前方宣言
//============================================

//============================================
// ギミッククラス
//============================================
class CParticle : public CObject
{
public:

	enum PARTICLETYPE
	{
		PARTICLETYPE_FIRE = 0,		//燃えてるパーティクル
		PARTICLETYPE_FOUNTAIN,		//噴水パーティクル
		PARTICLETYPE_SPLINTER,		//破片パーティクル
		PARTICLETYPE_BLOOD			//血パーティクル
	};

	CParticle();										//コンストラクタ
	~CParticle()override;								//デストラクタ

	HRESULT Init(void)override;							//パーティクルの初期化処理
	void Uninit(void)override;							//パーティクルの終了処理
	void Update(void)override;							//パーティクルの更新処理
	void Draw(void)override;							//パーティクルの描画処理

	//setter
	void SetPosition(D3DXVECTOR3 pos);									//パーティクルの位置処理
	void SetSize(D3DXVECTOR3 size);										//パーティクルのサイズの設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						//パーティクルの回転処理
	void SetMove(D3DXVECTOR3 move) { m_move = move; }					//パーティクルの移動処理
	void SetLength(float length) { length; }							//長さの設定処理
	void SetParticle(D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//パーティクルの設定処理
	void SetParticleType(PARTICLETYPE type);							//パーティクルの種類の設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						//テクスチャ反映

	//getter
	D3DXVECTOR3 GetPos(void) { return m_pos; }				//位置の取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }			//移動量の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }			//サイズの取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//回転の取得
	float GetLength(void) { return float(); }				//拡大縮小のスケールの取得

	static HRESULT Load(void);			//テクスチャの読み込み
	static void Unload(void);			//テクスチャの破棄

	static CParticle *CParticle::Create(PARTICLETYPE type, D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_rot;						//向き
	D3DXCOLOR m_col;						//色

	PARTICLETYPE m_type;					//パーティクルの種類

	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	int m_nLife;							//体力

	float m_Radius;							//半径
};

#endif

//============================================
//
//	hp.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _HP_H_
#define _HP_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================
#define LIFE_WIDTH			(35.0f)	//ポリゴンの幅
#define BOSS_LIFE_WIDTH		(1.5f)	//ボスのポリゴンの幅

//============================================
// 体力バークラス
//============================================
class CHp : public CObject
{
public:
	enum HPTYPE
	{
		HPTYPE_PLAYER = 0,		//プレイヤーのHP
		HPTYPE_BOSS,			//ボスのHP
		HPTYPEMAX
	};
	CHp();							//コンストラクタ
	~CHp()override;					//デストラクタ

	HRESULT Init(void)override;			//体力バーの初期化処理
	void Uninit(void)override;			//体力バーの終了処理
	void Update(void)override;			//体力バーの更新処理
	void Draw(void)override;			//体力バーの描画処理

	void SetPosition(D3DXVECTOR3 pos) { pos; }		//体力バーの位置
	void SetMove(D3DXVECTOR3 move) { move; }		//体力バーの移動
	void SetSize(D3DXVECTOR3 size) { size; };		//体力バーのサイズ
	void SetCol(D3DXCOLOR col) { col; }				//色
	void SetRot(D3DXVECTOR3 rot) { rot; }			//回転
	void SetLength(float length) { length; }					//拡大縮小のスケール
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { pTexture; }	//テクスチャ反映
	void SetHPType(HPTYPE type) { m_type = type;}				//HPの種類の設定
	void SetColor(float Red, float Green, float Blue, float α);	//色の設定

	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }			//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_size; }			//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }				//回転の取得
	float GetLength(void) override { return m_fLength; }			//拡大縮小のスケールの取得
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//バッファーの取得
	HPTYPE GetHPType(void) { return m_type;}						//HPの種類の取得処理

	static CHp *Create(HPTYPE type);	//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexturehp;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファのポインタ
	D3DXVECTOR3	m_pos;						//位置
	D3DXVECTOR3	m_move;						//移動
	D3DXVECTOR3 m_rot;						//回転
	D3DXVECTOR3 m_size;						//サイズ
	D3DXCOLOR m_col;						//色
	HPTYPE m_type;							//HPの種類
	int m_nPlayreLife;						//プレイヤーの体力を保存する
	int m_nBossLife;						//ボスの体力を保存する
	float m_fLength;						//拡大縮小のスケール
};

#endif

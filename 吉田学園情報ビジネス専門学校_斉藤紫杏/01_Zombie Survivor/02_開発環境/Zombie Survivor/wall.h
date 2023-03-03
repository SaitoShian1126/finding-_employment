//============================================
//
//	wall.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _WALL_H_
#define _WALL_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================

//============================================
// オブジェクトクラス
//============================================
class CWall : public CObject
{
public:
	explicit CWall();								//オブジェクト優先順位
	~CWall();										//デストラクタ

	HRESULT Init(void)override;						//ポリゴンの初期化処理
	void Uninit(void)override;						//ポリゴンの終了処理
	void Update(void)override;						//ポリゴンの更新処理
	void Draw(void)override;						//ポリゴンの描画処理

	void SetPosition(D3DXVECTOR3 pos)override;		//ポリゴンの位置
	void SetMove(D3DXVECTOR3 move)override;			//ポリゴンの移動
	void SetSize(D3DXVECTOR3 size);					//ポリゴンのサイズ
	void SetRot(D3DXVECTOR3 rot);					//回転
	void SetLength(float length) { length; }		//拡大縮小のスケール
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ反映

	float GetLength(void) override { return float(); }				//拡大縮小のスケールの取得

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//バッファーの取得
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }				//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_size; }				//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }					//回転の取得

	static CWall *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 rot);						//生成
	static HRESULT Load(void);			//テクスチャの読み込み
	static void Unload(void);			//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3	m_pos;						//位置
	D3DXVECTOR3	m_move;						//移動
	D3DXVECTOR3 m_rot;						//回転
	D3DXVECTOR3 m_size;						//サイズ
	D3DXCOLOR m_col;						//色
};

#endif

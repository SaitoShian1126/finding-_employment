
//============================================
//
//	line.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _LINE_H_
#define _LINE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
//マクロ定義
//============================================
#define MAX_LINE    (500)			//ラインの最大数

//============================================
// ライン表示クラス
//============================================
class CLine : public CObject
{
public:
	CLine();						//コンストラクタ
	~CLine();						//デストラクタ

	HRESULT Init(void);				//ライン表示の初期化処理
	void Uninit(void);				//ライン表示の終了処理
	void Update(void);				//ライン表示の更新処理
	void Draw(void);				//ライン表示の描画処理

	void SetPosition(D3DXVECTOR3 pos)override;			//ラインの位置
	void SetMove(D3DXVECTOR3 move)override { move; }	//ラインの移動
	void SetLength(float length)override { length; }	//拡大縮小のスケール

	void SetLine(void);									//ラインの頂点座標の設定

	float GetLength(void) override { return float(); }				//拡大縮小のスケールの取得
	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//位置の取得
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }	//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return D3DXVECTOR3(); }	//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }		//回転の取得

	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 end);	//生成

private:
	static D3DXVECTOR3 m_start;					//始点
	static D3DXVECTOR3 m_end;					//終点
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffLine;     //頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXCOLOR m_col;							//色
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	CLine *m_aLine[MAX_LINE];					//ラインの情報
};

#endif
//============================================
//
//	skybox.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================
#define MAX_SIZE				(1300.0f)	//サイズの最大値
#define MAX_SIDE				(30)		//横の最大値
#define MIN_SIDE				(5)			//横の最小値
#define START_SIDE				(16)		//横の最初の値
#define MAX_VERTICAL			(30)		//縦の最大値
#define MIN_VERTICAL			(5)			//縦の最小値
#define START_VERTICAL			(15)		//縦の最初の値

//============================================
// オブジェクトクラス
//============================================
class CSkyBox : public CObject
{
public:
	explicit CSkyBox();								//オブジェクト優先順位
	~CSkyBox();										//デストラクタ

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

	static CSkyBox *Create(const D3DXVECTOR3 &pos);						//生成
	CSkyBox *SetTexture(char *pFile);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//インデックスバッファへのポインタ											
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffCone;	// 円錐の頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3 IdxPosNor[3];						//Idxのpos
	D3DXVECTOR3 Calculation3DNor[2];				//3次元外積の計算結果
	D3DXVECTOR3 VecAnswer;							//外積の計算結果
	D3DXVECTOR3	m_pos;								//位置
	D3DXVECTOR3	m_move;								//移動
	D3DXVECTOR3 m_rot;								//回転
	D3DXVECTOR3 m_size;								//サイズ
	D3DXCOLOR m_col;								//色

	int	m_nHorizontal;		// 横
	int	m_nVertical;			// 縦
	int	m_nVtx;				// 頂点数
	int	m_nIdx;				// インデックス数
	int	m_nPolygon;			// ポリゴン数
};

#endif

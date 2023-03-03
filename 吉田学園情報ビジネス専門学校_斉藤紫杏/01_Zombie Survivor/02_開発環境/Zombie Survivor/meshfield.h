//============================================
//
//	meshffield.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================
#define MESHFIELD_X_BLOCK	(80)		//x方向のブロック
#define MESHFIELD_Z_BLOCK	(80)		//z方向のブロック
#define MESHFIELD_VERTEX	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))								//頂点数 ((xブロック数 + 1) * (zブロック数 + 1))
#define MESHFIELD_INDEX		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)	//インデックス数 ((xブロック数 + 1) * 2 * zブロック数 + (zブロック数 - 1) * 縮退ポリゴン用頂点数(z方向に増えたら2ずつ縮退ポリゴン用頂点数が増える))
#define MESHFIELD_PRIMITIVE	(MESHFIELD_X_BLOCK * (MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)		//ポリゴン数 (xブロック数 * zブロック数 * 2 + (zブロック数 - 1) * 縮退ポリゴン数(z方向に増えたら4ずつ縮退ポリゴン数が増える))

//============================================
// オブジェクトクラス
//============================================
class CMeshField : public CObject
{
public:
	explicit CMeshField(int nPriority = 3);			//オブジェクト優先順位
	~CMeshField();									//デストラクタ

	HRESULT Init(void)override;						//ポリゴンの初期化処理
	void Uninit(void)override;						//ポリゴンの終了処理
	void Update(void)override;						//ポリゴンの更新処理
	void Draw(void)override;						//ポリゴンの描画処理

	void SetPosition(D3DXVECTOR3 pos)override;		//ポリゴンの位置
	void SetMove(D3DXVECTOR3 move)override;			//ポリゴンの移動
	void SetSize(D3DXVECTOR3 size);					//ポリゴンのサイズ
	void SetRot(D3DXVECTOR3 rot);					//回転
	void SetLength(float length);					//拡大縮小のスケール
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ反映
	void CMeshField::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);	//テクスチャの設定
	void SetColor(float Red, float Green, float Blue, float α);									//色の設定

	void GetMeshFieldCollision(D3DXVECTOR3 *PlayerPos);					//メッシュフィールドの当たり判定の取得処理

	float GetLength(void) override { return m_fLength; }				//拡大縮小のスケールの取得

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuffMeshField; }	//バッファーの取得
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_move; }				//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_size; }				//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_rot; }					//回転の取得

	static CMeshField *Create(const D3DXVECTOR3 &pos);					//生成
	CMeshField *SetTexture(char *pFile);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMeshField;	//頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffMeshField;		//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureMeshField;			//テクスチャ
	D3DXMATRIX m_mtxWorldMeshField;					//ワールドマトリックス
	D3DXVECTOR3 SaveVtxNor[MESHFIELD_VERTEX];		//頂点分の法線ベクトル保存用配列
	D3DXVECTOR3 IdxPosNor[3];						//Idxのpos
	D3DXVECTOR3 Calculation3DNor[2];				//3次元外積の計算結果
	D3DXVECTOR3 VecAnswer;							//外積の計算結果
	D3DXVECTOR3	m_pos;								//位置
	D3DXVECTOR3	m_move;								//移動
	D3DXVECTOR3 m_rot;								//回転
	D3DXVECTOR3 m_size;								//サイズ
	D3DXCOLOR m_col;								//色

	int m_nVtxRand;									//頂点のy座標ランダム

	float m_fWidth;									//幅
	float m_fHeight;								//高さ
	float m_fAngle;									//角度
	float m_nTimer;									//時間
	float m_fLength;								//拡大縮小のスケール
	float m_fRotMove;								//向き

	bool m_RandFlag;								//ランダムフラグ
	bool m_Texture;									//テクスチャを使用しているかどうか
};

#endif

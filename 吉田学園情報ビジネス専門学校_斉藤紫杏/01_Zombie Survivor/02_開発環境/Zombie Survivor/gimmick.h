//============================================
//
//	gimmick.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

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
class CGimmick : public CObject
{
public:
	//============================================
	// ギミックの種類
	//============================================
	enum GIMMICKTYPE
	{
		GIMMICKTYPE_GASOLENE = 0,					//ガソリンギミック
		GIMMICKTYPE_MAX
	};

	CGimmick();											//コンストラクタ
	~CGimmick()override;								//デストラクタ

	HRESULT Init(void)override;							//ギミックの初期化処理
	void Uninit(void)override;							//ギミックの終了処理
	void Update(void)override;							//ギミックの更新処理
	void Draw(void)override;							//ギミックの描画処理

	void ShadowDraw(void);								//影の描画

	CGimmick *SetModel(char *pFile);

	//setter
	void SetPosition(D3DXVECTOR3 pos);						//ギミックの位置処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			//ギミックの回転処理
	void SetMove(D3DXVECTOR3 move);							//ギミックの移動処理
	void SetLength(float length) { length; }				//長さの設定処理

	//getter
	D3DXVECTOR3 GetPos(void);								//位置の取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }			//移動量の取得
	D3DXVECTOR3 GetSize(void);								//サイズの取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//回転の取得
	float GetLength(void) { return float(); }				//拡大縮小のスケールの取得

private:
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動
	D3DXVECTOR3 m_size;		//サイズ
	D3DXVECTOR3 m_rot;		//向き

	LPD3DXBUFFER m_BuffMat;	//バッファ
	LPD3DXMESH m_Mesh;		//メッシュ
	DWORD m_nNumMat;		//マテリアル
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
};

#endif

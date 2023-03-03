//============================================
//
//	enter.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _ENTER_H_
#define _ENTER_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================
#define ENTER_SIZE_X		 (20.0f)	//enterのxサイズ
#define ENTER_SIZE_Y		 (25.0f)	//enterのyサイズ

//============================================
// enterクラス
//============================================
class CEnter : public CObject2D
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_MAX
	};
public:
	CEnter();						//コンストラクタ
	~CEnter()override;				//デストラクタ

	HRESULT Init(void)override;		//enterの初期化処理
	void Uninit(void)override;		//enterの終了処理
	void Update(void)override;		//enterの更新処理
	void Draw(void)override;		//enterの描画処理

	static CEnter *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size);	//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTextureenter;	//テクスチャへのポインタ
	D3DXCOLOR m_nCol;							//カラー
	TYPE m_nType;								//タイプ
	int m_nCount;								//inとoutまでの時間
};

#endif









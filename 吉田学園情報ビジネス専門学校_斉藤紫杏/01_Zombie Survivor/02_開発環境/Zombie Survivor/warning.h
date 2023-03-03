//============================================
//
//	warning.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _WARNING_H_
#define _WARNING_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================
#define MAX_TEXTURE		(2)			//テクスチャの最大数
#define RELEASE_TIME	(300)		//破棄するまでの時間

//============================================
// 前方宣言
//============================================

//============================================
// Warningクラス
//============================================
class CWarning : public CObject2D
{
public:
	enum WARNINGTYPE
	{
		WARNINGTYPE_UI = 0,			//UI
		WARNINGTYPE_SCREEN,			//画面
		WARNINGTYPE_MAX
	};
public:
	CWarning();								//コンストラクタ
	~CWarning()override;					//デストラクタ

	HRESULT Init(void)override;				//Warningの初期化処理
	void Uninit(void)override;				//Warningの終了処理
	void Update(void)override;				//Warningの更新処理
	void Draw(void)override;				//Warningの描画処理

	WARNINGTYPE GetWarningType(void) { return WARNINGTYPE(); }	//Warningの種類の取得
	void SetWarningType(WARNINGTYPE type);						//Warningの種類の設定

	static CWarning *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, WARNINGTYPE type);	//生成

	static HRESULT Load(void);				//テクスチャの読み込み
	static void Unload(void);				//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXCOLOR m_col;									//色
	WARNINGTYPE m_type;									//Warningの種類

	int m_nUninitTimer;									//破棄までの時間
	bool m_flag;										//フラグ
};

#endif
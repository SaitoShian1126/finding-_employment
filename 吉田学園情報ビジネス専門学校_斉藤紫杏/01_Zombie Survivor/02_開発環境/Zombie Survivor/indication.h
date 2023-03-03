//============================================
//
//	indication.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _INDICATION_H_
#define _INDICATION_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================
#define INDICATION_SIZE_X		 (20.0f)	//表示のxサイズ
#define INDICATION_SIZE_Y		 (25.0f)	//表示のyサイズ
#define MAX_TEXTURE				 (4)		//テクスチャの最大数
#define RELEASE_TIME			 (300)		//破棄するまでの時間

//============================================
// 前方宣言
//============================================

//============================================
// 表示クラス
//============================================
class CIndication : public CObject2D
{
public:
	enum INDICATIONTYPE
	{
		INDICATIONTYPE_NONE = 0,
		INDICATIONTYPE_WAVE1,			//ウェーブ1の表示
		INDICATIONTYPE_WAVE2,			//ウェーブ2の表示
		INDICATIONTYPE_BLOOD,			//血しぶきの表示
		INDICATIONTYPE_MAX
	};
public:
	CIndication();							//コンストラクタ
	~CIndication()override;					//デストラクタ

	HRESULT Init(void)override;				//表示の初期化処理
	void Uninit(void)override;				//表示の終了処理
	void Update(void)override;				//表示の更新処理
	void Draw(void)override;				//表示の描画処理

	INDICATIONTYPE GetIndicationType(void) { return INDICATIONTYPE(); }	//表示の種類の取得
	void SetIndicationType(INDICATIONTYPE type);						//表示の種類の設定

	static CIndication *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, INDICATIONTYPE type);	//生成

	static HRESULT Load(void);				//テクスチャの読み込み
	static void Unload(void);				//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXCOLOR m_col;									//色
	INDICATIONTYPE m_nType;								//表示の種類
	int m_nUninitTimer;									//削除時間
	int m_Bomb;											//爆弾
	bool m_flag;										//フラグ
	bool m_ColorFlag;									//色のフラグ
	bool m_BloodFlag;									//血が出たかのフラグ
};

#endif
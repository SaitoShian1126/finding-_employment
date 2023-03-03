//============================================
//
//	ui.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _UI_H_
#define _UI_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// マクロ定義
//============================================

//============================================
// 前方宣言
//============================================
class CNumber;

//============================================
// UIクラス
//============================================
class CUi : public CObject2D
{
public:
	enum UITYPE
	{
		UITYPE_NUMBER = 0,
		UITYPE_BOMB,
		UITYPE_MAX
	};

	CUi();							//コンストラクタ
	~CUi()override;					//デストラクタ

	HRESULT Init(void)override;				//UIの初期化処理
	void Uninit(void)override;				//UIの終了処理
	void Update(void)override;				//UIの更新処理
	void Draw(void)override;				//UIの描画処理

	void SetBomb(int bomb);
	void AddBomb(int nValue);				//爆弾の数の加算処理
	void SubBomb(int nSubtract);			//爆弾の数の減算処理

	UITYPE GetUiType(void) { return m_type; }
	void SetUiType(UITYPE type) { m_type = type; }

	static CUi *Create(const D3DXVECTOR3 &pos,UITYPE type);	//生成

	static HRESULT Load(void);				//テクスチャの読み込み
	static void Unload(void);				//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXCOLOR m_col;						//色
	D3DXVECTOR3 m_size;						//サイズ
	CNumber *m_apNumber;					//スコアの数字(桁数)
	UITYPE m_type;							//UIの種類
	int m_nUninitTimer;						//削除時間
	int m_Bomb;								//爆弾
	bool m_flag;							//フラグ
	bool m_ColorFlag;						//色のフラグ
	bool m_BloodFlag;						//血が出たかのフラグ
};

#endif
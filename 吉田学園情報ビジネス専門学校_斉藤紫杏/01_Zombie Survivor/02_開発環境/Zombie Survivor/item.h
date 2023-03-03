//============================================
//
//	item.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _ITEM_H_
#define _ITEM_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// 前方宣言
//============================================

//============================================
// アイテムクラス
//============================================
class CItem : public CObjectBase
{
public:
	CItem();									//コンストラクタ
	~CItem() override;							//デストラクタ

	HRESULT Init(void)override;					//アイテムの初期化処理
	void Uninit(void)override;					//アイテムの終了処理
	void Update(void)override;					//アイテムの更新処理
	void Draw(void)override;					//アイテムの描画処理

	void HitItem(void);							//アイテムとプレイヤーが当たった時

	bool GetHitFlag(void) { return m_HitFlag; }			//当たったのかのフラグの取得処理
	void SetHitFlag(bool flag) { m_HitFlag = flag; }	//当たったのかのフラグの設定処理

	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);					//テクスチャの破棄

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTextureitem;		//テクスチャへのポインタ
	bool m_HitFlag;									//当たったのかのフラグ	
};

#endif
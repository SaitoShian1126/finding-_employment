//============================================
//
//	billboard.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectbase.h"
#include "shadow.h"

//============================================
// 前方宣言
//============================================

//============================================
// ビルボードクラス
//============================================
class CBillboard : public CObjectBase
{
public:
	CBillboard();									//コンストラクタ
	~CBillboard() override;							//デストラクタ

	HRESULT Init(void)override;						//ビルボードの初期化処理
	void Uninit(void)override;						//ビルボードの終了処理
	void Update(void)override;						//ビルボードの更新処理
	void Draw(void)override;						//ビルボードの描画処理

	void SetBillboardPos(D3DXVECTOR3 pos) { m_pos = pos; }	//ビルボードの位置設定
	D3DXVECTOR3 GetBillboardPos(void) { return m_pos; }		//ビルボードの位置取得
	static CBillboard *Create();							//生成

private:
	D3DXVECTOR3 m_pos;				//位置
};

#endif


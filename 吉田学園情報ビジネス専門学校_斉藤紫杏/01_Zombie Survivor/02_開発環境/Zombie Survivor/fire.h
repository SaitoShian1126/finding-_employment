//============================================
//
//	fire.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _FIRE_H_
#define _FIRE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// 前方宣言
//============================================

//============================================
// 炎クラス
//============================================
class CFire : public CObjectBase
{
public:
	CFire();									//コンストラクタ
	~CFire() override;							//デストラクタ

	HRESULT Init(void)override;						//炎の初期化処理
	void Uninit(void)override;						//炎の終了処理
	void Update(void)override;						//炎の更新処理
	void Draw(void)override;						//炎の描画処理

	static HRESULT Load(void);									//テクスチャの読み込み
	static void Unload(void);									//テクスチャの破棄

	static void SetfirePos(D3DXVECTOR3 pos) { m_pos = pos; }	//炎の位置設定
	static D3DXVECTOR3 GetfirePos(void) { return m_pos; }		//炎の位置取得
	static CFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTexturefire;		//テクスチャへのポインタ
	static D3DXVECTOR3 m_pos;						//位置

	int m_nCounterAnimfire;							//アニメーションカウンター
	int m_nPatternAnimfire;							//アニメーションXパターンNo.
	int m_nPatternAnimfireY;						//アニメーションYパターンNo.
};

#endif
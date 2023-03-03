//============================================
//
//	explosion.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// 前方宣言
//============================================

//============================================
// 爆発クラス
//============================================
class CExplosion : public CObjectBase
{
public:
	CExplosion();									//コンストラクタ
	~CExplosion() override;							//デストラクタ

	HRESULT Init(void)override;						//爆発の初期化処理
	void Uninit(void)override;						//爆発の終了処理
	void Update(void)override;						//爆発の更新処理
	void Draw(void)override;						//爆発の描画処理

	static void SetexplosionPos(D3DXVECTOR3 pos) { m_pos = pos; }	//爆発の位置設定
	static D3DXVECTOR3 GetexplosionPos(void) { return m_pos; }		//爆発の位置取得
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);	//生成

private:
	static LPDIRECT3DTEXTURE9 m_pTextureExplosion;		//テクスチャへのポインタ
	static D3DXVECTOR3 m_pos;							//位置

	int m_nCounterAnimExplosion;						//アニメーションカウンター
	int m_nPatternAnimExplosion;						//アニメーションXパターンNo.
	int m_nPatternAnimExplosionY;						//アニメーションYパターンNo.
};

#endif
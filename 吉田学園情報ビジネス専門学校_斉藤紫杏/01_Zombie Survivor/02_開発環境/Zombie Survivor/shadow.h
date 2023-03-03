//============================================
//
//	shadow.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object3d.h"

//============================================
// オブジェクトクラス
//============================================
class CShadow : public CObject3D
{
public:
	CShadow();						//コンストラクタ
	~CShadow();						//デストラクタ

	HRESULT Init(void)override;				//影の初期化処理
	void Uninit(void)override;				//影の終了処理
	void Update(void)override;				//影の更新処理
	void Draw(void)override;				//影の描画処理

	CShadow *SetTexture(char *pFile);
	static CShadow *Create(const D3DXVECTOR3 &pos);			//生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffShadow;			//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureShadow;				//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;									//位置

	bool m_Texture;
};

#endif

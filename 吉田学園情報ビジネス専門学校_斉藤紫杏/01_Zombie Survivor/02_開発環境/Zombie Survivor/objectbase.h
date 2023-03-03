//============================================
//
//	ObjectBase.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _OBJECTBASE_H_
#define _OBJECTBASE_H_

//============================================
// インクルード
//============================================
#include "main.h"
#include "object.h"

//============================================
// マクロ定義
//============================================

//============================================
// オブジェクト基礎クラス
//============================================
class CObjectBase : public CObject
{
public:
	CObjectBase();									//コンストラクタ
	~CObjectBase()override;							//デストラクタ

	HRESULT Init(void)override;						//オブジェクト基礎初期化処理
	void Uninit(void)override;						//オブジェクト基礎終了処理
	void Update(void)override;						//オブジェクト基礎更新処理
	void Draw(void)override;						//オブジェクト基礎描画処理

	CObjectBase *SetTexture(char *pFile);			//テクスチャの設定
	void SetTextureY(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);	//縦のテクスチャの設定

	void SetPosition(D3DXVECTOR3 pos)override;											//オブジェクト基礎位置
	void SetMove(D3DXVECTOR3 move)override;												//オブジェクト基礎移動
	void SetRot(D3DXVECTOR3 rot) { rot; }												//回転
	void SetSize(D3DXVECTOR3 size);														//オブジェクト基礎サイズ
	void SetLength(float length) { length; }											//拡大縮小のスケール
	void SetCol(D3DXCOLOR col) { m_ObjectBaseCol = col; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTextureObjectBase =pTexture; }	//テクスチャ反映
	float GetLength(void) override { return m_fLength; }								//拡大縮小のスケールの取得

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuffObjectBase; }				//バッファーの取得
	D3DXVECTOR3 GetPos(void) override { return m_ObjectBasePos; }						//位置の取得
	D3DXVECTOR3 GetMove(void) override { return m_ObjectBaseMove; }						//移動量の取得
	D3DXVECTOR3 GetSize(void) override { return m_ObjectBaseSize; }						//サイズの取得
	D3DXVECTOR3 GetRot(void) override { return m_ObjectBaseRot; }						//回転の取得

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffObjectBase;		//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureObjectBase;			//頂点バッファへのポインタ
	D3DXVECTOR3 m_ObjectBasePos;						//位置
	D3DXVECTOR3 m_ObjectBaseRot;						//向き
	D3DXVECTOR3	m_ObjectBaseMove;						//移動
	D3DXVECTOR3 m_ObjectBaseSize;						//サイズ
	D3DXCOLOR	m_ObjectBaseCol;						//色
	D3DXMATRIX m_ObjectBasemtxWorld;					//ワールドマトリックス

	int m_Life;											//体力

	float m_fLength;									//拡大縮小のスケール
	float m_Radius;										//半径

	bool m_ObjectBaseTexture;							//テクスチャの使用フラグ
};

#endif

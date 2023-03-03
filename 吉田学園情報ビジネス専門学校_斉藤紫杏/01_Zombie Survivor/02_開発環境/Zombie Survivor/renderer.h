//============================================
//
//	renderer.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _RENDERER_H_
#define  _RENDERER_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// 前方宣言
//============================================
class CCamera;

//============================================
// レンダリングクラス(描画クラス)
//============================================
class CRenderer
{
public:
	CRenderer();							//コンストラクタ
	~CRenderer();							//デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	LPDIRECT3DDEVICE9 GetDevice(void);		//デバイスの取得処理 

private:	
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;		//Deviceオブジェクト
	LPDIRECT3D9 m_pD3D = nullptr;					//Direct3Dオブジェクト
	LPD3DXFONT m_pFont = nullptr;					//フォント
	VERTEX_2D m_aVertex[4];							//頂点情報	
};

#endif




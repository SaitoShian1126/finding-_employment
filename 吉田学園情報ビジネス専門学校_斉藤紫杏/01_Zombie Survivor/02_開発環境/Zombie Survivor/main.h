//============================================
//
//	main.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _MAIN_H_
#define _MAIN_H_

//============================================
// ライブラリーリンク
//============================================
#define DIRECTINPUT_VERSION	(0x0800)	//ビルド時の警告対処用マクロ
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要
#pragma comment(lib,"dxguid.lib")

//============================================
// インクルード
//============================================
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include "dinput.h"				//入力処理に必要
#include "Xinput.h"				//ジョイパッド処理に必要
#include "xaudio2.h"			//サウンド処理に必要

//============================================
// 定数定義
//============================================
namespace
{
	// ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	// ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("Zombie Survivor");
}

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//座標,法線,カラー	※テクスチャも使う場合はここに追加(構造体にも追加)
// 線頂点フォーマット
const DWORD FVF_VERTEX_LINE = (D3DFVF_XYZ | D3DFVF_DIFFUSE);

//============================================
// 構造体定義
//============================================
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	//位置
	float rhw;			//rhw
	D3DCOLOR col;		//色
	D3DXVECTOR2 tex;	//テクスチャ
};

// 頂点データ
struct VERTEX_3D
{
	D3DXVECTOR3 pos;					//頂点座標
	D3DXVECTOR3 nor;					//法線ベクトル
	D3DCOLOR col;						//頂点カラー
	D3DXVECTOR2 tex;					//テクスチャ座標
};

//============================================
//	前方宣言
//============================================
class CRenderer;	//レンダリングクラス
class CObject;		//オブジェクトクラス

//============================================
// プロトタイプ宣言
//============================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS(void);				//FPSの取得処理

#endif

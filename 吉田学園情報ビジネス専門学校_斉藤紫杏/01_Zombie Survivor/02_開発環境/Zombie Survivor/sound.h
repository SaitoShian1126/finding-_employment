//=============================================================================
//
// サウンド処理 [sound.h]
// Author : saito shian
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_SHOT,				//撃つSE
	SOUND_LABEL_SE_HIT,					//被弾
	SOUND_LABEL_SE_RUN,					//走る
	SOUND_LABEL_SE_VOICE,				//ゾンビ声
	SOUND_LABEL_SE_DOG_VOICE,			//犬声
	SOUND_LABEL_SE_EXPLOTION,			//爆発
	SOUND_LABEL_SE_ROCKGIMMICK,			//岩のギミックのSE
	SOUND_LABEL_SE_BOSSATTACK,			//ボスの攻撃のSE
	SOUND_LABEL_SE_BOMB,				//爆弾のSE
	SOUND_LABEL_SE_BUTTOM,				//ボタンのSE
	SOUND_LABEL_TITLE,					//タイトルBGM
	SOUND_LABEL_SOUND,					//ゲーム内BGM
	SOUND_LABEL_GAMECLEAR,				//ゲームクリアBGM
	SOUND_LABEL_GAMEOVER,				//ゲームオーバーBGM
	SOUND_LABEL_RANKING,				//ランキングBGM
	SOUND_LABEL_MAX,	
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif



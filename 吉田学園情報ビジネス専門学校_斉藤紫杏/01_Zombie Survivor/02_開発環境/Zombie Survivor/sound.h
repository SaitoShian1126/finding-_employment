//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : saito shian
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_SHOT,				//����SE
	SOUND_LABEL_SE_HIT,					//��e
	SOUND_LABEL_SE_RUN,					//����
	SOUND_LABEL_SE_VOICE,				//�]���r��
	SOUND_LABEL_SE_DOG_VOICE,			//����
	SOUND_LABEL_SE_EXPLOTION,			//����
	SOUND_LABEL_SE_ROCKGIMMICK,			//��̃M�~�b�N��SE
	SOUND_LABEL_SE_BOSSATTACK,			//�{�X�̍U����SE
	SOUND_LABEL_SE_BOMB,				//���e��SE
	SOUND_LABEL_SE_BUTTOM,				//�{�^����SE
	SOUND_LABEL_TITLE,					//�^�C�g��BGM
	SOUND_LABEL_SOUND,					//�Q�[����BGM
	SOUND_LABEL_GAMECLEAR,				//�Q�[���N���ABGM
	SOUND_LABEL_GAMEOVER,				//�Q�[���I�[�o�[BGM
	SOUND_LABEL_RANKING,				//�����L���OBGM
	SOUND_LABEL_MAX,	
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif



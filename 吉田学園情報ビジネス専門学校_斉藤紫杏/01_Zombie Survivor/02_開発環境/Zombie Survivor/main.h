//============================================
//
//	main.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MAIN_H_
#define _MAIN_H_

//============================================
// ���C�u�����[�����N
//============================================
#define DIRECTINPUT_VERSION	(0x0800)	//�r���h���̌x���Ώ��p�}�N��
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�h�����ɕK�v
#pragma comment(lib,"dxguid.lib")

//============================================
// �C���N���[�h
//============================================
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include "dinput.h"				//���͏����ɕK�v
#include "Xinput.h"				//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"			//�T�E���h�����ɕK�v

//============================================
// �萔��`
//============================================
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("Zombie Survivor");
}

// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���W,�@��,�J���[	���e�N�X�`�����g���ꍇ�͂����ɒǉ�(�\���̂ɂ��ǉ�)
// �����_�t�H�[�}�b�g
const DWORD FVF_VERTEX_LINE = (D3DFVF_XYZ | D3DFVF_DIFFUSE);

//============================================
// �\���̒�`
//============================================
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	//�ʒu
	float rhw;			//rhw
	D3DCOLOR col;		//�F
	D3DXVECTOR2 tex;	//�e�N�X�`��
};

// ���_�f�[�^
struct VERTEX_3D
{
	D3DXVECTOR3 pos;					//���_���W
	D3DXVECTOR3 nor;					//�@���x�N�g��
	D3DCOLOR col;						//���_�J���[
	D3DXVECTOR2 tex;					//�e�N�X�`�����W
};

//============================================
//	�O���錾
//============================================
class CRenderer;	//�����_�����O�N���X
class CObject;		//�I�u�W�F�N�g�N���X

//============================================
// �v���g�^�C�v�錾
//============================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS(void);				//FPS�̎擾����

#endif

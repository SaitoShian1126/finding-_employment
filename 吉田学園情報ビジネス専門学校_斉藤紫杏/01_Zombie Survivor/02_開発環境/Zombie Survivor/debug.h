//============================================
//
//	debug.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �f�o�b�O�\���N���X
//============================================
class CDebugProc
{
public:
	CDebugProc();					//�R���X�g���N�^
	~CDebugProc();					//�f�X�g���N�^

	HRESULT Init(void);				//�f�o�b�O�\���̏���������
	void Uninit(void);				//�f�o�b�O�\���̏I������

	static void Print(const char *pFormat, ...);	//�f�o�b�O�\���֐�
	static void Draw(void);							//�f�o�b�O�\���̕`�揈��

private:
	static LPD3DXFONT m_pFont;	//�t�H���g
	static char m_aStr[0xfff];	//�\�����镶����
};

#endif
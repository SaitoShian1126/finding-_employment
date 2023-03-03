//============================================
//
//	tutorial.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "mode.h"

//============================================
// �O���錾
//============================================
class CObject2D;
class CFade;

//============================================
// �`���[�g���A���N���X
//============================================
class CTutorial : public CMode
{
public:
	CTutorial();				//�R���X�g���N�^
	~CTutorial();				//�f�X�g���N�^

	HRESULT Init(void);			//�`���[�g���A���̏���������
	void Uninit(void);			//�`���[�g���A���̏I������
	void Update(void);			//�`���[�g���A���̍X�V����
	void Draw(void);			//�`���[�g���A���̕`�揈��

	static CTutorial *Create();	//����

private:
	LPDIRECT3DTEXTURE9 m_pTextureTutorial;	//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject;					//�I�u�W�F�N�g�̃|�C���^
	CFade *m_pFade;							//�t�F�[�h
	bool m_BGMFlag;							//BGM�t���O
	bool m_flag;							//�t���O
};

#endif







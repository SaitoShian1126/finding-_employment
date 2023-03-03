//============================================
//
//	fade.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _FADE_H_
#define _FADE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2d.h"
#include "application.h"

//============================================
// �}�N����`
//============================================
#define  FADE_TIME	(60)	//�t�F�[�h�Ɋ|���鎞��

//============================================
// �t�F�[�h�N���X
//============================================
class CFade : public CObject2D
{
public:
	//============================================
	// �t�F�[�h�񋓌^
	//============================================
	enum FADETYPE
	{
		FADETYPE_NONE = 0,	//�������Ă��Ȃ����
		FADETYPE_IN,		//�t�F�[�hin
		FADETYE_OUT,		//�t�F�[�hout
		FADETYPE_MAX
	};

	CFade();												//�R���X�g���N�^
	~CFade() override;										//�f�X�g���N�^

	HRESULT Init(CApplication::MODE modenext);				//�t�F�[�h�̏���������
	void Uninit(void) override;								//�t�F�[�h�̏I������
	void Update(void) override;								//�t�F�[�h�̍X�V����

	static FADETYPE GetFade() { return m_Fade; }			//�t�F�[�h�̎擾����
	static D3DXCOLOR GetFadeCol() { return m_FadeColor; }	//�t�F�[�h�J���[�̎擾����

	static void SetFade(CApplication::MODE modenext);		//�t�F�[�h�̐ݒ菈��
	static CFade *Create(CApplication::MODE modenext);		//����

private:
	static CFade::FADETYPE m_Fade;			//�t�F�[�h�̏��
	static D3DXCOLOR m_FadeColor;			//�t�F�[�h�̐F
	static CApplication::MODE m_ModeNext;	//���̉��
	CObject2D *m_pObject;					//�I�u�W�F�N�g�̃|�C���^
};

#endif








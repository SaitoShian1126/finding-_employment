//============================================
//
//	fade.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "fade.h"
#include "application.h"
#include "renderer.h" 
#include "object3d.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
CFade::FADETYPE CFade::m_Fade = {};
D3DXCOLOR CFade::m_FadeColor = {};
CApplication::MODE CFade::m_ModeNext = {};

//============================================
// �t�F�[�h�̃R���X�g���N�^
//============================================
CFade::CFade() : CObject2D(PRIORITY_FADE)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	SetType(OBJTYPE_MODE);
}

//============================================
// �t�F�[�h�̃f�X�g���N�^
//============================================
CFade::~CFade()
{
	//���������Ȃ�
}

//============================================
// �t�F�[�h�̏���������
//============================================
HRESULT CFade::Init(CApplication::MODE modenext)
{
	CObject2D::Init();

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_Fade = FADETYPE_IN;								//�t�F�[�hin��Ԃ�
	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�����|���S���ɂ��Ă���
	m_ModeNext = modenext;								//���̉�ʂ�ݒ�

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f)); 
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));

	//���[�h�̐ݒ�
	CApplication::SetMode(m_ModeNext);

	return S_OK;
}

//============================================
// �t�F�[�h�̏I������
//============================================
void CFade::Uninit(void)
{
	CObject2D::Release();
}

//============================================
// �t�F�[�h�̍X�V����
//============================================
void CFade::Update()
{
	CObject2D::Update();

	if (m_Fade != FADETYPE_NONE)
	{
		if (m_Fade == FADETYPE_IN)
		{//�t�F�[�h�C����Ԃ�
			m_FadeColor.a -= 1.0f / FADE_TIME;			//�|���S���𓧖��ɂ��Ă���
			if (m_FadeColor.a <= 0.0f)
			{
				m_FadeColor.a = 0.0f;
				m_Fade = FADETYPE_NONE;					//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_Fade == FADETYE_OUT)
		{
			m_FadeColor.a += 1.0f / FADE_TIME;
			if (m_FadeColor.a >= 1.0f)
			{
				m_FadeColor.a = 1.0f;
				m_Fade = FADETYPE_IN;

				//���[�h�̐ݒ�
				CApplication::SetMode(m_ModeNext);
			}
		}
		SetColor(m_FadeColor.r, m_FadeColor.g, m_FadeColor.b, m_FadeColor.a);
	}
}

//============================================
// �t�F�[�h�̐ݒ菈��
//============================================
void CFade::SetFade(CApplication::MODE modenext)
{
	m_Fade = FADETYE_OUT;
	m_ModeNext = modenext;

	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//============================================
// �t�F�[�h�̐���
//============================================
CFade *CFade::Create(CApplication::MODE modenext)
{
	CFade *pFade = nullptr;

	//�N���X�̐���
	pFade = new CFade;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pFade != nullptr)
	{
		//����������
		pFade->Init(modenext);
	}
	else
	{
		assert(false);
	}

	return pFade;
}
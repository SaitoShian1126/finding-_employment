//============================================
//
//	warning.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "warning.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CWarning::m_pTexture[MAX_TEXTURE] = {};

//============================================
// Warning�̃R���X�g���N�^
//============================================
CWarning::CWarning() : CObject2D(PRIORITY_LEVEL5)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�F�̃N���A
}

//============================================
// Warning�̃f�X�g���N�^
//============================================
CWarning::~CWarning()
{
	//���������Ȃ�
}

//============================================
// Warning�̏���������
//============================================
HRESULT CWarning::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//�F�̏�����
	m_nUninitTimer = RELEASE_TIME;					//�j������܂ł̎��Ԃ̏�����
	m_flag = false;									//�t���O�̏�����

	//============================================
	// Warning�̎��
	//============================================
	switch (m_type)
	{
	case CWarning::WARNINGTYPE_UI:
		BindTexture(m_pTexture[0]);
		break;
	case CWarning::WARNINGTYPE_SCREEN:
		BindTexture(m_pTexture[1]);
		break;
	case CWarning::WARNINGTYPE_MAX:
		break;
	default:
		break;
	}

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//============================================
// Warning�̏I������
//============================================
void CWarning::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//============================================
// Warning�̍X�V����
//============================================
void CWarning::Update()
{
	//============================================
	// �{�X�o����Warning
	//============================================
	if (m_type == WARNINGTYPE_UI)
	{
		m_nUninitTimer--;
		if (m_flag == false)
		{
			m_col.a += 0.001f;
		}

		if (m_col.a >= 1.0f)
		{
			m_flag = true;
		}
		if (m_flag == true)
		{
			m_col.a -= 0.001f;
			if (m_col.a <= 0.5f)
			{
				m_flag = false;
			}
		}
		if (m_nUninitTimer <= 0)
		{
			Uninit();
			return;
		}

		//�F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}

	if (m_type == WARNINGTYPE_SCREEN)
	{
		m_nUninitTimer--;
		if (m_flag == false)
		{
			m_col.a += 0.025f;
		}

		if (m_col.a >= 0.5f)
		{
			m_flag = true;
		}
		if (m_flag == true)
		{
			m_col.a -= 0.025f;
			if (m_col.a <= 0.0f)
			{
				m_flag = false;
			}
		}
		if (m_nUninitTimer <= 0)
		{
			Uninit();
			return;
		}

		//�F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}
}

//============================================
// Warning�̕`�揈��
//============================================
void CWarning::Draw()
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//============================================
// Warning�̐���
//============================================
CWarning *CWarning::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, WARNINGTYPE type)
{
	CWarning *pwarning = nullptr;

	//�N���X�̐���
	pwarning = new CWarning;				//Warning�̃C���X�^���X����

	//null�`�F�b�N
	if (pwarning != nullptr)
	{
		pwarning->SetWarningType(type);		//Warning�̎�ނ̐ݒ菈��
		pwarning->Init();					//����������
		pwarning->SetPosition(pos);			//�ʒu�̐ݒ�
		pwarning->SetSize(size);			//�T�C�Y�̐ݒ�
	}
	else
	{
		assert(false);
	}

	return pwarning;
}

//============================================
// �e�N�X�`���̓ǂݍ���
//============================================
HRESULT CWarning::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/warning.png",
		&m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/�x��1.png",
		&m_pTexture[1]);

	return S_OK;
}

//============================================
// �e�N�X�`���̔j��
//============================================
void CWarning::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//============================================
// Warning�̐ݒ�
//============================================
void CWarning::SetWarningType(WARNINGTYPE type)
{
	m_type = type;
}
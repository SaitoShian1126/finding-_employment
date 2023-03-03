//============================================
//
//	indication.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "indication.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CIndication::m_pTexture[MAX_TEXTURE] = {};

//============================================
// �\���̃R���X�g���N�^
//============================================
CIndication::CIndication() : CObject2D(PRIORITY_LEVEL4)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�F�̃N���A
	m_nUninitTimer = 0;								//�j������܂ł̎��Ԃ̃N���A
	m_flag = false;									//�t���O�̃N���A
	m_ColorFlag = false;							//�F�̃t���O�̃N���A
	m_BloodFlag = false;							//���̃t���O�̃N���A
}

//============================================
// �\���̃f�X�g���N�^
//============================================
CIndication::~CIndication()
{
	//���������Ȃ�
}

//============================================
// �\���̏���������
//============================================
HRESULT CIndication::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//�F�̏�����
	m_nUninitTimer = RELEASE_TIME;					//�j������܂ł̎��Ԃ̏�����
	m_flag = false;									//�t���O�̏�����
	m_ColorFlag = false;							//�F�̃t���O�̏�����
	m_BloodFlag = false;							//���̃t���O�̏�����

	//============================================
	// �\���̎��
	//============================================
	switch (m_nType)
	{
	case INDICATIONTYPE_WAVE1:
		//�e�N�X�`�����f
		BindTexture(m_pTexture[0]);		//wave1�̃e�N�X�`��
		break;
	case INDICATIONTYPE_WAVE2:
		//�e�N�X�`�����f
		BindTexture(m_pTexture[1]);		//wave2�̃e�N�X�`��
		break;
	case INDICATIONTYPE_BLOOD:
		//�e�N�X�`�����f
		BindTexture(m_pTexture[2]);		//���̃e�N�X�`��
		break;
	default:
		break;
	}

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//============================================
// �\���̏I������
//============================================
void CIndication::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//============================================
// �\���̍X�V����
//============================================
void CIndication::Update()
{
	//�W���C�p�b�h�̃C���X�^���X
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	//============================================
	// wave1��wave2�̕\��
	//============================================
	if (m_nType == INDICATIONTYPE_WAVE1 || m_nType == INDICATIONTYPE_WAVE2)
	{
		if (m_flag == false)
		{
			m_col.a += 0.01f;
		}

		if (m_col.a >= 1.0f)
		{
			m_flag = true;
			m_nUninitTimer--;
		}
		if (m_nUninitTimer <= 0 && m_flag == true)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				Uninit();
				return;
			}
		}

		//�F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}

	//============================================
	// ���̕\��
	//============================================
	if (m_nType == INDICATIONTYPE_BLOOD)
	{
		if (m_ColorFlag == false)
		{
			m_col.a = 1.0f;
			m_ColorFlag = true;
		}
		m_nUninitTimer--;
		if (m_nUninitTimer <= 0 && m_ColorFlag == true)
		{
			m_col.a -= 0.005f;
			if (m_col.a <= 0.0f)
			{
				Uninit();
				return;
			}
		}
		//�F�̐ݒ�
		SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));
	}
}

//============================================
// �\���̕`�揈��
//============================================
void CIndication::Draw()
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//============================================
// �\���̐���
//============================================
CIndication *CIndication::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, INDICATIONTYPE type)
{
	CIndication *pIndication = nullptr;

	//�N���X�̐���
	pIndication = new CIndication;				//�\���̃C���X�^���X����

	//null�`�F�b�N
	if (pIndication != nullptr)
	{
		pIndication->SetIndicationType(type);	//�\���̎�ނ̐ݒ菈��
		pIndication->Init();					//����������
		pIndication->SetPosition(pos);			//�ʒu�̐ݒ�
		pIndication->SetSize(size);				//�T�C�Y�̐ݒ�
	}
	else
	{
		assert(false);
	}

	return pIndication;
}

//============================================
// �e�N�X�`���̓ǂݍ���
//============================================
HRESULT CIndication::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wave1.png",
		&m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wave2.png",
		&m_pTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/blood.png",
		&m_pTexture[2]);

	return S_OK;
}

//============================================
// �e�N�X�`���̔j��
//============================================
void CIndication::Unload(void)
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
// �\���̐ݒ�
//============================================
void CIndication::SetIndicationType(INDICATIONTYPE type)
{
	m_nType = type;
}
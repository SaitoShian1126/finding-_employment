//============================================
//
//	enter.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "enter.h"
#include "application.h"
#include "renderer.h"
#include "explosion.h"
#include "fade.h"
#include "input.h"
#include "player.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CEnter::m_pTextureenter = {};

//============================================
// enter�̃R���X�g���N�^
//============================================
CEnter::CEnter() : CObject2D(4)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// enter�̃f�X�g���N�^
//============================================
CEnter::~CEnter()
{
	//���������Ȃ�
}

//============================================
// enter�̏���������
//============================================
HRESULT CEnter::Init(void)
{
	CObject2D::Init();

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PRESS ENTER1.png",
		&m_pTextureenter);

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_nCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nType = TYPE_IN;
	m_nCount = 50;

	BindTexture(m_pTextureenter);
	return S_OK;
}

//============================================
// enter�̏I������
//============================================
void CEnter::Uninit(void)
{
	CObject2D::Uninit();
}

//============================================
// enter�̍X�V����
//============================================
void CEnter::Update()
{
	m_nCount--;
	if (m_nType == TYPE_IN && m_nCount <= 0)
	{
		m_nCol.a = 0.0f;
		m_nType = TYPE_OUT; 
		m_nCount = 50;
	}
	else if (m_nType == TYPE_OUT && m_nCount <= 0)
	{
		m_nCol.a = 1.0f;
		m_nType = TYPE_IN;
		m_nCount = 50;
	}
	SetColor(m_nCol.r, m_nCol.g, m_nCol.b, m_nCol.a);
}

//============================================
// enter�̕`�揈��
//============================================
void CEnter::Draw()
{
	CObject2D::Draw();
}

//============================================
// �X�|�[���̐���
//============================================
CEnter *CEnter::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size)
{
	CEnter *penter = nullptr;

	//�N���X�̐���
	penter = new CEnter;				//2D�I�u�W�F�N�g�̃C���X�^���X����

								//null�`�F�b�N
	if (penter != nullptr)
	{
		//����������
		penter->Init();
		//�ݒ菈��
		penter->SetPosition(pos);
		penter->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return penter;
}

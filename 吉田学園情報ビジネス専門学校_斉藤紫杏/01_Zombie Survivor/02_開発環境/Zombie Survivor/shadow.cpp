//============================================
//
//	shadow.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "objectX.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "shadow.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �e�̃R���X�g���N�^
//============================================
CShadow::CShadow()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================ 
}

//============================================
// �e�̃f�X�g���N�^
//============================================
CShadow::~CShadow()
{
}

//============================================
// �e�̏���������
//============================================
HRESULT CShadow::Init(void)
{
	CObject3D::Init();

	//============================================
	//�����o�ϐ��̏�����
	//============================================

	//�e�N�X�`���̎g�p��false�ɂ���
	m_Texture = false;
	//�e�N�X�`���̐ݒ�
	SetTexture("data/TEXTURE/shadow000.jpg");

	return S_OK;
}

//============================================
// �e�̏I������
//============================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//============================================
// �e�̍X�V����
//============================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//============================================
// �e�̕`�揈��
//============================================
void CShadow::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	//���Z�����̐ݒ�
	//============================================
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//============================================
	//���Z���������ɖ߂�
	//============================================
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================
// �e�̃e�N�X�`���̐ݒ�
//============================================
CShadow * CShadow::SetTexture(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureShadow);

	BindTexture(m_pTextureShadow);

	m_Texture = true;

	return S_OK;
}

//============================================
// �e�̐���
//============================================
CShadow * CShadow::Create(const D3DXVECTOR3 & pos)
{
	CShadow *pShadow = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pShadow = new CShadow;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pShadow != nullptr)
	{
		//����������
		pShadow->Init();
		//�ݒ菈��
		pShadow->SetPosition(pos);
		pShadow->SetSize(D3DXVECTOR3(100.0f, 1.0f, 100.0f));
	}
	else
	{
		assert(false);
	}
	return pShadow;
}

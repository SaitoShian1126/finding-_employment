//============================================
//
//	reticle.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "reticle.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CReticle::m_pTexture = nullptr;

//============================================
// ���e�B�N���̃R���X�g���N�^
//============================================
CReticle::CReticle() : CObject2D(PRIORITY_LEVEL5)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�F�̃N���A
}

//============================================
// ���e�B�N���̃f�X�g���N�^
//============================================
CReticle::~CReticle()
{
	//���������Ȃ�
}

//============================================
// ���e�B�N���̏���������
//============================================
HRESULT CReticle::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		//�F�̏�����

	//�e�N�X�`���̔��f
	BindTexture(m_pTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	return S_OK;
}

//============================================
// ���e�B�N���̏I������
//============================================
void CReticle::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//============================================
// ���e�B�N���̍X�V����
//============================================
void CReticle::Update()
{

}

//============================================
// ���e�B�N���̕`�揈��
//============================================
void CReticle::Draw()
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//============================================
// ���e�B�N���̐���
//============================================
CReticle *CReticle::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size)
{
	CReticle *pReticle = nullptr;

	//�N���X�̐���
	pReticle = new CReticle;				//���e�B�N���̃C���X�^���X����

	//null�`�F�b�N
	if (pReticle != nullptr)
	{
		pReticle->Init();					//����������
		pReticle->SetPosition(pos);			//�ʒu�̐ݒ�
		pReticle->SetSize(size);			//�T�C�Y�̐ݒ�
	}
	else
	{
		assert(false);
	}

	return pReticle;
}

//============================================
// �e�N�X�`���̓ǂݍ���
//============================================
HRESULT CReticle::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/���e�B�N��.png",
		&m_pTexture);
	return S_OK;
}

//============================================
// �e�N�X�`���̔j��
//============================================
void CReticle::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
//============================================
//
//	ui.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "ui.h"
#include "application.h"
#include "renderer.h"
#include "number.h"
#include "input.h"
#include "game.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture = nullptr;

//============================================
// �\���̃R���X�g���N�^
//============================================
CUi::CUi() : CObject2D(PRIORITY_LEVEL3)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_nUninitTimer = 100;
	m_flag = false;
	m_ColorFlag = false;
	m_BloodFlag = false;
}

//============================================
// �\���̃f�X�g���N�^
//============================================
CUi::~CUi()
{
	//���������Ȃ�
}

//============================================
// �\���̏���������
//============================================
HRESULT CUi::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_size = D3DXVECTOR3(55.0f, 35.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nUninitTimer = 100;
	m_Bomb = 3;
	m_flag = false;
	m_ColorFlag = false;
	m_BloodFlag = false;
	m_apNumber = nullptr;

	switch (m_type)
	{
	case CUi::UITYPE_NUMBER:
		m_apNumber = CNumber::Create(D3DXVECTOR3(570.0f, 670.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CNumber::NUMBERTYPE_BOMB);		//�i���o�[�̐���
		break;
	case CUi::UITYPE_BOMB:
		BindTexture(m_pTexture);
		break;
	case CUi::UITYPE_MAX:
		break;
	default:
		break;
	}
	
	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();
	SetSize(m_size);

	return S_OK;
}

//============================================
// �\���̏I������
//============================================
void CUi::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//============================================
// �\���̍X�V����
//============================================
void CUi::Update()
{

}

//============================================
// �\���̕`�揈��
//============================================
void CUi::Draw()
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//============================================
// �X�|�[���̐���
//============================================
CUi *CUi::Create(const D3DXVECTOR3 &pos, UITYPE type)
{
	CUi *pScene = nullptr;

	//�N���X�̐���
	pScene = new CUi;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pScene != nullptr)
	{
		pScene->SetUiType(type);
		//����������
		pScene->Init();
		//�ݒ菈��
		pScene->SetPosition(pos);
	}
	else
	{
		assert(false);
	}

	return pScene;
}

//============================================
// �e�N�X�`���̓ǂݍ���
//============================================
HRESULT CUi::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/���e1.png",
		&m_pTexture);

	return S_OK;
}

//============================================
// �e�N�X�`���̔j��
//============================================
void CUi::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//============================================
// �c��̔��e�̐ݒ�
//============================================
void CUi::SetBomb(int bomb)
{
	int aPosTexU = m_Bomb;	//�e���̔��e�̐����i�[
	m_Bomb = bomb;

	aPosTexU = m_Bomb % 10 / 1;

	//������,���Ԗڂ�
	m_apNumber->SetTexture(10.0f, (float)aPosTexU, 1.0f, 0.0f);
}

//============================================
// ���e�̐��̉��Z����
//============================================
void CUi::AddBomb(int nValue)
{
	//�����o�ϐ��ɃX�R�A�����Z
	SetBomb(m_Bomb + nValue);
}

//============================================
// ���e�̐��̌��Z����
//============================================
void CUi::SubBomb(int nSubtract)
{
	//�����o�ϐ��ɃX�R�A�����Z
	SetBomb(m_Bomb - nSubtract);
}

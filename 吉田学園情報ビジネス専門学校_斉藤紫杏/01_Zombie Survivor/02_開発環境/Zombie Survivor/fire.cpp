//============================================
//
//	fire.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "fire.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CFire::m_pTexturefire = nullptr;
D3DXVECTOR3 CFire::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//============================================
// ���̃R���X�g���N�^
//============================================
CFire::CFire()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_nCounterAnimfire = 0;						//�J�E���g�A�j���[�V�����̃N���A
	m_nPatternAnimfire = 0;						//�p�^�[���A�j���[�V�����̃N���A
	m_nPatternAnimfireY = 0;					//Y�p�^�[���A�j���[�V�����̃N���A
}

//============================================
// ���̃f�X�g���N�^
//============================================
CFire::~CFire()
{
}

//============================================
// ���̏���������
//============================================
HRESULT CFire::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_nCounterAnimfire = 0;						//�J�E���g�A�j���[�V�����̏�����
	m_nPatternAnimfire = 0;						//�p�^�[���A�j���[�V�����̏�����
	m_nPatternAnimfireY = 0;					//Y�p�^�[���A�j���[�V�����̏�����

	//�I�u�W�F�N�g��b�̏���������
	CObjectBase::Init();

	BindTexture(m_pTexturefire);
	SetTextureY(5.0f, 0.0f, 4.0f, 0.0f);

	return S_OK;
}

//============================================
// ���̏I������
//============================================
void CFire::Uninit(void)
{
	if (m_pTexturefire != nullptr)
	{
		//�I�u�W�F�N�g��b�̏I������
		CObjectBase::Uninit();
	}
}

//============================================
// ���̍X�V����
//============================================
void CFire::Update(void)
{
	//============================================
	//	���̃A�j���[�V����
	//============================================
	//objectbase�̍X�V�����֐��Ăяo��
	CObjectBase::Update();

	//�A�j���[�V�����J�E���^�[���C���N�������g
	m_nCounterAnimfire++;

	if (m_nCounterAnimfire % 10 == 0)
	{
		//�e�N�X�`���̐ݒ�
		SetTextureY(5.0f, (float)m_nPatternAnimfire, 4.0f, (float)m_nPatternAnimfireY);

		//�A�j���[�V�����p�^�[���̃C���N������
		m_nPatternAnimfire++;
	}

	//�A�j���[�V�����p�^�[�����Ō�܂ōs�����烋�[�v
	else if (m_nPatternAnimfire == 5.0f)
	{
		m_nPatternAnimfire = 0;
		m_nPatternAnimfireY++;
		m_nPatternAnimfire++;
		if (m_nPatternAnimfireY == 4.0f)
		{
			m_nPatternAnimfireY = 0.0f;
		}
	}
}

//============================================
// ���̕`�揈��
//============================================
void CFire::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CObjectBase::Draw();
}

//============================================
// ���̃e�N�X�`���ǂݍ���
//============================================
HRESULT CFire::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/��.png",
		&m_pTexturefire);

	return S_OK;
}

//============================================
// ���̃e�N�X�`���j��
//============================================
void CFire::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexturefire != nullptr)
	{
		m_pTexturefire->Release();
		m_pTexturefire = nullptr;
	}
}

//============================================
// ���̐���
//============================================
CFire * CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFire *pfire = nullptr;

	//���̐���
	pfire = new CFire;				//���̃C���X�^���X����

	//null�`�F�b�N
	if (pfire != nullptr)
	{
		//����������
		pfire->Init();
		pfire->SetPosition(pos);
		pfire->SetSize(size);
	}
	else
	{
		assert(false);
	}
	return pfire;
}
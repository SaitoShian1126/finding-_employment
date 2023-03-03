//============================================
//
//	explosion.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "explosion.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion = nullptr;
D3DXVECTOR3 CExplosion::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//============================================
// �����̃R���X�g���N�^
//============================================
CExplosion::CExplosion()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_nCounterAnimExplosion = 0;						//�J�E���g�A�j���[�V�����̃N���A
	m_nPatternAnimExplosion = 0;						//�p�^�[���A�j���[�V�����̃N���A
	m_nPatternAnimExplosionY = 0;						//Y�p�^�[���A�j���[�V�����̃N���A
}

//============================================
// �����̃f�X�g���N�^
//============================================
CExplosion::~CExplosion()
{
}

//============================================
// �����̏���������
//============================================
HRESULT CExplosion::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_nCounterAnimExplosion = 0;						//�J�E���g�A�j���[�V�����̏�����
	m_nPatternAnimExplosion = 0;						//�p�^�[���A�j���[�V�����̏�����
	m_nPatternAnimExplosionY = 0;						//Y�p�^�[���A�j���[�V�����̏�����

	//�I�u�W�F�N�g��b�̏���������
	CObjectBase::Init();

	SetTexture("data/TEXTURE/����.png");
	SetTextureY(8.0f, 0.0f, 2.0f, 0.0f);

	return S_OK;
}

//============================================
// �����̏I������
//============================================
void CExplosion::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CObjectBase::Uninit();
}

//============================================
// �����̍X�V����
//============================================
void CExplosion::Update(void)
{
	//============================================
	//	�����̃A�j���[�V����
	//============================================
	//objectbase�̍X�V�����֐��Ăяo��
	CObjectBase::Update();

	//�A�j���[�V�����J�E���^�[���C���N�������g
	m_nCounterAnimExplosion++;

	if (m_nCounterAnimExplosion % 5 == 0)
	{
		//�e�N�X�`���̐ݒ�
		SetTextureY(8.0f, (float)m_nPatternAnimExplosion, 2.0f, (float)m_nPatternAnimExplosionY);

		//�A�j���[�V�����p�^�[���̃C���N������
		m_nPatternAnimExplosion++;
	}

	//�A�j���[�V�����p�^�[�����Ō�܂ōs������I��
	else if (m_nPatternAnimExplosion == 8.0f)
	{
		m_nPatternAnimExplosion = 0;
		m_nPatternAnimExplosionY++;
		m_nPatternAnimExplosion++;
		if (m_nPatternAnimExplosionY == 2.0f)
		{
			Uninit();	//�g�p����ĂȂ�
			return;
		}
	}
}

//============================================
// �����̕`�揈��
//============================================
void CExplosion::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CObjectBase::Draw();
}

//============================================
// �����̐���
//============================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pexplosion = nullptr;

	//�����̐���
	pexplosion = new CExplosion;				//�����̃C���X�^���X����

	//null�`�F�b�N
	if (pexplosion != nullptr)
	{
		//����������
		pexplosion->Init();
		pexplosion->SetPosition(pos);
		pexplosion->SetSize(size);
	}
	else
	{
		assert(false);
	}
	return pexplosion;
}
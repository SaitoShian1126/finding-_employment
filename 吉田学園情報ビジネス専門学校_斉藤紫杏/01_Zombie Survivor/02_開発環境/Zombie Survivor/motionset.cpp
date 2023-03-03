//============================================
//
//	motionset.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include <stdio.h>
#include "motionset.h"
#include "application.h"
#include "renderer.h"
#include "keyset.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// ���[�V�����ݒ�̃R���X�g���N�^
//============================================
CMotionSet::CMotionSet()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_Loop = false;							//���[�v
	m_Num_Key = 0;							//�L�[�̐�
	m_NumParts = 0;							//�p�[�c�̎��
	m_apKeySet[KEY_NUMBER] = {};		//KeySet�\���̂̔z��
}

//============================================
// �L�[�̃f�X�g���N�^
//============================================
CMotionSet::~CMotionSet()
{
	//���������Ȃ�
}

//============================================
// �L�[�̏���������
//============================================
HRESULT CMotionSet::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_Loop = 0;								//���[�v
	m_Num_Key = 0;							//�L�[�̐�
	m_NumParts = 0;							//�p�[�c�̎��

	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		//�L�[�ݒ�̐���
		m_apKeySet[nCnt] = CKeySet::Create();
	}

	return S_OK;
}

//============================================
// �L�[�ݒ�̏I������
//============================================
void CMotionSet::Uninit()
{
	//�L�[�̏I������
	for (int nCnt = 0; nCnt < KEY_NUMBER; nCnt++)
	{
		if (m_apKeySet[nCnt] != nullptr)
		{
			m_apKeySet[nCnt]->Uninit();
			delete m_apKeySet[nCnt];
			m_apKeySet[nCnt] = nullptr;
		}
	}
}

//============================================
// ����
//============================================
CMotionSet * CMotionSet::Create()
{
	CMotionSet *pMotionSet = nullptr;

	// 3D�I�u�W�F�N�g�N���X�̐���
	pMotionSet = new CMotionSet;				// 3D�I�u�W�F�N�g�̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pMotionSet != nullptr)
	{
		// ����������
		pMotionSet->Init();
	}
	else
	{
		assert(false);
	}
	return pMotionSet;
}
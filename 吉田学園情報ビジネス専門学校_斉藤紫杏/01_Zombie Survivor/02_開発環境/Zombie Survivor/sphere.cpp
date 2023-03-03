//============================================
//
//	Sphere.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "sphere.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CSphere::CSphere()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_RotDest = {};
	m_Move = {};
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CSphere::~CSphere()
{
	//���������Ȃ�
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CSphere::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_RotDest = {};
	m_Move = {};

	CObjectX::Init();

	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CSphere::Uninit(void)
{
	CObjectX::Uninit();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CSphere::Update(void)
{
	//�C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
//	CMeshField *pMeshField = CGame::GetMeshField();
	D3DXVECTOR3 CameraRot = CCamera::GetCameraRot();
	D3DXVECTOR3 SpherePos = GetPos();
	D3DXVECTOR3 SphereRot = GetRot();

	CObjectX::Update();

	//�����
	if (pInput->GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			SpherePos.x -= sinf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//�ړ���
			SpherePos.z -= cosf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//�ړ���
			m_RotDest.y = (CameraRot.y + D3DX_PI * 0.75f);						//�����p�x
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			SpherePos.x += sinf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//�ړ���
			SpherePos.z += cosf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//�ړ���
			m_RotDest.y = (CameraRot.y - D3DX_PI * 0.75f);						//�����p�x
		}
		else
		{
			SpherePos.x += sinf(CameraRot.y) * SPHERE_MOVE;						//�ړ���
			SpherePos.z += cosf(CameraRot.y) * SPHERE_MOVE;						//�ړ���
			//m_RotDest.y = (CameraRot.y + D3DX_PI);							//�����p�x

			SphereRot.x += (cosf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
			SphereRot.z += (sinf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
		}
	}
	//������
	else if (pInput->GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			SpherePos.x -= sinf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//�ړ���
			SpherePos.z -= cosf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//�ړ���
			m_RotDest.y = (CameraRot.y + D3DX_PI * 0.25f);						//�����p�x
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			SpherePos.x += sinf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//�ړ���
			SpherePos.z += cosf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//�ړ���
			m_RotDest.y = (CameraRot.y - D3DX_PI * 0.25f);						//�����p�x
		}
		else
		{
			SpherePos.x -= sinf(CameraRot.y) * SPHERE_MOVE;						//�ړ���
			SpherePos.z -= cosf(CameraRot.y) * SPHERE_MOVE;						//�ړ���
			//m_RotDest.y = CameraRot.y;										//�����p�x

			SphereRot.x -= (cosf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
			SphereRot.z -= (sinf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
		}
	}
	//������
	else if (pInput->GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		SpherePos.x -= sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//�ړ���
		SpherePos.z -= cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//�ړ���
		//m_RotDest.y = (CameraRot.y + D3DX_PI / 2);							//�����p�x

		SphereRot.x -= (cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
		SphereRot.z -= (sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
	}
	//�E����
	else if (pInput->GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		SpherePos.x += sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//�ړ���
		SpherePos.z += cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//�ړ���
		//m_RotDest.y = (CameraRot.y - D3DX_PI / 2);							//�����p�x

		SphereRot.x += (cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
		SphereRot.z += (sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
	}

	//============================================
	// �ړI�̊p�x�̐��K��
	//============================================
	if (m_RotDest.y - SphereRot.y > D3DX_PI)
	{
		m_RotDest.y = m_RotDest.y - D3DX_PI * 2;
	}
	else if (m_RotDest.y - SphereRot.y < -D3DX_PI)
	{
		m_RotDest.y = m_RotDest.y + D3DX_PI * 2;
	}

	//�p�x����
	//SphereRot.y += (m_RotDest.y - SphereRot.y) * 0.1f;

	//============================================
	// �p�x�̐��K��
	//============================================
	if (SphereRot.y > D3DX_PI)
	{
		SphereRot.y = SphereRot.y - D3DX_PI * 2;
	}
	else if (SphereRot.y < -D3DX_PI)
	{
		SphereRot.y = SphereRot.y + D3DX_PI * 2;
	}

//	pMeshField->GetMeshFieldCollision(&SpherePos);
	SetPosition(SpherePos);
	SetRot(SphereRot);
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CSphere::Draw(void)
{
	CObjectX::Draw();
}

//============================================
// ����
//============================================
CSphere * CSphere::Create(const D3DXVECTOR3 &pos)
{
	CSphere *pSphere = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pSphere = new CSphere;				//3D�I�u�W�F�N�g�̃C���X�^���X����

										//null�`�F�b�N
	if (pSphere != nullptr)
	{
		//����������
		pSphere->Init();
		pSphere->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pSphere;
}

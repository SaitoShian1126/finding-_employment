//============================================
//
//	camera.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <time.h>
#include <math.h>
#include <assert.h>
#include "camera.h"
#include "application.h"
#include "renderer.h" 
#include "object3d.h"
#include "fade.h"
#include "input.h"
#include "application.h"
#include "player.h"
#include "debug.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
D3DXVECTOR3 CCamera::m_Rot = {};

//============================================
// �J�����̃R���X�g���N�^
//============================================
CCamera::CCamera()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �J�����̃f�X�g���N�^
//============================================
CCamera::~CCamera()
{
	//���������Ȃ�
}

//============================================
// �J�����̏���������
//============================================
HRESULT CCamera::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================

	//����
	srand((unsigned int)time(nullptr));			//�N�����Ɉ�񂾂��s�����ߏ������ɏ���
	m_nQuakeFrameCount = 0;
	m_fQuakeMagnitude = 0;

	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_OffsetV = D3DXVECTOR3(0.0f,75.0f,150.0f);
	m_OffsetR = D3DXVECTOR3(0.0f, 0.0f, -150.0f);

	m_PosVDest = D3DXVECTOR3(0.0f, 100.0f, -150.0f);
	m_PosRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//<-�Œ�ŗǂ�

	//�O�����̒藝(sqrtf�̓��[�g�̖���)
	m_fDistance = sqrtf(((m_PosRDest.x - m_PosVDest.x) * (m_PosRDest.x - m_PosVDest.x)) + ((m_PosRDest.z - m_PosVDest.z) * (m_PosRDest.z - m_PosVDest.z)));

	return S_OK;
}

//============================================
// �J�����̏I������
//============================================
void CCamera::Uninit(void)
{

}

//============================================
// �J�����̍X�V����
//============================================
void CCamera::Update()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
	D3DXVECTOR3 PlayerRot = CPlayer::GetPlayerRot();	//�v���C���[�̌����̎擾
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();	//�v���C���[�̈ʒu�̎擾

	//============================================
	// �J�����̒Ǐ]����
	//============================================
	//�ړI�̒����_�̐ݒ�
	m_PosDest = PlayerPos;

	//���_�̌�������
	m_pos.x += (m_PosDest.x - m_pos.x) * 1.0f;
	m_pos.y += (m_PosDest.y - m_pos.y) * 1.0f;
	m_pos.z += (m_PosDest.z - m_pos.z) * 1.0f;

	//============================================
	// �J�����̉�]����
	//============================================
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);													//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, PlayerRot.y, PlayerRot.x, PlayerRot.z);		//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);								//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);						//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�x�N�g���ϊ�
	D3DXVec3TransformCoord(&m_PosVDest, &m_OffsetV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_PosRDest, &m_OffsetR, &m_mtxWorld);

	//============================================
	// �G�C���������̎��_����
	//============================================
	//���_�̌���
	m_PosV.x += (m_PosVDest.x - m_PosV.x) * 0.1f;
	m_PosV.y += (m_PosVDest.y - m_PosV.y) * 0.1f;
	m_PosV.z += (m_PosVDest.z - m_PosV.z) * 0.1f;
					
	//�����_�̌���
	m_PosR.x += (m_PosRDest.x - m_PosR.x) * 0.1f;
	m_PosR.y += (m_PosRDest.y - m_PosR.y) * 0.1f;
	m_PosR.z += (m_PosRDest.z - m_PosR.z) * 0.1f;

	//============================================
	// �J�����̌����Ă�����Ɉړ��ł��鏈��
	//============================================
	m_Rot.y = atan2(m_PosR.x - m_PosV.x,m_PosR.z - m_PosV.z);

	//============================================
	// �f�o�b�N�\��
	//============================================
	/*CDebugProc::Print("�J�����̎��_ : %.3f,%.3f,%.3f\n", m_PosVDest.x, m_PosVDest.y, m_PosVDest.z);
	CDebugProc::Print("�J�����̒����_ : %.3f,%.3f,%.3f\n", m_PosRDest.x, m_PosRDest.y, m_PosRDest.z);*/
}

//============================================
// �J�����̐ݒ�
//============================================
void CCamera::SetCamera()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 adjustPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nQuakeFrameCount > 0)
	{
		m_nQuakeFrameCount--;
		////�����ŗh��̑傫����ς���
		adjustPos.x = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.y = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.z = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
	}
	//�r���[�}�g���b�N�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�̐���
	D3DXVECTOR3 PosV = (adjustPos + m_PosV);
	D3DXVECTOR3 PosR = (adjustPos + m_PosR);

	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,
		&PosR,
		&m_VecU);

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,

		D3DXToRadian(45.0f),									//����p
		(float)m_Viewport.Width / (float)m_Viewport.Height,		//�A�X�y�N�g��
		10.0f,													//�j�A
		5000.0f);												//�t�@�[

	//�v���W�F�N�V�����}�g���b�N�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//============================================
// �����̐ݒ�
//============================================
void CCamera::SetOffset(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_OffsetV = posV;
	m_OffsetR = posR;
}

//============================================
// �h��̐ݒ�
//============================================
void CCamera::SetShakeCamera(int QuakeFrame, int QuakeMagnitude)
{
	m_nQuakeFrameCount = QuakeFrame;
	m_fQuakeMagnitude = QuakeMagnitude;
}

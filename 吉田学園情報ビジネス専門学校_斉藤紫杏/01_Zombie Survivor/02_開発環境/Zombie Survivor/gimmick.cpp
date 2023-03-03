//============================================
//
//	gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "gimmick.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "gasolene_gimmick.h"
#include "application.h"
#include "renderer.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �M�~�b�N�̃R���X�g���N�^
//============================================
CGimmick::CGimmick()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �M�~�b�N�̃f�X�g���N�^
//============================================
CGimmick::~CGimmick()
{
	//���������Ȃ�
}

//============================================
// �M�~�b�N�̏���������
//============================================
HRESULT CGimmick::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f���^�C�v
	SetType(OBJTYPE_GIMMICK);

	return S_OK;
}

//============================================
// �M�~�b�N�̏I������
//============================================
void CGimmick::Uninit(void)
{
	//���b�V���̔j��
	if (m_Mesh != nullptr)
	{
		m_Mesh->Release();
		m_Mesh = nullptr;
	}
	//�}�e���A���̔j��
	if (m_BuffMat != nullptr)
	{
		m_BuffMat->Release();
		m_BuffMat = nullptr;
	}

	//�j������
	Release();
}

//============================================
// �M�~�b�N�̍X�V����
//============================================
void CGimmick::Update(void)
{
	SetPosition(m_pos);
	SetMove(m_move);
}

//============================================
// �M�~�b�N�̕`�揈��
//============================================
void CGimmick::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);									//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ShadowDraw();	//�e�̕`��

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);					//���[���h���W�s��̐ݒ�

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		m_Mesh->DrawSubset(nCntMat);
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//============================================
// �e�̕`��
//============================================
void CGimmick::ShadowDraw(void)
{
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DMATERIAL9 Material;

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = D3DXVECTOR4(-1.0f, 1.0f, 0.5f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);	//�@���ƕ��ʂ�1�_���畽�ʂ��쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);	//���C�g�ƕ��ʂ���e�s����쐬

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);					//���[���h���W�s��̐ݒ�

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�}�e���A���̕ۑ�
		Material = pMat[nCntMat].MatD3D;

		//�F�����ɂ���
		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Material);

		//���f���p�[�c�̕`��
		m_Mesh->DrawSubset(nCntMat);
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//============================================
// ���f���̐ݒ�
//============================================
CGimmick * CGimmick::SetModel(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&m_Mesh);

	return S_OK;
}

//============================================
// �ʒu�̐ݒ�
//============================================
void CGimmick::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �ړ��̐ݒ�
//============================================
void CGimmick::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// �ʒu�̎擾����
//============================================
D3DXVECTOR3 CGimmick::GetPos(void)
{
	return m_pos;
}

//============================================
// �T�C�Y�̎擾����
//============================================
D3DXVECTOR3 CGimmick::GetSize(void)
{
	return m_size;
}

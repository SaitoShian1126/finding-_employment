//============================================
//
//	objectX.cpp
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
#include "player.h"
#include "camera.h"

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CObjectX::~CObjectX()
{
	//���������Ȃ�
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CObjectX::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_nNumMat = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//�����̏����ݒ�

	//���f���̎g�p��false�ɂ���
	m_Model = false;
	//SetModel("data/XMODEL/car.x");
	
	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CObjectX::Uninit(void)
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

	//���f���̔j��
	if (m_Model == true)
	{
		m_Model = false;
	}

	//�j������
	Release();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CObjectX::Update(void)
{
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CObjectX::Draw(void)
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

	ShadowDraw();

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
// ����
//============================================
CObjectX * CObjectX::Create(const D3DXVECTOR3 & pos)
{
	CObjectX *pObjectX = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pObjectX = new CObjectX;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pObjectX != nullptr)
	{
		//����������
		pObjectX->Init();
		//�ݒ菈��
		pObjectX->SetPosition(pos);
		pObjectX->SetSize(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	}
	else
	{
		assert(false);
	}
	return pObjectX;
}

//============================================
// ���f���̐ݒ�
//============================================
CObjectX * CObjectX::SetModel(char * pFile)
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

	m_Model = true;

	return S_OK;
}

//============================================
// �|���S���̐ݒ菈��
//============================================
void CObjectX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �I�u�W�F�N�gx�̉�]�̐ݒ菈��
//============================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// �e�̕`��
//============================================
void CObjectX::ShadowDraw(void)
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

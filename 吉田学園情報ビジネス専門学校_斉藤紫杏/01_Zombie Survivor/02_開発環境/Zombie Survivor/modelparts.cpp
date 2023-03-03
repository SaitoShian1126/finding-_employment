//============================================
//
//	modelparts.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include <stdio.h>
#include "modelparts.h"
#include "application.h"
#include "renderer.h"
#include "line.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// ���f���p�[�c�̃R���X�g���N�^
//============================================
CModelParts::CModelParts()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pMesh = {};
	m_pBuffMat = {};
	m_pNumMat = {};
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	nIdxModelParent = 0;
}

//============================================
// ���f���p�[�c�̃f�X�g���N�^
//============================================
CModelParts::~CModelParts()
{
	//���������Ȃ�
}

//============================================
// ���f���p�[�c�̏���������
//============================================
HRESULT CModelParts::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pMesh = {};
	m_pBuffMat = {};
	m_pNumMat = {};
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	nIdxModelParent = 0;
	m_LineUseFlag = false;
	return S_OK;
}

//============================================
// ���f���p�[�c�̏I������
//============================================
void CModelParts::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{	  
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{	  
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	////�e�N�X�`���̔j��
	//for (int nCnt = 0; nCnt < (int)m_pNumMat; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != nullptr)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = nullptr;
	//	}
	//}

	//if (m_pTexture != nullptr)
	//{
	//	delete[] m_pTexture;
	//	m_pTexture = nullptr;
	//}
}

//============================================
// ���f���p�[�c�̍X�V����
//============================================
void CModelParts::Update(void)
{
	if (m_LineUseFlag == false)
	{
		//���̐�
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));

		//��̐�							  							 																				 			   				
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z));

		//�c�̐�						  						 														 									   				
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMinModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMinModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMaxModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMaxModel.z));
		CLine::Create(m_pos, m_rot, D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMaxModel.y, m_VtxMinModel.z), D3DXVECTOR3(m_VtxMaxModel.x, m_VtxMinModel.y, m_VtxMinModel.z));
		m_LineUseFlag = true;
	}
}

//============================================
// ���f���p�[�c�̕`�揈��
//============================================
void CModelParts::DrawFile(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_pmtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);							//���[���h���W�s��̐ݒ�

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef); 

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//============================================
// �}�g���b�N�X�̎擾
//============================================
D3DXMATRIX * CModelParts::GetMatrix(void)
{
	return &m_mtxWorld;
}

//============================================
// ���b�V���̎擾
//============================================
LPD3DXMESH CModelParts::GetMesh(void)
{
	return m_pMesh;
}

//============================================
// �}�g���b�N�X�̐ݒ�
//============================================
void CModelParts::SetMatrix(D3DXMATRIX * matrixparent)
{
	m_pmtxParent = matrixparent;
}

//============================================
// �ʒu�̎擾
//============================================
D3DXVECTOR3 CModelParts::GetPos(void)
{
	return m_pos;
}

//============================================
// �ő�̎擾
//============================================
D3DXVECTOR3 CModelParts::GetVtxMax(void)
{
	return m_VtxMaxModel;
}

//============================================
// �ŏ��̎擾
//============================================
D3DXVECTOR3 CModelParts::GetVtxMin(void)
{
	return m_VtxMinModel;
}

//============================================
// �ʒu�̐ݒ�
//============================================
void CModelParts::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �����̎擾
//============================================
D3DXVECTOR3 CModelParts::GetRot(void)
{
	return m_rot;
}

//============================================
// �����̐ݒ�
//============================================
void CModelParts::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// �ő�̐ݒ�
//============================================
void CModelParts::SetVtxMax(D3DXVECTOR3 max)
{
	m_VtxMaxModel = max;
}

//============================================
// �ŏ��̐ݒ�
//============================================
void CModelParts::SetVtxMin(D3DXVECTOR3 min)
{
	m_VtxMinModel = min;
}

//============================================
// ����
//============================================
CModelParts * CModelParts::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelParts *pModelParts = nullptr;

	// 3D�I�u�W�F�N�g�N���X�̐���
	pModelParts = new CModelParts;				// 3D�I�u�W�F�N�g�̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pModelParts != nullptr)
	{
		// ����������
		pModelParts->Init();
		pModelParts->m_pos = pos;
		pModelParts->m_rot = rot;
	}
	else
	{
		assert(false);
	}
	return pModelParts;
}

//============================================
// ���f���̐ݒ�
//============================================
void CModelParts::SetModel(char * pFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_pNumMat,
		&m_pMesh);

	//// �e�N�X�`��
	//m_pTexture = new LPDIRECT3DTEXTURE9[m_pNumMat];

	////��񂪓����ĂȂ�������
	//assert(m_pTexture != nullptr);

	//// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	//D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//// �e���b�V���̃}�e���A�������擾����
	//for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	//{
	//	//���̏�����
	//	m_pTexture[nCntMat] = nullptr;

	//	//�|���S���ɓ\��t����e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(pDevice,
	//		pMat[nCntMat].pTextureFilename,
	//		&m_pTexture[nCntMat]);
	//}
}

//============================================
// ���f���̓����蔻��
//============================================
void CModelParts::ModelCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size)
{
	//���̓����蔻��
	if (pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z
		&&pPosOld->x + size.x / 2.0f <= m_pos.x + m_VtxMinModel.x
		&&pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x)
	{
		pPos->x = m_pos.x + m_VtxMinModel.x - size.x / 2.0f;
	}
	//�E�̓����蔻��
	if (pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z
		&&pPosOld->x - size.x / 2.0f >= m_pos.x + m_VtxMaxModel.x
		&&pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x)
	{
		pPos->x = m_pos.x + m_VtxMaxModel.x + size.x / 2.0f;
	}
	//��O�̓����蔻��
	if (pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x
		&&pPosOld->z + size.z / 2.0f <= m_pos.z + m_VtxMinModel.z
		&&pPos->z + size.z / 2.0f > m_pos.z + m_VtxMinModel.z)
	{
		pPos->z = m_pos.z + m_VtxMinModel.z - size.z / 2.0f;
	}

	//���̓����蔻��
	if (pPos->x - size.x / 2.0f < m_pos.x + m_VtxMaxModel.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_VtxMinModel.x
		&&pPosOld->z - size.z / 2.0f >= m_pos.z + m_VtxMaxModel.z
		&&pPos->z - size.z / 2.0f < m_pos.z + m_VtxMaxModel.z)
	{
		pPos->z = m_pos.z + m_VtxMaxModel.z + size.z / 2.0f;
	}
}

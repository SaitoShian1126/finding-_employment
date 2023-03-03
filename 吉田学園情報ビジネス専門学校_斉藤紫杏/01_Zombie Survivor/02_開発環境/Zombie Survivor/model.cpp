//============================================
// 
// 	model.cpp
// 	Author: saito shian
// 
//============================================

//============================================
// �C���N���[�h
//============================================
#include <stdio.h>
#include <assert.h>
#include "model.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"
#include "modelparts.h"
#include "keyset.h"
#include "key.h"
#include "motionset.h"
#include "score.h"
#include "line.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// ���f���̃R���X�g���N�^
//============================================
CModel::CModel()
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
}

//============================================
// ���f���̃f�X�g���N�^
//============================================
CModel::~CModel()
{
	// ���������Ȃ�
}

//============================================
// ���f��(�|���S��)�̏���������
//============================================
HRESULT CModel::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountModel = 0;
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	//���f���̃t�@�C���ǂݍ���
	LoadModel();

	//���_�̍ő�ŏ�
	Vtx();

	return S_OK;
}

//============================================
// ���f��(�|���S��)�̏I������
//============================================
void CModel::Uninit(void)
{
	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//============================================
// ���f��(�|���S��)�̍X�V����
//============================================
void CModel::Update(void)
{
	/*for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt])
		{
			m_apModel[nCnt]->Update();
		}
	}*/
}

//============================================
// ���f��(�|���S��)�̕`�揈��
//============================================
void CModel::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[�J���}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���f���p�[�c��for��
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->DrawFile();
		}
	}
}

//============================================
// ����
//============================================
CModel * CModel::Create()
{
	CModel *pModel = nullptr;

	// 3D���f���N���X�̐���
	pModel = new CModel;				// 3D���f���̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pModel != nullptr)
	{
		// ����������
		pModel->Init();
	}
	else
	{
		assert(false);
	}
	return pModel;
}

//============================================
// �O���t�@�C���ǂݍ���
//============================================
void CModel::LoadModel()
{
	int nNumParts;
	char aText[2000];						//��������i�[����z��
	char FileName[NUMBER_OF_MODELS][2000];		//2�����z��

	FILE *pFile; //�t�@�C���|�C���^��錾

	pFile = fopen("data/XMODEL/model.txt", "r");

	aText[0] = '\0';	//������Ȃ�

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���ɓ��͂����f�[�^�������o������
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fgets(aText, MAX_MODEL_WORD, pFile);        //��s���Ɠǂݍ���
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_MODEL_WORD, pFile);        //��s���Ɠǂݍ���
				continue;
			}

			//�t�@�C���l�[���𕡐����͂���
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
				fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0�Ԗڂ���ǂݍ��܂��

				//���f���p�[�c�̐���
				m_apModel[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nCountModel++;
			}

			if (strcmp(&aText[0], "MODELSET") == 0)
			{
				D3DXVECTOR3 pos, rot;
				int Ind = 0;

				while (strcmp(&aText[0], "END_MODELSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_MODEL_WORD, pFile);        //��s���Ɠǂݍ���
						continue;
					}

					if (strcmp(&aText[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%d", &Ind);

						m_ModelNumber = Ind;
					}

					else if (strcmp(&aText[0], "POS") == 0)
					{
						float x = 0.0f;
						float y = 0.0f;
						float z = 0.0f;
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &x);
						fscanf(pFile, "%f", &y);
						fscanf(pFile, "%f", &z);
						pos = D3DXVECTOR3(x, y, z);
					}

					else if (strcmp(&aText[0], "ROT") == 0)
					{
						float x = 0.0f;
						float y = 0.0f;
						float z = 0.0f;
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &x);
						fscanf(pFile, "%f", &y);
						fscanf(pFile, "%f", &z);
						rot = D3DXVECTOR3(x, y, z);
					}
				}

				//���f���p�[�c�̐���
				m_apModel[Ind] = CModelParts::Create(pos,rot);

				//���f���p�[�c�̓ǂݍ���
				m_apModel[Ind]->SetModel(&FileName[Ind][0]);

				//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
				m_apModel[Ind]->SetMatrix(&m_mtxWorld);
			}
		}
	}
}

//============================================
// ���_�̍ő�ŏ�
//============================================
void CModel::Vtx(void)
{
	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = m_apModel[nCnt]->GetMesh()->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_apModel[nCnt]->GetMesh()->GetFVF());

		//���_�o�b�t�@�̃��b�N
		m_apModel[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		D3DXVECTOR3 min = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		D3DXVECTOR3 max = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ŏ��l�A�ő�l���擾
			//x�̔�r
			if (vtx.x < min.x)
			{
				min.x = vtx.x;
			}
			if (vtx.x > max.x)
			{
				max.x = vtx.x;
			}

			//y�̔�r(�ŏ��l)
			if (vtx.y < min.y)
			{
				min.y = vtx.y;
			}
			if (vtx.y > max.y)
			{
				max.y = vtx.y;
			}

			//z�̔�r(�ŏ��l)
			if (vtx.z < min.z)
			{
				min.z = vtx.z;
			}
			if (vtx.z > max.z)
			{
				max.z = vtx.z;
			}
			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		m_apModel[nCnt]->GetMesh()->UnlockVertexBuffer();

		m_apModel[nCnt]->SetVtxMin(min);
		m_apModel[nCnt]->SetVtxMax(max);

	}
}

//============================================
// �z�񃂃f���p�[�c�̎擾
//============================================
CModelParts ** CModel::GetModelParts(void)
{
	return m_apModel;
}

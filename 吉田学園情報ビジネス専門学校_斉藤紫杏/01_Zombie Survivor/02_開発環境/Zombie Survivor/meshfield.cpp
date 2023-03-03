//============================================
//
//	meshfield.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include <time.h>
#include "meshfield.h"
#include "renderer.h"
#include "object.h"
#include "application.h"

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pVtxBuffMeshField = nullptr;				//�o�b�t�@�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�̃N���A
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F�̃N���A
	m_fWidth = 0.0f;							//���̃N���A
	m_fHeight = 0.0f;							//�����̃N���A
	m_fLength = 0;								//�g��k���̃X�P�[���̃N���A
	m_fAngle = 0;								//�p�x�̃N���A
	m_nTimer = 0;								//���Ԃ̃N���A
	m_RandFlag = false;							//�����_���̃N���A
	m_fRotMove = 0;								//�����̃N���A
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CMeshField::~CMeshField()
{
	//���������Ȃ�
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CMeshField::Init(void)
{
	//����
	srand((unsigned int)time(nullptr));											//�N�����Ɉ�񂾂��s�����ߏ������ɏ���	
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_pVtxBuffMeshField = nullptr;												//�o�b�t�@�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ʒu�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ړ��̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//��]�̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);									//�F�̏�����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�T�C�Y
	m_fWidth = 25.0f;															//���̏�����
	m_fHeight = 25.0f;															//�����̏�����
	m_fLength = sqrtf(((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_fWidth, m_fHeight);										//�p�x�̏�����
	m_nTimer = 0;																//���Ԃ̏�����
	m_RandFlag = false;															//�����_���t���O��false
	m_fRotMove = 5.0f;															//�����̃N���A

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̎g�p��false�ɂ���
	m_Texture = false;
	//�e�N�X�`���̐ݒ�
	SetTexture("data/TEXTURE/��.jpeg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMeshField,
		nullptr);

	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�̓ǂݍ���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,	//�C���f�b�N�X���̌v�Z�}�N����`
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffMeshField,
		nullptr);

	//z�����̌J��Ԃ�
	for (int nCntMeshFieldZ = 0; nCntMeshFieldZ < MESHFIELD_Z_BLOCK + 1; nCntMeshFieldZ++)
	{
		//x�����̌J��Ԃ�
		for (int nCntMeshFieldX = 0; nCntMeshFieldX < MESHFIELD_X_BLOCK + 1; nCntMeshFieldX++)
		{
			//m_nVtxRand = (float)sin(nCntMeshFieldX * 0.5f) * 60;
			m_nVtxRand = rand() % 40 + 0;
			//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-150.0f + (nCntMeshFieldX * 15.0f), 0.0f, 150.0f - (nCntMeshFieldZ * 15.0f));
			//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[�̐ݒ�						
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�				  
			pVtx[nCntMeshFieldX + (nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCntMeshFieldX, (float)nCntMeshFieldZ);
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);
	int nCntMeshFieldX = 0;

	//�C���f�b�N�X�̐ݒ�
	//z�����̌J��Ԃ�
	for (int nCntMeshFieldZ = 0; nCntMeshFieldZ < MESHFIELD_Z_BLOCK; nCntMeshFieldZ++)
	{
		//x�����̌J��Ԃ�
		for (nCntMeshFieldX = 0; nCntMeshFieldX < MESHFIELD_X_BLOCK + 1; nCntMeshFieldX++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCntMeshFieldX + nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCntMeshFieldX + nCntMeshFieldZ * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);
			pIdx += 2;	//pIdx��2���Z����
		}
		//�k�ރ|���S���̐ݒ�
		if (nCntMeshFieldZ != MESHFIELD_Z_BLOCK)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) * nCntMeshFieldZ + MESHFIELD_X_BLOCK;
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) * (nCntMeshFieldZ + 2);
			pIdx += 2;	//pIdx��2���Z����
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshField->Unlock();

	//���_�o�b�t�@�����b�N
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE - 2; nCnt++)
	{
		//Idx��pos
		IdxPosNor[0] = pVtx[pIdx[nCnt]].pos;
		IdxPosNor[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPosNor[2] = pVtx[pIdx[nCnt + 2]].pos;

		//�k�ރ|���S���̔���𖳎����鏈��
		if (pIdx[nCnt] == pIdx[nCnt + 1] || pIdx[nCnt + 1] == pIdx[nCnt + 2] || pIdx[nCnt + 2] == pIdx[nCnt])
		{
			continue;
		}

		//3�����O�ς̌v�Z
		Calculation3DNor[0] = IdxPosNor[1] - IdxPosNor[0];
		Calculation3DNor[1] = IdxPosNor[2] - IdxPosNor[0];
		D3DXVec3Cross(&VecAnswer, &Calculation3DNor[0], &Calculation3DNor[1]);

		//���K��
		D3DXVec3Normalize(&VecAnswer, &VecAnswer);

		if (nCnt % 2 == 1)
		{
			VecAnswer *= -1;
		}

		//�ۑ��p�z��ɖ@���x�N�g����ۑ�
		SaveVtxNor[pIdx[nCnt]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 1]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 2]] += VecAnswer;

		//���K��
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt]], &SaveVtxNor[pIdx[nCnt]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 1]], &SaveVtxNor[pIdx[nCnt + 1]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 2]], &SaveVtxNor[pIdx[nCnt + 2]]);

		//�@��
		pVtx[pIdx[nCnt]].nor = SaveVtxNor[pIdx[nCnt]];
		pVtx[pIdx[nCnt + 1]].nor = SaveVtxNor[pIdx[nCnt + 1]];
		pVtx[pIdx[nCnt + 2]].nor = SaveVtxNor[pIdx[nCnt + 2]];
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshField->Unlock();
	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffMeshField != nullptr)
	{
		m_pVtxBuffMeshField->Release();
		m_pVtxBuffMeshField = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuffMeshField != nullptr)
	{
		m_pIdxBuffMeshField->Release();
		m_pIdxBuffMeshField = nullptr;
	}

	//�j������
	Release();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CMeshField::Update(void)
{

}
//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CMeshField::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldMeshField);									//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);	//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);					//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureMeshField);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX, 0, MESHFIELD_PRIMITIVE);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}

//============================================
// �|���S���̐ݒ菈��
//============================================
void CMeshField::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �|���S���̈ړ�
//============================================
void CMeshField::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//============================================
// �|���S���̃T�C�Y�̐ݒ菈��
//============================================
void CMeshField::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// �|���S���̉�]�̐ݒ菈��
//============================================
void CMeshField::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//============================================
// �|���S���̒����̐ݒ菈��
//============================================
void CMeshField::SetLength(float length)
{
	m_fLength = length;
}
//============================================
// ����
//============================================
CMeshField *CMeshField::Create(const D3DXVECTOR3 &pos)
{
	CMeshField *pmeshfield = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pmeshfield = new CMeshField;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	//nullptr�`�F�b�N
	if (pmeshfield != nullptr)
	{
		//����������
		pmeshfield->Init();
		//�ݒ菈��
		pmeshfield->SetPosition(pos);
		pmeshfield->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		assert(false);
	}
	return pmeshfield;
}

//============================================
// �e�N�X�`���̐ݒ�
//============================================
CMeshField * CMeshField::SetTexture(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureMeshField);

	m_Texture = true;

	return S_OK;
}

//============================================
// �e�N�X�`�����f
//============================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTextureMeshField = pTexture;
}
//============================================
// �c�e�N�X�`���摜�̐ݒ�
//============================================
void CMeshField::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshField->Unlock();
}

//============================================
// �F�̐ݒ�
//============================================
void CMeshField::SetColor(float Red, float Green, float Blue, float ��)
{
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Red, Green, Blue, ��);
	pVtx[1].col = D3DXCOLOR(Red, Green, Blue, ��);
	pVtx[2].col = D3DXCOLOR(Red, Green, Blue, ��);
	pVtx[3].col = D3DXCOLOR(Red, Green, Blue, ��);

	//���_�o�b�t�@���A�����b�N����
	Buffer->Unlock();
}

//============================================
// �v���C���[�ƃ��b�V���t�B�[���h�̓����蔻��
//============================================
void CMeshField::GetMeshFieldCollision(D3DXVECTOR3 *PlayerPos)
{
	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;
	WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idx��pos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB
	D3DXVECTOR3 Calculation3D[2];		//3�����O�ς̌v�Z����
	float Calculation2D[3];				//2�����O�ς̌v�Z����
	D3DXVECTOR3 Answer;					//�O�ς̌v�Z����
	D3DXVECTOR3 PlayerDist;				//�v���C���[�ƒ��_�̋���

	//���_�o�b�t�@�����b�N
	m_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE - 2; nCnt++)
	{
		//Idx��pos
		IdxPos[0] = pVtx[pIdx[nCnt]].pos;
		IdxPos[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPos[2] = pVtx[pIdx[nCnt + 2]].pos;

		//�v���C���[�ƒ��_�̋����̌v�Z
		PlayerDist = *PlayerPos - IdxPos[0];
		D3DXVec3Length(&PlayerDist);

		//�k�ރ|���S���̔���𖳎����鏈��
		if (IdxPos[0] == IdxPos[1] || IdxPos[1] == IdxPos[2] || IdxPos[2] == IdxPos[0])
		{
			continue;
		}
		
		//������30.0f�ȉ���������ŏ�����
		if (30.0f <= D3DXVec3Length(&PlayerDist))
		{
			continue;
		}

		//VecA
		VecA[0] = IdxPos[1] - IdxPos[0];
		VecA[1] = IdxPos[2] - IdxPos[1];
		VecA[2] = IdxPos[0] - IdxPos[2];

		//VecB
		VecB[0] = *PlayerPos - (IdxPos[0] + m_pos);
		VecB[1] = *PlayerPos - (IdxPos[1] + m_pos);
		VecB[2] = *PlayerPos - (IdxPos[2] + m_pos);

		//2�����O�ς̌v�Z����
		Calculation2D[0] = VecA[0].x *VecB[0].z - VecB[0].x * VecA[0].z;
		Calculation2D[1] = VecA[1].x *VecB[1].z - VecB[1].x * VecA[1].z;
		Calculation2D[2] = VecA[2].x *VecB[2].z - VecB[2].x * VecA[2].z;

		//�v���C���[�̈ʒu���S��-��+
		if ((Calculation2D[0] >= 0 && Calculation2D[1] >= 0 && Calculation2D[2] >= 0) || (Calculation2D[0] <= 0 && Calculation2D[1] <= 0 && Calculation2D[2] <= 0))
		{
			//3�����O�ς̌v�Z
			Calculation3D[0] = IdxPos[1] - IdxPos[0];
			Calculation3D[1] = IdxPos[2] - IdxPos[0];
			D3DXVec3Cross(&Answer, &Calculation3D[0], &Calculation3D[1]);

			//���K��
			D3DXVec3Normalize(&Answer, &Answer);

			//���ς̌v�Z
			PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshField->Unlock();
	//���_�o�b�t�@���A�����b�N
	m_pIdxBuffMeshField->Unlock();
}

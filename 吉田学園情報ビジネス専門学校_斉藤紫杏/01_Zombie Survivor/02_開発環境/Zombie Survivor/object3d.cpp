//============================================
//
//	object3D.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "object3d.h"
#include "renderer.h"
#include "object.h"
#include "application.h"

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pVtxBuffMeshPolygon = nullptr;			//�o�b�t�@�̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�̃N���A
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F�̃N���A
	m_fWidth = 0.0f;							//���̃N���A
	m_fHeight = 0.0f;							//�����̃N���A
	m_fLength = 0;								//�g��k���̃X�P�[���̃N���A
	m_fAngle = 0;								//�p�x�̃N���A
	m_nTimer = 0;								//���Ԃ̃N���A
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CObject3D::~CObject3D()
{
	//���������Ȃ�
}
//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CObject3D::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pVtxBuffMeshPolygon = nullptr;											//�o�b�t�@�̏�����
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

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̎g�p��false�ɂ���
	m_Texture = false;
	//�e�N�X�`���̐ݒ�
	SetTexture("data/TEXTURE/field001.jpg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMeshPolygon,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, -m_size.z);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshPolygon->Unlock();

	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffMeshPolygon != NULL)
	{
		m_pVtxBuffMeshPolygon->Release();
		m_pVtxBuffMeshPolygon = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuffMeshPolygon != NULL)
	{	
		m_pIdxBuffMeshPolygon->Release();
		m_pIdxBuffMeshPolygon = NULL;
	}

	//�j������
	Release();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CObject3D::Update(void)
{
	SetPosition(m_pos);
	SetSize(m_size);
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CObject3D::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldMeshPolygon);										//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);				//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorldMeshPolygon, &m_mtxWorldMeshPolygon, &mtxRot);	//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);					//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorldMeshPolygon, &m_mtxWorldMeshPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshPolygon);						//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffMeshPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureMeshPolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//============================================
// �|���S���̐ݒ菈��
//============================================
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �|���S���̈ړ�
//============================================
void CObject3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// �|���S���̃T�C�Y�̐ݒ菈��
//============================================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	m_size = size;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̍X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// �|���S���̉�]�̐ݒ菈��
//============================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// �|���S���̒����̐ݒ菈��
//============================================
void CObject3D::SetLength(float length)
{
	m_fLength = length;

	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;	//�g��k���̃X�P�[���̏�����
	m_fAngle = atan2f(m_size.y, m_size.x);									//�p�x�̏�����

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle)*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle)*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle)*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle)*m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle)*m_fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// ����
//============================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 &pos)
{
	CObject3D *pObject3D = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pObject3D = new CObject3D;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pObject3D != nullptr)
	{
		//����������
		pObject3D->Init();
		//�ݒ菈��
		pObject3D->SetPosition(pos);
		pObject3D->SetSize(D3DXVECTOR3(100.0f, 0.5f, 100.0f));
		pObject3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		assert(false);
	}
	return pObject3D;
}

//============================================
// �e�N�X�`���̐ݒ�
//============================================
CObject3D * CObject3D::SetTexture(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureMeshPolygon);

	m_Texture = true;

	return S_OK;
}

//============================================
// �e�N�X�`�����f
//============================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTextureMeshPolygon = pTexture;
}

//============================================
// �c�e�N�X�`���摜�̐ݒ�
//============================================
void CObject3D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffMeshPolygon->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffMeshPolygon->Unlock();
}

//============================================
// �F�̐ݒ�
//============================================
void CObject3D::SetColor(float Red, float Green, float Blue, float ��)
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

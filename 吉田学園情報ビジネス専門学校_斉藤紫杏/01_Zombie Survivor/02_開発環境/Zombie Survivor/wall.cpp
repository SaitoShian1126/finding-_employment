//============================================
//
//	wall.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "wall.h"
#include "player.h"
#include "game.h"
#include "mode.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CWall::m_pTexture = nullptr;

//============================================
// �R���X�g���N�^
//============================================
CWall::CWall()
{
}

//============================================
// �f�X�g���N�^
//============================================
CWall::~CWall()
{
}

//============================================
// ������
//============================================
HRESULT CWall::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_size = D3DXVECTOR3(100.0f,0.0f,40.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// �I��
//============================================
void CWall::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�j������
	Release();
}

//============================================
// �X�V
//============================================
void CWall::Update()
{

}

//============================================
// �`��
//============================================
void CWall::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);										//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);				//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);	//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);					//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);						//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//============================================
// �ʒu�̐ݒ菈��
//============================================
void CWall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �ړ��̐ݒ菈��
//============================================
void CWall::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================================
// �T�C�Y�̐ݒ菈��
//============================================
void CWall::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// �����̐ݒ菈��
//============================================
void CWall::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// �e�N�X�`�����f
//============================================
void CWall::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//============================================
// ����
//============================================
CWall *CWall::Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 rot)
{
	CWall *pWall;
	pWall = new CWall;

	if (pWall != nullptr)
	{
		pWall->Init();
		pWall->SetPosition(pos);
		pWall->SetRot(rot);
	}
	else
	{
		assert(false);
	}

	return pWall;
}

//============================================
//�e�N�X�`���ǂݍ���
//============================================
HRESULT CWall::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall.jpg",
		&m_pTexture);

	return S_OK;
}

//============================================
//�e�N�X�`���j��
//============================================
void CWall::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}


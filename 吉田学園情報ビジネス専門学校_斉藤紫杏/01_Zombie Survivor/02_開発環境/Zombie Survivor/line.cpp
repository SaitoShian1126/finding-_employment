//============================================
//
//	line.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "line.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
D3DXVECTOR3 CLine::m_start = {};
D3DXVECTOR3 CLine::m_end = {};

//============================================
// ���C���\���̃R���X�g���N�^
//============================================
CLine::CLine()
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
	m_pVtxBuffLine = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		m_aLine[nCnt] = nullptr;
	}
}

//============================================
// ���C���\���̃f�X�g���N�^
//============================================
CLine::~CLine()
{
	//���������Ȃ�
}

//============================================
// ���C���\���̏���������
//============================================
HRESULT CLine::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_pVtxBuffLine = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_end = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_mtxWorld = {};
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		m_aLine[nCnt] = nullptr;
	}

	return S_OK;
}

//============================================
// ���C���\���̏I������
//============================================
void CLine::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffLine != NULL)
	{
		m_pVtxBuffLine->Release();
		m_pVtxBuffLine = NULL;
	}
}

//============================================
// ���C���\���̍X�V����
//============================================
void CLine::Update(void)
{
}

//============================================
// ���C���\���̕`�揈��
//============================================
void CLine::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌����ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�����h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffLine, 0, sizeof(VERTEX_LINE));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_LINE);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================
// ���C���\���̈ʒu�ݒ�
//============================================
void CLine::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// ���C���\���̐�������
//============================================
CLine *CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	CLine *pLine = nullptr;

	//�v���C���[�N���X�̐���
	pLine = new CLine;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pLine != nullptr)
	{
		// ����������
		pLine->Init();
		pLine->SetPosition(pos);
		pLine->m_rot = rot;
		pLine->m_start = start;
		pLine->m_end = end;
		pLine->SetLine();
	}
	else
	{
		assert(false);
	}
	return pLine;
}

//============================================
// ���C���\���̒��_���W�ݒ�
//============================================
void CLine::SetLine(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_LINE) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_LINE,
		D3DPOOL_MANAGED,
		&m_pVtxBuffLine,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_LINE*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_end;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffLine->Unlock();
}

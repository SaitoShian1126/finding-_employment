//============================================
//
//	ObjectBase.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "objectbase.h"
#include "application.h"
#include "renderer.h" 
#include "object2d.h"
#include "fade.h"
#include "input.h"
#include "player.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �I�u�W�F�N�g��b�R���X�g���N�^
//============================================
CObjectBase::CObjectBase()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pVtxBuffObjectBase = nullptr;
	m_pTextureObjectBase = nullptr;
	m_ObjectBasePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBasemtxWorld = {};
	m_fLength = 0.0f;
}

//============================================
// �I�u�W�F�N�g��b�f�X�g���N�^
//============================================
CObjectBase::~CObjectBase()
{
	//���������Ȃ�
}

//============================================
// �I�u�W�F�N�g��b����������
//============================================
HRESULT CObjectBase::Init(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pVtxBuffObjectBase = nullptr;
	m_pTextureObjectBase = nullptr;
	m_ObjectBasemtxWorld = {};
	m_ObjectBasePos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_ObjectBaseRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ObjectBaseCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_Radius = 0.0f;
	m_Life = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffObjectBase,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
	pVtx[0].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_ObjectBaseCol;
	pVtx[1].col = m_ObjectBaseCol;
	pVtx[2].col = m_ObjectBaseCol;
	pVtx[3].col = m_ObjectBaseCol;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffObjectBase->Unlock();

	//�T�C�Y�̐ݒ�
	SetSize(m_ObjectBaseSize);

	return S_OK;
}

//============================================
// �I�u�W�F�N�g��b�I������
//============================================
void CObjectBase::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffObjectBase != nullptr)
	{			  
		m_pVtxBuffObjectBase->Release();
		m_pVtxBuffObjectBase = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTextureObjectBase != nullptr)
	{
		m_pTextureObjectBase->Release();
		m_pTextureObjectBase = nullptr;
	}

	//�j������
	CObject::Release();
}

//============================================
// �I�u�W�F�N�g��b�X�V����
//============================================
void CObjectBase::Update()
{

}

//============================================
// �I�u�W�F�N�g��b�`�揈��
//============================================
void CObjectBase::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_ObjectBasemtxWorld);//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	 //�r���[�}�g���b�N�X���擾
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�	(2�t����������΃r���{�[�h����Ɍ����Ȃ�)
	m_ObjectBasemtxWorld._11 = mtxView._11;
	m_ObjectBasemtxWorld._12 = mtxView._21;
	m_ObjectBasemtxWorld._13 = mtxView._31;
	m_ObjectBasemtxWorld._21 = mtxView._12;
	m_ObjectBasemtxWorld._22 = mtxView._22;
	m_ObjectBasemtxWorld._23 = mtxView._32;
	m_ObjectBasemtxWorld._31 = mtxView._13;
	m_ObjectBasemtxWorld._32 = mtxView._23;
	m_ObjectBasemtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_ObjectBasePos.x, m_ObjectBasePos.y, m_ObjectBasePos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_ObjectBasemtxWorld, &m_ObjectBasemtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_ObjectBasemtxWorld);	//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffObjectBase, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureObjectBase);

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================
// �e�N�X�`���̐ݒ�
//============================================
CObjectBase * CObjectBase::SetTexture(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTextureObjectBase);

	m_ObjectBaseTexture = true;

	return S_OK;
}

//============================================
//�c�e�N�X�`���摜�̐ݒ�
//============================================
void CObjectBase::SetTextureY(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY) / SplitY);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY) / SplitY);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / SplitX, (nNumIndexY + 1) / SplitY);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / SplitX, (nNumIndexY + 1) / SplitY);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffObjectBase->Unlock();
}

//============================================
// �ʒu�̐ݒ�
//============================================
void CObjectBase::SetPosition(D3DXVECTOR3 pos)
{
	m_ObjectBasePos = pos;
}

//============================================
// �ړ��̐ݒ�
//============================================
void CObjectBase::SetMove(D3DXVECTOR3 move)
{
	m_ObjectBaseMove = move;
}

//============================================
// �T�C�Y�̐ݒ�
//============================================
void CObjectBase::SetSize(D3DXVECTOR3 size)
{
	m_ObjectBaseSize = size;

	//���_���ւ̃|�C���^
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuffObjectBase->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
	pVtx[0].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_ObjectBaseSize.x, m_ObjectBaseSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_ObjectBaseSize.x, -m_ObjectBaseSize.y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffObjectBase->Unlock();
}

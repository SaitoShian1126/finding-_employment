//============================================
//
//	hp.cpp
//	Author: saito shian
//
//============================================

//============================================
//�C���N���[�h
//============================================
#include <assert.h>
#include "hp.h"
#include "application.h"
#include "renderer.h"
#include "explosion.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "game.h"
#include "spawn.h"
#include "boss.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CHp::m_pTexturehp = {};

//============================================
// hp�̃R���X�g���N�^
//============================================
CHp::CHp() : CObject(PRIORITY_LEVEL3)
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
}

//============================================
// hp�̃f�X�g���N�^
//============================================
CHp::~CHp()
{
	//���������Ȃ�
}

//============================================
// hp�̏���������
//============================================
HRESULT CHp::Init(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_nPlayreLife = 0;
	m_nBossLife = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1280.0f, 720.0f - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nPlayreLife, 720.0f - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nPlayreLife, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// hp�̏I������
//============================================
void CHp::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�j������
	CObject::Release();
}

//============================================
// hp�̍X�V����
//============================================
void CHp::Update()
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//============================================
	//�@�v���C���[��HP
	//============================================
	if (m_type == HPTYPE::HPTYPE_PLAYER)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		if (pPlayer != nullptr)
		{
			//�v���C���[�̗̑͂̎擾
			m_nPlayreLife = pPlayer->GetLife();

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(375.0f - LIFE_WIDTH * m_nPlayreLife, 650.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(375.0f, 650.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(375.0f - LIFE_WIDTH * m_nPlayreLife, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(375.0f, 700.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();

			if (m_nPlayreLife <= 5)
			{
				SetColor(1.0f, 1.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife <= 3)
			{
				SetColor(1.0f, 0.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife <= 10 && m_nPlayreLife > 5)
			{
				SetColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife > 10)
			{
				SetColor(0.0f, 0.5f, 1.0f, 1.0f);
				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(275.0f - LIFE_WIDTH * 10, 75.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(275.0f, 75.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(275.0f - LIFE_WIDTH * 10, 100.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(275.0f, 100.0f, 0.0f);

				//���_�o�b�t�@���A�����b�N����
				m_pVtxBuff->Unlock();
			}
		}
	}

	//============================================
	//�@�{�X��HP
	//============================================
	if (m_type == HPTYPE::HPTYPE_BOSS)
	{
		CBoss *pBoss = CSpawn::GetBoss();

		if (pBoss != nullptr)
		{
			//�v���C���[�̗̑͂̎擾
			m_nBossLife = pBoss->GetLife();

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(550.0f - BOSS_LIFE_WIDTH * m_nBossLife, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(550.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550.0f - BOSS_LIFE_WIDTH * m_nBossLife, 60.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(550.0f, 60.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();

			SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
}

//============================================
// hp�̕`�揈��
//============================================
void CHp::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,									//���_���̐擪�A�h���X
		2);									//�v���~�e�B�u�̐�
}

//============================================
// �X�|�[���̐���
//============================================
CHp *CHp::Create(HPTYPE type)
{
	CHp *php = nullptr;

	//�N���X�̐���
	php = new CHp;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (php != nullptr)
	{
		php->SetHPType(type);
		//����������
		php->Init();
	}
	else
	{
		assert(false);
	}

	return php;
}

//============================================
// �F�̐ݒ�
//============================================
void CHp::SetColor(float Red, float Green, float Blue, float ��)
{
	VERTEX_2D*pVtx;				//���_���ւ̃|�C���^

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
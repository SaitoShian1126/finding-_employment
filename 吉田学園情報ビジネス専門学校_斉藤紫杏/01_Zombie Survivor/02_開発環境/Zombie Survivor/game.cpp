//============================================
//
//	game.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "object3d.h"
#include "objectX.h"
#include "game.h"
#include "player.h"
#include "billboard.h"
#include "meshfield.h"
#include "sphere.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "number.h"
#include "score.h"
#include "objectbase.h"
#include "enemy.h"
#include "model.h"
#include "particle.h"
#include "boss.h"
#include "gasolene_gimmick.h"
#include "bullet.h"
#include "explosion.h"
#include "spawn.h"
#include "particle.h"
#include "camera.h"
#include "rock_gimmick.h"
#include "skybox.h"
#include "wall.h"
#include "sound.h"
#include "hp.h"
#include "fire.h"
#include "indication.h"
#include "item.h"
#include "ui.h"
#include "reticle.h"
#include "warning.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
CMeshField *CGame::m_pMeshField = nullptr;
CScore *CGame::m_pScore = nullptr;
CGasolene_Gimmick *CGame::m_pGasoleneGimmick[MAX_GASOLENE] = {};
CModel *CGame::m_Model = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CSpawn *CGame::m_pSpawn = nullptr;
CParticle *CGame::m_pParticle[MAX_PARTICLE] = {};
CRock_gimmick *CGame::m_pRockGimmick[MAX_ROCK] = {};
CBoss *CGame::m_pBoss = nullptr;
CIndication *CGame::m_pIndication = nullptr;
CItem *CGame::m_pItem = nullptr;
CUi *CGame::m_pUi[MAX_UI] = {};

//============================================
// �Q�[���̃R���X�g���N�^
//============================================
CGame::CGame()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �Q�[���̃f�X�g���N�^
//============================================
CGame::~CGame()
{
	//���������Ȃ�
}

//============================================
// �Q�[���̏���������
//============================================
HRESULT CGame::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_ParticleCreateTime = PARTICLE_TIME;
	m_ItemSpawnTime = 100;
	m_ItemGetFlag = false;
	m_BGMFlag = false;

	//============================================
	//	�e�N�X�`���ǂݍ���
	//============================================
	CNumber::Load();		//�i���o�[�e�N�X�`���̓ǂݍ���
	CWall::Load();			//�ǂ̃e�N�X�`���ǂݍ���
	CParticle::Load();		//�p�[�e�B�N���̃e�N�X�`���ǂݍ���
	CFire::Load();			//���̃e�N�X�`���ǂݍ���
	CIndication::Load();	//�\���̃e�N�X�`���ǂݍ���
	CItem::Load();			//�A�C�e���̃e�N�X�`���ǂݍ���
	CUi::Load();			//UI�̃e�N�X�`���ǂݍ���
	CReticle::Load();		//���e�B�N���̃e�N�X�`���ǂݍ���
	CWarning::Load();		//Warning�̃e�N�X�`���ǂݍ���

	//============================================
	//	�I�u�W�F�N�g�̐���
	//============================================
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));													//���b�V���t�B�[���h�̐���
	m_Model = CModel::Create();																							//���f���̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));															//�v���C���[�̐���
	m_pSpawn = CSpawn::Create();																						//�G�̐���
	CSkyBox::Create(D3DXVECTOR3(400.0f, 0.0f, -460.0f));																//�X�J�C�{�b�N�X�̐���
	CFire::Create(D3DXVECTOR3(400.0f, 35.0f, -100.0f),D3DXVECTOR3(50.0f,75.0f,0.0f));									//���̐���
	CFire::Create(D3DXVECTOR3(630.0f, 90.0f, -400.0f), D3DXVECTOR3(25.0f, 35.0f, 0.0f));								//���̐���
	CFire::Create(D3DXVECTOR3(170, 20.0f, -460.0f), D3DXVECTOR3(35.0f, 55.0f, 0.0f));									//���̐���

	//============================================
	//	UI�̐���
	//============================================																							
	m_pScore = CScore::Create();																						//�X�R�A�̐���
	CHp::Create(CHp::HPTYPE_PLAYER);																					//�v���C���[�̗̑͐���
	m_pIndication = CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE1);	//�\���̐���
	m_pUi[0] = CUi::Create(D3DXVECTOR3(-750.0f, 650.0f, 0.0f), CUi::UITYPE_NUMBER);										//UI�̐���
	m_pUi[1] = CUi::Create(D3DXVECTOR3(450.0f, 675.0f, 0.0f), CUi::UITYPE_BOMB);										//UI�̐���

	//============================================
	//	�A�C�e���̐���
	//============================================			
	m_pItem = CItem::Create(D3DXVECTOR3(480.0f,20.0f,-980.0f), D3DXVECTOR3(3.0f, 3.0f, 0.0f));

	//============================================
	//�@�M�~�b�N�̐���
	//============================================
	//�K�\����
	m_pGasoleneGimmick[0] = CGasolene_Gimmick::Create(D3DXVECTOR3(230.0f, 0.0f, -420.0f));									
	m_pGasoleneGimmick[1] = CGasolene_Gimmick::Create(D3DXVECTOR3(250.0f, 0.0f, -640.0f));
	m_pGasoleneGimmick[2] = CGasolene_Gimmick::Create(D3DXVECTOR3(510.0f, 0.0f, -800.0f));
	m_pGasoleneGimmick[3] = CGasolene_Gimmick::Create(D3DXVECTOR3(490.0f, 0.0f, -20.0f));
	//��
	m_pRockGimmick[0] = CRock_gimmick::Create(D3DXVECTOR3(1000.0f, 0.0f, -500.0f), CRock_gimmick::MODELTYPE_SUPPORTBAR);
	m_pRockGimmick[1] = CRock_gimmick::Create(D3DXVECTOR3(1000.0f, 120.0f, -520.0f), CRock_gimmick::MODELTYPE_ROCK);
	m_pRockGimmick[2] = CRock_gimmick::Create(D3DXVECTOR3(-90.0f, 0.0f, -975.0f), CRock_gimmick::MODELTYPE_SUPPORTBAR);
	m_pRockGimmick[3] = CRock_gimmick::Create(D3DXVECTOR3(-90.0f, 120.0f, -990), CRock_gimmick::MODELTYPE_ROCK);

	//============================================
	//�@�ǂ̐���
	//============================================
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-50.0f + 200.0f * nCnt, 40.0f, 150.0f), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI, D3DX_PI));			//���̓����̕�
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-50.0f + 200.0f * nCnt, 40.0f, -1050.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, D3DX_PI));			//��O�̓����̕�
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(1050.0f, 40.0f, 50.0f - 200.0f * nCnt), D3DXVECTOR3(-D3DX_PI / 2, -D3DX_PI / 2, D3DX_PI));	//�E�̓����̕�
	}
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		CWall::Create(D3DXVECTOR3(-150, 40.0f, 50.0f - 200.0f * nCnt), D3DXVECTOR3(-D3DX_PI / 2, D3DX_PI, D3DX_PI / 2));		//���̓����̕�
	}

	return S_OK;
}

//============================================
// �Q�[���̏I������
//============================================
void CGame::Uninit(void)
{
	//============================================
	// �T�E���h�̒�~
	//============================================
	StopSound();

	//============================================
	//	�e�N�X�`���j��
	//============================================
	CNumber::Unload();			//�i���o�[�e�N�X�`���̔j��
	CWall::Unload();			//�ǂ̃e�N�X�`���j��
	CParticle::Unload();		//�p�[�e�B�N���̃e�N�X�`���j��
	CFire::Unload();			//���̃e�N�X�`���j��
	CIndication::Unload();		//�\���̃e�N�X�`���j��
	CItem::Unload();			//�A�C�e���̃e�N�X�`���j��
	CUi::Unload();				//UI�̃e�N�X�`���j��
	CReticle::Unload();			//���e�B�N���̃e�N�X�`���j��
	CWarning::Unload();			//Warning�̃e�N�X�`���j��

	CObject::Release();
}

//============================================
// �Q�[���̍X�V����
//============================================
void CGame::Update()
{
	//============================================
	// �T�E���h�̍Đ�
	//============================================
	if (m_BGMFlag == false)
	{
		PlaySound(SOUND_LABEL_SOUND);
		m_BGMFlag = true;
	}
	m_ParticleCreateTime--;
	if (m_ParticleCreateTime <= 0)
	{
		for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
		{
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(400.0f, 10.0f, -100.0f), 80, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(630.0f, 90.0f, -410.0f), 30, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FIRE, D3DXVECTOR3(170, 10.0f, -460.0f), 40, D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f));
			m_pParticle[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, D3DXVECTOR3(615.0f, 40.0f, 20.0f), PARTICLE_TIME, D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));
		}
	}
	if (m_ParticleCreateTime <= 0)
	{
		m_ParticleCreateTime = PARTICLE_TIME / 2;
	}

	/*if (m_ItemGetFlag == false && CGame::GetItem() == nullptr)
	{
		m_ItemSpawnTime--;
		if (m_ItemSpawnTime <= 0)
		{
			m_pItem = CItem::Create(D3DXVECTOR3(480.0f, 20.0f, -980.0f), D3DXVECTOR3(3.0f, 3.0f, 0.0f));
			m_ItemSpawnTime = 100;
			m_ItemGetFlag = true;
		}
	}*/
}

//============================================
// �Q�[���̕`�揈��
//============================================
void CGame::Draw()
{

}

//============================================
// �v���C���[�̐ݒ菈��
//============================================
void CGame::SetPlayer(CPlayer * player)
{
	m_pPlayer = player;
}

//============================================
// �A�C�e���̐ݒ菈��
//============================================
void CGame::SetItem(CItem * item)
{
	m_pItem = item;
}

//============================================
// �Q�[���̐���
//============================================
CGame *CGame::Create()
{
	CGame *pgame = nullptr;

	//�N���X�̐���
	pgame = new CGame;				//�Q�[���̃C���X�^���X����

	//null�`�F�b�N
	if (pgame != nullptr)
	{
		//����������
		pgame->Init();
	}
	else
	{
		assert(false);
	}

	return pgame;
}
//============================================
//
//	spawn.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "spawn.h"
#include "enemy.h"
#include "objectX.h"
#include "game.h"
#include "player.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "indication.h"
#include "boss.h"
#include "hp.h"
#include "sound.h"
#include "warning.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
CBoss *CSpawn::m_pBoss = nullptr;

//============================================
// �R���X�g���N�^
//============================================
CSpawn::CSpawn()
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
}

//============================================
// �f�X�g���N�^
//============================================
CSpawn::~CSpawn()
{
	//���������Ȃ�
}

//============================================
// �ʎY�̏���������
//============================================
HRESULT CSpawn::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_EnemyCreateTime = 0;
	m_RandNumber = 0;
	m_EnemyCount = 0;
	m_WaveTime = 0;
	m_BossAppearTime = 0;
	m_RandFlag = false;
	m_MaxEnemyFlag = false;
	m_IndicationFlag = false;
	m_BossFlag = false;

	return S_OK;
}

//============================================
// �ʎY�̏I������
//============================================
void CSpawn::Uninit(void)
{
	//�j������
	Release();
}

//============================================
// �ʎY�̍X�V����
//============================================
void CSpawn::Update(void)
{
	if (CPlayer::GetBullet() != nullptr)
	{
		m_EnemyCount = CPlayer::GetBullet()->GetTotalEnemy();
	}

	if (m_EnemyCount < MAX_ENEMY_1 && m_EnemyCreateTime == ENEMY_CREATE_TIME_WAVE_1)
	{
		m_MaxEnemyFlag = false;
	}
	if (m_EnemyCount < MAX_ENEMY_2 && m_EnemyCreateTime == ENEMY_CREATE_TIME_WAVE_2)
	{
		m_MaxEnemyFlag = false;
	}

	if (m_MaxEnemyFlag == false)
	{
		//�G�̗ʎY�����̊֐��Ăяo��
		EnemySpawn();
	}
}

//============================================
// �ʎY�̕`�揈��
//============================================
void CSpawn::Draw(void)
{

}

//============================================
// �ʎY�̐�������
//============================================
CSpawn *CSpawn::Create()
{
	CSpawn *pSpawn = nullptr;

	// �ʎY�N���X�̐���
	pSpawn = new CSpawn;				// �ʎY�C���X�^���X����

	// nullptr�`�F�b�N
	if (pSpawn != nullptr)
	{
		// ����������
		pSpawn->Init();
	}
	else
	{
		assert(false);
	}
	return pSpawn;
}

//============================================
// �{�X�̃C���X�^���X�̐ݒ菈��
//============================================
void CSpawn::SetBoss(CBoss *boss)
{
	m_pBoss = boss;
}

//============================================
// �G�̗ʎY����
//============================================
void CSpawn::EnemySpawn(void)
{
	//�G�����������܂ł̎��Ԃ����炵�Ă���
	m_EnemyCreateTime--;
	m_WaveTime++;
	m_BossAppearTime++;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	if (m_EnemyCreateTime <= 0 && m_RandFlag == false && m_MaxEnemyFlag == false)
	{
		m_RandNumber = 1;								//�����_���Ȑ��l�����߂�
		x = rand() % (1000 - (-135 + 1)) + (-135);		//x�͈̔͂Ƀ����_��
		y = 0.0f;										//y��0.0f�ɌŒ�
		z = rand() % (150 - (-1050 + 1)) + (-1050);		//z�͈̔͂Ƀ����_��
		m_EnemySpawnType = rand() % 3 + 1;				//�]���r�̎�ރ����_��
		m_RandFlag = true;								//�����_���Ȑ��l�����ߏI�����
	}
	//�E�F�[�u1
	if (m_EnemyCreateTime <= 0 && m_WaveTime <= WAVE_TIME)
	{	
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_1;	//���Ԃ�������

		if (m_EnemyCount >= MAX_ENEMY_1)
		{
			m_MaxEnemyFlag = true;
		}
	}
	//�E�F�[�u2
	if (m_EnemyCreateTime <= 0 && m_WaveTime >= WAVE_TIME)
	{
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_2;	//���Ԃ�������

		if (m_IndicationFlag == false)
		{
			CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE2);	//�\���̐���
			m_IndicationFlag = true;
		}

		if (m_EnemyCount >= MAX_ENEMY_2)
		{
			m_MaxEnemyFlag = true;
		}
	}
	//�E�F�[�u3
	if (m_EnemyCreateTime <= 0 && m_WaveTime >= WAVE_TIME)
	{
		m_EnemyCreateTime = ENEMY_CREATE_TIME_WAVE_2;	//���Ԃ�������

		if (m_IndicationFlag == false)
		{
			CIndication::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), CIndication::INDICATIONTYPE_WAVE2);	//�\���̐���
			m_IndicationFlag = true;
		}

		if (m_EnemyCount >= MAX_ENEMY_2)
		{
			m_MaxEnemyFlag = true;
		}
	}
	if (m_RandNumber == 1 && m_RandFlag == true)
	{
		CEnemy::Create(D3DXVECTOR3(x, y, z), CEnemy::ENEMYTYPE_HUMAN);
		if (m_EnemySpawnType == 1 && m_WaveTime >= WAVE_TIME)
		{
			CEnemy::Create(D3DXVECTOR3(x, y, z), CEnemy::ENEMYTYPE_DOG);
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_DOG_VOICE);
		}
		if (m_BossAppearTime >= WAVE_TIME2 && m_BossFlag == false && m_pBoss == nullptr)
		{
			m_pBoss = CBoss::Create(D3DXVECTOR3(555.0f,0.0f, -200.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));		//�{�X�̐���
			CHp::Create(CHp::HPTYPE_BOSS);																//�{�X�̗̑͐���
			CWarning::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CWarning::WARNINGTYPE_SCREEN);	//Warning�̐���
			m_BossAppearTime = WAVE_TIME2;
			m_BossFlag = true;
		}
		m_EnemyCount++;
		m_RandFlag = false;
	}

	//if (m_EnemyCount >= 1)
	//{
	//	m_MaxEnemyFlag = true;
	//}
}

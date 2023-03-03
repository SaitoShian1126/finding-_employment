//============================================
//
//	bullet.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "bullet.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "object2D.h"
#include "score.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "result.h"
#include "billboard.h"
#include "gasolene_gimmick.h"
#include "spawn.h"
#include "explosion.h"
#include "sound.h"
#include "boss.h"
#include "indication.h"
#include "particle.h"
#include "camera.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �e�̃R���X�g���N�^
//============================================
CBullet::CBullet()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyDeathFlag = false;
	m_GimmickUninitFlag = false;
}

//============================================
// �e�̃f�X�g���N�^
//============================================
CBullet::~CBullet()
{
	//���������Ȃ�
}

//============================================
// �e�̏���������
//============================================
HRESULT CBullet::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyDeathFlag = false;
	m_GimmickUninitFlag = false;
	m_BulletMoveFlag = false;
	m_RandFlag = false;
	m_BossDeathFlag = false;
	m_nBulletExplosionTime = 150;
	m_ExplosionTime = 50;
	m_ResultTime = 200;

	//�I�u�W�F�N�g��b�̏���������
	CObjectBase::Init();

	switch (m_type)
	{
	case CBullet::BULLETTYPE_PLAYER:
		SetTexture("data/TEXTURE/bullet000.png");
		break;
	case CBullet::BULLETTYPE_BOSS:
		SetTexture("data/TEXTURE/�e.png");
		break;
	case CBullet::BULLETTYPE_BOMB:
		SetTexture("data/TEXTURE/���e.png");
		break;
	case CBullet::BULLETTYPE_MAX:
		break;
	default:
		break;
	}

	return S_OK;
}

//============================================
// �e�̏I������
//============================================
void CBullet::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CObjectBase::Uninit();
}

//============================================
// �e�̍X�V����
//============================================
void CBullet::Update(void)
{
	//�e�̏��擾
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletMove = GetMove();
	D3DXVECTOR3 BulletSize = GetSize();

	//�J�����̏����擾
	CCamera *pCamera = CApplication::GetCamera();

	//�e�̈ʒu�X�V
	BulletPos += BulletMove;

	//���������炷����
	m_nLife--;

	//�v���C���[�̒e�̎�
	if (m_nLife <= 0 && m_type == CBullet::BULLETTYPE_PLAYER)
	{
		Uninit();
		return;
	}

	//���e�̔j������
	if (m_nLife <= 0 && m_type == CBullet::BULLETTYPE_BOMB)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_BOMB);
		//�J������h�炷
		pCamera->SetShakeCamera(10, 1);
		CExplosion::Create(D3DXVECTOR3(BulletPos.x, BulletPos.y + 20.0f, BulletPos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
		//�e�̍폜
		Uninit();
		return;
	}

	//�{�X�̒e�̍U������
	if (m_type == CBullet::BULLETTYPE_BOSS && CGame::GetPlayer() != nullptr && CBoss::GetBullet() != nullptr)
	{
		BossBullet(BulletPos, D3DXVECTOR3(BOMB_HIT_SIZE, 0.0f, BOMB_HIT_SIZE), BulletMove);
		m_nBulletExplosionTime--;
		if (m_nBulletExplosionTime <= 0)
		{
			Uninit();
			return;
		}
	}

	//�e(���e)�ƃ{�X�̓����蔻��
	if (m_type == BULLETTYPE_BOMB && CSpawn::GetBoss() != nullptr)
	{
		BombHitBoss(BulletPos, D3DXVECTOR3(BOMB_SIZE, BOMB_SIZE, 0.0f));
	}

	//�e�ƃM�~�b�N�̓����蔻��
	if (m_GimmickUninitFlag == false)
	{
		HitGimmick(BulletPos);
	}
	//�e�ƃ{�X�̓����蔻�菈��
	if (CSpawn::GetBoss() != nullptr && m_type == CBullet::BULLETTYPE_PLAYER)
	{
		HitBoss(BulletPos);
	}

	//�e�ƓG�̓����蔻�菈��
	if (m_EnemyDeathFlag == false && m_type != CBullet::BULLETTYPE_BOSS)
	{
		HitEnemy(BulletPos);
	}

	//�{�X�̒e�̗U������
	if (m_type == CBullet::BULLETTYPE_BOSS)
	{
		BulletBehavior();
	}

	//�ʒu�̐ݒ�
	SetPosition(BulletPos);
	//�����̐ݒ�
	SetRot(m_BulletRot);
	//�T�C�Y�̐ݒ菈��
	SetSize(BulletSize);

	//�I�u�W�F�N�g��b�̍X�V����
	CObjectBase::Update();
}

//============================================
// �e�̕`�揈��
//============================================
void CBullet::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CObjectBase::Draw();
}

//============================================
// �e�̐���
//============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, BULLETTYPE type)
{
	CBullet *pBullet = nullptr;

	//�e�̃C���X�^���X�̐���
	pBullet = new CBullet;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pBullet != nullptr)
	{
		pBullet->SetBulletType(type);
		//����������
		pBullet->Init();
		//�ݒ菈��
		pBullet->SetPosition(pos);
		pBullet->SetMove(move);
		pBullet->SetLife(nLife);
		pBullet->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pBullet;
}

//============================================
// �e�̎g�p�҂̐ݒ菈��
//============================================
void CBullet::SetBulletType(BULLETTYPE type)
{
	m_type = type;
}

//============================================
// �e�ƓG�̓����蔻��
//============================================
void CBullet::HitEnemy(D3DXVECTOR3 pos)
{
	//�G�̑���
	m_TotalEnemy = CGame::GetSpawn()->GetEnemyCount();
	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;

			//�G�̈ʒu
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			//�G�̃T�C�Y
			D3DXVECTOR3 EnemySize = pEnemy->GetEnemySize();
			//�G�̗̑�
			int EnemyLife = pEnemy->GetLife();
			//�e�ƓG�̓����蔻��
			if (pos.x + 0.5f >= EnemyPos.x - EnemySize.x
				&&pos.x - 0.5f <= EnemyPos.x + EnemySize.x
				&&pos.y + 0.5f >= EnemyPos.y - EnemySize.y
				&&pos.z + 0.5f >= EnemyPos.z - EnemySize.z
				&&pos.z - 0.5f <= EnemyPos.z + EnemySize.z)
			{
				//�e�̍폜
				m_nLife = 0;
				SetLife(m_nLife);

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_HIT);

				EnemyLife--;

				if (EnemyLife <= 0)
				{
					for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
					{
						CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_BLOOD, D3DXVECTOR3(EnemyPos.x, 15.0f, EnemyPos.z), 0, D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f));
					}
					m_TotalEnemy--;
					CGame::GetSpawn()->SetEnemyCount(m_TotalEnemy);
					CGame::GetScore()->AddScore(200);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
				else
				{
					pEnemy->SetLife(EnemyLife);
				}
				break;
			}
		}
		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//============================================
// �e�ƃM�~�b�N�̓����蔻��
//============================================
void CBullet::HitGimmick(D3DXVECTOR3 pos)
{
	//�J�����̏����擾
	CCamera *pCamera = CApplication::GetCamera();

	for (int nCnt = 0; nCnt < MAX_GASOLENE; nCnt++)
	{
		if (CGame::GetGasoleneGimmick()[nCnt] != nullptr)
		{
			//�M�~�b�N�̈ʒu
			D3DXVECTOR3 GasolenePos = CGame::GetGasoleneGimmick()[nCnt]->GetPos();
			//�M�~�b�N�̃T�C�Y
			D3DXVECTOR3 GasoleneSize = CGame::GetGasoleneGimmick()[nCnt]->GetGasoleneSize();
			//�M�~�b�N�̗̑�
			int GasoleneLife = CGame::GetGasoleneGimmick()[nCnt]->GetGasoleneLife();

			//�e�ƃM�~�b�N�̓����蔻��
			if (pos.x + 0.5f >= GasolenePos.x - GasoleneSize.x
				&&pos.x - 0.5f <= GasolenePos.x + GasoleneSize.x
				&&pos.y + 0.5f >= GasolenePos.y - GasoleneSize.y
				&&pos.y - 0.5f <= GasolenePos.y + GasoleneSize.y
				&&pos.z + 0.5f >= GasolenePos.z - GasoleneSize.z
				&&pos.z - 0.5f <= GasolenePos.z + GasoleneSize.z)
			{
				//�e�̍폜
				m_nLife = 0;
				SetLife(m_nLife);

				//float x = 0.0f;
				//float y = 0.0f;
				//float z = 0.0f;

				//if (m_RandFlag == false)
				//{
				//	x = (float)(rand() % (int)(GasolenePos.x * 200) / 100) - GasolenePos.x;		//x�͈̔͂Ƀ����_��
				//	y = (float)(rand() % (int)(GasolenePos.y * 200) / 100) - GasolenePos.y;		//y��0.0f�ɌŒ�
				//	z = (float)(rand() % (int)(GasolenePos.z * 200) / 100) - GasolenePos.z;		//z�͈̔͂Ƀ����_��
				//	m_RandFlag = true;
				//}

				GasoleneLife--;
				if (GasoleneLife <= 0)
				{
					//�J������h�炷
					pCamera->SetShakeCamera(20, 3);
				/*	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
					{
						CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_BLOOD, D3DXVECTOR3(x, y, z), 0, D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f));
					}*/
					CExplosion::Create(D3DXVECTOR3(GasolenePos.x, GasolenePos.y + 20.0f, GasolenePos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_EXPLOTION);
					CGame::GetGasoleneGimmick()[nCnt]->HitDamage();
					CGame::GetGasoleneGimmick()[nCnt]->Uninit();
					CGame::GetGasoleneGimmick()[nCnt] = nullptr;
				}
				else
				{
					CGame::GetGasoleneGimmick()[nCnt]->SetGasoleneLife(GasoleneLife);
				}
			}
		}
	}
}

//============================================
// �e�ƃ{�X�̓����蔻��
//============================================
void CBullet::HitBoss(D3DXVECTOR3 pos)
{
	//CBoss *pBoss = CSpawn::GetBoss();

	if (CSpawn::GetBoss() != nullptr)
	{
		//�M�~�b�N�̈ʒu
		D3DXVECTOR3 BossPos = CSpawn::GetBoss()->GetBossPos();
		//�M�~�b�N�̃T�C�Y
		D3DXVECTOR3 BossSize = CSpawn::GetBoss()->GetBossSize();
		//�M�~�b�N�̗̑�
		int BossLife = CSpawn::GetBoss()->GetLife();

		//�e�ƃM�~�b�N�̓����蔻��
		if (pos.x + 0.5f >= BossPos.x - BossSize.x
			&&pos.x - 0.5f <= BossPos.x + BossSize.x
			&&pos.y + 0.5f >= BossPos.y - BossSize.y
			&&pos.y - 0.5f <= BossPos.y + BossSize.y
			&&pos.z + 0.5f >= BossPos.z - BossSize.z
			&&pos.z - 0.5f <= BossPos.z + BossSize.z)
		{
			//�e�̍폜
			m_nLife = 0;
			SetLife(m_nLife);

			if (m_type == BULLETTYPE_BOMB)
			{
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
			}

			BossLife -= 10;
			if (BossLife <= 0)
			{
				m_BossDeathFlag = true;
				CGame::GetScore()->AddScore(5000000);
				CFade::SetFade(CApplication::MODE_RESULT);
				CResult::SetType(CResult::TYPE_GAMECLEAR);
				CSpawn::GetBoss()->SetBossDeathFlag(true);
				CSpawn::GetBoss()->Uninit();
				CSpawn::SetBoss(nullptr);
				return;
			}
			else
			{
				CSpawn::GetBoss()->SetLife(BossLife);
			}
		}
	}
}

//============================================
// �e�̋���
//============================================
void CBullet::BulletBehavior()
{
	//============================================
	//  �v���C���[��Ǐ]���鏈��
	//============================================
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();
	//�e�̏��擾
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletMove = GetMove();

	BulletMove = BulletPos - PlayerPos;				//�v���C���[�̈ʒu�ƓG�̈ʒu���v�Z���Ĉړ��ɑ��
	D3DXVec3Normalize(&BulletMove, &BulletMove);	//�ړ��̐��K��
	BulletMove *= -5.0f;							//�ړ��X�s�[�h

	//�ړ��ʌ���
	m_BulletPos.x += (0.0f - BulletMove.x) * 0.1f;
	m_BulletPos.y += (0.0f - BulletMove.y) * 0.1f;
	m_BulletPos.z += (0.0f - BulletMove.z) * 0.1f;

	//�ړ��̐ݒ�
	SetMove(BulletMove);
}

//============================================
// �e(���e)�ƃ{�X�̓����蔻��
//============================================
void CBullet::BombHitBoss(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	D3DXVECTOR3 BossPos = CSpawn::GetBoss()->GetBossPos();
	D3DXVECTOR3 BossSize = CSpawn::GetBoss()->GetBossSize();
	int BossLife = CSpawn::GetBoss()->GetLife();

	if (pos.x + size.x >= BossPos.x - BossSize.x
		&&pos.x - size.x <= BossPos.x + BossSize.x
		&&pos.y + size.y >= BossPos.y - BossSize.y
		&&pos.y - size.y <= BossPos.y + BossSize.y
		&&pos.z + size.z >= BossPos.z - BossSize.z
		&&pos.z - size.z <= BossPos.z + BossSize.z)

	{
		//�e�̍폜
		m_nLife = 0;
		SetLife(m_nLife);

		BossLife -= 50;
		if (BossLife <= 0)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_BOMB);
			CGame::GetScore()->AddScore(5000000);
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
			CFade::SetFade(CApplication::MODE_RESULT);
			CResult::SetType(CResult::TYPE_GAMECLEAR);
			CSpawn::GetBoss()->Uninit();
			CSpawn::SetBoss(nullptr);
			return;
		}
		else
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_BOMB);
			CSpawn::GetBoss()->SetLife(BossLife);
		}
	}
}

//============================================
// �{�X�̒e�̍U������
//============================================
void CBullet::BossBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPlayerPos();
	D3DXVECTOR3 PlayerSize = CGame::GetPlayer()->GetPlayerSize();
	int PlayerLife = CGame::GetPlayer()->GetLife();
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_BOSSATTACK);
	CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));

	//�Ǐ]�����e�̔����͈�
	if (PlayerPos.x + PlayerSize.x >= pos.x - size.x && PlayerPos.x - PlayerSize.x <= pos.x + size.x
		&& PlayerPos.z + PlayerSize.z >= pos.z - size.z && PlayerPos.z - PlayerSize.z <= pos.z + size.z)
	{
		PlayerLife -= 2;
		if (PlayerLife <= 0)
		{
			CFade::SetFade(CApplication::MODE_RESULT);
			CResult::SetType(CResult::TYPE_GAMEOVER);
		}
		else
		{
			if (m_RandFlag == false)
			{
				for (int nCnt = 0; nCnt < 20; nCnt++)
				{
					float x = (float)(rand() % 1280 + 1);
					float y = (float)(rand() % 720 + 1);
					float sxy = (float)(rand() % 75 + 15);
					CIndication::Create(D3DXVECTOR3(x, y, 0.0f), D3DXVECTOR3(sxy, sxy, 0.0f), CIndication::INDICATIONTYPE_BLOOD);
				}
				m_RandFlag = true;
			}
			CGame::GetPlayer()->SetPlayerLife(PlayerLife);
		}
	}
	//�ړ��̐ݒ�
	SetMove(move);
}
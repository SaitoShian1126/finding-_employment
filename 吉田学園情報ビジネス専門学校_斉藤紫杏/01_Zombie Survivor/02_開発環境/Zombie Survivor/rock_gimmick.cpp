//============================================
//
//	rock_gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "rock_gimmick.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "spawn.h"
#include "enemy.h"
#include "score.h"
#include "input.h"
#include "application.h"
#include "particle.h"
#include "shadow.h"
#include "object2D.h"
#include "application.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"
#include "sound.h"
#include "camera.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �M�~�b�N�̃R���X�g���N�^
//============================================
CRock_gimmick::CRock_gimmick()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PushCount = 0;
}

//============================================
// �M�~�b�N�̃f�X�g���N�^
//============================================
CRock_gimmick::~CRock_gimmick()
{
	//���������Ȃ�
}

//============================================
// �M�~�b�N�̏���������
//============================================
HRESULT CRock_gimmick::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PushCount = 0;
	m_PushCountFlag = false;
	m_UninitFlag = false;

	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/!.png",
		&m_pTexture);

	switch (m_type)
	{
	case CRock_gimmick::MODELTYPE_ROCK:
		CGimmick::SetModel("data/XMODEL/rock.x");
		break;
	case CRock_gimmick::MODELTYPE_SUPPORTBAR:
		CGimmick::SetModel("data/XMODEL/supportbar.x");
		break;
	default:
		break;
	}

	//�I�u�W�F�N�g��b�̏���������
	CGimmick::Init();

	return S_OK;
}

//============================================
// �M�~�b�N�̏I������
//============================================
void CRock_gimmick::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CGimmick::Uninit();
}

//============================================
// �M�~�b�N�̍X�V����
//============================================
void CRock_gimmick::Update(void)
{
	//���쏈��
	Operation();

	//�I�u�W�F�N�g��b�̍X�V����
	CGimmick::Update();
}

//============================================
// �M�~�b�N�̕`�揈��
//============================================
void CRock_gimmick::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CGimmick::Draw();
}

//============================================
// �����������̓����蔻��
//============================================
void CRock_gimmick::HitDamage()
{
	D3DXVECTOR3 GimmickPos = CGimmick::GetPos();

	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			//�G�̈ʒu�̎擾
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			int EnemyLife = pEnemy->GetLife();

			if (EnemyPos.x <= GimmickPos.x + 50.0f && EnemyPos.x >= GimmickPos.x - 50.0f
				&& EnemyPos.z <= GimmickPos.z + 50.0f && EnemyPos.z >= GimmickPos.z - 50.0f)
			{
				EnemyLife = 0;
				if (EnemyLife <= 0)
				{
					CGame::GetScore()->AddScore(300);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
			}
		}
		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//============================================
// �M�~�b�N���쏈��
//============================================
void CRock_gimmick::Operation()
{
	// �C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();
	//�J�����̏����擾
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 GimmickPos = CGimmick::GetPos();
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPlayerPos();

	if (GimmickPos.x + 50.0f >= PlayerPos.x && GimmickPos.x - 50.0f <= PlayerPos.x
		&& PlayerPos.z <= GimmickPos.z + 50.0f && PlayerPos.z >= GimmickPos.z - 50.0f)
	{
		if (pInput->GetKeyboardTrigger(DIK_SPACE) == true
			|| pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B))
		{
			m_PushCount++;
			if (m_PushCount >= MAX_PUSH)
			{
				m_PushCountFlag = true;
			}
		}
	}

	if (m_type == MODELTYPE_ROCK)
	{
		//�ʒu�̍X�V
		GimmickPos += m_move;

		if (m_PushCountFlag == true)
		{
			GimmickPos.y -= 2.0f;
			if (GimmickPos.y <= 0.0f)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_ROCKGIMMICK);

				//�J������h�炷
				pCamera->SetShakeCamera(50, 3);

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_SPLINTER, D3DXVECTOR3(GimmickPos.x, 5.0f, GimmickPos.z), PARTICLE_TIME, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
				}
				HitDamage();
				Uninit();
				return;
			}

			//�ړ��ʌ���
			GimmickPos.x += (0.0f - m_move.x) * 0.1f;
			GimmickPos.y += (0.0f - m_move.y) * 0.1f;
			GimmickPos.z += (0.0f - m_move.z) * 0.1f;
			SetPosition(GimmickPos);
		}
	}
}

//============================================
// ���f���̎�ނ̐ݒ�
//============================================
void CRock_gimmick::SetModelType(MODELTYPE type)
{
	m_type = type;
}

//============================================
// ����
//============================================
CRock_gimmick * CRock_gimmick::Create(D3DXVECTOR3 pos, MODELTYPE type)
{
	CRock_gimmick *pRock = nullptr;

	//��M�~�b�N�̐���
	pRock = new CRock_gimmick;				//��M�~�b�N�̃C���X�^���X����

	//null�`�F�b�N
	if (pRock != nullptr)
	{
		pRock->SetModelType(type);
		//����������
		pRock->Init();
		pRock->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pRock;
}

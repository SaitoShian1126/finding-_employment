//============================================
//
//	gasolene_gimmick.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "gasolene_gimmick.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "spawn.h"
#include "enemy.h"
#include "score.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================

//============================================
// �M�~�b�N�̃R���X�g���N�^
//============================================
CGasolene_Gimmick::CGasolene_Gimmick()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================================
// �M�~�b�N�̃f�X�g���N�^
//============================================
CGasolene_Gimmick::~CGasolene_Gimmick()
{
	//���������Ȃ�
}

//============================================
// �M�~�b�N�̏���������
//============================================
HRESULT CGasolene_Gimmick::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_size = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
	m_nLife = 1;

	//�I�u�W�F�N�g��b�̏���������
	CGimmick::Init();
	CGimmick::SetModel("data/XMODEL/gasolene.x");

	return S_OK;
}

//============================================
// �M�~�b�N�̏I������
//============================================
void CGasolene_Gimmick::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CGimmick::Uninit();
}

//============================================
// �M�~�b�N�̍X�V����
//============================================
void CGasolene_Gimmick::Update(void)
{
	//�I�u�W�F�N�g��b�̍X�V����
	CGimmick::Update();
}

//============================================
// �M�~�b�N�̕`�揈��
//============================================
void CGasolene_Gimmick::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CGimmick::Draw();
}

//============================================
// �����������̓����蔻��
//============================================
void CGasolene_Gimmick::HitDamage()
{
	CObject *pObject = GetTop(PRIORITY_LEVEL0);
	D3DXVECTOR3 GasolinePos = CGimmick::GetPos();

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			//�G�̈ʒu�̎擾
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			D3DXVECTOR3 EnemySize = pEnemy->GetEnemySize();
			int EnemyLife = pEnemy->GetLife();

			if (GasolinePos.x + 100.0f >= EnemyPos.x - EnemySize.x / 2 && GasolinePos.x - 100.0f <= EnemyPos.x + EnemySize.x / 2
				&& EnemyPos.z - EnemySize.z / 2 <= GasolinePos.z + 100.0f && EnemyPos.z + EnemySize.z / 2 >= GasolinePos.z - 100.0f)
			{
				EnemyLife--;
				if (EnemyLife <= 0)
				{
					CGame::GetScore()->AddScore(300);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
				else
				{
					pEnemy->SetLife(EnemyLife);
				}
			}
		}
		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}
}

//============================================
// ����
//============================================
CGasolene_Gimmick * CGasolene_Gimmick::Create(D3DXVECTOR3 pos)
{
	CGasolene_Gimmick *pGasolene = nullptr;

	//3D�I�u�W�F�N�g�N���X�̐���
	pGasolene = new CGasolene_Gimmick;				//3D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pGasolene != nullptr)
	{
		//����������
		pGasolene->Init();
		pGasolene->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pGasolene;
}

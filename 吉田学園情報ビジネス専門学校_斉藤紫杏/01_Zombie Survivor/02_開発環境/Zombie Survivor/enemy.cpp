//============================================
// 
// 	enemy.cpp
// 	Author: saito shian
// 
//============================================

//============================================
// �C���N���[�h
//============================================
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "enemy.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"
#include "modelparts.h"
#include "keyset.h"
#include "key.h"
#include "motionset.h"
#include "score.h"
#include "player.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "indication.h"

//============================================
// �ÓI�����o�ϐ��錾
//===========================================

//============================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//============================================
CEnemy::CEnemy()
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
	m_nCountModel = 0;
	m_nLife = 0;
}

//============================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//============================================
CEnemy::~CEnemy()
{
	// ���������Ȃ�
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏���������
//============================================
HRESULT CEnemy::Init(void)
{
	//============================================
	// ����
	//============================================
	srand((unsigned int)time(nullptr));							//�N�����Ɉ�񂾂��s�����ߏ������ɏ���	

	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountModel = 0;
	m_PresentKeySet = 0;
	m_Frame = 0;
	m_nLife = 1;
	m_EnemyNumber = 0;
	m_VoiceCount = 0;
	m_MoveRand = 0;
	m_AttackCount = ATTACK_COUNT;
	m_PlayerDethFlag = false;
	m_MoveRandFlag = false;
	m_VoiceFlag = false;
	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			m_apModelHuman[nCnt] = nullptr;								//���f�����̏�����
			m_FrameSpeedHuman[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�t���[���X�s�[�h�̏�����
			m_RotSpeedHuman[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�X�s�[�h�̏�����
		}
	}
	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			m_apModelDog[nCnt] = nullptr;								//���f�����̏�����
			m_FrameSpeedDog[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�t���[���X�s�[�h�̏�����
			m_RotSpeedDog[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]�X�s�[�h�̏�����
		}
	}

	switch (m_type)
	{
	case CEnemy::ENEMYTYPE_HUMAN:
		//�v���C���[�̃t�@�C���ǂݍ���
		LoadEnemy("data/XMODEL/EnemyMotion.txt");
		break;
	case CEnemy::ENEMYTYPE_DOG:
		//�v���C���[�̃t�@�C���ǂݍ���
		LoadEnemy("data/XMODEL/EnemyDogMotion.txt");
		break;
	default:
		break;
	}

	//�ő�ŏ�
	Vtx();

	return S_OK;
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̏I������
//============================================
void CEnemy::Uninit(void)
{
	//�T�E���h�̒�~
//	StopSound(SOUND_LABEL_SE_VOICE);

	////���f���p�[�c�̏I������
	//for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
	//{
	//	if (m_apModel[nCnt] != nullptr)
	//	{
	//		m_apModel[nCnt]->Uninit();
	//		delete m_apModel[nCnt];
	//		m_apModel[nCnt] = nullptr;
	//	}
	//}

	//�j������
	Release();
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̍X�V����
//============================================
void CEnemy::Update(void)
{
//	CMeshField *pMeshField = CGame::GetMeshField();
	D3DXVECTOR3 CameraRot = CCamera::GetCameraRot();
	int EnemyCount = CGame::GetSpawn()->GetEnemyCount();

	m_posOld = m_pos;

	if (m_MoveRandFlag == false)
	{
		m_MoveRand = (float)(rand() % 9 + 7);
		m_MoveRandFlag = true;
	}
	if (m_PlayerDethFlag == false && m_MoveRandFlag == true)
	{
		if (m_type == ENEMYTYPE_HUMAN)
		{
			//�G�̈ړ�����
			EnemyMove(m_MoveRand);
		}
		if (m_type == ENEMYTYPE_DOG)
		{
			//�G�̈ړ�����
			EnemyMove(m_MoveRand);
		}
	}

	//���b�V���t�B�[���h�ƓG�̓����蔻��
	//pMeshField->GetMeshFieldCollision(&m_pos);

	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		//���f���Ƃ̓����蔻��
		CModelParts *pModelParts = CGame::GetModel()->GetModelParts()[nCnt];
		pModelParts->ModelCollision(&m_pos, &m_posOld, m_size);
	}

	if (m_VoiceCount >= 0)
	{
		m_VoiceCount--;
		if (m_VoiceCount <= 0)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_VOICE);
			m_VoiceCount = 300;
		}
	}

	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNext�̕ۑ�
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			if (pEnemy != this)
			{
				pEnemy->CollisionEnemy(&m_pos, &m_posOld, m_size);
			}
		}
		//pObject��pObject��pNext����
		pObject = pObjectNext;
	}


	//�����̐ݒ�
	SetRot(m_rot);
	//�ړ��̐ݒ�
	SetMove(m_move);
	//�ʒu�̐ݒ�
	SetPosition(m_pos);
}

//============================================
// �I�u�W�F�N�g(�|���S��)�̕`�揈��
//============================================
void CEnemy::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[�J���}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);											//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_type == ENEMYTYPE_HUMAN)
	{
		//���f���p�[�c��for��
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			if (m_apModelHuman[nCnt] != nullptr)
			{
				m_apModelHuman[nCnt]->DrawFile();
			}
		}
	}
	if (m_type == ENEMYTYPE_DOG)
	{
		//���f���p�[�c��for��
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			if (m_apModelDog[nCnt] != nullptr)
			{
				m_apModelDog[nCnt]->DrawFile();
			}
		}
	}
}

//============================================
// ����
//============================================
CEnemy * CEnemy::Create(const D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	// 3D�I�u�W�F�N�g�N���X�̐���
	pEnemy = new CEnemy;				// 3D�I�u�W�F�N�g�̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pEnemy != nullptr)
	{
		pEnemy->SetEnemyType(type);
		// ����������
		pEnemy->Init();
		pEnemy->SetPosition(pos);
		pEnemy->SetType(OBJTYPE_ENEMY);
	}
	else
	{
		assert(false);
	}
	return pEnemy;
}

//============================================
// �O���t�@�C���ǂݍ���
//============================================
void CEnemy::LoadEnemy(char * pFileName)
{
	if (m_type == ENEMYTYPE_HUMAN)
	{
		int nNumParts;
		int nCntMotionSet = 0;
		int Loop = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;
		char aText[2000];							//��������i�[����z��
		char FileName[MODEL_HUMAN_PARTS][2000];		//2�����z��

		FILE *pFile; //�t�@�C���|�C���^��錾

		pFile = fopen(pFileName, "r");

		aText[0] = '\0';	//������Ȃ�

		if (pFile != nullptr)
		{//�t�@�C�����J�����ꍇ
		 //�t�@�C���ɓ��͂����f�[�^�������o������
			while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
			{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
				fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
			}

			while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
			{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
				fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

				if (strncmp(&aText[0], "#", strlen("#")) == 0)
				{
					fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
					continue;
				}

				//�t�@�C���l�[���𕡐����͂���
				if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
					fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0�Ԗڂ���ǂݍ��܂��

					//���f���p�[�c�̐���
					m_apModelHuman[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					m_nCountModel++;
				}

				if (strcmp(&aText[0], "CHARACTERSET") == 0)
				{
					while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
					{
						fscanf(pFile, "%s", &aText[0]);

						if (strncmp(&aText[0], "#", strlen("#")) == 0)
						{
							fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
							continue;
						}

						if (strcmp(&aText[0], "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
							fscanf(pFile, "%d", &nNumParts);
						}

						if (strcmp(&aText[0], "PARTSSET") == 0)
						{
							D3DXVECTOR3 pos, rot;
							int IndexParent = 0;	//�e�̔ԍ�
							int Ind = 0;

							while (strcmp(&aText[0], "END_PARTSSET") != 0)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strncmp(&aText[0], "#", strlen("#")) == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
									continue;
								}

								if (strcmp(&aText[0], "INDEX") == 0)
								{
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &Ind);
								}

								else if (strcmp(&aText[0], "PARENT") == 0)
								{

									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &IndexParent);
								}

								else if (strcmp(&aText[0], "POS") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									pos = D3DXVECTOR3(x, y, z);
								}

								else if (strcmp(&aText[0], "ROT") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									rot = D3DXVECTOR3(x, y, z);
								}
							}

							//���f���p�[�c�̐���
							m_apModelHuman[Ind] = CModelParts::Create(pos, rot);

							//���f���p�[�c�̓ǂݍ���
							m_apModelHuman[Ind]->SetModel(&FileName[Ind][0]);

							//���f���p�[�c�ɏ�񂪓����Ă�����
							if (m_apModelHuman[Ind])
							{
								//���f���p�[�c�̌����̐ݒ�
								m_apModelHuman[Ind]->SetRot(rot);
							}

							//�e�̔ԍ���0��艺��������
							if (IndexParent < 0)
							{
								//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
								m_apModelHuman[Ind]->SetMatrix(&m_mtxWorld);
							}
							//�e�̔ԍ������f���p�[�c��菬����������
							else if (IndexParent < MODEL_HUMAN_PARTS)
							{
								//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
								m_apModelHuman[Ind]->SetMatrix(m_apModelHuman[IndexParent]->GetMatrix());
							}
						}
					}
				}
				if (strcmp(&aText[0], "MOTIONSET") == 0)
				{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�

					m_MotionSet[nCntMotionSet] = CMotionSet::Create();

					m_MotionSet[nCntMotionSet]->SetNumParts(nNumParts);

					while (strcmp(&aText[0], "END_MOTIONSET") != 0)
					{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
						fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							int numKey = 0;
							fscanf(pFile, "%s %d", &aText[0], &numKey);
							m_MotionSet[nCntMotionSet]->SetNumKey(numKey);
						}

						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &Loop);

							if (Loop == 1)
							{

								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(1);
							}

							else
							{
								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(0);
							}
						}

						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strcmp(&aText[0], "#") == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
									continue;
								}

								if (strcmp(&aText[0], "END_KEYSET") == 0)
								{
									nCntKeySet++;
									nCntKey = 0;
									break;
								}

								if (strcmp(&aText[0], "FRAME") == 0)
								{
									int nFrame = 0;
									fscanf(pFile, "%s %d", &aText[0], &nFrame);

									m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->SetFrame(nFrame);
								}

								else if (strcmp(&aText[0], "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aText[0]);

										if (strcmp(&aText[0], "END_KEY") == 0)
										{
											nCntKey++;

											if (nCntKey >= m_MotionSet[nCntMotionSet]->GetNumParts())
											{
												nCntKey = 0;
											}
											break;
										}
										else if (strcmp(&aText[0], "POS") == 0)
										{
											float px = 0.0f;
											float py = 0.0f;
											float pz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &px);
											fscanf(pFile, "%f", &py);
											fscanf(pFile, "%f", &pz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetPos(D3DXVECTOR3(px, py, pz));
										}

										else if (strcmp(&aText[0], "ROT") == 0)
										{
											float rx = 0.0f;
											float ry = 0.0f;
											float rz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &rx);
											fscanf(pFile, "%f", &ry);
											fscanf(pFile, "%f", &rz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetRot(D3DXVECTOR3(rx, ry, rz));
										}
									}
								}
							}
						}
					}

					nCntMotionSet++;
					nCntKeySet = 0;
					nCntKey = 0;
				}
			}
		}
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			if (m_apModelHuman[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos, rot;
				pos = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetPos();
				rot = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetRot();
				m_apModelHuman[nCnt]->SetPos(pos);
				m_apModelHuman[nCnt]->SetRot(rot);
			}
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		int nNumParts;
		int nCntMotionSet = 0;
		int Loop = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;
		char aText[2000];							//��������i�[����z��
		char FileName[MODEL_DOG_PARTS][2000];		//2�����z��

		FILE *pFile; //�t�@�C���|�C���^��錾

		pFile = fopen(pFileName, "r");

		aText[0] = '\0';	//������Ȃ�

		if (pFile != nullptr)
		{//�t�@�C�����J�����ꍇ
		 //�t�@�C���ɓ��͂����f�[�^�������o������
			while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
			{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
				fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
			}

			while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
			{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
				fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

				if (strncmp(&aText[0], "#", strlen("#")) == 0)
				{
					fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
					continue;
				}

				//�t�@�C���l�[���𕡐����͂���
				if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
					fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0�Ԗڂ���ǂݍ��܂��

																		//���f���p�[�c�̐���
					m_apModelDog[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					m_nCountModel++;
				}

				if (strcmp(&aText[0], "CHARACTERSET") == 0)
				{
					while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
					{
						fscanf(pFile, "%s", &aText[0]);

						if (strncmp(&aText[0], "#", strlen("#")) == 0)
						{
							fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
							continue;
						}

						if (strcmp(&aText[0], "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
							fscanf(pFile, "%d", &nNumParts);
						}

						if (strcmp(&aText[0], "PARTSSET") == 0)
						{
							D3DXVECTOR3 pos, rot;
							int IndexParent = 0;	//�e�̔ԍ�
							int Ind = 0;

							while (strcmp(&aText[0], "END_PARTSSET") != 0)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strncmp(&aText[0], "#", strlen("#")) == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
									continue;
								}

								if (strcmp(&aText[0], "INDEX") == 0)
								{
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &Ind);
								}

								else if (strcmp(&aText[0], "PARENT") == 0)
								{

									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &IndexParent);
								}

								else if (strcmp(&aText[0], "POS") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									pos = D3DXVECTOR3(x, y, z);
								}

								else if (strcmp(&aText[0], "ROT") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									rot = D3DXVECTOR3(x, y, z);
								}
							}

							//���f���p�[�c�̐���
							m_apModelDog[Ind] = CModelParts::Create(pos, rot);

							//���f���p�[�c�̓ǂݍ���
							m_apModelDog[Ind]->SetModel(&FileName[Ind][0]);

							//���f���p�[�c�ɏ�񂪓����Ă�����
							if (m_apModelDog[Ind])
							{
								//���f���p�[�c�̌����̐ݒ�
								m_apModelDog[Ind]->SetRot(rot);
							}

							//�e�̔ԍ���0��艺��������
							if (IndexParent < 0)
							{
								//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
								m_apModelDog[Ind]->SetMatrix(&m_mtxWorld);
							}
							//�e�̔ԍ������f���p�[�c��菬����������
							else if (IndexParent < MODEL_DOG_PARTS)
							{
								//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
								m_apModelDog[Ind]->SetMatrix(m_apModelDog[IndexParent]->GetMatrix());
							}
						}
					}
				}
				if (strcmp(&aText[0], "MOTIONSET") == 0)
				{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�

					m_MotionSet[nCntMotionSet] = CMotionSet::Create();

					m_MotionSet[nCntMotionSet]->SetNumParts(nNumParts);

					while (strcmp(&aText[0], "END_MOTIONSET") != 0)
					{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
						fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							int numKey = 0;
							fscanf(pFile, "%s %d", &aText[0], &numKey);
							m_MotionSet[nCntMotionSet]->SetNumKey(numKey);
						}

						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &Loop);

							if (Loop == 1)
							{

								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(1);
							}

							else
							{
								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(0);
							}
						}

						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strcmp(&aText[0], "#") == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //��s���Ɠǂݍ���
									continue;
								}

								if (strcmp(&aText[0], "END_KEYSET") == 0)
								{
									nCntKeySet++;
									nCntKey = 0;
									break;
								}

								if (strcmp(&aText[0], "FRAME") == 0)
								{
									int nFrame = 0;
									fscanf(pFile, "%s %d", &aText[0], &nFrame);

									m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->SetFrame(nFrame);
								}

								else if (strcmp(&aText[0], "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aText[0]);

										if (strcmp(&aText[0], "END_KEY") == 0)
										{
											nCntKey++;

											if (nCntKey >= m_MotionSet[nCntMotionSet]->GetNumParts())
											{
												nCntKey = 0;
											}
											break;
										}
										else if (strcmp(&aText[0], "POS") == 0)
										{
											float px = 0.0f;
											float py = 0.0f;
											float pz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &px);
											fscanf(pFile, "%f", &py);
											fscanf(pFile, "%f", &pz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetPos(D3DXVECTOR3(px, py, pz));
										}

										else if (strcmp(&aText[0], "ROT") == 0)
										{
											float rx = 0.0f;
											float ry = 0.0f;
											float rz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &rx);
											fscanf(pFile, "%f", &ry);
											fscanf(pFile, "%f", &rz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetRot(D3DXVECTOR3(rx, ry, rz));
										}
									}
								}
							}
						}
					}

					nCntMotionSet++;
					nCntKeySet = 0;
					nCntKey = 0;
				}
			}
		}
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			if (m_apModelDog[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos, rot;
				pos = m_MotionSet[0]->GetKeySet(1)->GetKey(nCnt)->GetPos();
				rot = m_MotionSet[0]->GetKeySet(1)->GetKey(nCnt)->GetRot();
				m_apModelDog[nCnt]->SetPos(pos);
				m_apModelDog[nCnt]->SetRot(rot);
			}
		}
	}
}

//============================================
// ���[�V�����֐�
//============================================
void CEnemy::MotionEnemyAnimation(void)
{
	m_Frame++;		//�t���[���̃C���N�������g

	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			D3DXVECTOR3 pos = m_apModelHuman[nCnt]->GetPos();		//���f���p�[�c�̈ʒu�擾
			D3DXVECTOR3 rot = m_apModelHuman[nCnt]->GetRot();		//���f���p�[�c�̌����擾
			pos += m_FrameSpeedHuman[nCnt];							//���f���p�[�c�̈ʒu�Ƀt���[���̑�������
			rot += m_RotSpeedHuman[nCnt];							//���f���p�[�c�̌����Ɍ����̑�������
			m_apModelHuman[nCnt]->SetPos(pos);						//�ʒu�̐ݒ�
			m_apModelHuman[nCnt]->SetRot(rot);						//�����̐ݒ�
		}

		if (m_Frame >= m_MotionSet[m_MotionType]->GetKeySet(m_PresentKeySet)->GetFrame())
		{	//���݂̃A�j���[�V�����̃t���[�����ȏゾ������

			int NextKeySet = 0;					//���̃L�[�Z�b�g�ϐ�
			NextKeySet = m_PresentKeySet + 1;	//���̃L�[�Z�b�g����

			if (NextKeySet >= m_MotionSet[m_MotionType]->GetNumKey() && m_MotionSet[m_MotionType]->GetLoop() == 1)
			{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���

				NextKeySet = 0;					//�Đ����̃L�[���J�E���g��������

			}
			else if (NextKeySet >= m_MotionSet[m_MotionType]->GetNumKey() && m_MotionSet[m_MotionType]->GetLoop() == 0)
			{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ�

				m_MotionSet[m_MotionType]->SetLoop(false);		//���[�v��false�ɐݒ肷��	
				NextKeySet = 0;											//���̃L�[�Z�b�g�̏�����
			}

			for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
			{
				//���x�̌v�Z
				m_FrameSpeedHuman[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_apModelHuman[nCnt]->GetPos());
				m_FrameSpeedHuman[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedHuman[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedHuman[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				//��]�̌v�Z
				m_RotSpeedHuman[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_apModelHuman[nCnt]->GetRot());
				m_RotSpeedHuman[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedHuman[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedHuman[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			}

			m_Frame = 0;						//�t���[���̏�����
			m_PresentKeySet = NextKeySet;
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			D3DXVECTOR3 pos = m_apModelDog[nCnt]->GetPos();			//���f���p�[�c�̈ʒu�擾
			D3DXVECTOR3 rot = m_apModelDog[nCnt]->GetRot();			//���f���p�[�c�̌����擾
			pos += m_FrameSpeedDog[nCnt];							//���f���p�[�c�̈ʒu�Ƀt���[���̑�������
			rot += m_RotSpeedDog[nCnt];								//���f���p�[�c�̌����Ɍ����̑�������
			m_apModelDog[nCnt]->SetPos(pos);						//�ʒu�̐ݒ�
			m_apModelDog[nCnt]->SetRot(rot);						//�����̐ݒ�
		}

		if (m_Frame >= m_MotionSet[0]->GetKeySet(m_PresentKeySet)->GetFrame())
		{	//���݂̃A�j���[�V�����̃t���[�����ȏゾ������

			int NextKeySet = 0;					//���̃L�[�Z�b�g�ϐ�
			NextKeySet = m_PresentKeySet + 1;	//���̃L�[�Z�b�g����

			if (NextKeySet >= m_MotionSet[0]->GetNumKey() && m_MotionSet[0]->GetLoop() == 1)
			{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���

				NextKeySet = 0;					//�Đ����̃L�[���J�E���g��������

			}
			else if (NextKeySet >= m_MotionSet[0]->GetNumKey() && m_MotionSet[0]->GetLoop() == 0)
			{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ�

				m_MotionSet[0]->SetLoop(false);		//���[�v��false�ɐݒ肷��	
				NextKeySet = 0;											//���̃L�[�Z�b�g�̏�����
			}

			for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
			{
				//���x�̌v�Z
				m_FrameSpeedDog[nCnt] = (m_MotionSet[0]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_apModelDog[nCnt]->GetPos());
				m_FrameSpeedDog[nCnt].x /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedDog[nCnt].y /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedDog[nCnt].z /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				//��]�̌v�Z
				m_RotSpeedDog[nCnt] = (m_MotionSet[0]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_apModelDog[nCnt]->GetRot());
				m_RotSpeedDog[nCnt].x /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedDog[nCnt].y /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedDog[nCnt].z /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
			}

			m_Frame = 0;						//�t���[���̏�����
			m_PresentKeySet = NextKeySet;
		}
	}
}


//============================================
// ���_�̍ő�ŏ�
//============================================
void CEnemy::Vtx(void)
{
	D3DXVECTOR3 min = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			int nNumVtx;	//���_��
			DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

			//���_���̎擾
			nNumVtx = m_apModelHuman[nCnt]->GetMesh()->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(m_apModelHuman[nCnt]->GetMesh()->GetFVF());

			//���_�o�b�t�@�̃��b�N
			m_apModelHuman[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ă��f���̍ŏ��l�A�ő�l���擾
				//x�̔�r
				if (vtx.x < min.x)
				{
					min.x = vtx.x;
				}
				if (vtx.x > max.x)
				{
					max.x = vtx.x;
				}

				//y�̔�r(�ŏ��l)
				if (vtx.y < min.y)
				{
					min.y = vtx.y;
				}
				if (vtx.y > max.y)
				{
					max.y = vtx.y;
				}

				//z�̔�r(�ŏ��l)
				if (vtx.z < min.z)
				{
					min.z = vtx.z;
				}
				if (vtx.z > max.z)
				{
					max.z = vtx.z;
				}
				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			//���_�o�b�t�@�̃A�����b�N
			m_apModelHuman[nCnt]->GetMesh()->UnlockVertexBuffer();

			m_apModelHuman[nCnt]->SetVtxMin(min);
			m_apModelHuman[nCnt]->SetVtxMax(max);
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			int nNumVtx;	//���_��
			DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
			BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

							//���_���̎擾
			nNumVtx = m_apModelDog[nCnt]->GetMesh()->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(m_apModelDog[nCnt]->GetMesh()->GetFVF());

			//���_�o�b�t�@�̃��b�N
			m_apModelDog[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ă��f���̍ŏ��l�A�ő�l���擾
				//x�̔�r
				if (vtx.x < min.x)
				{
					min.x = vtx.x;
				}
				if (vtx.x > max.x)
				{
					max.x = vtx.x;
				}

				//y�̔�r(�ŏ��l)
				if (vtx.y < min.y)
				{
					min.y = vtx.y;
				}
				if (vtx.y > max.y)
				{
					max.y = vtx.y;
				}

				//z�̔�r(�ŏ��l)
				if (vtx.z < min.z)
				{
					min.z = vtx.z;
				}
				if (vtx.z > max.z)
				{
					max.z = vtx.z;
				}
				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			//���_�o�b�t�@�̃A�����b�N
			m_apModelDog[nCnt]->GetMesh()->UnlockVertexBuffer();

			m_apModelDog[nCnt]->SetVtxMin(min);
			m_apModelDog[nCnt]->SetVtxMax(max);
		}
	}
	//�G�̃T�C�Y
	m_size = D3DXVECTOR3(max.x - min.x, max.y - min.y, max.z - min.z);
}

//============================================
// �v���C���[�̓����蔻��
//============================================
void CEnemy::CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size)
{
	//���̓����蔻��
	if (pPos->z - size.z / 2.0f < m_pos.z + m_size.z / 2
		&& pPos->z + size.z / 2.0f > m_pos.z - m_size.z / 2
		&& (int)(pPosOld->x + size.x / 2.0f) <= (int)(m_pos.x - m_size.x / 2)
		&& (int)(pPos->x + size.x / 2.0f) > (int)(m_pos.x - m_size.x / 2))
	{
		pPos->x = (int)(m_pos.x - m_size.x / 2 - size.x / 2.0f);
	}

	//�E�̓����蔻��
	if (pPos->z - size.z / 2.0f < m_pos.z + m_size.z / 2
		&& pPos->z + size.z / 2.0f > m_pos.z - m_size.z / 2
		&& (int)(pPosOld->x - size.x / 2.0f) >= (int)(m_pos.x + m_size.x / 2)
		&& (int)(pPos->x - size.x / 2.0f) < (int)(m_pos.x + m_size.x / 2))
	{
		pPos->x = (int)(m_pos.x + m_size.x / 2 + size.x / 2.0f);
	}

	//��O�̓����蔻��
	if (pPos->x - size.x / 2.0f < m_pos.x + m_pos.x / 2
		&&pPos->x + size.x / 2.0f > m_pos.x - m_pos.x  /2
		&& (int)(pPosOld->z + size.z / 2.0f) <= (int)(m_pos.z - m_pos.z / 2)
		&& (int)(pPos->z + size.z / 2.0f) > (int)(m_pos.z - m_pos.z / 2))
	{
		pPos->z = (int)(m_pos.z - m_pos.z / 2 - size.z / 2.0f);
	}

	//���̓����蔻��
	if (pPos->x - size.x / 2.0f < m_pos.x + m_pos.x / 2
		&& pPos->x + size.x / 2.0f > m_pos.x - m_pos.x / 2
		&& (int)(pPosOld->z - size.z / 2.0f) >= (int)(m_pos.z + m_pos.z / 2)
		&& (int)(pPos->z - size.z / 2.0f) < (int)(m_pos.z + m_pos.z / 2))
	{
		pPos->z = (int)(m_pos.z + m_pos.z / 2 + size.z / 2.0f);
	}
}

//============================================
// �G�̈ړ�����
//============================================
void CEnemy::EnemyMove(float speed)
{
	D3DXVECTOR3 PlayerRot = GetRot();

	//�O��̈ʒu��ۑ�
	m_posOld = m_pos;

	//============================================
	//  �ړI�̊p�x�̐��K��
	//============================================
	if (m_rotDest.y - PlayerRot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - PlayerRot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	// �p�x����
	PlayerRot.y += (m_rotDest.y - PlayerRot.y) * 0.1f;

	//============================================
	//  �p�x�̐��K��
	//============================================
	if (PlayerRot.y > D3DX_PI)
	{
		PlayerRot.y = PlayerRot.y - D3DX_PI * 2;
	}
	else if (PlayerRot.y < -D3DX_PI)
	{
		PlayerRot.y = PlayerRot.y + D3DX_PI * 2;
	}

	//���[�V�����֐�
	MotionEnemyAnimation();

	//============================================
	//  �v���C���[��Ǐ]���鏈��
	//============================================
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();

	m_move = m_pos - PlayerPos;				//�v���C���[�̈ʒu�ƓG�̈ʒu���v�Z���Ĉړ��ɑ��
	D3DXVec3Normalize(&m_move, &m_move);	//�ړ��̐��K��
	m_move *= speed;						//�ړ��X�s�[�h

	//2�_�Ԃ̋��������߂�
	float Rotx = m_pos.x - PlayerPos.x;
	float Rotz = m_pos.z - PlayerPos.z;

	//�p�x�̐ݒ�
	float Angle = atan2f(Rotx, Rotz);

	//�ړI�̌����̐ݒ�
	m_rotDest = D3DXVECTOR3(0.0f, Angle, 0.0f);

	//======================
	//�ړI�̕����̐��K��
	//======================
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//�ړI�̒l�ɋ߂Â���
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.08f;

	//======================
	//���K��
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	//�ړ����[�V�����ɐݒ�
	SetMotionType(CEnemy::MOTIONTYPE_MOVE);

	if (m_PlayerDethFlag == false && CGame::GetPlayer() != nullptr)
	{
		int PlayerLife = CGame::GetPlayer()->GetLife();

		if (PlayerPos.x + 30.0f >= m_pos.x + m_size.x && PlayerPos.x - 30.0f <= m_pos.x - m_size.x
			&&PlayerPos.z + 30.0f >= m_pos.z + m_size.z && PlayerPos.z - 30.0f <= m_pos.z - m_size.z)
		{	//�G���v���C���[���U������͈�
			SetMotionType(CEnemy::MOTIONTYPE_ATTACK);
			if (m_MotionType == MOTIONTYPE_ATTACK)
			{
				m_AttackCount--;
				if (m_AttackCount <= 0)
				{
					PlayerLife--;

					if (PlayerLife <= 0)
					{
						m_PlayerDethFlag = true;
						CFade::SetFade(CApplication::MODE_RESULT);
						CResult::SetType(CResult::TYPE_GAMEOVER);
						CGame::GetPlayer()->Uninit();
						CGame::SetPlayer(nullptr);
						CSpawn::SetBoss(nullptr);
						return;
					}
					else
					{
						if (m_RandFlag == false)
						{
							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								float x = rand() % 1280 + 1;
								float y = rand() % 720 + 1;
								float sxy = rand() % 75 + 15;
								CIndication::Create(D3DXVECTOR3(x, y, 0.0f), D3DXVECTOR3(sxy, sxy, 0.0f), CIndication::INDICATIONTYPE_BLOOD);
							}
							m_RandFlag = true;
						}
						CGame::GetPlayer()->SetPlayerLife(PlayerLife);
					}
				}
				if (m_AttackCount <= 0)
				{
					m_AttackCount = ATTACK_COUNT;
				}
			}
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SetMove(m_move);
		}
		else
		{
			m_AttackCount = ATTACK_COUNT;
		}
	}

	//�ړ��ʌ���
	m_pos.x += (0.0f - m_move.x) * 0.1f;
	m_pos.y += (0.0f - m_move.y) * 0.1f;
	m_pos.z += (0.0f - m_move.z) * 0.1f;
}

//============================================
// ���[�V�����̎�ނ̐ݒ�
//============================================
void CEnemy::SetMotionType(MOTIONTYPE type)
{
	m_MotionType = type;
}


//============================================
// �G�̎��
//============================================
void CEnemy::SetEnemyType(ENEMYTYPE type)
{
	m_type = type;
}

//============================================
// �ʒu�̐ݒ�
//============================================
void CEnemy::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �����̐ݒ�
//============================================
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// �ړ��̐ݒ�
//============================================
void CEnemy::SetMove(D3DXVECTOR3 move)
{
	move;
}

//============================================
// �����̐ݒ�
//============================================
void CEnemy::SetLength(float length)
{
	length;
}

//============================================
// �̗͂̐ݒ�
//============================================
void CEnemy::SetLife(int life)
{
	m_nLife = life;
}

//============================================
// �ʒu�̎擾
//============================================
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

//============================================
// �ړ��̎擾
//============================================
D3DXVECTOR3 CEnemy::GetMove(void)
{
	return D3DXVECTOR3();
}

//============================================
// �����̎擾
//============================================
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

//============================================
// �����̎擾
//============================================
float CEnemy::GetLength(void)
{
	return 0.0f;
}

//============================================
// �̗͂̎擾
//============================================
int CEnemy::GetLife(void)
{
	return m_nLife;
}


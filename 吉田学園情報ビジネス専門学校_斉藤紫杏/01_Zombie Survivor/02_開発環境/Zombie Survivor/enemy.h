//============================================
//
//	enemy.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"
#include "model.h"
#include "spawn.h"

//============================================
// �}�N����`
//============================================
#define HUMAN_MOVE			(7.0f)		//�l�^�G�̈ړ�
#define DOG_MOVE			(10.0f)		//���^�G�̈ړ�
#define MAX_ENEMY_WORD		(512)		//���[�h��
#define MODEL_HUMAN_PARTS	(15)		//�l�^�]���r���f���̃p�[�c��
#define MODEL_DOG_PARTS		(12)		//���^�]���r���f���̃p�[�c��
#define MOTION_ENEMY_NUMBER	(2)			//���[�V������
#define ATTACK_COUNT		(40)		//�U������܂ł̎���

//============================================
// �O���錾
//============================================
class CShadow;
class CModelParts;
class CMotionSet;
class CKeySet;
class CKey;

//============================================
// �G�N���X
//============================================
class CEnemy : public CObject
{
public:
	enum ENEMYTYPE
	{
		ENEMYTYPE_NONE = 0,
		ENEMYTYPE_HUMAN,	//�l�^�̓G
		ENEMYTYPE_DOG,		//���^�̓G
		ENEMYTYPE_MAX
	};

	//============================================
	// ���[�V�����̎��
	//============================================
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,					//�j���[�g�������[�V����
		MOTIONTYPE_MOVE,								//�ړ����[�V����
		MOTIONTYPE_ATTACK,								//�U�����[�V����
		MOTIONTYPE_MAX
	};

	CEnemy();											//�R���X�g���N�^
	~CEnemy()override;									//�f�X�g���N�^

	HRESULT Init(void)override;							//�G�̏���������
	void Uninit(void)override;							//�G�̏I������
	void Update(void)override;							//�G�̍X�V����
	void Draw(void)override;							//�G�̕`�揈��

	void LoadEnemy(char * pFileName);					//�G�̓ǂݍ���
	void Vtx(void);										//�ő�ŏ�
	void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//���f���Ƃ̓����蔻��
	void EnemyMove(float speed);						//�G�̈ړ�����

	//setter
	void SetPosition(D3DXVECTOR3 pos);					//�G�̈ʒu����
	void SetRot(D3DXVECTOR3 rot);						//�G�̉�]����
	void SetMove(D3DXVECTOR3 move);						//�G�̈ړ�����
	void SetLength(float length);						//�����̐ݒ菈��
	void SetLife(int life);								//�̗͂̐ݒ菈��
	void SetMotionType(MOTIONTYPE type);				//���[�V�����̎�ނ̐ݒ菈��
	void SetEnemyType(ENEMYTYPE type);					//�G�̎��

	//getter
	D3DXVECTOR3 GetEnemyPos(void) { return m_pos; }		//�G�̈ʒu�擾
	D3DXVECTOR3 GetEnemySize(void) { return m_size; }	//�G�̃T�C�Y�擾
	D3DXVECTOR3 GetEnemyRot(void) { return m_rot; }		//�G�̌����̎擾
	D3DXVECTOR3 GetPos(void);							//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void);							//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(); }	//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void);							//��]�̎擾
	float GetLength(void);								//�g��k���̃X�P�[���̎擾
	int GetLife(void);									//�̗͂̎擾����

	static CEnemy *Create(const D3DXVECTOR3 pos, ENEMYTYPE type);				//����

private:
	//============================================
	// �v���C�x�[�g�֐�
	//============================================
	void MotionEnemyAnimation(void);					//���[�V�����֐�

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR3 m_size;									//�T�C�Y
	D3DXVECTOR3 m_VtxMinModel;							//�ŏ�
	D3DXVECTOR3 m_VtxMaxModel;							//�ő�
	CModelParts *m_apModelHuman[MODEL_HUMAN_PARTS];		//�l�^���f���p�[�c
	CModelParts *m_apModelDog[MODEL_DOG_PARTS];			//���^���f���p�[�c
	CMotionSet *m_MotionSet[MOTION_ENEMY_NUMBER];		//���[�V�����Z�b�g
	CKeySet *m_KeySet;									//�L�[�Z�b�g
	CKey *m_Key;										//�L�[
	D3DXVECTOR3 m_posOld;								//�ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;								//�ړI�̌���
	D3DXVECTOR3 m_FrameSpeedHuman[MODEL_HUMAN_PARTS];	//�l�^�t���[���̑���
	D3DXVECTOR3 m_FrameSpeedDog[MODEL_DOG_PARTS];		//���^�t���[���̑���
	D3DXVECTOR3 m_RotSpeedHuman[MODEL_HUMAN_PARTS];		//�l�^��]�̑���
	D3DXVECTOR3 m_RotSpeedDog[MODEL_DOG_PARTS];			//���^��]�̑���
	D3DXVECTOR3 m_move;									//�ړ�
	D3DXMATRIX m_mtxWorld;								//���[���h�}�g���b�N�X
	D3DXMATRIX *m_pmtxParent;							//�e�̃}�g���b�N�X
	CShadow *m_pShadow;									//�e

	MOTIONTYPE m_MotionType;							//���[�V�����̎��
	ENEMYTYPE m_type;									//�G�̎��

	int m_Frame;										//�t���[��
	int m_PresentKeySet;								//���݂̃L�[�Z�b�g
	int m_nLife;										//�̗�
	int m_nCountModel;									//���f�����̃J�E���g
	int m_EnemyNumber;									//�G�̔ԍ�
	int m_AttackCount;									//�U������܂ł̎���
	int m_VoiceCount;									//���𔭂���܂ł̎���
	int m_VoiceRand;									//���𔭂���܂ł̃����_���Ȏ���
	int m_MoveRand;										//�ړ��̃����_���ϐ�

	float m_PlayerHeightPos;							//�G�̍����̈ʒu
	float m_Length;										//����
	float m_Angle;										//�p�x

	bool m_PlayerDethFlag;								//�v���C���[�����񂾂̂��t���O
	bool m_VoiceFlag;									//���𔭂��Ă��邩
	bool m_RandFlag;									//�����_���t���O
	bool m_MoveRandFlag;								//�ړ��̃����_���t���O
};

#endif

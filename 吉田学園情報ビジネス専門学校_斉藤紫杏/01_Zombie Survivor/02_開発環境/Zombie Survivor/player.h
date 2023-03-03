//============================================
//
//	player.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================
#define PLAYER_MOVE			(1.5f)		//�v���C���[�̈ړ�
#define PLAYER_DASH_MOVE	(2.5f)		//�����Ă���Ƃ��̈ړ�
#define PLAYER__ADS_MOVE	(0.5f)		//�v���C���[��ADS�ړ�
#define MAX_WORD			(512)		//���[�h��
#define MODEL_NUMBER		(20)		//���f���̃p�[�c��
#define MOTION_NUMBER		(6)			//���[�V������
#define BULLET_TIME			(20)		//�e�����������܂ł̎���

//============================================
// �O���錾
//============================================
class CModelParts;
class CMotionSet;
class CKeySet;
class CKey;
class CCamera;
class CBillboard;
class CBullet;
class CReticle;

//============================================
// �v���C���[�N���X
//============================================
class CPlayer : public CObject
{
public:
	//============================================
	// ���[�V�����̎��
	//============================================
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,				//�j���[�g�������[�V����
		MOTIONTYPE_STANDBYATTACK,					//�e���\���郂�[�V����
		MOTIONTYPE_ATTACK,							//�U�����[�V����
		MOTIONTYPE_MOVE,							//�ړ����[�V����
		MOTIONTYPE_DASH,							//�ړ�(����)���[�V����
		MOTIONTYPE_THROW,							//�����郂�[�V����
		MOTIONTYPE_NONE,
		MOTIONTYPE_MAX
	};

	CPlayer();										//�R���X�g���N�^
	~CPlayer()override;								//�f�X�g���N�^

	HRESULT Init(void)override;						//�v���C���[�̏���������
	void Uninit(void)override;						//�v���C���[�̏I������
	void Update(void)override;						//�v���C���[�̍X�V����
	void Draw(void)override;						//�v���C���[�̕`�揈��

	void LoadPlayer();								//�v���C���[�̓ǂݍ���
	void Vtx(void);									//�ő�ŏ�
	void CollisionPlayer(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//���f���Ƃ̓����蔻��
	void CollisionMaxModel();															//�S���̃��f���Ƃ̓����蔻��

	static D3DXVECTOR3 GetPlayerPos(void) { return m_pos; }		//�v���C���[�̈ʒu�擾
	static D3DXVECTOR3 GetPlayerRot(void) { return m_rot; }		//�v���C���[�̌����̎擾
	D3DXVECTOR3 GetPlayerSize(void) { return m_size; }			//�v���C���[�̃T�C�Y�̎擾
	static CBullet *GetBullet(void) { return m_pBullet; }		//�e�̏��̎擾����

	int GetLife(void) { return m_Life; }						//�v���C���[�̗̑͂̎擾����

	static CPlayer *Create(const D3DXVECTOR3 &pos);				//����

	void SetPosition(D3DXVECTOR3 pos);			//�v���C���[�̈ʒu����
	void SetRot(D3DXVECTOR3 rot);				//�v���C���[�̌����̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);				//�v���C���[�̈ړ�����
	void SetLength(float length);				//�v���C���[�̒����̐ݒ菈��
	void SetMotionType(MOTIONTYPE type);		//���[�V�����̎�ނ̐ݒ菈��
	void SetPlayerLife(int life);				//�v���C���[�̗̑͂̐ݒ菈��
	void SetBombUseCount(int usecnt);			//���e������g�p�����̂��̐ݒ菈��
	void GetBombUseFlag(bool flag);				//���e���g�p�����̂��̐ݒ菈��
	static void SetBullet(CBullet *bullet);		//�{�X�̐ݒ菈��

	void PlayerMove(void);						//�v���C���[�̈ړ�����
	void PlayerAttack(void);					//�v���C���[�̍U������

	D3DXVECTOR3 GetPos(void);					//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void);					//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void);					//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void);					//��]�̎擾
	float GetLength(void);						//�g��k���̃X�P�[���̎擾
	int GetBombUseCount(void);					//���e������g�p�����̂��̎擾����
	bool GetBombUseFlag(void);					//���e���g�p�����̂��̎擾����

private:

	//============================================
	// �v���C�x�[�g�֐�
	//============================================
	void MotionAnimation(void);				//���[�V�����֐�

	//============================================
	// �����o�ϐ�
	//============================================
	static D3DXVECTOR3 m_pos;				//�ʒu
	static D3DXVECTOR3 m_rot;				//����
	static CBullet *m_pBullet;				//�e�̃C���X�^���X
	
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_posOld;					//�O��̈ʒu
	D3DXVECTOR3 m_rotDest;					//�ړI�̌���
	D3DXVECTOR3 m_ADSRotDest;				//�G�C�����̖ړI�̌���
	D3DXVECTOR3 m_FrameSpeed[MODEL_NUMBER];	//�t���[���̑���
	D3DXVECTOR3 m_RotSpeed[MODEL_NUMBER];	//��]�̑���
	D3DXVECTOR3 m_VtxMinModel;				//�ŏ�
	D3DXVECTOR3 m_VtxMaxModel;				//�ő�
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX *m_pmtxParent;				//�e�̃}�g���b�N�X	
	CModelParts *m_apModel[MODEL_NUMBER];	//���f���p�[�c
	CMotionSet *m_MotionSet[MOTION_NUMBER];	//���[�V�����Z�b�g
	CBillboard *m_pBillboard;				//�r���{�[�h�̃C���X�^���X����
	CObject *m_pObjectTarget;				//�����蔻��Ώۂ̃I�u�W�F�N�g
	CReticle *m_pReticle;					//���e�B�N���̃C���X�^���X

	MOTIONTYPE m_MotionType;				//���[�V�����̎��

	int m_Life;								//�̗�
	int m_Frame;							//�t���[��
	int m_PresentKeySet;					//���݂̃L�[�Z�b�g
	int m_nCountModel;						//���f�����̃J�E���g
	int m_BulletCreateTime;					//�e�𐶐�����܂ł̎���
	int m_ThrowTime;						//�����郂�[�V�������I���܂ł̎���
	int m_BombUseCount;						//���e������g�p�����̂�

	static bool m_PlayerAttackFlag;			//�v���C���[���G�C���������̂��t���O

	float m_PlayerHeightPos;				//�v���C���[�̍����̈ʒu
	float m_Speed;							//�ړ�����

	bool m_AnimationFlag;					//�ړ��̃A�j���[�V�����t���O
	bool m_AttackAnimationFlag;				//�U���̐��̃A�j���[�V�����̃t���O
	bool m_SoundRunFlag;					//�����Ă���T�E���h���g���Ă��邩
	bool m_SoundAttackFlag;					//�U���̃T�E���h���g���Ă��邩	
	bool m_BulletCreateFlag;				//�e���������ꂽ���̃t���O
	bool m_ThrowFlag;						//�����郂�[�V�����t���O
	bool m_BombUseCountFlag;				//���e������g�p�����̂��t���O
	bool m_DashFlag;						//�����Ă��邩�t���O
	bool m_DashAnimationFlag;				//�����Ă��鎞�̃��[�V�����t���O
};

#endif

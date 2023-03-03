//============================================
//
//	bullet.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _BULLET_H_
#define _BULLET_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectBase.h"

//============================================
// �}�N����`
//============================================
#define BOMB_SIZE			(9.0f)				//���e�̃T�C�Y
#define BOMB_HIT_SIZE		(75.0f)				//�{�X�̒e�̓����蔻��T�C�Y

//============================================
// �O���錾
//============================================
class CEnemy;
class CFade;

//============================================
// �e�N���X
//============================================
class CBullet : public CObjectBase
{
public:
	enum BULLETTYPE
	{
		BULLETTYPE_PLAYER = 0,					//�v���C���[�̒e
		BULLETTYPE_BOMB,						//���e
		BULLETTYPE_BOSS,						//�{�X�̒e
		BULLETTYPE_MAX
	};

	CBullet();									//�R���X�g���N�^
	~CBullet()override;							//�f�X�g���N�^

	HRESULT Init(void)override;					//�e�̏���������
	void Uninit(void)override;					//�e�̏I������
	void Update(void)override;					//�e�̍X�V����
	void Draw(void)override;					//�e�̕`�揈��

	void HitEnemy(D3DXVECTOR3 pos);											//�e�ƓG�̓����蔻��
	void HitGimmick(D3DXVECTOR3 pos);										//�e�ƃM�~�b�N�̓����蔻��
	void HitBoss(D3DXVECTOR3 pos);											//�e�ƃ{�X�̓����蔻��
	void BulletBehavior();													//�e�̋���
	void BombHitBoss(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//�e(���e)�ƃ{�X�̓����蔻��
	void BossBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);	//�{�X�̒e�̍U������

	//getter
	D3DXVECTOR3 GetBulletPos(void) { return m_BulletPos;}					//�e�̈ʒu�̎擾����
	BULLETTYPE GetBulletType(void) { return m_type; }						//�e�̎�ނ̎擾����
	int GetBulletLife(void) { return m_nLife; }								//�e�̗̑͂̎擾����
	int GetTotalEnemy(void) { return m_TotalEnemy; }						//�G�̑����̎擾����
	bool GetBossDeathFlag(void) { return m_BossDeathFlag; }					//�{�X�����񂾂̂��t���O�̎擾����

	//setter
	void SetLife(int life) { m_nLife = life; }								//�e�̃��C�t�̐ݒ菈��
	void SetBulletPos(D3DXVECTOR3 pos) { m_BulletPos = pos; }				//�e�̈ʒu�̐ݒ�
	void SetGimmickUninitFlag(bool flag) { m_GimmickUninitFlag = flag; }	//�M�~�b�N���������̂��t���O�̐ݒ菈��
	void SetBossDeathFlag(bool flag) { m_BossDeathFlag = flag; }			//�{�X�����񂾂̂��t���O�̐ݒ菈��
	void SetBulletType(BULLETTYPE type);	//�e�̎g�p�҂̐ݒ菈��

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, BULLETTYPE type);		//����

private:
	D3DXVECTOR3 m_BulletSize;						//�T�C�Y
	D3DXVECTOR3 m_BulletPos;						//�ʒu
	D3DXVECTOR3 m_BulletRot;						//����
	D3DXVECTOR3	m_BulletMove;						//�ړ�

	BULLETTYPE m_type;								//�e�̎��

	CEnemy *m_pEnemy;								//�G�̃C���X�^���X
	CFade *m_pFade;									//�t�F�[�h�̃C���X�^���X

	int m_nLife;									//�̗�
	int m_nBulletExplosionTime;						//�e����������܂ł̎���
	int m_TotalEnemy;								//�G�̑���
	int m_ResultTime;								//���U���g��ʂɍs���܂ł̎���
	int m_ExplosionTime;							//��������܂ł̎���

	bool m_RandFlag;								//�����_���t���O
	bool m_EnemyDeathFlag;							//�G�����񂾂̂��t���O
	bool m_GimmickUninitFlag;						//�M�~�b�N���������̂��t���O
	bool m_BulletMoveFlag;							//�e�����e�B�N���̕����֌������Ă����t���O
	bool m_BossDeathFlag;							//�{�X�����񂾂̂��̃t���O
};

#endif


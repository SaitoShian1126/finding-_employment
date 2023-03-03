//============================================
//
//	spawn.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _SPAWN_H_
#define _SPAWN_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectX.h"

//============================================
// �}�N����`
//============================================
#define ENEMY_CREATE_TIME_WAVE_1	(150)		//�G���E�F�[�u1�ɐ��������܂ł̎���
#define ENEMY_CREATE_TIME_WAVE_2	(100)		//�G���E�F�[�u2�ɐ��������܂ł̎���
#define MAX_ENEMY_1					(20)		//�G�E�F�[�u1�̍ő吔
#define MAX_ENEMY_2					(40)		//�G�E�F�[�u2�̍ő吔
#define WAVE_TIME					(2000)		//�E�F�[�u1����2�̃^�C��
#define WAVE_TIME2					(400)		//�E�F�[�u2����3�̃^�C��

//============================================
// �O���錾
//============================================
class CBoss;									//�{�X�̃N���X

//============================================
// �ʎY�N���X
//============================================
class CSpawn : public CObject
{
public:
	CSpawn();						//�R���X�g���N�^
	~CSpawn();						//�f�X�g���N�^

	HRESULT Init(void);				//�ʎY�̏���������
	void Uninit(void);				//�ʎY�̏I������
	void Update(void);				//�ʎY�̍X�V����
	void Draw(void);				//�ʎY�̕`�揈��

	void EnemySpawn(void);			//�G�̗ʎY����
	
	//============================================
	// getter
	//============================================
	D3DXVECTOR3 GetPos(void) { return D3DXVECTOR3(); }		//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3(); }		//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(); }		//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void) { return D3DXVECTOR3(); }		//��]�̎擾
	float GetLength(void) { return float(); }				//�g��k���̃X�P�[���̎擾
	int GetEnemyCount(void) { return m_EnemyCount; }		//�G�̑����̎擾����
	static CBoss *GetBoss(void) { return m_pBoss;}			//�{�X�̃C���X�^���X�̎擾����
			
	//============================================
	// setter
	//============================================
	void SetPosition(D3DXVECTOR3 pos) {pos; }				//�M�~�b�N�̈ʒu����
	void SetRot(D3DXVECTOR3 rot) {rot; }					//�M�~�b�N�̉�]����
	void SetMove(D3DXVECTOR3 move) { move; }				//�M�~�b�N�̈ړ�����
	void SetLength(float length) { length; }				//�����̐ݒ菈��
	void SetEnemyCount(int cnt) { m_EnemyCount = cnt; }		//�G�̑����̐ݒ菈��
	static void SetBoss(CBoss *boss);						//�{�X�̐ݒ菈��

	static CSpawn *Create();								//��������

private:
	static CBoss *m_pBoss;									//�{�X�̃C���X�^���X

	D3DXVECTOR3 m_pos;										//�ʒu
	int m_EnemyCreateTime;									//�G�����������܂ł̎���
	int m_RandNumber;										//�����_���Ȓl������ϐ�
	int m_EnemyCount;										//�G�̑���
	int m_EnemySpawnType;									//�G���X�|�[��������
	int m_WaveTime;											//�E�F�[�u�^�C��
	int m_BossAppearTime;									//�{�X���o������܂ł̎���
	int m_BossCount;										//�{�X�̃J�E���g

	bool m_RandFlag;										//�G�̃����_���t���O
	bool m_MaxEnemyFlag;									//�G���ő�l�ɒB�����̂��̃t���O
	bool m_IndicationFlag;									//wave�\���̃t���O
	bool m_BossFlag;										//�{�X���o�������̂��̃t���O

};
#endif
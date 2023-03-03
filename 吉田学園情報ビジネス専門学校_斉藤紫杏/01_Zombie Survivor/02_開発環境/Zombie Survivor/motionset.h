//============================================
//
//	motionset.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MOTIONSET_H_
#define _MOTIONSET_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �}�N����`
//============================================
#define KEY_NUMBER	(2)			//�L�[��

//============================================
// �O���錾
//============================================
class CKeySet;

//============================================
// ���[�V�����ݒ�N���X
//============================================
class CMotionSet
{
public:
	CMotionSet();					//�R���X�g���N�^
	~CMotionSet();					//�f�X�g���N�^

	HRESULT Init(void);				//���[�V�����ݒ�̏���������
	void Uninit(void);				//���[�V�����ݒ�̏I������

	//getter
	int GetLoop(void) { return m_Loop; }				//���[�v�̎擾����
	int GetNumKey(void) {return m_Num_Key;}				//���[�V�����̐��̎擾����
	int GetNumParts(void) { return m_NumParts; }		//�p�[�c�̎�ނ̎擾����
	CKeySet *GetKeySet(int keyset) { return m_apKeySet[keyset]; }

	//setter
	void SetLoop(int Loop) { m_Loop = Loop; }					//���[�v�̐ݒ菈��
	void SetNumKey(int NumKey) { m_Num_Key = NumKey; }			//���[�V�����̐��̐ݒ菈��
	void SetNumParts(int NumParts) { m_NumParts = NumParts; }	//�p�[�c�̎�ނ̐ݒ菈��

	static CMotionSet *Create();		//����

private:
	int m_Loop;								//���[�v
	int m_Num_Key;							//���[�V�����̐�
	int m_NumParts;							//�p�[�c�̎��
	CKeySet *m_apKeySet[KEY_NUMBER];	//KeySet�\���̂̔z��
};

#endif


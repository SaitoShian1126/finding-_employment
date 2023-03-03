//============================================
//
//	key.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _KEY_H_
#define _KEY_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �L�[�N���X
//============================================
class CKey
{
public:
	CKey();						//�R���X�g���N�^
	~CKey();					//�f�X�g���N�^

	HRESULT Init(void);			//�L�[�̏���������
	void Uninit();				//�L�[�̏I������

	static CKey *Create();		//����

	//getter
	D3DXVECTOR3 GetPos() { return m_pos; }	//�ʒu�̎擾����
	D3DXVECTOR3 GetRot() { return m_rot; }	//�����̎擾����

	//setter
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�̐ݒ菈��
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	//�����̎擾����

private:
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif

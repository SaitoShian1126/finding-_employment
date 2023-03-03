//============================================
//
//	sphere.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectx.h"

//============================================
// �}�N����`
//============================================
#define SPHERE_MOVE	(1.0f)	//���̈ړ�

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CSphere : public CObjectX
{
public:
	CSphere();											//�R���X�g���N�^
	~CSphere()override;									//�f�X�g���N�^

	HRESULT Init(void)override;							//���̏���������
	void Uninit(void)override;							//���̏I������
	void Update(void)override;							//���̍X�V����
	void Draw(void)override;							//���̕`�揈��

	static CSphere *Create(const D3DXVECTOR3 &pos);		//����

private:
	D3DXVECTOR3 m_RotDest;		//�ړI�̊p�x
	D3DXVECTOR3 m_Move;			//�ړ�
};

#endif

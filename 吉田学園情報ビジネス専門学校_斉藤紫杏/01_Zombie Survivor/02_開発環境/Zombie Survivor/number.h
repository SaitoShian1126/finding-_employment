//============================================
//
//	number.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define NUMBER_SIZE_X		 (25.0f)	//������x�T�C�Y
#define NUMBER_SIZE_Y		 (250.0f)	//������y�T�C�Y

//============================================
// �����N���X
//============================================
class CNumber : public CObject2D
{
public:
	enum NUMBERTYPE
	{
		NUMBERTYPE_SCORE = 0,			//�X�R�A
		NUMBERTYPE_BOMB,				//���e�̌�
		NUMBERTYPE_MAX
	};
	CNumber();							//�R���X�g���N�^
	~CNumber()override;					//�f�X�g���N�^

	HRESULT Init(void)override;			//�����̏���������
	void Uninit(void)override;			//�����̏I������
	void Update(void)override;			//�����̍X�V����
	void Draw(void)override;			//�����̕`�揈��

	static HRESULT Load(void);			//�e�N�X�`���̓ǂݍ���
	static void Unload(void);			//�e�N�X�`���̔j��
	static CNumber *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, NUMBERTYPE type);	//����

	NUMBERTYPE GetType(void) { return m_type; }			//�i���o�[�̎�ނ̎擾
	void SetType(NUMBERTYPE type) { m_type = type; }	//�i���o�[�̎�ނ̐ݒ�

private:
	static LPDIRECT3DTEXTURE9 m_pTextureNumber;		//�e�N�X�`���ւ̃|�C���^
	NUMBERTYPE m_type;								//�i���o�[�̎��
};

#endif






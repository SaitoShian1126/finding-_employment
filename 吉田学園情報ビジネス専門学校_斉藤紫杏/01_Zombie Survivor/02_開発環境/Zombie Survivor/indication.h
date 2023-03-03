//============================================
//
//	indication.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _INDICATION_H_
#define _INDICATION_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define INDICATION_SIZE_X		 (20.0f)	//�\����x�T�C�Y
#define INDICATION_SIZE_Y		 (25.0f)	//�\����y�T�C�Y
#define MAX_TEXTURE				 (4)		//�e�N�X�`���̍ő吔
#define RELEASE_TIME			 (300)		//�j������܂ł̎���

//============================================
// �O���錾
//============================================

//============================================
// �\���N���X
//============================================
class CIndication : public CObject2D
{
public:
	enum INDICATIONTYPE
	{
		INDICATIONTYPE_NONE = 0,
		INDICATIONTYPE_WAVE1,			//�E�F�[�u1�̕\��
		INDICATIONTYPE_WAVE2,			//�E�F�[�u2�̕\��
		INDICATIONTYPE_BLOOD,			//�����Ԃ��̕\��
		INDICATIONTYPE_MAX
	};
public:
	CIndication();							//�R���X�g���N�^
	~CIndication()override;					//�f�X�g���N�^

	HRESULT Init(void)override;				//�\���̏���������
	void Uninit(void)override;				//�\���̏I������
	void Update(void)override;				//�\���̍X�V����
	void Draw(void)override;				//�\���̕`�揈��

	INDICATIONTYPE GetIndicationType(void) { return INDICATIONTYPE(); }	//�\���̎�ނ̎擾
	void SetIndicationType(INDICATIONTYPE type);						//�\���̎�ނ̐ݒ�

	static CIndication *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, INDICATIONTYPE type);	//����

	static HRESULT Load(void);				//�e�N�X�`���̓ǂݍ���
	static void Unload(void);				//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXCOLOR m_col;									//�F
	INDICATIONTYPE m_nType;								//�\���̎��
	int m_nUninitTimer;									//�폜����
	int m_Bomb;											//���e
	bool m_flag;										//�t���O
	bool m_ColorFlag;									//�F�̃t���O
	bool m_BloodFlag;									//�����o�����̃t���O
};

#endif
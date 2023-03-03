//============================================
//
//	warning.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _WARNING_H_
#define _WARNING_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define MAX_TEXTURE		(2)			//�e�N�X�`���̍ő吔
#define RELEASE_TIME	(300)		//�j������܂ł̎���

//============================================
// �O���錾
//============================================

//============================================
// Warning�N���X
//============================================
class CWarning : public CObject2D
{
public:
	enum WARNINGTYPE
	{
		WARNINGTYPE_UI = 0,			//UI
		WARNINGTYPE_SCREEN,			//���
		WARNINGTYPE_MAX
	};
public:
	CWarning();								//�R���X�g���N�^
	~CWarning()override;					//�f�X�g���N�^

	HRESULT Init(void)override;				//Warning�̏���������
	void Uninit(void)override;				//Warning�̏I������
	void Update(void)override;				//Warning�̍X�V����
	void Draw(void)override;				//Warning�̕`�揈��

	WARNINGTYPE GetWarningType(void) { return WARNINGTYPE(); }	//Warning�̎�ނ̎擾
	void SetWarningType(WARNINGTYPE type);						//Warning�̎�ނ̐ݒ�

	static CWarning *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size, WARNINGTYPE type);	//����

	static HRESULT Load(void);				//�e�N�X�`���̓ǂݍ���
	static void Unload(void);				//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	D3DXCOLOR m_col;									//�F
	WARNINGTYPE m_type;									//Warning�̎��

	int m_nUninitTimer;									//�j���܂ł̎���
	bool m_flag;										//�t���O
};

#endif
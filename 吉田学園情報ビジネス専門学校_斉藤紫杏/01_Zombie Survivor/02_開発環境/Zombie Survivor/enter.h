//============================================
//
//	enter.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _ENTER_H_
#define _ENTER_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define ENTER_SIZE_X		 (20.0f)	//enter��x�T�C�Y
#define ENTER_SIZE_Y		 (25.0f)	//enter��y�T�C�Y

//============================================
// enter�N���X
//============================================
class CEnter : public CObject2D
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_IN,
		TYPE_OUT,
		TYPE_MAX
	};
public:
	CEnter();						//�R���X�g���N�^
	~CEnter()override;				//�f�X�g���N�^

	HRESULT Init(void)override;		//enter�̏���������
	void Uninit(void)override;		//enter�̏I������
	void Update(void)override;		//enter�̍X�V����
	void Draw(void)override;		//enter�̕`�揈��

	static CEnter *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size);	//����

private:
	static LPDIRECT3DTEXTURE9 m_pTextureenter;	//�e�N�X�`���ւ̃|�C���^
	D3DXCOLOR m_nCol;							//�J���[
	TYPE m_nType;								//�^�C�v
	int m_nCount;								//in��out�܂ł̎���
};

#endif









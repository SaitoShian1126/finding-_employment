//============================================
//
//	reticle.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _RETICLE_H_
#define _RETICLE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================

//============================================
// �O���錾
//============================================

//============================================
// �\���N���X
//============================================
class CReticle : public CObject2D
{
public:
	CReticle();								//�R���X�g���N�^
	~CReticle()override;					//�f�X�g���N�^

	HRESULT Init(void)override;				//�\���̏���������
	void Uninit(void)override;				//�\���̏I������
	void Update(void)override;				//�\���̍X�V����
	void Draw(void)override;				//�\���̕`�揈��

	static CReticle *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 size);	//����

	static HRESULT Load(void);				//�e�N�X�`���̓ǂݍ���
	static void Unload(void);				//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXCOLOR m_col;						//�F
};

#endif
//============================================
//
//	shadow.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object3d.h"

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CShadow : public CObject3D
{
public:
	CShadow();						//�R���X�g���N�^
	~CShadow();						//�f�X�g���N�^

	HRESULT Init(void)override;				//�e�̏���������
	void Uninit(void)override;				//�e�̏I������
	void Update(void)override;				//�e�̍X�V����
	void Draw(void)override;				//�e�̕`�揈��

	CShadow *SetTexture(char *pFile);
	static CShadow *Create(const D3DXVECTOR3 &pos);			//����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffShadow;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureShadow;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;									//�ʒu

	bool m_Texture;
};

#endif

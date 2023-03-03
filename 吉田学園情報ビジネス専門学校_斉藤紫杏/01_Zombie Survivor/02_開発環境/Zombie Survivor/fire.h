//============================================
//
//	fire.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _FIRE_H_
#define _FIRE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// �O���錾
//============================================

//============================================
// ���N���X
//============================================
class CFire : public CObjectBase
{
public:
	CFire();									//�R���X�g���N�^
	~CFire() override;							//�f�X�g���N�^

	HRESULT Init(void)override;						//���̏���������
	void Uninit(void)override;						//���̏I������
	void Update(void)override;						//���̍X�V����
	void Draw(void)override;						//���̕`�揈��

	static HRESULT Load(void);									//�e�N�X�`���̓ǂݍ���
	static void Unload(void);									//�e�N�X�`���̔j��

	static void SetfirePos(D3DXVECTOR3 pos) { m_pos = pos; }	//���̈ʒu�ݒ�
	static D3DXVECTOR3 GetfirePos(void) { return m_pos; }		//���̈ʒu�擾
	static CFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//����

private:
	static LPDIRECT3DTEXTURE9 m_pTexturefire;		//�e�N�X�`���ւ̃|�C���^
	static D3DXVECTOR3 m_pos;						//�ʒu

	int m_nCounterAnimfire;							//�A�j���[�V�����J�E���^�[
	int m_nPatternAnimfire;							//�A�j���[�V����X�p�^�[��No.
	int m_nPatternAnimfireY;						//�A�j���[�V����Y�p�^�[��No.
};

#endif
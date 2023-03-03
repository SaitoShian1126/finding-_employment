//============================================
//
//	explosion.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// �O���錾
//============================================

//============================================
// �����N���X
//============================================
class CExplosion : public CObjectBase
{
public:
	CExplosion();									//�R���X�g���N�^
	~CExplosion() override;							//�f�X�g���N�^

	HRESULT Init(void)override;						//�����̏���������
	void Uninit(void)override;						//�����̏I������
	void Update(void)override;						//�����̍X�V����
	void Draw(void)override;						//�����̕`�揈��

	static void SetexplosionPos(D3DXVECTOR3 pos) { m_pos = pos; }	//�����̈ʒu�ݒ�
	static D3DXVECTOR3 GetexplosionPos(void) { return m_pos; }		//�����̈ʒu�擾
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);	//����

private:
	static LPDIRECT3DTEXTURE9 m_pTextureExplosion;		//�e�N�X�`���ւ̃|�C���^
	static D3DXVECTOR3 m_pos;							//�ʒu

	int m_nCounterAnimExplosion;						//�A�j���[�V�����J�E���^�[
	int m_nPatternAnimExplosion;						//�A�j���[�V����X�p�^�[��No.
	int m_nPatternAnimExplosionY;						//�A�j���[�V����Y�p�^�[��No.
};

#endif
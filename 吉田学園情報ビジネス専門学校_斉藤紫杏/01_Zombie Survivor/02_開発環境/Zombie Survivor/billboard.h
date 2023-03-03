//============================================
//
//	billboard.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectbase.h"
#include "shadow.h"

//============================================
// �O���錾
//============================================

//============================================
// �r���{�[�h�N���X
//============================================
class CBillboard : public CObjectBase
{
public:
	CBillboard();									//�R���X�g���N�^
	~CBillboard() override;							//�f�X�g���N�^

	HRESULT Init(void)override;						//�r���{�[�h�̏���������
	void Uninit(void)override;						//�r���{�[�h�̏I������
	void Update(void)override;						//�r���{�[�h�̍X�V����
	void Draw(void)override;						//�r���{�[�h�̕`�揈��

	void SetBillboardPos(D3DXVECTOR3 pos) { m_pos = pos; }	//�r���{�[�h�̈ʒu�ݒ�
	D3DXVECTOR3 GetBillboardPos(void) { return m_pos; }		//�r���{�[�h�̈ʒu�擾
	static CBillboard *Create();							//����

private:
	D3DXVECTOR3 m_pos;				//�ʒu
};

#endif


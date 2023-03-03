//============================================
//
//	item.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _ITEM_H_
#define _ITEM_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectbase.h"

//============================================
// �O���錾
//============================================

//============================================
// �A�C�e���N���X
//============================================
class CItem : public CObjectBase
{
public:
	CItem();									//�R���X�g���N�^
	~CItem() override;							//�f�X�g���N�^

	HRESULT Init(void)override;					//�A�C�e���̏���������
	void Uninit(void)override;					//�A�C�e���̏I������
	void Update(void)override;					//�A�C�e���̍X�V����
	void Draw(void)override;					//�A�C�e���̕`�揈��

	void HitItem(void);							//�A�C�e���ƃv���C���[������������

	bool GetHitFlag(void) { return m_HitFlag; }			//���������̂��̃t���O�̎擾����
	void SetHitFlag(bool flag) { m_HitFlag = flag; }	//���������̂��̃t���O�̐ݒ菈��

	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);					//�e�N�X�`���̔j��

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//����

private:
	static LPDIRECT3DTEXTURE9 m_pTextureitem;		//�e�N�X�`���ւ̃|�C���^
	bool m_HitFlag;									//���������̂��̃t���O	
};

#endif
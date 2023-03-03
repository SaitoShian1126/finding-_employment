//============================================
//
//	gasolene_gimmick.h
//	Author: saito shian
//
//============================================
#ifndef _GASOLENE_GIMMICK_H_
#define _GASOLENE_GIMMICK_H_

//============================================
// �C���N���[�h�t�@�C��
//============================================
#include "gimmick.h"

//============================================
// �O����`
//============================================

//============================================
// �N���X�̒�`
//============================================
class CGasolene_Gimmick : public CGimmick
{
public:
	CGasolene_Gimmick();				//�R���X�g���N�^
	~CGasolene_Gimmick() override;		//�f�X�g���N�^

	HRESULT Init() override;			//����������
	void Uninit() override;				//�I������
	void Update() override;				//�X�V����
	void Draw() override;				//�`�揈��

	void HitDamage();					//�K�\�����������������̓����蔻��

	int GetGasoleneLife(void) { return m_nLife; }			//�K�\�����̗̑͂̎擾

	D3DXVECTOR3 GetGasolenePos(void) { return m_pos; }		//�K�\�����̈ʒu�̎擾
	D3DXVECTOR3 GetGasoleneSize(void) { return m_size; }	//�K�\�����̃T�C�Y�̎擾

	void SetGasoleneLife(int life) { m_nLife = life; }		//�K�\�����̗̑͂̐ݒ�

	static CGasolene_Gimmick *Create(D3DXVECTOR3 pos);		//����

private:
	D3DXVECTOR3 m_pos;					//�K�\�����̈ʒu
	D3DXVECTOR3 m_size;					//�K�\�����̃T�C�Y
	int m_nLife;						//�K�\�����̗̑�
};
#endif

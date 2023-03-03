//============================================
//
//	rock_gimmick.h
//	Author: saito shian
//
//============================================
#ifndef _ROCK_GIMMICK_H_
#define _ROCK_GIMMICK_H_

//============================================
// �C���N���[�h�t�@�C��
//============================================
#include "gimmick.h"

//============================================
// �}�N����`
//============================================
#define MAX_PUSH	(5)				//�����ő吔

//============================================
// �O����`
//============================================
class CShadow;

//============================================
// �N���X�̒�`
//============================================
class CRock_gimmick : public CGimmick
{
public:

	enum MODELTYPE
	{
		MODELTYPE_ROCK = 0,				//��
		MODELTYPE_SUPPORTBAR			//�x���_
	};

	CRock_gimmick();					//�R���X�g���N�^
	~CRock_gimmick() override;			//�f�X�g���N�^

	HRESULT Init() override;			//����������
	void Uninit() override;				//�I������
	void Update() override;				//�X�V����
	void Draw() override;				//�`�揈��

	void HitDamage();					//�₪���������̓����蔻��
	void Operation();					//�M�~�b�N���쏈��

	D3DXVECTOR3 GetGasolenePos(void) { return m_pos; }		//��̈ʒu�̎擾
	D3DXVECTOR3 GetGasoleneSize(void) { return m_size; }	//��̃T�C�Y�̎擾

	void SetModelType(MODELTYPE type);						//���f���̎�ނ̐ݒ�

	static CRock_gimmick *Create(D3DXVECTOR3 pos, MODELTYPE type);		//����

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	D3DXVECTOR3 m_pos;					//��̈ʒu
	D3DXVECTOR3 m_move;					//��̈ړ�
	D3DXVECTOR3 m_size;					//��̃T�C�Y
	MODELTYPE m_type;					//���f���̎��

	int m_PushCount;					//�������J�E���g

	bool m_PushCountFlag;				//���������������̂��̃t���O
	bool m_UninitFlag;					//�M�~�b�N���������̂��t���O
};
#endif

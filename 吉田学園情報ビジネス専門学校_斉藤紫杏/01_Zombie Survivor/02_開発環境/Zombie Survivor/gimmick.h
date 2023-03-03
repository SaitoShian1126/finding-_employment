//============================================
//
//	gimmick.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================

//============================================
// �O���錾
//============================================

//============================================
// �M�~�b�N�N���X
//============================================
class CGimmick : public CObject
{
public:
	//============================================
	// �M�~�b�N�̎��
	//============================================
	enum GIMMICKTYPE
	{
		GIMMICKTYPE_GASOLENE = 0,					//�K�\�����M�~�b�N
		GIMMICKTYPE_MAX
	};

	CGimmick();											//�R���X�g���N�^
	~CGimmick()override;								//�f�X�g���N�^

	HRESULT Init(void)override;							//�M�~�b�N�̏���������
	void Uninit(void)override;							//�M�~�b�N�̏I������
	void Update(void)override;							//�M�~�b�N�̍X�V����
	void Draw(void)override;							//�M�~�b�N�̕`�揈��

	void ShadowDraw(void);								//�e�̕`��

	CGimmick *SetModel(char *pFile);

	//setter
	void SetPosition(D3DXVECTOR3 pos);						//�M�~�b�N�̈ʒu����
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }			//�M�~�b�N�̉�]����
	void SetMove(D3DXVECTOR3 move);							//�M�~�b�N�̈ړ�����
	void SetLength(float length) { length; }				//�����̐ݒ菈��

	//getter
	D3DXVECTOR3 GetPos(void);								//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }			//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void);								//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//��]�̎擾
	float GetLength(void) { return float(); }				//�g��k���̃X�P�[���̎擾

private:
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ�
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXVECTOR3 m_rot;		//����

	LPD3DXBUFFER m_BuffMat;	//�o�b�t�@
	LPD3DXMESH m_Mesh;		//���b�V��
	DWORD m_nNumMat;		//�}�e���A��
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};

#endif

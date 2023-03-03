
//============================================
//
//	line.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _LINE_H_
#define _LINE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
//�}�N����`
//============================================
#define MAX_LINE    (500)			//���C���̍ő吔

//============================================
// ���C���\���N���X
//============================================
class CLine : public CObject
{
public:
	CLine();						//�R���X�g���N�^
	~CLine();						//�f�X�g���N�^

	HRESULT Init(void);				//���C���\���̏���������
	void Uninit(void);				//���C���\���̏I������
	void Update(void);				//���C���\���̍X�V����
	void Draw(void);				//���C���\���̕`�揈��

	void SetPosition(D3DXVECTOR3 pos)override;			//���C���̈ʒu
	void SetMove(D3DXVECTOR3 move)override { move; }	//���C���̈ړ�
	void SetLength(float length)override { length; }	//�g��k���̃X�P�[��

	void SetLine(void);									//���C���̒��_���W�̐ݒ�

	float GetLength(void) override { return float(); }				//�g��k���̃X�P�[���̎擾
	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return D3DXVECTOR3(); }	//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return D3DXVECTOR3(); }	//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return D3DXVECTOR3(); }		//��]�̎擾

	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 end);	//����

private:
	static D3DXVECTOR3 m_start;					//�n�_
	static D3DXVECTOR3 m_end;					//�I�_
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffLine;     //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXCOLOR m_col;							//�F
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	CLine *m_aLine[MAX_LINE];					//���C���̏��
};

#endif
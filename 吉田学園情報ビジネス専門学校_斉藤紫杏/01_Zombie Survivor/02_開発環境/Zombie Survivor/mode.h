//============================================
//
//	mode.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MODE_H_
#define _MODE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// ���[�h�N���X
//============================================
class CMode : public CObject
{
public:
	CMode();
	virtual ~CMode();

	virtual HRESULT Init(void) { return S_OK; }						//�|���S���̏���������
	virtual void Uninit(void) {} ;									//�|���S���̏I������
	virtual void Update(void) = 0;									//�|���S���̍X�V����

	void SetPosition(D3DXVECTOR3 pos)override { pos; }				//�|���S���̈ʒu
	void SetMove(D3DXVECTOR3 move)override { move; }				//�|���S���̈ړ�
	void SetLength(float length)override { length; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { pTexture; }		//�e�N�X�`�����f

	float GetLength(void) override { return m_fLength; }			//�g��k���̃X�P�[���̎擾

	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }			//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }			//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }				//��]�̎擾

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//�o�b�t�@�[�̎擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3	m_pos;					//�ʒu
	D3DXVECTOR3	m_move;					//�ړ�
	D3DXVECTOR3 m_rot;					//��]
	D3DXVECTOR3 m_size;					//�T�C�Y
	D3DXCOLOR m_col;					//�F

	float m_fWidth;						//��
	float m_fHeight;					//����
	float m_fAngle;						//�p�x
	float m_nTimer;						//����
	float m_fLength;					//�g��k���̃X�P�[��
};

#endif





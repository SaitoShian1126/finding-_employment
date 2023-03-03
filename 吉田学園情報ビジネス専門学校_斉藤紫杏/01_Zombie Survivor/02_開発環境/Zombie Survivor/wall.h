//============================================
//
//	wall.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _WALL_H_
#define _WALL_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CWall : public CObject
{
public:
	explicit CWall();								//�I�u�W�F�N�g�D�揇��
	~CWall();										//�f�X�g���N�^

	HRESULT Init(void)override;						//�|���S���̏���������
	void Uninit(void)override;						//�|���S���̏I������
	void Update(void)override;						//�|���S���̍X�V����
	void Draw(void)override;						//�|���S���̕`�揈��

	void SetPosition(D3DXVECTOR3 pos)override;		//�|���S���̈ʒu
	void SetMove(D3DXVECTOR3 move)override;			//�|���S���̈ړ�
	void SetSize(D3DXVECTOR3 size);					//�|���S���̃T�C�Y
	void SetRot(D3DXVECTOR3 rot);					//��]
	void SetLength(float length) { length; }		//�g��k���̃X�P�[��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`�����f

	float GetLength(void) override { return float(); }				//�g��k���̃X�P�[���̎擾

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//�o�b�t�@�[�̎擾
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }				//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }				//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }					//��]�̎擾

	static CWall *Create(const D3DXVECTOR3 &pos, D3DXVECTOR3 rot);						//����
	static HRESULT Load(void);			//�e�N�X�`���̓ǂݍ���
	static void Unload(void);			//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;						//�ʒu
	D3DXVECTOR3	m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//��]
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXCOLOR m_col;						//�F
};

#endif

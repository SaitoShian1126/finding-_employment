//============================================
//
//	objectX.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �O���錾
//============================================

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = 3);			//�I�u�W�F�N�g�D�揇��
	~CObjectX();									//�f�X�g���N�^

	HRESULT Init(void)override;						//�|���S���̏���������
	void Uninit(void)override;						//�|���S���̏I������
	void Update(void)override;						//�|���S���̍X�V����
	void Draw(void)override;						//�|���S���̕`�揈��

	void SetPosition(D3DXVECTOR3 pos)override;					//�|���S���̈ʒu
	void SetMove(D3DXVECTOR3 move)override { move; }			//�|���S���̈ړ�
	void SetSize(D3DXVECTOR3 size) { size; }					//�|���S���̃T�C�Y
	void SetRot(D3DXVECTOR3 rot);								//��]
	void SetLength(float length) { length; }					//�g��k���̃X�P�[��

	void ShadowDraw(void);										//�e�̕`��

	D3DXVECTOR3 GetPos(void) override { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }		//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }		//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			//��]�̎擾

	float GetLength(void) override { return m_fLength; }		//�g��k���̃X�P�[���̎擾

	static CObjectX *Create(const D3DXVECTOR3 &pos);			//����
	CObjectX *SetModel(char *pFile);

private:
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_move;							//�ʒu
	D3DXVECTOR3 m_size;							//�T�C�Y
	D3DXVECTOR3 m_VtxMinModel;					//�ŏ�
	D3DXVECTOR3 m_VtxMaxModel;					//�ő�
	LPD3DXBUFFER m_BuffMat;
	LPD3DXMESH m_Mesh;
	DWORD m_nNumMat;
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	CObjectX *m_pObjectX;						//�I�u�W�F�N�gX�̏��

	int m_nIdxModelParent;						//�e���f���̃C���f�b�N�X
	float m_fLength;					//�g��k���̃X�P�[��
	bool m_Model;						//�e�N�X�`�����g�p���Ă��邩�ǂ���
};

#endif

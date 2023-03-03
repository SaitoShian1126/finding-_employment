//============================================
//
//	object2D.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CObject3D : public CObject
{
public:
	explicit CObject3D(int nPriority = 3);			//�I�u�W�F�N�g�D�揇��
	~CObject3D();									//�f�X�g���N�^

	HRESULT Init(void)override;						//�|���S���̏���������
	void Uninit(void)override;						//�|���S���̏I������
	void Update(void)override;						//�|���S���̍X�V����
	void Draw(void)override;						//�|���S���̕`�揈��

	void SetPosition(D3DXVECTOR3 pos)override;		//�|���S���̈ʒu
	void SetMove(D3DXVECTOR3 move)override;			//�|���S���̈ړ�
	void SetSize(D3DXVECTOR3 size);					//�|���S���̃T�C�Y
	void SetRot(D3DXVECTOR3 rot);					//��]
	void SetLength(float length);					//�g��k���̃X�P�[��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`�����f
	void CObject3D::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);		//�e�N�X�`���̐ݒ�
	void SetColor(float Red, float Green, float Blue, float ��);									//�F�̐ݒ�

	float GetLength(void) override { return m_fLength; }		//�g��k���̃X�P�[���̎擾

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuffMeshPolygon; }	//�o�b�t�@�[�̎擾
	D3DXVECTOR3 GetPos(void) override { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }		//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }		//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }			//��]�̎擾

	static CObject3D *Create(const D3DXVECTOR3 &pos);			//����
	CObject3D *SetTexture(char *pFile);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMeshPolygon;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshPolygon;		//�e�N�X�`��
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffMeshPolygon;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorldMeshPolygon;				//���[���h�}�g���b�N�X
	D3DXVECTOR3	m_pos;					//�ʒu
	D3DXVECTOR3	m_move;					//�ړ�
	D3DXVECTOR3 m_rot;					//��]
	D3DXVECTOR3 m_size;					//�T�C�Y
	D3DXCOLOR m_col;					//�F

	bool m_Texture;						//�e�N�X�`�����g�p���Ă��邩�ǂ���

	float m_fWidth;						//��
	float m_fHeight;					//����
	float m_fAngle;						//�p�x
	float m_nTimer;						//����
	float m_fLength;					//�g��k���̃X�P�[��
};

#endif
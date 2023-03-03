//============================================
//
//	meshffield.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================
#define MESHFIELD_X_BLOCK	(80)		//x�����̃u���b�N
#define MESHFIELD_Z_BLOCK	(80)		//z�����̃u���b�N
#define MESHFIELD_VERTEX	((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))								//���_�� ((x�u���b�N�� + 1) * (z�u���b�N�� + 1))
#define MESHFIELD_INDEX		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)	//�C���f�b�N�X�� ((x�u���b�N�� + 1) * 2 * z�u���b�N�� + (z�u���b�N�� - 1) * �k�ރ|���S���p���_��(z�����ɑ�������2���k�ރ|���S���p���_����������))
#define MESHFIELD_PRIMITIVE	(MESHFIELD_X_BLOCK * (MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)		//�|���S���� (x�u���b�N�� * z�u���b�N�� * 2 + (z�u���b�N�� - 1) * �k�ރ|���S����(z�����ɑ�������4���k�ރ|���S������������))

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CMeshField : public CObject
{
public:
	explicit CMeshField(int nPriority = 3);			//�I�u�W�F�N�g�D�揇��
	~CMeshField();									//�f�X�g���N�^

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
	void CMeshField::SetTexture(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);	//�e�N�X�`���̐ݒ�
	void SetColor(float Red, float Green, float Blue, float ��);									//�F�̐ݒ�

	void GetMeshFieldCollision(D3DXVECTOR3 *PlayerPos);					//���b�V���t�B�[���h�̓����蔻��̎擾����

	float GetLength(void) override { return m_fLength; }				//�g��k���̃X�P�[���̎擾

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuffMeshField; }	//�o�b�t�@�[�̎擾
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }				//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }				//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }					//��]�̎擾

	static CMeshField *Create(const D3DXVECTOR3 &pos);					//����
	CMeshField *SetTexture(char *pFile);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMeshField;	//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffMeshField;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshField;			//�e�N�X�`��
	D3DXMATRIX m_mtxWorldMeshField;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 SaveVtxNor[MESHFIELD_VERTEX];		//���_���̖@���x�N�g���ۑ��p�z��
	D3DXVECTOR3 IdxPosNor[3];						//Idx��pos
	D3DXVECTOR3 Calculation3DNor[2];				//3�����O�ς̌v�Z����
	D3DXVECTOR3 VecAnswer;							//�O�ς̌v�Z����
	D3DXVECTOR3	m_pos;								//�ʒu
	D3DXVECTOR3	m_move;								//�ړ�
	D3DXVECTOR3 m_rot;								//��]
	D3DXVECTOR3 m_size;								//�T�C�Y
	D3DXCOLOR m_col;								//�F

	int m_nVtxRand;									//���_��y���W�����_��

	float m_fWidth;									//��
	float m_fHeight;								//����
	float m_fAngle;									//�p�x
	float m_nTimer;									//����
	float m_fLength;								//�g��k���̃X�P�[��
	float m_fRotMove;								//����

	bool m_RandFlag;								//�����_���t���O
	bool m_Texture;									//�e�N�X�`�����g�p���Ă��邩�ǂ���
};

#endif

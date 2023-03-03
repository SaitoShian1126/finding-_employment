//============================================
//
//	skybox.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================
#define MAX_SIZE				(1300.0f)	//�T�C�Y�̍ő�l
#define MAX_SIDE				(30)		//���̍ő�l
#define MIN_SIDE				(5)			//���̍ŏ��l
#define START_SIDE				(16)		//���̍ŏ��̒l
#define MAX_VERTICAL			(30)		//�c�̍ő�l
#define MIN_VERTICAL			(5)			//�c�̍ŏ��l
#define START_VERTICAL			(15)		//�c�̍ŏ��̒l

//============================================
// �I�u�W�F�N�g�N���X
//============================================
class CSkyBox : public CObject
{
public:
	explicit CSkyBox();								//�I�u�W�F�N�g�D�揇��
	~CSkyBox();										//�f�X�g���N�^

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

	static CSkyBox *Create(const D3DXVECTOR3 &pos);						//����
	CSkyBox *SetTexture(char *pFile);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^											
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffCone;	// �~���̒��_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`��
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 IdxPosNor[3];						//Idx��pos
	D3DXVECTOR3 Calculation3DNor[2];				//3�����O�ς̌v�Z����
	D3DXVECTOR3 VecAnswer;							//�O�ς̌v�Z����
	D3DXVECTOR3	m_pos;								//�ʒu
	D3DXVECTOR3	m_move;								//�ړ�
	D3DXVECTOR3 m_rot;								//��]
	D3DXVECTOR3 m_size;								//�T�C�Y
	D3DXCOLOR m_col;								//�F

	int	m_nHorizontal;		// ��
	int	m_nVertical;			// �c
	int	m_nVtx;				// ���_��
	int	m_nIdx;				// �C���f�b�N�X��
	int	m_nPolygon;			// �|���S����
};

#endif

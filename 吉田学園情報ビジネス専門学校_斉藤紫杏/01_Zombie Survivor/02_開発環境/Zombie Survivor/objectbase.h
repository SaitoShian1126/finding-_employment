//============================================
//
//	ObjectBase.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _OBJECTBASE_H_
#define _OBJECTBASE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object.h"

//============================================
// �}�N����`
//============================================

//============================================
// �I�u�W�F�N�g��b�N���X
//============================================
class CObjectBase : public CObject
{
public:
	CObjectBase();									//�R���X�g���N�^
	~CObjectBase()override;							//�f�X�g���N�^

	HRESULT Init(void)override;						//�I�u�W�F�N�g��b����������
	void Uninit(void)override;						//�I�u�W�F�N�g��b�I������
	void Update(void)override;						//�I�u�W�F�N�g��b�X�V����
	void Draw(void)override;						//�I�u�W�F�N�g��b�`�揈��

	CObjectBase *SetTexture(char *pFile);			//�e�N�X�`���̐ݒ�
	void SetTextureY(float SplitX, float nNumIndexX, float SplitY, float nNumIndexY);	//�c�̃e�N�X�`���̐ݒ�

	void SetPosition(D3DXVECTOR3 pos)override;											//�I�u�W�F�N�g��b�ʒu
	void SetMove(D3DXVECTOR3 move)override;												//�I�u�W�F�N�g��b�ړ�
	void SetRot(D3DXVECTOR3 rot) { rot; }												//��]
	void SetSize(D3DXVECTOR3 size);														//�I�u�W�F�N�g��b�T�C�Y
	void SetLength(float length) { length; }											//�g��k���̃X�P�[��
	void SetCol(D3DXCOLOR col) { m_ObjectBaseCol = col; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTextureObjectBase =pTexture; }	//�e�N�X�`�����f
	float GetLength(void) override { return m_fLength; }								//�g��k���̃X�P�[���̎擾

	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuffObjectBase; }				//�o�b�t�@�[�̎擾
	D3DXVECTOR3 GetPos(void) override { return m_ObjectBasePos; }						//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_ObjectBaseMove; }						//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_ObjectBaseSize; }						//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_ObjectBaseRot; }						//��]�̎擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffObjectBase;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureObjectBase;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_ObjectBasePos;						//�ʒu
	D3DXVECTOR3 m_ObjectBaseRot;						//����
	D3DXVECTOR3	m_ObjectBaseMove;						//�ړ�
	D3DXVECTOR3 m_ObjectBaseSize;						//�T�C�Y
	D3DXCOLOR	m_ObjectBaseCol;						//�F
	D3DXMATRIX m_ObjectBasemtxWorld;					//���[���h�}�g���b�N�X

	int m_Life;											//�̗�

	float m_fLength;									//�g��k���̃X�P�[��
	float m_Radius;										//���a

	bool m_ObjectBaseTexture;							//�e�N�X�`���̎g�p�t���O
};

#endif

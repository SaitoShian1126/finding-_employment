//============================================
//
//	hp.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _HP_H_
#define _HP_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define LIFE_WIDTH			(35.0f)	//�|���S���̕�
#define BOSS_LIFE_WIDTH		(1.5f)	//�{�X�̃|���S���̕�

//============================================
// �̗̓o�[�N���X
//============================================
class CHp : public CObject
{
public:
	enum HPTYPE
	{
		HPTYPE_PLAYER = 0,		//�v���C���[��HP
		HPTYPE_BOSS,			//�{�X��HP
		HPTYPEMAX
	};
	CHp();							//�R���X�g���N�^
	~CHp()override;					//�f�X�g���N�^

	HRESULT Init(void)override;			//�̗̓o�[�̏���������
	void Uninit(void)override;			//�̗̓o�[�̏I������
	void Update(void)override;			//�̗̓o�[�̍X�V����
	void Draw(void)override;			//�̗̓o�[�̕`�揈��

	void SetPosition(D3DXVECTOR3 pos) { pos; }		//�̗̓o�[�̈ʒu
	void SetMove(D3DXVECTOR3 move) { move; }		//�̗̓o�[�̈ړ�
	void SetSize(D3DXVECTOR3 size) { size; };		//�̗̓o�[�̃T�C�Y
	void SetCol(D3DXCOLOR col) { col; }				//�F
	void SetRot(D3DXVECTOR3 rot) { rot; }			//��]
	void SetLength(float length) { length; }					//�g��k���̃X�P�[��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { pTexture; }	//�e�N�X�`�����f
	void SetHPType(HPTYPE type) { m_type = type;}				//HP�̎�ނ̐ݒ�
	void SetColor(float Red, float Green, float Blue, float ��);	//�F�̐ݒ�

	D3DXVECTOR3 GetPos(void) override { return m_pos; }				//�ʒu�̎擾
	D3DXVECTOR3 GetMove(void) override { return m_move; }			//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) override { return m_size; }			//�T�C�Y�̎擾
	D3DXVECTOR3 GetRot(void) override { return m_rot; }				//��]�̎擾
	float GetLength(void) override { return m_fLength; }			//�g��k���̃X�P�[���̎擾
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }		//�o�b�t�@�[�̎擾
	HPTYPE GetHPType(void) { return m_type;}						//HP�̎�ނ̎擾����

	static CHp *Create(HPTYPE type);	//����

private:
	static LPDIRECT3DTEXTURE9 m_pTexturehp;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3	m_pos;						//�ʒu
	D3DXVECTOR3	m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//��]
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXCOLOR m_col;						//�F
	HPTYPE m_type;							//HP�̎��
	int m_nPlayreLife;						//�v���C���[�̗̑͂�ۑ�����
	int m_nBossLife;						//�{�X�̗̑͂�ۑ�����
	float m_fLength;						//�g��k���̃X�P�[��
};

#endif

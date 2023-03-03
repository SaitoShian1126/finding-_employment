//============================================
//
//	score.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _SCORE_H_
#define _SCORE_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"
#include "number.h"

//============================================
// �}�N����`
//============================================
#define SCORE_SIZE_X		 (25.0f)	//�X�R�A��x�T�C�Y
#define SCORE_SIZE_Y		 (250.0f)	//�X�R�A��y�T�C�Y
#define SCORE_DIGIT			 (7)		//�X�R�A�̌���

//============================================
// �X�R�A�N���X
//============================================
class CScore : public CObject
{
public:
	CScore();							//�R���X�g���N�^
	~CScore()override;					//�f�X�g���N�^

	HRESULT Init(void)override;			//�X�R�A�̏���������
	void Uninit(void)override;			//�X�R�A�̏I������
	void Update(void)override;			//�X�R�A�̍X�V����
	void Draw(void)override;			//�X�R�A�̕`�揈��

	void SetScore(int nScore);			//�X�R�A�̐ݒ菈��
	void AddScore(int nValue);			//�X�R�A�̉��Z����
	void SubScore(int nSubtract);		//�X�R�A�̌��Z����
	void SetPosition(D3DXVECTOR3 pos)override { pos; }					//�|���S���̈ʒu����
	void SetMove(D3DXVECTOR3 move)override { move; }					//�|���S���̈ړ�����
	void SetLength(float length)override { length; }					//�|���S���̒���

	D3DXVECTOR3 GetPos(void)override { return D3DXVECTOR3(); }			//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void)override { return D3DXVECTOR3(); };		//�ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void)override { return D3DXVECTOR3(); };		//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void)override { return D3DXVECTOR3(); };			//��]�̎擾

	int GetScore(void) { return m_nScore; }								//�X�R�A�̎擾����
	float GetLength(void)override { return 0; }							//�g��k���̃X�P�[���̎擾

	static CScore *Create();											//����

private:
	CNumber *m_apNumber[SCORE_DIGIT];		//�X�R�A�̐���(����)
	int m_nScore;							//�X�R�A
};

#endif






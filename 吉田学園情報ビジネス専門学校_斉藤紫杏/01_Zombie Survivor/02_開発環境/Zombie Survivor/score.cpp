//============================================
//
//	score.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "score.h"
#include "application.h"
#include "renderer.h" 
#include "ranking.h"
#include "result.h"

//============================================
// �X�R�A�̃R���X�g���N�^
//============================================
CScore::CScore() : CObject(PRIORITY_LEVEL3)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}

//============================================
// �X�R�A�̃f�X�g���N�^
//============================================
CScore::~CScore()
{
	//���������Ȃ�
}

//============================================
// �X�R�A�̏���������
//============================================
HRESULT CScore::Init(void)
{
	//============================================
	//�����o�ϐ��̏�����
	//============================================
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		//�X�R�A�̐���
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(800.0f + 70.0f * nCnt, 50.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f),CNumber::NUMBERTYPE_SCORE);
	}
	m_nScore = 0;
	return S_OK;
}

//============================================
// �X�R�A�̏I������
//============================================
void CScore::Uninit(void)
{
	//�����o�ϐ��̏�����
	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
		}

		m_apNumber[nCnt] = nullptr;
	}

	CObject::Release();
}

//============================================
// �X�R�A�̍X�V����
//============================================
void CScore::Update()
{
	
}

//============================================
// �X�R�A�̕`�揈��
//============================================
void CScore::Draw()
{

}

//============================================
// �X�R�A�̐ݒ菈��
//============================================
void CScore::SetScore(int nScore)
{
	int aPosTexU[7];	//�e���̃X�R�A���i�[
	m_nScore = nScore;

	aPosTexU[0] = m_nScore % 10000000 / 1000000;
	aPosTexU[1] = m_nScore % 1000000 / 100000;
	aPosTexU[2] = m_nScore % 100000 / 10000;
	aPosTexU[3] = m_nScore % 10000 / 1000;
	aPosTexU[4] = m_nScore % 1000 / 100;
	aPosTexU[5] = m_nScore % 100 / 10;
	aPosTexU[6] = m_nScore % 10 / 1;

	for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
	{
		//������,���Ԗڂ�
		m_apNumber[nCnt]->SetTexture(10.0f, (float)aPosTexU[nCnt], 1.0f, 0.0f);
	}
	CRanking::SetRanking(m_nScore);
}

//============================================
// �X�R�A�̉��Z����
//============================================
void CScore::AddScore(int nValue)
{
	//�����o�ϐ��ɃX�R�A�����Z
	SetScore(m_nScore + nValue);
}

//============================================
// �X�R�A�̌��Z����
//============================================
void CScore::SubScore(int nSubtract)
{
	//�����o�ϐ��ɃX�R�A�����Z
	SetScore(m_nScore - nSubtract);
}
//============================================
// �X�R�A�̐���
//============================================
CScore *CScore::Create()
{
	CScore *pScore = nullptr;

	//�N���X�̐���
	pScore = new CScore;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pScore != nullptr)
	{
		//����������
		pScore->Init();
	}
	else
	{
		assert(false);
	}

	return pScore;
}

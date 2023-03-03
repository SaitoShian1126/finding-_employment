//********************************************
//
//	ranking.cpp
//	Author: saito shian
//
//********************************************

//�C���N���[�h
#include <stdio.h>
#include <assert.h>
#include "ranking.h"
#include "application.h"
#include "renderer.h" 
#include "input.h"
#include "object2D.h"
#include "fade.h"
#include "result.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
CNumber *CRanking::m_pNumber[MAX_RANKINGRANK][SCORE_DIGIT] = {};
int CRanking::m_aData[5] = {};
int CRanking::m_aRanking = 0;

//�����L���O�̃R���X�g���N�^
CRanking::CRanking()
{
	//********************************
	//�����o�ϐ��̃N���A
	//********************************
}

//�����L���O�̃f�X�g���N�^
CRanking::~CRanking()
{
	//���������Ȃ�
}

//�����L���O�̏���������
HRESULT CRanking::Init(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking.png",
		&m_pTextureRanking[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number.png",
		&m_pTextureRanking[1]);

	//********************************
	//�����o�ϐ��̏�����
	//********************************
	m_BGMFlag = false;

	m_pObject[0] = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject[0]->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject[0]->BindTexture(m_pTextureRanking[0]);

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			m_pNumber[nCntRanking][nCnt] = CNumber::Create(D3DXVECTOR3(425.0f + 90.0f * nCnt, 260.0f + 75.0f * nCntRanking, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),CNumber::NUMBERTYPE_SCORE);
			m_pNumber[nCntRanking][nCnt]->BindTexture(m_pTextureRanking[1]);
		}
	}

	LoadRanking();
	return S_OK;
}

//�����L���O�̏I������
void CRanking::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();

	CObject::Release();

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			if (m_pNumber[nCntRanking][nCnt] != nullptr)
			{
				m_pNumber[nCntRanking][nCnt]->Uninit();
			}
		}
	}
}

//�����L���O�̍X�V����
void CRanking::Update()
{
	//�C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true || pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B) && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_RANKING)
	{
		PlaySound(SOUND_LABEL_SE_BUTTOM);
		SaveRanking();
		CFade::SetFade(CApplication::MODE_TITLE);
	}

	//============================================
	// �T�E���h�̍Đ�
	//============================================
	if (m_BGMFlag == false)
	{
		PlaySound(SOUND_LABEL_RANKING);
		m_BGMFlag = true;
	}
}

//�����L���O�̕`�揈��
void CRanking::Draw()
{

}

//�����L���O�̐���
CRanking *CRanking::Create()
{
	CRanking *pRanking = nullptr;

	//�N���X�̐���
	pRanking = new CRanking;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pRanking != nullptr)
	{
		//����������
		pRanking->Init();
	}
	else
	{
		assert(false);
	}

	return pRanking;
}

//�����L���O�ǂݍ���
void CRanking::LoadRanking()
{
	FILE * pFile;	//�t�@�C���|�C���^��錾

	pFile = fopen("data/Save/ranking.txt", "r");

	if (pFile != nullptr)
	{
		//�X�R�A5���ǂݍ���
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//�t�@�C�����當�����ǂݍ���
			fscanf(pFile, "%d \n\n", &m_aData[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}

//�����L���O�ۑ�
void CRanking::SaveRanking()
{
	FILE * pFile;	//�t�@�C���|�C���^��錾

	pFile = fopen("data/Save/ranking.txt", "w");

	if (pFile != nullptr)
	{
		//�X�R�A��5�������o��
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//�t�@�C���ɏ����o��
			fprintf(pFile, "%d\n", m_aData[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}

//�����L���O�̐ݒ�
void CRanking::SetRankingScore()
{
	int aPosTexU[5][SCORE_DIGIT];	//�e���̐������i�[

	//�V�����X�R�A���Â��X�R�A�Ɣ�ׂ�
	if (m_aRanking > m_aData[4])
	{
		m_aData[4] = m_aRanking;
	}
	//�o�u���\�[�g(����)
	for (int nCount1 = 0; nCount1 < 4; nCount1++)
	{
		for (int nCount2 = nCount1 + 1; nCount2 < 5; nCount2++)
		{
			if (m_aData[nCount1] < m_aData[nCount2])
			{
				int tmp = m_aData[nCount1];
				m_aData[nCount1] = m_aData[nCount2];
				m_aData[nCount2] = tmp;
			}
		}
	}
	//8���̃����L���O�X�R�A��5��
	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		aPosTexU[nCntRanking][0] = m_aData[nCntRanking] % 10000000 / 1000000;
		aPosTexU[nCntRanking][1] = m_aData[nCntRanking] % 1000000 / 100000;
		aPosTexU[nCntRanking][2] = m_aData[nCntRanking] % 100000 / 10000;
		aPosTexU[nCntRanking][3] = m_aData[nCntRanking] % 10000 / 1000;
		aPosTexU[nCntRanking][4] = m_aData[nCntRanking] % 1000 / 100;
		aPosTexU[nCntRanking][5] = m_aData[nCntRanking] % 100 / 10;
		aPosTexU[nCntRanking][6] = m_aData[nCntRanking] % 10 / 1;
	}

	for (int nCntRanking = 0; nCntRanking < 5; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < SCORE_DIGIT; nCnt++)
		{
			//������,���Ԗڂ�
			m_pNumber[nCntRanking][nCnt]->SetTexture(10.0f, (float)aPosTexU[nCntRanking][nCnt], 1.0f, 0.0f);
		}
	}
}

void CRanking::SetRanking(int Score)
{
	m_aRanking = Score;
}

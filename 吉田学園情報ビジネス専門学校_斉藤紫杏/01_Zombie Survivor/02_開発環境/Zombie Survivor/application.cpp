//============================================
//
//	application.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <time.h>
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"
#include "input.h"
#include "debug.h"
#include "player.h"
#include "tutorial.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
CRenderer *CApplication::m_pRenderer = nullptr;
CInput *CApplication::m_pInput = nullptr;
CJoyPad *CApplication::m_pJoyPad = nullptr;
CMode *CApplication::m_pMode = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CDebugProc *CApplication::m_pDebug = nullptr;
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//============================================
// �A�v���P�[�V�����̃R���X�g���N�^
//============================================
CApplication::CApplication()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pRenderer = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//�A�v���P�[�V�����̃f�X�g���N�^
CApplication::~CApplication()
{
	//���������Ȃ�
}

//�A�v���P�[�V�����̏���������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_pRenderer = nullptr;
	m_pInput = nullptr;
	m_pJoyPad = nullptr;
	m_pMode = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pDebug = nullptr;
	m_mode = MODE_TITLE;

	//�����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;
	//�J�����N���X�̐���
	m_pCamera = new CCamera;
	//���C�g�N���X�̐���
	m_pLight = new CLight;
	//�C���v�b�g�̃C���X�^���X����
	m_pInput = new CInput;
	//�W���C�p�b�h�̃C���X�^���X����
	m_pJoyPad = new CJoyPad;
	//�f�o�b�O�\���̃C���X�^���X����
	m_pDebug = new CDebugProc;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//�W���C�p�b�h�̏���������
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pCamera->Init();
	m_pLight->Init();
	m_pDebug->Init();

	CFade::Create(MODE_GAME);

	return S_OK;
}

//============================================
// �A�v���P�[�V�����̏I������
//============================================
void CApplication::Uninit(void)
{
	//�L�[�{�[�h�̔j��
	if (m_pInput != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInput->Uninit();

		delete m_pInput;
		m_pInput = nullptr;
	}

	//�W���C�p�b�h�̔j��
	if (m_pJoyPad != nullptr)
	{
		//�W���C�p�b�h�̏I������
		m_pJoyPad->Uninit();

		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//�����_�����O�̔j��
	if (m_pRenderer != nullptr)
	{
		//�����_�����O�̏I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//�J�����̔j��
	if (m_pCamera != nullptr)
	{
		//�J�����̏I������
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//�f�o�b�O�\���̔j��
	if (m_pDebug != nullptr)
	{
		//�f�o�b�O�\���̏I������
		m_pDebug->Uninit();

		delete m_pDebug;
		m_pDebug = nullptr;
	}
	//�I�u�W�F�N�g�̔j������
	CObject::ReleaseAll();
}

//============================================
// �A�v���P�[�V�����̍X�V����
//============================================
void CApplication::Update(void)
{
	//============================================
	//	�X�V����
	//============================================
	if (m_pInput != nullptr)
	{
		//�L�[�{�[�h�̍X�V����
		m_pInput->Update();
	}

	if (m_pJoyPad != nullptr)
	{
		//�W���C�p�b�h�̍X�V����
		m_pJoyPad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//�����_�����O�̍X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != nullptr)
	{
		//���[�h�̍X�V����
		m_pCamera->Update();
	}

	if (m_pMode != nullptr)
	{
		//���[�h�̍X�V����
		m_pMode->Update();
	}
}

//============================================
// �A�v���P�[�V�����̕`�揈��
//============================================
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//�����_�����O�̕`�揈��
		m_pRenderer->Draw();
	}
}

//============================================
// �����_�����O�̃C���X�^���X�擾����
//============================================
CRenderer *CApplication::GetRenderer (void)
{
	return m_pRenderer;
}

//============================================
// ���[�h�̐ݒ菈��
//============================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}
	
	CObject::ModeRelease();

	m_mode = mode;

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case CApplication::MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;
	case CApplication::MODE_GAME:
		m_pMode = CGame::Create();
		break;
	case CApplication::MODE_RESULT:
		m_pMode = CResult::Create();
		break;
	case CApplication::MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
		break;
	case CApplication::MODE_MAX:
		break;
	default:
		break;
	}
}



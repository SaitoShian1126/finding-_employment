//============================================
//
//	tutorial.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "tutorial.h"
#include "application.h"
#include "renderer.h" 
#include "input.h"
#include "object2D.h"
#include "fade.h"
#include "bullet.h"
#include "sound.h"
#include "enter.h"

//============================================
// �`���[�g���A���̃R���X�g���N�^
//============================================
CTutorial::CTutorial()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �`���[�g���A���̃f�X�g���N�^
//============================================
CTutorial::~CTutorial()
{
	//���������Ȃ�
}

//============================================
// �`���[�g���A���̏���������
//============================================
HRESULT CTutorial::Init(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial.png",
		&m_pTextureTutorial);

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_BGMFlag = false;
	m_flag = false;

	m_pObject = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject->BindTexture(m_pTextureTutorial);

	return S_OK;
}

//============================================
// �`���[�g���A���̏I������
//============================================
void CTutorial::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();

	CObject::Release();
}

//============================================
// �`���[�g���A���̍X�V����
//============================================
void CTutorial::Update()
{
	//�C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	if (m_pFade->GetFade() == CFade::FADETYPE_NONE && m_flag == false)
	{
		CEnter::Create(D3DXVECTOR3(1000.0f, 650.0f, 0.0f), D3DXVECTOR3(250.0f, 75.0f, 0.0f));
		m_flag = true;
	}

	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_TUTORIAL
		|| pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B) && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_TUTORIAL)
	{
		PlaySound(SOUND_LABEL_SE_BUTTOM);
		CFade::SetFade(CApplication::MODE_GAME);
	}

	//============================================
	// �T�E���h�̍Đ�
	//============================================
	if (m_BGMFlag == false)
	{
		PlaySound(SOUND_LABEL_TITLE);
		m_BGMFlag = true;
	}
}

//============================================
// �`���[�g���A���̕`�揈��
//============================================
void CTutorial::Draw()
{

}

//============================================
// �`���[�g���A���̐���
//============================================
CTutorial *CTutorial::Create()
{
	CTutorial *ptutorial = nullptr;

	//�N���X�̐���
	ptutorial = new CTutorial;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (ptutorial != nullptr)
	{
		//����������
		ptutorial->Init();
	}
	else
	{
		assert(false);
	}

	return ptutorial;
}
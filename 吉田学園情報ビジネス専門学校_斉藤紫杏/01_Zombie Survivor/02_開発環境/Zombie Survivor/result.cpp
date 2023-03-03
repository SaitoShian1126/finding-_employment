//============================================
//
//	result.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include <assert.h>
#include "result.h"
#include "application.h"
#include "renderer.h" 
#include "input.h"
#include "fade.h"
#include "sound.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CResult::m_pTextureResult[2] = {};
CResult::TYPE CResult::m_TypeNumber = TYPE_NONE;

//============================================
// ���U���g�̃R���X�g���N�^
//============================================
CResult::CResult()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// ���U���g�̃f�X�g���N�^
//============================================
CResult::~CResult()
{
	//���������Ȃ�
}

//============================================
// ���U���g�̏���������
//============================================
HRESULT CResult::Init(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameOverResult.png",
		&m_pTextureResult[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameClearResult.png",
		&m_pTextureResult[1]);

	//============================================
	//�����o�ϐ��̏�����
	//============================================
	m_BGMFlag = false;

	m_pObject = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	switch (m_TypeNumber)
	{
	case CResult::TYPE_GAMEOVER:
		m_pObject->BindTexture(m_pTextureResult[0]);
		break;
	case CResult::TYPE_GAMECLEAR:
		m_pObject->BindTexture(m_pTextureResult[1]);
		break;
	default:
		break;
	}

	return S_OK;
}

//============================================
// ���U���g�̏I������
//============================================
void CResult::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();

	CObject::Release();
}

//============================================
// ���U���g�̍X�V����
//============================================
void CResult::Update()
{
	//�C���v�b�g�̃C���X�^���X����
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true ||  pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B) && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_RESULT)
	{
		PlaySound(SOUND_LABEL_SE_BUTTOM);
		CFade::SetFade(CApplication::MODE_RANKING);
	}

	//============================================
	// �T�E���h�̍Đ�
	//============================================
	if (m_BGMFlag == false && m_TypeNumber == CResult::TYPE_GAMECLEAR)
	{
		PlaySound(SOUND_LABEL_GAMECLEAR);
		m_BGMFlag = true;
	}

	//============================================
	// �T�E���h�̍Đ�
	//============================================
	if (m_BGMFlag == false && m_TypeNumber == CResult::TYPE_GAMEOVER)
	{
		PlaySound(SOUND_LABEL_GAMEOVER);
		m_BGMFlag = true;
	}
}

//============================================
// ���U���g�̕`�揈��
//============================================
void CResult::Draw()
{

}

//============================================
// ���U���g�̐ݒ菈��
//============================================
void CResult::SetType(TYPE type)
{
	m_TypeNumber = type;
}
//============================================
// ���U���g�̐���
//============================================
CResult *CResult::Create()
{
	CResult *pResult = nullptr;

	//�N���X�̐���
	pResult = new CResult;				//2D�I�u�W�F�N�g�̃C���X�^���X����

	//null�`�F�b�N
	if (pResult != nullptr)
	{
		//����������
		pResult->Init();
	}
	else
	{
		assert(false);
	}

	return pResult;
}

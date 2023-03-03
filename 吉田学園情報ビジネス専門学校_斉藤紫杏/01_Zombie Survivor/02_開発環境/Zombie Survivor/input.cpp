//============================================
//
//	input.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include "input.h"

//============================================
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================================
// ���͂̃R���X�g���N�^
//============================================
CInput::CInput(void)
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
	m_pDevice = nullptr;							//���̓f�o�C�X�ւ̃|�C���^
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = {};
		m_aKeyStateTrigger[nCnt] = {};
		m_aKeyStateRelease[nCnt] = {};
	}
}

//============================================
// ���͂̃f�X�g���N�^
//============================================
CInput::~CInput(void)
{

}

//============================================
// ���͂̏���������
//============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�̂�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X��
	m_pDevice->Acquire();

	return S_OK;
}

//============================================
// ���͂̏I������
//============================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//============================================
// ���͂̍X�V����
//============================================
void CInput::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])  & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyStateTrigger[nCntKey] ^ 0);
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//============================================
// �L�[����������
//============================================
bool CInput::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//============================================
// �L�[�P������
//============================================
bool CInput::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//============================================
// Release����
//============================================
bool CInput::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//============================================
//	�W���C�p�b�h
//============================================
//���͂̃R���X�g���N�^
CJoyPad::CJoyPad(void)
{
	//============================================
	// �����o�ϐ��̃N���A
	//============================================
}

//============================================
// ���͂̃f�X�g���N�^
//============================================
CJoyPad::~CJoyPad(void)
{

}
//============================================
// �W���C�p�b�h�̏���������
//============================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	//�������[�̃N���A
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	m_bUseJoypad = false;

	return S_OK;
}

//============================================
// �W���C�p�b�h�̏I������
//============================================
void CJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//============================================
// �W���C�p�b�h�̍X�V����
//============================================
void CJoyPad::Update(void)
{
	XINPUT_STATE joykeyState;	//�W���C�p�b�h�̓��͏���

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		m_JoykeyStateTrigger.Gamepad.wButtons = ~m_JoykeyState.Gamepad.wButtons& joykeyState.Gamepad.wButtons; // �g���K�[����ۑ�
		m_JoykeyState = joykeyState;  // �v���X����
		m_bUseJoypad = true;
	}
	else
	{
		m_bUseJoypad = false;
	}
}

//============================================
//	�W���C�p�b�g(�X�e�B�b�N�v���X����
//============================================
D3DXVECTOR3 CJoyPad::GetJoypadStick(JOYKEY Key)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoykeyState.Gamepad.sThumbLX / 32767.0f, -m_JoykeyState.Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos = D3DXVECTOR3(m_JoykeyState.Gamepad.sThumbRX / 32767.0f, -m_JoykeyState.Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_JoyStickPos;
}

//============================================
//	�W���C�p�b�g�g���K�[�y�_������
//============================================
int CJoyPad::GetJoypadTriggerPedal(JOYKEY Key)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoykeyState.Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoykeyState.Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//============================================
// �W���C�p�b�h�v���X�̎擾����
//============================================
bool CJoyPad::GetJoypadPress(JOYKEY key)
{
	return (m_JoykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//============================================
// �W���C�p�b�h�g���K�[�̎擾����
//============================================
bool CJoyPad::GetJoypadTrigger(JOYKEY key)
{
	return (m_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//============================================
// �W���C�p�b�h�̎g�p�󋵂��擾
//============================================
bool * CJoyPad::GetUseJoypad(void)
{
	return &m_bUseJoypad;
}
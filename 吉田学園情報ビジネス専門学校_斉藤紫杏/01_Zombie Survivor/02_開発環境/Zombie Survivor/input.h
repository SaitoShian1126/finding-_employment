//============================================
//
//	input.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _INPUT_H_
#define _INPUT_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �}�N����`
//============================================
#define NUM_KEY_MAX	(256)		//�L�[�̍ő�l

//============================================
// ���̓N���X
//============================================
class CInput
{
public:
	CInput();	//�R���X�g���N�^
	~CInput();	//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void);								//�X�V����
	bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�v���X�̎擾����
	bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�g���K�[�̎擾����
	bool GetRelease(int nKey);								//�L�[�{�[�h�����[�X�̎擾����

protected:
	BYTE m_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
	LPDIRECTINPUTDEVICE8 m_pDevice;					//�f�o�C�X
	static LPDIRECTINPUT8 m_pInput;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
};

//============================================
// ���̓N���X(�W���C�p�b�h)
//============================================
class CJoyPad : public CInput
{
public:
	//============================================
	// �{�^���̗񋓌^
	//============================================
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_LEFT_STICK,			//���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			//�E�X�e�B�b�N
		JOYKEY_MAX
	};

	CJoyPad();	//�R���X�g���N�^
	~CJoyPad();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	//�W���C�p�b�h�̏���������
	void Uninit(void)override;								//�W���C�p�b�h�̏I������
	void Update(void)override;								//�W���C�p�b�h�̍X�V����

	D3DXVECTOR3 GetJoypadStick(JOYKEY Key);					//�W���C�p�b�h�X�e�B�b�N����
	int GetJoypadTriggerPedal(JOYKEY Key);					//�W���C�p�b�h�g���K�[�y�_������

	bool GetJoypadPress(JOYKEY key);						//�W���C�p�b�h�̃v���X�̎擾����
	bool GetJoypadTrigger(JOYKEY key);						//�W���C�p�b�h�̃g���K�[����
	bool *GetUseJoypad(void);								//�W���C�p�b�h�̎g�p�󋵂��擾

private:
	XINPUT_STATE m_JoykeyState;								//�W���C�p�b�h�̃v���X���
	XINPUT_STATE m_JoykeyStateTrigger;						//�W���C�p�b�h�̃g���K�[���
	XINPUT_VIBRATION m_JoyMoter;							//�W���C�p�b�h�̃��[�^�[
	D3DXVECTOR3 m_JoyStickPos;								//�W���C�X�e�B�b�N�̌X��
	int m_aJoykeyStateTrigger;								//�W���C�p�b�h�̃g���K�[���
	int m_aJoykeyStateRelese;								//�W���C�p�b�h�̃����[�X���
	bool m_bUseJoypad;										//�W���C�p�b�h���g�p���Ă邩�ǂ���
};

#endif
//============================================
//
//	ui.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _UI_H_
#define _UI_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================

//============================================
// �O���錾
//============================================
class CNumber;

//============================================
// UI�N���X
//============================================
class CUi : public CObject2D
{
public:
	enum UITYPE
	{
		UITYPE_NUMBER = 0,
		UITYPE_BOMB,
		UITYPE_MAX
	};

	CUi();							//�R���X�g���N�^
	~CUi()override;					//�f�X�g���N�^

	HRESULT Init(void)override;				//UI�̏���������
	void Uninit(void)override;				//UI�̏I������
	void Update(void)override;				//UI�̍X�V����
	void Draw(void)override;				//UI�̕`�揈��

	void SetBomb(int bomb);
	void AddBomb(int nValue);				//���e�̐��̉��Z����
	void SubBomb(int nSubtract);			//���e�̐��̌��Z����

	UITYPE GetUiType(void) { return m_type; }
	void SetUiType(UITYPE type) { m_type = type; }

	static CUi *Create(const D3DXVECTOR3 &pos,UITYPE type);	//����

	static HRESULT Load(void);				//�e�N�X�`���̓ǂݍ���
	static void Unload(void);				//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXCOLOR m_col;						//�F
	D3DXVECTOR3 m_size;						//�T�C�Y
	CNumber *m_apNumber;					//�X�R�A�̐���(����)
	UITYPE m_type;							//UI�̎��
	int m_nUninitTimer;						//�폜����
	int m_Bomb;								//���e
	bool m_flag;							//�t���O
	bool m_ColorFlag;						//�F�̃t���O
	bool m_BloodFlag;						//�����o�����̃t���O
};

#endif
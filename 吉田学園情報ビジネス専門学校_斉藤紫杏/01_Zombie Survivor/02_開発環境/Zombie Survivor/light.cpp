//============================================
//
//	light.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
//============================================
#include "application.h"
#include "renderer.h"
#include "light.h"

//============================================
// ���C�g�̃R���X�g���N�^
//============================================
CLight::CLight()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// ���C�g�̃f�X�g���N�^
//============================================
CLight::~CLight()
{
	//���������Ȃ�
}
//============================================
// ���C�g�̏���������
//============================================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;												//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&m_nLight, sizeof(m_nLight));						//�\���̕ϐ����[���N���A�ł���֗��֐�(memset)�Ɠ���

	//============================================
	//	���C�g1��
	//============================================

	//���C�g�̎�ނ�ݒ�
	m_nLight[0].Type = D3DLIGHT_DIRECTIONAL;					//���s����

	//���C�g�̊g�U����ݒ�(�F)
	m_nLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//���C�g�̐F

	//���C�g�̕�����ݒ�(x,y,z)
	vecDir = D3DXVECTOR3(1.0f, -1.0f, -0.5f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[0].Direction = vecDir;

	//���C�g��ݒ肷�遫0��0�Ԗڂ̃��C�g��ݒ�(�����u���Ƃ��͂����̐����𑝂₹�΂���)
	pDevice->SetLight(0, &m_nLight[0]);

	//���C�g��L��������
	pDevice->LightEnable(0, TRUE);

	//============================================
	//	���C�g2��
	//============================================

	m_nLight[1].Type = D3DLIGHT_DIRECTIONAL;					//���s����

	m_nLight[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//���C�g�̐F

	//���C�g�̕�����ݒ�(x,y,z)
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[1].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &m_nLight[1]);

	//���C�g��L��������
	pDevice->LightEnable(1, TRUE);

	//============================================
	//	���C�g3��
	//============================================

	m_nLight[2].Type = D3DLIGHT_DIRECTIONAL;					//���s����

	m_nLight[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//���C�g�̐F

	//���C�g�̕�����ݒ�(x,y,z)
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, -0.0f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[2].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(2, &m_nLight[2]);

	//���C�g��L��������
	pDevice->LightEnable(2, TRUE);

	//============================================
	//	���C�g4��
	//============================================

	m_nLight[3].Type = D3DLIGHT_DIRECTIONAL;					//���s����

	m_nLight[3].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//���C�g�̐F

	//���C�g�̕�����ݒ�(x,y,z)
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[3].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(3, &m_nLight[3]);

	//���C�g��L��������
	pDevice->LightEnable(3, TRUE);

	return S_OK;
}

//============================================
// ���C�g�̏I������
//============================================
void CLight::Uninit(void)
{

}

//============================================
// ���C�g�̍X�V����
//============================================
void CLight::Update(void)
{

}


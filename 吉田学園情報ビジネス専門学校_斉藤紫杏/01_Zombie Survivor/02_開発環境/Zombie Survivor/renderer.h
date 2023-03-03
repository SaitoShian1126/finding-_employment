//============================================
//
//	renderer.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _RENDERER_H_
#define  _RENDERER_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �O���錾
//============================================
class CCamera;

//============================================
// �����_�����O�N���X(�`��N���X)
//============================================
class CRenderer
{
public:
	CRenderer();							//�R���X�g���N�^
	~CRenderer();							//�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void);		//�f�o�C�X�̎擾���� 

private:	
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;		//Device�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D = nullptr;					//Direct3D�I�u�W�F�N�g
	LPD3DXFONT m_pFont = nullptr;					//�t�H���g
	VERTEX_2D m_aVertex[4];							//���_���	
};

#endif




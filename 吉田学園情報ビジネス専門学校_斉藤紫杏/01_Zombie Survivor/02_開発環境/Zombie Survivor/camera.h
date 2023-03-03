//============================================
//
//	camera.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// �}�N����`
//============================================
#define CAMERA_SPEED	(0.5f)	//�J�����̑��x

//============================================
// �J�����N���X
//============================================
class CCamera
{
public:
	CCamera();				//�R���X�g���N�^
	~CCamera();				//�f�X�g���N�^

	HRESULT Init(void);		//�J�����̏���������
	void Uninit(void);		//�J�����̏I������
	void Update(void);		//�J�����̍X�V����

	void SetCamera();												//�J�����̐ݒ菈��
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }					//�J�����̉�]�̐ݒ菈��
	void SetDistance(float distance) { m_fDistance = distance; }	//�J�����̋�������
	void SetOffset(D3DXVECTOR3 posV, D3DXVECTOR3 posR);				//�J�����̋����̐ݒ菈��
	void SetShakeCamera(int QuakeFrame, int QuakeMagnitude);		//�J�����̗h��̐ݒ菈��

	D3DXVECTOR3 GetPosV() { return m_PosVDest; }
	D3DXVECTOR3 GetPosR() { return m_PosRDest; }
	D3DXVECTOR3 GetVecU() { return m_VecU; }
	float GetDistance() { return m_fDistance; }

	static D3DXVECTOR3 GetCameraRot() { return m_Rot; }		//�J�����̉�]�̎擾����	

private:
	static D3DXVECTOR3 m_Rot;		//����
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_PosVDest;			//���_
	D3DXVECTOR3 m_PosDest;			//�ړI�̎��_
	D3DXVECTOR3 m_PosRDest;			//�����_
	D3DXVECTOR3 m_VecU;				//������x�N�g��
	D3DXVECTOR3 m_OffsetV;			//���_�̋���
	D3DXVECTOR3 m_OffsetR;			//�����_�̋���
	D3DXVECTOR3 m_PosV;				//�ړI�̎��_
	D3DXVECTOR3 m_PosR;				//�ړI�̒����_
	D3DVIEWPORT9 m_Viewport;		//�r���[�|�[�g
	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X

	int m_nQuakeFrameCount;			//�h�炷�t���[����
	int m_fQuakeMagnitude;			//�h��̗�

	float m_fDistance;				//���_���璍���_�̋���		
};

#endif
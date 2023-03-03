//============================================
//
//	model.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MODEL_H_
#define _MODEL_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "objectx.h"

//============================================
// �}�N����`
//============================================
#define MAX_MODEL_WORD		(512)	//���[�h��
#define NUMBER_OF_MODELS	(64)	//���f����

//============================================
// �O���錾
//============================================
class CModelParts;
class CLine;

//============================================
// ���f���N���X
//============================================
class CModel : public CObjectX
{
public:

	CModel();										//�R���X�g���N�^
	~CModel()override;								//�f�X�g���N�^

	HRESULT Init(void)override;						//���f���̏���������
	void Uninit(void)override;						//���f���̏I������
	void Update(void)override;						//���f���̍X�V����
	void Draw(void)override;						//���f���̕`�揈��

	void LoadModel();								//���f���̓ǂݍ���
	void Vtx(void);									//�ő�ŏ�

	CModelParts **GetModelParts(void);

	static CModel *Create();						//����
	
private:
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_rot;								//����
	D3DXVECTOR3 m_size;								//�T�C�Y
	CModelParts *m_apModel[NUMBER_OF_MODELS];		//���f���p�[�c
	D3DXVECTOR3 m_posOld;							//�ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;							//�ړI�̌���
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;								//���b�V��
	LPD3DXBUFFER m_pBuffMat;						//�o�b�t�@�[
	DWORD m_nNumMat;								//�}�e���A��
	D3DXMATRIX *m_pmtxParent;						//�e�̃}�g���b�N�X

	int m_nLife;									//�̗�
	int m_nCountModel;								//���f�����̃J�E���g
	int m_ModelNumber;

	float m_PlayerHeightPos;						//���f���̍����̈ʒu
};

#endif

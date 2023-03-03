//============================================
//
//	modelparts.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"

//============================================
// ���f���p�[�c�N���X
//============================================
class CModelParts
{
public:
	CModelParts();					//�R���X�g���N�^
	~CModelParts();					//�f�X�g���N�^

	HRESULT Init(void);				//���f���p�[�c�̏���������
	void Uninit(void);				//���f���p�[�c�̏I������
	void Update(void);				//���f���p�[�c�̍X�V����
	void DrawFile(void);			//���f���p�[�c�̕`�揈��

	//getter
	D3DXMATRIX *GetMatrix(void);				//�}�g���b�N�X�̎擾
	LPD3DXMESH GetMesh(void);					//���b�V���̎擾
	D3DXVECTOR3 GetRot(void);					//����
	D3DXVECTOR3 GetPos(void);					//�ʒu�̎擾
	D3DXVECTOR3 GetVtxMax(void);				//�ő�̎擾
	D3DXVECTOR3 GetVtxMin(void);				//�ŏ��̎擾

	//setter
	void SetMatrix(D3DXMATRIX *matrixparent);	//�}�g���b�N�X�̐ݒ�
	void SetPos(D3DXVECTOR3 pos);				//�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);				//�����̐ݒ�
	void SetVtxMax(D3DXVECTOR3 max);			//�ő�̐ݒ�
	void SetVtxMin(D3DXVECTOR3 min);			
		
	void SetModel(char * pFile);				//���f���̐ݒ�
	void ModelCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size);	//���f���̓����蔻��

	static CModelParts *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);			//����

private:
	LPDIRECT3DTEXTURE9 *m_pTexture;					//�e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;						//�o�b�t�@
	LPD3DXMESH m_pMesh;								//���b�V��
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_rot;								//����
	D3DXVECTOR3 m_VtxMinModel;						//�ŏ�
	D3DXVECTOR3 m_VtxMaxModel;						//�ő�
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	D3DXMATRIX *m_pmtxParent;						//�e�̃}�g���b�N�X
	DWORD m_pNumMat;								//�}�e���A��

	int nIdxModelParent;							//�e���f���̃C���f�b�N�X
	bool m_LineUseFlag;								//���C�����g�p���ꂽ��
};

#endif
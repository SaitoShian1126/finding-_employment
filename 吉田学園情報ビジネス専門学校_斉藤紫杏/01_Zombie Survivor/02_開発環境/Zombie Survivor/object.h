//=============================================================================
//
// �I�u�W�F�N�g����
// Author : SAITO SHIAN
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObject
{
public:

	struct VERTEX_LINE
	{
		D3DXVECTOR3 pos;			//xyz���W
		D3DCOLOR col;				//�J�[���[
	};

	//-------------------------------------------------------------------------
	// �񋓌^
	//-------------------------------------------------------------------------
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PAUSE,		//�|�[�Y
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_BG,			//�w�i
		OBJTYPE_EFFECT,		//�G�t�F�N�g
		OBJTYPE_MESH,		//���b�V��
		OBJTYPE_NUMBER,		//�ԍ�
		OBJTYPE_SCORE,		//�X�R�A
		OBJTYPE_MODE,		//���[�h
		OBJTYPE_TITLEROGO,	//�^�C�g�����S
		OBJTYPE_COUNTDOWN,	//�J�E���g�_�E��
		OBJTYPE_MODEL,		//���f��
		OBJTYPE_GIMMICK,	//�M�~�b�N
		OBJTYPE_MAX,
		OBJTYPE_INVALID
	};

	enum EPRIORITY
	{
		PRIORITY_LEVEL0 = 0,
		PRIORITY_LEVEL1,
		PRIORITY_LEVEL2,
		PRIORITY_LEVEL3,
		PRIORITY_LEVEL4,
		PRIORITY_LEVEL5,
		PRIORITY_FADE,
		PRIORITY_LEVELMAX
	};

	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	virtual HRESULT Init() = 0;							// ����������
	virtual void Uninit() = 0;							// �I������
	virtual void Update() = 0;							// �X�V����
	virtual void Draw() = 0;							// �`�揈��
	virtual void VtxUpdate() {}							// ���_���W�X�V����

	virtual void SetPosition(D3DXVECTOR3 pos) = 0;		//�|���S���̈ʒu����
	virtual void SetMove(D3DXVECTOR3 move) = 0;			//�|���S���̈ړ�����
	virtual void SetLength(float length) = 0;

	virtual D3DXVECTOR3 GetPos(void) = 0;				//�ʒu�̎擾����
	virtual D3DXVECTOR3 GetMove(void) = 0;				//�ړ��ʂ̎擾
	virtual D3DXVECTOR3 GetSize(void) = 0;				//�T�C�Y�̎擾����
	virtual D3DXVECTOR3 GetRot(void) = 0;				//��]�̎擾
	virtual float GetLength(void) = 0;					//�g��k���̃X�P�[���̎擾

	virtual int GetLife(void) { return 0; }				//�̗͂̎擾
	virtual void SetLife(int nLife) { nLife; }			//�̗͂̐ݒ�

	virtual void SetType(const EObjType type);			// �^�C�v�ݒ菈��
	virtual void SetCanPoseUpdate() { m_canPoseUpdate = true; }
	virtual EObjType GetObjType(void);								// �I�u�W�F�N�g�̃^�C�v�擾����

	static void ReleaseAll(void);						// �S�ẴC���X�^���X�̏I������
	static void UpdateAll(void);						// �S�ẴC���X�^���X�̍X�V����
	static void DrawAll(void);							// �S�ẴC���X�^���X�̕`�揈��
	static void ModeRelease();							// ���[�h�ȊO��������j������
	void Death(void);									// �I�u�W�F�N�g�j������

	static CObject* GetTop(int nPriority) { return m_pTop[nPriority]; }
	static CObject* GetCurrent(int nPriority) { return m_pCurrent[nPriority]; }
	CObject* GetNext() { return m_pNext; }

protected:
	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	void Release();										// �C���X�^���X�̉������

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	static int m_nNumAll;										// �I�u�W�F�N�g�̑���
	int m_nID;													// �ڑ���̔ԍ�	
	int m_nPriority;											// �v���C�I���e�B�̕ۑ�
	EObjType m_objType;											// �I�u�W�F�N�g�̎��

	// ���X�g�\��
	static CObject *m_pTop[PRIORITY_LEVELMAX];					// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[PRIORITY_LEVELMAX];				// ����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;											// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;											// ���̃I�u�W�F�N�g�ւ̃|�C���^

	bool m_bDeath;												// ���t���O

	bool m_canPoseUpdate;	// �|�[�Y���̍X�V���o���邩
};

#endif
//============================================
//
//	game.h
//	Author: saito shian
//
//============================================

//============================================
// 2�d�C���N���[�h�K�[�h
//============================================
#ifndef _GAME_H_
#define _GAME_H_

//============================================
// �C���N���[�h
//============================================
#include "main.h"
#include "mode.h"
#include "object2D.h"

//============================================
// �}�N����`
//============================================
#define MAX_PARTICLE	(100)	//�p�[�e�B�N���̍ő吔
#define MAX_GASOLENE	(4)		//�K�\�����̍ő吔
#define MAX_ROCK		(4)		//��M�~�b�N�̍ő吔
#define PARTICLE_TIME	(125)	//�p�[�e�B�N����������܂ł̎���
#define MAX_UI			(2)		//UI�̍ő吔

//============================================
// �O���錾
//============================================
class CMeshField;
class CEnemy;
class CFade;
class CScore;
class CGasolene_Gimmick;
class CModel;
class CHitBox;
class CPlayer;
class CSpawn;
class CParticle;
class CRock_gimmick;
class CBoss;
class CIndication;
class CItem;
class CUi;

//============================================
// �Q�[���N���X
//============================================
class CGame : public CMode
{
public:
	CGame();					//�R���X�g���N�^
	~CGame();					//�f�X�g���N�^

	HRESULT Init(void);			//�Q�[���̏���������
	void Uninit(void);			//�Q�[���̏I������
	void Update(void);			//�Q�[���̍X�V����
	void Draw(void);			//�Q�[���̕`�揈��

	static CMeshField *GetMeshField(void) { return m_pMeshField; }								//���b�V���t�B�[���h�̏��̎擾����
	static CScore *GetScore(void) { return m_pScore; }											//�G�̏��̎擾����
	static CGasolene_Gimmick **GetGasoleneGimmick(void) { return m_pGasoleneGimmick; }			//�K�\�����M�~�b�N�̏��̎擾����
	static CModel *GetModel(void) { return m_Model; }											//���f���̎擾����
	static CPlayer *GetPlayer(void) { return m_pPlayer; }										//�v���C���[�擾����
	static CSpawn *GetSpawn(void) { return m_pSpawn; }											//�X�|�[���̎擾����
	static CParticle **GetParticle(void) { return m_pParticle; }								//�p�[�e�B�N���̎擾����
	static CRock_gimmick **GetRockGimmick(void) { return m_pRockGimmick; }						//��M�~�b�N�̎擾����
	static CBoss *GetBoss(void) { return m_pBoss; }												//�{�X�̎擾����
	static CIndication *GetIndication(void) { return m_pIndication; }							//�\���̎擾����
	static CItem *GetItem(void) { return m_pItem; }												//�A�C�e���̎擾����
	static CUi **GetUi(void) { return m_pUi; }													//UI�̎擾����

	static void SetPlayer(CPlayer *player);														//�v���C���[�̐ݒ菈��
	static void SetItem(CItem *item);															//�A�C�e���̐ݒ菈��

	static CGame *Create();												//����

private:
	static CMeshField *m_pMeshField;							//���b�V���t�B�[���h�̃C���X�^���X
	static CScore *m_pScore;									//�X�R�A�̃C���X�^���X
	static CGasolene_Gimmick *m_pGasoleneGimmick[MAX_GASOLENE];	//�K�\�����M�~�b�N�̃C���X�^���X
	static CModel *m_Model;										//���f���̃C���X�^���X
	static CPlayer *m_pPlayer;									//�v���C���[�̃C���X�^���X
	static CSpawn *m_pSpawn;									//�X�|�[���̃C���X�^���X
	static CParticle *m_pParticle[MAX_PARTICLE];				//�p�[�e�B�N���̃C���X�^���X
	static CRock_gimmick *m_pRockGimmick[MAX_ROCK];				//��M�~�b�N�̃C���X�^���X
	static CBoss *m_pBoss;										//�{�X�̃C���X�^���X
	static CIndication *m_pIndication;							//�\���̃C���X�^���X
	static CItem *m_pItem;										//�A�C�e���̃C���X�^���X
	static CUi *m_pUi[MAX_UI];									//UI�̃C���X�^���X
	CFade *m_pFade;												//�t�F�[�h�̃C���X�^���X

	int m_ParticleCreateTime;									//�p�[�e�B�N���̐��������܂ł̎���
	int m_ItemSpawnTime;										//�A�C�e�����ăX�|�[�����鎞��
	bool m_ItemGetFlag;											//�A�C�e�����擾�����̂��̃t���O
	bool m_BGMFlag;												//BGM���g�p����Ă���̂��t���O
	bool m_EnemyFlag;
};
#endif




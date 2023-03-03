//********************************************
//
//	ranking.h
//	Author: saito shian
//
//********************************************

//2�d�C���N���[�h�K�[�h
#ifndef _RANKING_H_
#define _RANKING_H_

//�C���N���[�h
#include "main.h"
#include "mode.h"
#include "score.h"

//�}�N����`
#define MAX_RANKINGRANK	(5)

//�O���錾
class CObject2D;
class CFade;
class CNumber;

//�����L���O�N���X
class CRanking : public CMode
{
public:
	CRanking();							//�R���X�g���N�^
	~CRanking();						//�f�X�g���N�^

	HRESULT Init(void);					//�����L���O�̏���������
	void Uninit(void);					//�����L���O�̏I������
	void Update(void);					//�����L���O�̍X�V����
	void Draw(void);					//�����L���O�̕`�揈��
	void LoadRanking(void);				//�����L���O�ǂݍ���
	void SaveRanking(void);				//�����L���O�ۑ�

	static void SetRankingScore(void);	//�����L���O�X�R�A�̐ݒ�
	static void SetRanking(int Score);	//�����L���O�̐ݒ�
	static CRanking *Create();			//����

private:
	static CNumber *m_pNumber[MAX_RANKINGRANK][SCORE_DIGIT];	//�����̃|�C���^
	static int m_aData[5];										//�O���t�@�C���̃f�[�^
	static int m_aRanking;										//��������_
	LPDIRECT3DTEXTURE9 m_pTextureRanking[2] = {};				//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject[2];									//�I�u�W�F�N�g�̃|�C���^
	CFade *m_pFade;												//�t�F�[�h

	bool m_BGMFlag;							//BGM�t���O
};

#endif
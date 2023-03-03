//============================================
// 
// 	enemy.cpp
// 	Author: saito shian
// 
//============================================

//============================================
// インクルード
//============================================
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "enemy.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"
#include "modelparts.h"
#include "keyset.h"
#include "key.h"
#include "motionset.h"
#include "score.h"
#include "player.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "indication.h"

//============================================
// 静的メンバ変数宣言
//===========================================

//============================================
// オブジェクトのコンストラクタ
//============================================
CEnemy::CEnemy()
{
	//============================================
	// メンバ変数のクリア
	//============================================
	m_nCountModel = 0;
	m_nLife = 0;
}

//============================================
// オブジェクトのデストラクタ
//============================================
CEnemy::~CEnemy()
{
	// 何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CEnemy::Init(void)
{
	//============================================
	// 乱数
	//============================================
	srand((unsigned int)time(nullptr));							//起動時に一回だけ行うため初期化に書く	

	//============================================
	// メンバ変数の初期化
	//============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountModel = 0;
	m_PresentKeySet = 0;
	m_Frame = 0;
	m_nLife = 1;
	m_EnemyNumber = 0;
	m_VoiceCount = 0;
	m_MoveRand = 0;
	m_AttackCount = ATTACK_COUNT;
	m_PlayerDethFlag = false;
	m_MoveRandFlag = false;
	m_VoiceFlag = false;
	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			m_apModelHuman[nCnt] = nullptr;								//モデル数の初期化
			m_FrameSpeedHuman[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//フレームスピードの初期化
			m_RotSpeedHuman[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転スピードの初期化
		}
	}
	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			m_apModelDog[nCnt] = nullptr;								//モデル数の初期化
			m_FrameSpeedDog[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//フレームスピードの初期化
			m_RotSpeedDog[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転スピードの初期化
		}
	}

	switch (m_type)
	{
	case CEnemy::ENEMYTYPE_HUMAN:
		//プレイヤーのファイル読み込み
		LoadEnemy("data/XMODEL/EnemyMotion.txt");
		break;
	case CEnemy::ENEMYTYPE_DOG:
		//プレイヤーのファイル読み込み
		LoadEnemy("data/XMODEL/EnemyDogMotion.txt");
		break;
	default:
		break;
	}

	//最大最小
	Vtx();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CEnemy::Uninit(void)
{
	//サウンドの停止
//	StopSound(SOUND_LABEL_SE_VOICE);

	////モデルパーツの終了処理
	//for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
	//{
	//	if (m_apModel[nCnt] != nullptr)
	//	{
	//		m_apModel[nCnt]->Uninit();
	//		delete m_apModel[nCnt];
	//		m_apModel[nCnt] = nullptr;
	//	}
	//}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CEnemy::Update(void)
{
//	CMeshField *pMeshField = CGame::GetMeshField();
	D3DXVECTOR3 CameraRot = CCamera::GetCameraRot();
	int EnemyCount = CGame::GetSpawn()->GetEnemyCount();

	m_posOld = m_pos;

	if (m_MoveRandFlag == false)
	{
		m_MoveRand = (float)(rand() % 9 + 7);
		m_MoveRandFlag = true;
	}
	if (m_PlayerDethFlag == false && m_MoveRandFlag == true)
	{
		if (m_type == ENEMYTYPE_HUMAN)
		{
			//敵の移動処理
			EnemyMove(m_MoveRand);
		}
		if (m_type == ENEMYTYPE_DOG)
		{
			//敵の移動処理
			EnemyMove(m_MoveRand);
		}
	}

	//メッシュフィールドと敵の当たり判定
	//pMeshField->GetMeshFieldCollision(&m_pos);

	for (int nCnt = 0; nCnt < NUMBER_OF_MODELS; nCnt++)
	{
		//モデルとの当たり判定
		CModelParts *pModelParts = CGame::GetModel()->GetModelParts()[nCnt];
		pModelParts->ModelCollision(&m_pos, &m_posOld, m_size);
	}

	if (m_VoiceCount >= 0)
	{
		m_VoiceCount--;
		if (m_VoiceCount <= 0)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_VOICE);
			m_VoiceCount = 300;
		}
	}

	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;
			if (pEnemy != this)
			{
				pEnemy->CollisionEnemy(&m_pos, &m_posOld, m_size);
			}
		}
		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}


	//向きの設定
	SetRot(m_rot);
	//移動の設定
	SetMove(m_move);
	//位置の設定
	SetPosition(m_pos);
}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CEnemy::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//ローカルマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_type == ENEMYTYPE_HUMAN)
	{
		//モデルパーツのfor文
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			if (m_apModelHuman[nCnt] != nullptr)
			{
				m_apModelHuman[nCnt]->DrawFile();
			}
		}
	}
	if (m_type == ENEMYTYPE_DOG)
	{
		//モデルパーツのfor文
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			if (m_apModelDog[nCnt] != nullptr)
			{
				m_apModelDog[nCnt]->DrawFile();
			}
		}
	}
}

//============================================
// 生成
//============================================
CEnemy * CEnemy::Create(const D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	// 3Dオブジェクトクラスの生成
	pEnemy = new CEnemy;				// 3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pEnemy != nullptr)
	{
		pEnemy->SetEnemyType(type);
		// 初期化処理
		pEnemy->Init();
		pEnemy->SetPosition(pos);
		pEnemy->SetType(OBJTYPE_ENEMY);
	}
	else
	{
		assert(false);
	}
	return pEnemy;
}

//============================================
// 外部ファイル読み込み
//============================================
void CEnemy::LoadEnemy(char * pFileName)
{
	if (m_type == ENEMYTYPE_HUMAN)
	{
		int nNumParts;
		int nCntMotionSet = 0;
		int Loop = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;
		char aText[2000];							//文字列を格納する配列
		char FileName[MODEL_HUMAN_PARTS][2000];		//2次元配列

		FILE *pFile; //ファイルポインタを宣言

		pFile = fopen(pFileName, "r");

		aText[0] = '\0';	//文字列なし

		if (pFile != nullptr)
		{//ファイルが開けた場合
		 //ファイルに入力したデータを書き出す処理
			while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
			{//テキストの最初の行を読み込むまで繰り返す
				fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
			}

			while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
			{//テキストの最後の行を読み込むまで繰り返す
				fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

				if (strncmp(&aText[0], "#", strlen("#")) == 0)
				{
					fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
					continue;
				}

				//ファイルネームを複数個入力する
				if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aText[0]);        // = を読み込む
					fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0番目から読み込まれる

					//モデルパーツの生成
					m_apModelHuman[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					m_nCountModel++;
				}

				if (strcmp(&aText[0], "CHARACTERSET") == 0)
				{
					while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
					{
						fscanf(pFile, "%s", &aText[0]);

						if (strncmp(&aText[0], "#", strlen("#")) == 0)
						{
							fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
							continue;
						}

						if (strcmp(&aText[0], "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%s", &aText[0]);        // = を読み込む
							fscanf(pFile, "%d", &nNumParts);
						}

						if (strcmp(&aText[0], "PARTSSET") == 0)
						{
							D3DXVECTOR3 pos, rot;
							int IndexParent = 0;	//親の番号
							int Ind = 0;

							while (strcmp(&aText[0], "END_PARTSSET") != 0)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strncmp(&aText[0], "#", strlen("#")) == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
									continue;
								}

								if (strcmp(&aText[0], "INDEX") == 0)
								{
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &Ind);
								}

								else if (strcmp(&aText[0], "PARENT") == 0)
								{

									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &IndexParent);
								}

								else if (strcmp(&aText[0], "POS") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									pos = D3DXVECTOR3(x, y, z);
								}

								else if (strcmp(&aText[0], "ROT") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									rot = D3DXVECTOR3(x, y, z);
								}
							}

							//モデルパーツの生成
							m_apModelHuman[Ind] = CModelParts::Create(pos, rot);

							//モデルパーツの読み込み
							m_apModelHuman[Ind]->SetModel(&FileName[Ind][0]);

							//モデルパーツに情報が入っていたら
							if (m_apModelHuman[Ind])
							{
								//モデルパーツの向きの設定
								m_apModelHuman[Ind]->SetRot(rot);
							}

							//親の番号が0より下だったら
							if (IndexParent < 0)
							{
								//モデルパーツのマトリックスの設定
								m_apModelHuman[Ind]->SetMatrix(&m_mtxWorld);
							}
							//親の番号がモデルパーツより小さかったら
							else if (IndexParent < MODEL_HUMAN_PARTS)
							{
								//モデルパーツのマトリックスの設定
								m_apModelHuman[Ind]->SetMatrix(m_apModelHuman[IndexParent]->GetMatrix());
							}
						}
					}
				}
				if (strcmp(&aText[0], "MOTIONSET") == 0)
				{//テキストの最初の行を読み込むまで繰り返す

					m_MotionSet[nCntMotionSet] = CMotionSet::Create();

					m_MotionSet[nCntMotionSet]->SetNumParts(nNumParts);

					while (strcmp(&aText[0], "END_MOTIONSET") != 0)
					{//テキストの最後の行を読み込むまで繰り返す
						fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							int numKey = 0;
							fscanf(pFile, "%s %d", &aText[0], &numKey);
							m_MotionSet[nCntMotionSet]->SetNumKey(numKey);
						}

						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &Loop);

							if (Loop == 1)
							{

								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(1);
							}

							else
							{
								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(0);
							}
						}

						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strcmp(&aText[0], "#") == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
									continue;
								}

								if (strcmp(&aText[0], "END_KEYSET") == 0)
								{
									nCntKeySet++;
									nCntKey = 0;
									break;
								}

								if (strcmp(&aText[0], "FRAME") == 0)
								{
									int nFrame = 0;
									fscanf(pFile, "%s %d", &aText[0], &nFrame);

									m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->SetFrame(nFrame);
								}

								else if (strcmp(&aText[0], "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aText[0]);

										if (strcmp(&aText[0], "END_KEY") == 0)
										{
											nCntKey++;

											if (nCntKey >= m_MotionSet[nCntMotionSet]->GetNumParts())
											{
												nCntKey = 0;
											}
											break;
										}
										else if (strcmp(&aText[0], "POS") == 0)
										{
											float px = 0.0f;
											float py = 0.0f;
											float pz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &px);
											fscanf(pFile, "%f", &py);
											fscanf(pFile, "%f", &pz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetPos(D3DXVECTOR3(px, py, pz));
										}

										else if (strcmp(&aText[0], "ROT") == 0)
										{
											float rx = 0.0f;
											float ry = 0.0f;
											float rz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &rx);
											fscanf(pFile, "%f", &ry);
											fscanf(pFile, "%f", &rz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetRot(D3DXVECTOR3(rx, ry, rz));
										}
									}
								}
							}
						}
					}

					nCntMotionSet++;
					nCntKeySet = 0;
					nCntKey = 0;
				}
			}
		}
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			if (m_apModelHuman[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos, rot;
				pos = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetPos();
				rot = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetRot();
				m_apModelHuman[nCnt]->SetPos(pos);
				m_apModelHuman[nCnt]->SetRot(rot);
			}
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		int nNumParts;
		int nCntMotionSet = 0;
		int Loop = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;
		char aText[2000];							//文字列を格納する配列
		char FileName[MODEL_DOG_PARTS][2000];		//2次元配列

		FILE *pFile; //ファイルポインタを宣言

		pFile = fopen(pFileName, "r");

		aText[0] = '\0';	//文字列なし

		if (pFile != nullptr)
		{//ファイルが開けた場合
		 //ファイルに入力したデータを書き出す処理
			while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
			{//テキストの最初の行を読み込むまで繰り返す
				fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
			}

			while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
			{//テキストの最後の行を読み込むまで繰り返す
				fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

				if (strncmp(&aText[0], "#", strlen("#")) == 0)
				{
					fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
					continue;
				}

				//ファイルネームを複数個入力する
				if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aText[0]);        // = を読み込む
					fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0番目から読み込まれる

																		//モデルパーツの生成
					m_apModelDog[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					m_nCountModel++;
				}

				if (strcmp(&aText[0], "CHARACTERSET") == 0)
				{
					while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
					{
						fscanf(pFile, "%s", &aText[0]);

						if (strncmp(&aText[0], "#", strlen("#")) == 0)
						{
							fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
							continue;
						}

						if (strcmp(&aText[0], "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%s", &aText[0]);        // = を読み込む
							fscanf(pFile, "%d", &nNumParts);
						}

						if (strcmp(&aText[0], "PARTSSET") == 0)
						{
							D3DXVECTOR3 pos, rot;
							int IndexParent = 0;	//親の番号
							int Ind = 0;

							while (strcmp(&aText[0], "END_PARTSSET") != 0)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strncmp(&aText[0], "#", strlen("#")) == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
									continue;
								}

								if (strcmp(&aText[0], "INDEX") == 0)
								{
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &Ind);
								}

								else if (strcmp(&aText[0], "PARENT") == 0)
								{

									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%d", &IndexParent);
								}

								else if (strcmp(&aText[0], "POS") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									pos = D3DXVECTOR3(x, y, z);
								}

								else if (strcmp(&aText[0], "ROT") == 0)
								{
									float x = 0.0f;
									float y = 0.0f;
									float z = 0.0f;
									fscanf(pFile, "%s", &aText[0]);
									fscanf(pFile, "%f", &x);
									fscanf(pFile, "%f", &y);
									fscanf(pFile, "%f", &z);
									rot = D3DXVECTOR3(x, y, z);
								}
							}

							//モデルパーツの生成
							m_apModelDog[Ind] = CModelParts::Create(pos, rot);

							//モデルパーツの読み込み
							m_apModelDog[Ind]->SetModel(&FileName[Ind][0]);

							//モデルパーツに情報が入っていたら
							if (m_apModelDog[Ind])
							{
								//モデルパーツの向きの設定
								m_apModelDog[Ind]->SetRot(rot);
							}

							//親の番号が0より下だったら
							if (IndexParent < 0)
							{
								//モデルパーツのマトリックスの設定
								m_apModelDog[Ind]->SetMatrix(&m_mtxWorld);
							}
							//親の番号がモデルパーツより小さかったら
							else if (IndexParent < MODEL_DOG_PARTS)
							{
								//モデルパーツのマトリックスの設定
								m_apModelDog[Ind]->SetMatrix(m_apModelDog[IndexParent]->GetMatrix());
							}
						}
					}
				}
				if (strcmp(&aText[0], "MOTIONSET") == 0)
				{//テキストの最初の行を読み込むまで繰り返す

					m_MotionSet[nCntMotionSet] = CMotionSet::Create();

					m_MotionSet[nCntMotionSet]->SetNumParts(nNumParts);

					while (strcmp(&aText[0], "END_MOTIONSET") != 0)
					{//テキストの最後の行を読み込むまで繰り返す
						fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							int numKey = 0;
							fscanf(pFile, "%s %d", &aText[0], &numKey);
							m_MotionSet[nCntMotionSet]->SetNumKey(numKey);
						}

						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &Loop);

							if (Loop == 1)
							{

								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(1);
							}

							else
							{
								m_MotionSet[nCntMotionSet]->GetLoop();
								m_MotionSet[nCntMotionSet]->SetLoop(0);
							}
						}

						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aText[0]);

								if (strcmp(&aText[0], "#") == 0)
								{
									fgets(aText, MAX_ENEMY_WORD, pFile);        //一行ごと読み込む
									continue;
								}

								if (strcmp(&aText[0], "END_KEYSET") == 0)
								{
									nCntKeySet++;
									nCntKey = 0;
									break;
								}

								if (strcmp(&aText[0], "FRAME") == 0)
								{
									int nFrame = 0;
									fscanf(pFile, "%s %d", &aText[0], &nFrame);

									m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->SetFrame(nFrame);
								}

								else if (strcmp(&aText[0], "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aText[0]);

										if (strcmp(&aText[0], "END_KEY") == 0)
										{
											nCntKey++;

											if (nCntKey >= m_MotionSet[nCntMotionSet]->GetNumParts())
											{
												nCntKey = 0;
											}
											break;
										}
										else if (strcmp(&aText[0], "POS") == 0)
										{
											float px = 0.0f;
											float py = 0.0f;
											float pz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &px);
											fscanf(pFile, "%f", &py);
											fscanf(pFile, "%f", &pz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetPos(D3DXVECTOR3(px, py, pz));
										}

										else if (strcmp(&aText[0], "ROT") == 0)
										{
											float rx = 0.0f;
											float ry = 0.0f;
											float rz = 0.0f;
											fscanf(pFile, "%s", &aText[0]);
											fscanf(pFile, "%f", &rx);
											fscanf(pFile, "%f", &ry);
											fscanf(pFile, "%f", &rz);
											m_MotionSet[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetRot(D3DXVECTOR3(rx, ry, rz));
										}
									}
								}
							}
						}
					}

					nCntMotionSet++;
					nCntKeySet = 0;
					nCntKey = 0;
				}
			}
		}
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			if (m_apModelDog[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos, rot;
				pos = m_MotionSet[0]->GetKeySet(1)->GetKey(nCnt)->GetPos();
				rot = m_MotionSet[0]->GetKeySet(1)->GetKey(nCnt)->GetRot();
				m_apModelDog[nCnt]->SetPos(pos);
				m_apModelDog[nCnt]->SetRot(rot);
			}
		}
	}
}

//============================================
// モーション関数
//============================================
void CEnemy::MotionEnemyAnimation(void)
{
	m_Frame++;		//フレームのインクリメント

	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			D3DXVECTOR3 pos = m_apModelHuman[nCnt]->GetPos();		//モデルパーツの位置取得
			D3DXVECTOR3 rot = m_apModelHuman[nCnt]->GetRot();		//モデルパーツの向き取得
			pos += m_FrameSpeedHuman[nCnt];							//モデルパーツの位置にフレームの速さを代入
			rot += m_RotSpeedHuman[nCnt];							//モデルパーツの向きに向きの速さを代入
			m_apModelHuman[nCnt]->SetPos(pos);						//位置の設定
			m_apModelHuman[nCnt]->SetRot(rot);						//向きの設定
		}

		if (m_Frame >= m_MotionSet[m_MotionType]->GetKeySet(m_PresentKeySet)->GetFrame())
		{	//現在のアニメーションのフレーム数以上だったら

			int NextKeySet = 0;					//次のキーセット変数
			NextKeySet = m_PresentKeySet + 1;	//次のキーセットを代入

			if (NextKeySet >= m_MotionSet[m_MotionType]->GetNumKey() && m_MotionSet[m_MotionType]->GetLoop() == 1)
			{	//再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している

				NextKeySet = 0;					//再生中のキー数カウントを初期化

			}
			else if (NextKeySet >= m_MotionSet[m_MotionType]->GetNumKey() && m_MotionSet[m_MotionType]->GetLoop() == 0)
			{	//再生中のキー数カウントがキー数の最大値を超えたとき

				m_MotionSet[m_MotionType]->SetLoop(false);		//ループをfalseに設定する	
				NextKeySet = 0;											//次のキーセットの初期化
			}

			for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
			{
				//速度の計算
				m_FrameSpeedHuman[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_apModelHuman[nCnt]->GetPos());
				m_FrameSpeedHuman[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedHuman[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedHuman[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				//回転の計算
				m_RotSpeedHuman[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_apModelHuman[nCnt]->GetRot());
				m_RotSpeedHuman[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedHuman[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedHuman[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			}

			m_Frame = 0;						//フレームの初期化
			m_PresentKeySet = NextKeySet;
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			D3DXVECTOR3 pos = m_apModelDog[nCnt]->GetPos();			//モデルパーツの位置取得
			D3DXVECTOR3 rot = m_apModelDog[nCnt]->GetRot();			//モデルパーツの向き取得
			pos += m_FrameSpeedDog[nCnt];							//モデルパーツの位置にフレームの速さを代入
			rot += m_RotSpeedDog[nCnt];								//モデルパーツの向きに向きの速さを代入
			m_apModelDog[nCnt]->SetPos(pos);						//位置の設定
			m_apModelDog[nCnt]->SetRot(rot);						//向きの設定
		}

		if (m_Frame >= m_MotionSet[0]->GetKeySet(m_PresentKeySet)->GetFrame())
		{	//現在のアニメーションのフレーム数以上だったら

			int NextKeySet = 0;					//次のキーセット変数
			NextKeySet = m_PresentKeySet + 1;	//次のキーセットを代入

			if (NextKeySet >= m_MotionSet[0]->GetNumKey() && m_MotionSet[0]->GetLoop() == 1)
			{	//再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している

				NextKeySet = 0;					//再生中のキー数カウントを初期化

			}
			else if (NextKeySet >= m_MotionSet[0]->GetNumKey() && m_MotionSet[0]->GetLoop() == 0)
			{	//再生中のキー数カウントがキー数の最大値を超えたとき

				m_MotionSet[0]->SetLoop(false);		//ループをfalseに設定する	
				NextKeySet = 0;											//次のキーセットの初期化
			}

			for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
			{
				//速度の計算
				m_FrameSpeedDog[nCnt] = (m_MotionSet[0]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_apModelDog[nCnt]->GetPos());
				m_FrameSpeedDog[nCnt].x /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedDog[nCnt].y /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_FrameSpeedDog[nCnt].z /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				//回転の計算
				m_RotSpeedDog[nCnt] = (m_MotionSet[0]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_apModelDog[nCnt]->GetRot());
				m_RotSpeedDog[nCnt].x /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedDog[nCnt].y /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
				m_RotSpeedDog[nCnt].z /= (float)m_MotionSet[0]->GetKeySet(NextKeySet)->GetFrame();
			}

			m_Frame = 0;						//フレームの初期化
			m_PresentKeySet = NextKeySet;
		}
	}
}


//============================================
// 頂点の最大最小
//============================================
void CEnemy::Vtx(void)
{
	D3DXVECTOR3 min = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	if (m_type == ENEMYTYPE_HUMAN)
	{
		for (int nCnt = 0; nCnt < MODEL_HUMAN_PARTS; nCnt++)
		{
			int nNumVtx;	//頂点数
			DWORD sizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;	//頂点バッファへのポインタ

			//頂点数の取得
			nNumVtx = m_apModelHuman[nCnt]->GetMesh()->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(m_apModelHuman[nCnt]->GetMesh()->GetFVF());

			//頂点バッファのロック
			m_apModelHuman[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してモデルの最小値、最大値を取得
				//xの比較
				if (vtx.x < min.x)
				{
					min.x = vtx.x;
				}
				if (vtx.x > max.x)
				{
					max.x = vtx.x;
				}

				//yの比較(最小値)
				if (vtx.y < min.y)
				{
					min.y = vtx.y;
				}
				if (vtx.y > max.y)
				{
					max.y = vtx.y;
				}

				//zの比較(最小値)
				if (vtx.z < min.z)
				{
					min.z = vtx.z;
				}
				if (vtx.z > max.z)
				{
					max.z = vtx.z;
				}
				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			//頂点バッファのアンロック
			m_apModelHuman[nCnt]->GetMesh()->UnlockVertexBuffer();

			m_apModelHuman[nCnt]->SetVtxMin(min);
			m_apModelHuman[nCnt]->SetVtxMax(max);
		}
	}

	if (m_type == ENEMYTYPE_DOG)
	{
		for (int nCnt = 0; nCnt < MODEL_DOG_PARTS; nCnt++)
		{
			int nNumVtx;	//頂点数
			DWORD sizeFVF;	//頂点フォーマットのサイズ
			BYTE *pVtxBuff;	//頂点バッファへのポインタ

							//頂点数の取得
			nNumVtx = m_apModelDog[nCnt]->GetMesh()->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(m_apModelDog[nCnt]->GetMesh()->GetFVF());

			//頂点バッファのロック
			m_apModelDog[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してモデルの最小値、最大値を取得
				//xの比較
				if (vtx.x < min.x)
				{
					min.x = vtx.x;
				}
				if (vtx.x > max.x)
				{
					max.x = vtx.x;
				}

				//yの比較(最小値)
				if (vtx.y < min.y)
				{
					min.y = vtx.y;
				}
				if (vtx.y > max.y)
				{
					max.y = vtx.y;
				}

				//zの比較(最小値)
				if (vtx.z < min.z)
				{
					min.z = vtx.z;
				}
				if (vtx.z > max.z)
				{
					max.z = vtx.z;
				}
				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			//頂点バッファのアンロック
			m_apModelDog[nCnt]->GetMesh()->UnlockVertexBuffer();

			m_apModelDog[nCnt]->SetVtxMin(min);
			m_apModelDog[nCnt]->SetVtxMax(max);
		}
	}
	//敵のサイズ
	m_size = D3DXVECTOR3(max.x - min.x, max.y - min.y, max.z - min.z);
}

//============================================
// プレイヤーの当たり判定
//============================================
void CEnemy::CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 size)
{
	//左の当たり判定
	if (pPos->z - size.z / 2.0f < m_pos.z + m_size.z / 2
		&& pPos->z + size.z / 2.0f > m_pos.z - m_size.z / 2
		&& (int)(pPosOld->x + size.x / 2.0f) <= (int)(m_pos.x - m_size.x / 2)
		&& (int)(pPos->x + size.x / 2.0f) > (int)(m_pos.x - m_size.x / 2))
	{
		pPos->x = (int)(m_pos.x - m_size.x / 2 - size.x / 2.0f);
	}

	//右の当たり判定
	if (pPos->z - size.z / 2.0f < m_pos.z + m_size.z / 2
		&& pPos->z + size.z / 2.0f > m_pos.z - m_size.z / 2
		&& (int)(pPosOld->x - size.x / 2.0f) >= (int)(m_pos.x + m_size.x / 2)
		&& (int)(pPos->x - size.x / 2.0f) < (int)(m_pos.x + m_size.x / 2))
	{
		pPos->x = (int)(m_pos.x + m_size.x / 2 + size.x / 2.0f);
	}

	//手前の当たり判定
	if (pPos->x - size.x / 2.0f < m_pos.x + m_pos.x / 2
		&&pPos->x + size.x / 2.0f > m_pos.x - m_pos.x  /2
		&& (int)(pPosOld->z + size.z / 2.0f) <= (int)(m_pos.z - m_pos.z / 2)
		&& (int)(pPos->z + size.z / 2.0f) > (int)(m_pos.z - m_pos.z / 2))
	{
		pPos->z = (int)(m_pos.z - m_pos.z / 2 - size.z / 2.0f);
	}

	//奥の当たり判定
	if (pPos->x - size.x / 2.0f < m_pos.x + m_pos.x / 2
		&& pPos->x + size.x / 2.0f > m_pos.x - m_pos.x / 2
		&& (int)(pPosOld->z - size.z / 2.0f) >= (int)(m_pos.z + m_pos.z / 2)
		&& (int)(pPos->z - size.z / 2.0f) < (int)(m_pos.z + m_pos.z / 2))
	{
		pPos->z = (int)(m_pos.z + m_pos.z / 2 + size.z / 2.0f);
	}
}

//============================================
// 敵の移動処理
//============================================
void CEnemy::EnemyMove(float speed)
{
	D3DXVECTOR3 PlayerRot = GetRot();

	//前回の位置を保存
	m_posOld = m_pos;

	//============================================
	//  目的の角度の正規化
	//============================================
	if (m_rotDest.y - PlayerRot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - PlayerRot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	// 角度慣性
	PlayerRot.y += (m_rotDest.y - PlayerRot.y) * 0.1f;

	//============================================
	//  角度の正規化
	//============================================
	if (PlayerRot.y > D3DX_PI)
	{
		PlayerRot.y = PlayerRot.y - D3DX_PI * 2;
	}
	else if (PlayerRot.y < -D3DX_PI)
	{
		PlayerRot.y = PlayerRot.y + D3DX_PI * 2;
	}

	//モーション関数
	MotionEnemyAnimation();

	//============================================
	//  プレイヤーを追従する処理
	//============================================
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();

	m_move = m_pos - PlayerPos;				//プレイヤーの位置と敵の位置を計算して移動に代入
	D3DXVec3Normalize(&m_move, &m_move);	//移動の正規化
	m_move *= speed;						//移動スピード

	//2点間の距離を求める
	float Rotx = m_pos.x - PlayerPos.x;
	float Rotz = m_pos.z - PlayerPos.z;

	//角度の設定
	float Angle = atan2f(Rotx, Rotz);

	//目的の向きの設定
	m_rotDest = D3DXVECTOR3(0.0f, Angle, 0.0f);

	//======================
	//目的の方向の正規化
	//======================
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//目的の値に近づける
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.08f;

	//======================
	//正規化
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	//移動モーションに設定
	SetMotionType(CEnemy::MOTIONTYPE_MOVE);

	if (m_PlayerDethFlag == false && CGame::GetPlayer() != nullptr)
	{
		int PlayerLife = CGame::GetPlayer()->GetLife();

		if (PlayerPos.x + 30.0f >= m_pos.x + m_size.x && PlayerPos.x - 30.0f <= m_pos.x - m_size.x
			&&PlayerPos.z + 30.0f >= m_pos.z + m_size.z && PlayerPos.z - 30.0f <= m_pos.z - m_size.z)
		{	//敵がプレイヤーを攻撃する範囲
			SetMotionType(CEnemy::MOTIONTYPE_ATTACK);
			if (m_MotionType == MOTIONTYPE_ATTACK)
			{
				m_AttackCount--;
				if (m_AttackCount <= 0)
				{
					PlayerLife--;

					if (PlayerLife <= 0)
					{
						m_PlayerDethFlag = true;
						CFade::SetFade(CApplication::MODE_RESULT);
						CResult::SetType(CResult::TYPE_GAMEOVER);
						CGame::GetPlayer()->Uninit();
						CGame::SetPlayer(nullptr);
						CSpawn::SetBoss(nullptr);
						return;
					}
					else
					{
						if (m_RandFlag == false)
						{
							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								float x = rand() % 1280 + 1;
								float y = rand() % 720 + 1;
								float sxy = rand() % 75 + 15;
								CIndication::Create(D3DXVECTOR3(x, y, 0.0f), D3DXVECTOR3(sxy, sxy, 0.0f), CIndication::INDICATIONTYPE_BLOOD);
							}
							m_RandFlag = true;
						}
						CGame::GetPlayer()->SetPlayerLife(PlayerLife);
					}
				}
				if (m_AttackCount <= 0)
				{
					m_AttackCount = ATTACK_COUNT;
				}
			}
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SetMove(m_move);
		}
		else
		{
			m_AttackCount = ATTACK_COUNT;
		}
	}

	//移動量減衰
	m_pos.x += (0.0f - m_move.x) * 0.1f;
	m_pos.y += (0.0f - m_move.y) * 0.1f;
	m_pos.z += (0.0f - m_move.z) * 0.1f;
}

//============================================
// モーションの種類の設定
//============================================
void CEnemy::SetMotionType(MOTIONTYPE type)
{
	m_MotionType = type;
}


//============================================
// 敵の種類
//============================================
void CEnemy::SetEnemyType(ENEMYTYPE type)
{
	m_type = type;
}

//============================================
// 位置の設定
//============================================
void CEnemy::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// 向きの設定
//============================================
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================
// 移動の設定
//============================================
void CEnemy::SetMove(D3DXVECTOR3 move)
{
	move;
}

//============================================
// 長さの設定
//============================================
void CEnemy::SetLength(float length)
{
	length;
}

//============================================
// 体力の設定
//============================================
void CEnemy::SetLife(int life)
{
	m_nLife = life;
}

//============================================
// 位置の取得
//============================================
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

//============================================
// 移動の取得
//============================================
D3DXVECTOR3 CEnemy::GetMove(void)
{
	return D3DXVECTOR3();
}

//============================================
// 向きの取得
//============================================
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

//============================================
// 長さの取得
//============================================
float CEnemy::GetLength(void)
{
	return 0.0f;
}

//============================================
// 体力の取得
//============================================
int CEnemy::GetLife(void)
{
	return m_nLife;
}


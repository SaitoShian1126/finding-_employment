//============================================
// 
// 	boss.cpp
// 	Author: saito shian
// 
//============================================

//============================================
// インクルード
//============================================
#include <stdio.h>
#include <assert.h>
#include "boss.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"
#include "modelparts.h"
#include "keyset.h"
#include "key.h"
#include "motionset.h"
#include "score.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

//============================================
// 静的メンバ変数宣言
//============================================
D3DXVECTOR3 CBoss::m_pos = {};
D3DXVECTOR3 CBoss::m_rot = {};
D3DXVECTOR3 CBoss::m_size = {};
CBullet *CBoss::m_pBullet = nullptr;

//============================================
// オブジェクトのコンストラクタ
//============================================
CBoss::CBoss()
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
CBoss::~CBoss()
{
	// 何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CBoss::Init(void)
{
	// ============================================
	// メンバ変数の初期化
	// ============================================
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(10.0f, 50.0f, 10.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountModel = 0;
	m_PresentKeySet = 0;
	m_Frame = 0;
	m_EnemyCount = 0;
	m_BulletCount = 0;
	m_nLife = 350;
	m_RandCount = 100;
	m_MotionFlag = false;
	m_RandFlag = false;
	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		m_apModel[nCnt] = nullptr;								//モデル数の初期化
		m_FrameSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//フレームスピードの初期化
		m_RotSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転スピードの初期化
	}

	//プレイヤーのファイル読み込み
	LoadBoss();

	//最大最小
	Vtx();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CBoss::Uninit(void)
{
	//モデルパーツの終了処理
	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	//破棄処理
	Release();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CBoss::Update(void)
{
	//ボスの向き
	BossRot();

	//ボスの攻撃処理
	BossAttack();

	//移動の設定
	SetMove(m_move);
	//位置の設定
	SetPosition(m_pos);
}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CBoss::Draw(void)
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

	//モデルパーツのfor文
	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->DrawFile();
		}
	}
}

//============================================
// 生成
//============================================
CBoss * CBoss::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBoss *pBoss = nullptr;

	// 3Dオブジェクトクラスの生成
	pBoss = new CBoss;				// 3Dオブジェクトのインスタンス生成

	// nullptrチェック
	if (pBoss != nullptr)
	{
		// 初期化処理
		pBoss->Init();
		pBoss->SetPosition(pos);
		pBoss->m_move = move;
	}
	else
	{
		assert(false);
	}
	return pBoss;
}

//============================================
// 外部ファイル読み込み
//============================================
void CBoss::LoadBoss()
{
	int nNumParts;
	int nCntMotionSet = 0;
	int Loop = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	char aText[2000];							//文字列を格納する配列
	char FileName[MODEL_BOSS_PARTS][2000];		//2次元配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data/XMODEL/BossMotion.txt", "r");

	aText[0] = '\0';	//文字列なし

	if (pFile != nullptr)
	{//ファイルが開けた場合
	 //ファイルに入力したデータを書き出す処理
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_BOSS_WORD, pFile);        //一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_BOSS_WORD, pFile);        //一行ごと読み込む
				continue;
			}

			//ファイルネームを複数個入力する
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);        // = を読み込む
				fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0番目から読み込まれる

																	//モデルパーツの生成
				m_apModel[m_nCountModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nCountModel++;
			}

			if (strcmp(&aText[0], "CHARACTERSET") == 0)
			{
				while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_BOSS_WORD, pFile);        //一行ごと読み込む
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
								fgets(aText, MAX_BOSS_WORD, pFile);        //一行ごと読み込む
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
						m_apModel[Ind] = CModelParts::Create(pos, rot);

						//モデルパーツの読み込み
						m_apModel[Ind]->SetModel(&FileName[Ind][0]);

						//モデルパーツに情報が入っていたら
						if (m_apModel[Ind])
						{
							//モデルパーツの向きの設定
							m_apModel[Ind]->SetRot(rot);
						}

						//親の番号が0より下だったら
						if (IndexParent < 0)
						{
							//モデルパーツのマトリックスの設定
							m_apModel[Ind]->SetMatrix(&m_mtxWorld);
						}
						//親の番号がモデルパーツより小さかったら
						else if (IndexParent < MODEL_BOSS_PARTS)
						{
							//モデルパーツのマトリックスの設定
							m_apModel[Ind]->SetMatrix(m_apModel[IndexParent]->GetMatrix());
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
								fgets(aText, MAX_BOSS_WORD, pFile);        //一行ごと読み込む
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
	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			D3DXVECTOR3 pos, rot;
			pos = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetPos();
			rot = m_MotionSet[m_MotionType]->GetKeySet(1)->GetKey(nCnt)->GetRot();
			m_apModel[nCnt]->SetPos(pos);
			m_apModel[nCnt]->SetRot(rot);
		}
	}
}

//============================================
// 頂点の最大最小
//============================================
void CBoss::Vtx(void)
{
	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = m_apModel[nCnt]->GetMesh()->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_apModel[nCnt]->GetMesh()->GetFVF());

		//頂点バッファのロック
		m_apModel[nCnt]->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		D3DXVECTOR3 min = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		D3DXVECTOR3 max = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

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
		m_apModel[nCnt]->GetMesh()->UnlockVertexBuffer();

		m_apModel[nCnt]->SetVtxMin(min);
		m_apModel[nCnt]->SetVtxMax(max);

		//敵のサイズ
		m_size = D3DXVECTOR3(max.x - min.x, max.y - min.y, max.z - min.z);
	}
}

//============================================
// ボスの向き
//============================================
void CBoss::BossRot()
{
	//プレイヤーの位置取得
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();

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
}

//============================================
// ボスの攻撃処理
//============================================
void CBoss::BossAttack()
{
	//============================================
	// 追従爆発弾
	//============================================
	m_RandCount--;
	if (m_RandCount <= 0)
	{
		m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + 25.0f, 80.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6.0f, 6.0f, 0.0f), 100, CBullet::BULLETTYPE_BOSS);
		m_RandCount = 200;
	}

	MotionBossAnimation();
}

//============================================
// モーション関数
//============================================
void CBoss::MotionBossAnimation(void)
{
	m_Frame++;		//フレームのインクリメント

	for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
	{
		D3DXVECTOR3 pos = m_apModel[nCnt]->GetPos();		//モデルパーツの位置取得
		D3DXVECTOR3 rot = m_apModel[nCnt]->GetRot();		//モデルパーツの向き取得
		pos += m_FrameSpeed[nCnt];							//モデルパーツの位置にフレームの速さを代入
		rot += m_RotSpeed[nCnt];							//モデルパーツの向きに向きの速さを代入
		m_apModel[nCnt]->SetPos(pos);						//位置の設定
		m_apModel[nCnt]->SetRot(rot);						//向きの設定
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

		for (int nCnt = 0; nCnt < MODEL_BOSS_PARTS; nCnt++)
		{
			//速度の計算
			m_FrameSpeed[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_apModel[nCnt]->GetPos());
			m_FrameSpeed[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			m_FrameSpeed[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			m_FrameSpeed[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			//回転の計算
			m_RotSpeed[nCnt] = (m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_apModel[nCnt]->GetRot());
			m_RotSpeed[nCnt].x /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].y /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].z /= (float)m_MotionSet[m_MotionType]->GetKeySet(NextKeySet)->GetFrame();
		}

		m_Frame = 0;						//フレームの初期化
		m_PresentKeySet = NextKeySet;
	}
}

//============================================
// モーションの種類の設定
//============================================
void CBoss::SetMotionType(MOTIONTYPE type)
{
	m_MotionType = type;
}

//============================================
// ボスが死んだのかの設定
//============================================
void CBoss::SetBossDeathFlag(bool flag)
{
	m_BossDeathFlag = flag;
}

//============================================
// 位置の設定
//============================================
void CBoss::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// 移動の設定
//============================================
void CBoss::SetMove(D3DXVECTOR3 move)
{
	move;
}

//============================================
// 長さの設定
//============================================
void CBoss::SetLength(float length)
{
	length;
}

//============================================
// 体力の設定
//============================================
void CBoss::SetLife(int life)
{
	m_nLife = life;
}

//============================================
// 位置の取得
//============================================
D3DXVECTOR3 CBoss::GetPos(void)
{
	return m_pos;
}

//============================================
// 移動の取得
//============================================
D3DXVECTOR3 CBoss::GetMove(void)
{
	return D3DXVECTOR3();
}

//============================================
// サイズの取得
//============================================
D3DXVECTOR3 CBoss::GetSize(void)
{
	return m_size;
}

//============================================
// 向きの取得
//============================================
D3DXVECTOR3 CBoss::GetRot(void)
{
	return m_rot;
}

//============================================
// 長さの取得
//============================================
float CBoss::GetLength(void)
{
	return 0.0f;
}

//============================================
// 体力の取得
//============================================
int CBoss::GetLife(void)
{
	return m_nLife;
}

//============================================
// ボスが死んだのかフラグ
//============================================
bool CBoss::GetBossDethFlag(void)
{
	return m_BossDeathFlag;
}



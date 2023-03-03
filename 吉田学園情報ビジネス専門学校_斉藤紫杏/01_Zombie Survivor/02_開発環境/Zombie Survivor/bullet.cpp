//============================================
//
//	bullet.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "bullet.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "object2D.h"
#include "score.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "result.h"
#include "billboard.h"
#include "gasolene_gimmick.h"
#include "spawn.h"
#include "explosion.h"
#include "sound.h"
#include "boss.h"
#include "indication.h"
#include "particle.h"
#include "camera.h"

//============================================
// 静的メンバ変数宣言
//============================================

//============================================
// 弾のコンストラクタ
//============================================
CBullet::CBullet()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyDeathFlag = false;
	m_GimmickUninitFlag = false;
}

//============================================
// 弾のデストラクタ
//============================================
CBullet::~CBullet()
{
	//何も書かない
}

//============================================
// 弾の初期化処理
//============================================
HRESULT CBullet::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EnemyDeathFlag = false;
	m_GimmickUninitFlag = false;
	m_BulletMoveFlag = false;
	m_RandFlag = false;
	m_BossDeathFlag = false;
	m_nBulletExplosionTime = 150;
	m_ExplosionTime = 50;
	m_ResultTime = 200;

	//オブジェクト基礎の初期化処理
	CObjectBase::Init();

	switch (m_type)
	{
	case CBullet::BULLETTYPE_PLAYER:
		SetTexture("data/TEXTURE/bullet000.png");
		break;
	case CBullet::BULLETTYPE_BOSS:
		SetTexture("data/TEXTURE/弾.png");
		break;
	case CBullet::BULLETTYPE_BOMB:
		SetTexture("data/TEXTURE/爆弾.png");
		break;
	case CBullet::BULLETTYPE_MAX:
		break;
	default:
		break;
	}

	return S_OK;
}

//============================================
// 弾の終了処理
//============================================
void CBullet::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CObjectBase::Uninit();
}

//============================================
// 弾の更新処理
//============================================
void CBullet::Update(void)
{
	//弾の情報取得
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletMove = GetMove();
	D3DXVECTOR3 BulletSize = GetSize();

	//カメラの情報を取得
	CCamera *pCamera = CApplication::GetCamera();

	//弾の位置更新
	BulletPos += BulletMove;

	//寿命を減らす処理
	m_nLife--;

	//プレイヤーの弾の時
	if (m_nLife <= 0 && m_type == CBullet::BULLETTYPE_PLAYER)
	{
		Uninit();
		return;
	}

	//爆弾の破棄処理
	if (m_nLife <= 0 && m_type == CBullet::BULLETTYPE_BOMB)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_BOMB);
		//カメラを揺らす
		pCamera->SetShakeCamera(10, 1);
		CExplosion::Create(D3DXVECTOR3(BulletPos.x, BulletPos.y + 20.0f, BulletPos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
		//弾の削除
		Uninit();
		return;
	}

	//ボスの弾の攻撃処理
	if (m_type == CBullet::BULLETTYPE_BOSS && CGame::GetPlayer() != nullptr && CBoss::GetBullet() != nullptr)
	{
		BossBullet(BulletPos, D3DXVECTOR3(BOMB_HIT_SIZE, 0.0f, BOMB_HIT_SIZE), BulletMove);
		m_nBulletExplosionTime--;
		if (m_nBulletExplosionTime <= 0)
		{
			Uninit();
			return;
		}
	}

	//弾(爆弾)とボスの当たり判定
	if (m_type == BULLETTYPE_BOMB && CSpawn::GetBoss() != nullptr)
	{
		BombHitBoss(BulletPos, D3DXVECTOR3(BOMB_SIZE, BOMB_SIZE, 0.0f));
	}

	//弾とギミックの当たり判定
	if (m_GimmickUninitFlag == false)
	{
		HitGimmick(BulletPos);
	}
	//弾とボスの当たり判定処理
	if (CSpawn::GetBoss() != nullptr && m_type == CBullet::BULLETTYPE_PLAYER)
	{
		HitBoss(BulletPos);
	}

	//弾と敵の当たり判定処理
	if (m_EnemyDeathFlag == false && m_type != CBullet::BULLETTYPE_BOSS)
	{
		HitEnemy(BulletPos);
	}

	//ボスの弾の誘導処理
	if (m_type == CBullet::BULLETTYPE_BOSS)
	{
		BulletBehavior();
	}

	//位置の設定
	SetPosition(BulletPos);
	//向きの設定
	SetRot(m_BulletRot);
	//サイズの設定処理
	SetSize(BulletSize);

	//オブジェクト基礎の更新処理
	CObjectBase::Update();
}

//============================================
// 弾の描画処理
//============================================
void CBullet::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObjectBase::Draw();
}

//============================================
// 弾の生成
//============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nLife, BULLETTYPE type)
{
	CBullet *pBullet = nullptr;

	//弾のインスタンスの生成
	pBullet = new CBullet;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pBullet != nullptr)
	{
		pBullet->SetBulletType(type);
		//初期化処理
		pBullet->Init();
		//設定処理
		pBullet->SetPosition(pos);
		pBullet->SetMove(move);
		pBullet->SetLife(nLife);
		pBullet->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pBullet;
}

//============================================
// 弾の使用者の設定処理
//============================================
void CBullet::SetBulletType(BULLETTYPE type)
{
	m_type = type;
}

//============================================
// 弾と敵の当たり判定
//============================================
void CBullet::HitEnemy(D3DXVECTOR3 pos)
{
	//敵の総数
	m_TotalEnemy = CGame::GetSpawn()->GetEnemyCount();
	CObject *pObject = GetTop(PRIORITY_LEVEL0);

	while (pObject != nullptr)
	{
		//pNextの保存
		CObject *pObjectNext = pObject->GetNext();
		if (pObject->GetObjType() == OBJTYPE_ENEMY)
		{
			CEnemy* pEnemy = (CEnemy*)pObject;

			//敵の位置
			D3DXVECTOR3 EnemyPos = pEnemy->GetEnemyPos();
			//敵のサイズ
			D3DXVECTOR3 EnemySize = pEnemy->GetEnemySize();
			//敵の体力
			int EnemyLife = pEnemy->GetLife();
			//弾と敵の当たり判定
			if (pos.x + 0.5f >= EnemyPos.x - EnemySize.x
				&&pos.x - 0.5f <= EnemyPos.x + EnemySize.x
				&&pos.y + 0.5f >= EnemyPos.y - EnemySize.y
				&&pos.z + 0.5f >= EnemyPos.z - EnemySize.z
				&&pos.z - 0.5f <= EnemyPos.z + EnemySize.z)
			{
				//弾の削除
				m_nLife = 0;
				SetLife(m_nLife);

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_HIT);

				EnemyLife--;

				if (EnemyLife <= 0)
				{
					for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
					{
						CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_BLOOD, D3DXVECTOR3(EnemyPos.x, 15.0f, EnemyPos.z), 0, D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f));
					}
					m_TotalEnemy--;
					CGame::GetSpawn()->SetEnemyCount(m_TotalEnemy);
					CGame::GetScore()->AddScore(200);
					pEnemy->Uninit();
					pEnemy = nullptr;
				}
				else
				{
					pEnemy->SetLife(EnemyLife);
				}
				break;
			}
		}
		//pObjectにpObjectのpNextを代入
		pObject = pObjectNext;
	}
}

//============================================
// 弾とギミックの当たり判定
//============================================
void CBullet::HitGimmick(D3DXVECTOR3 pos)
{
	//カメラの情報を取得
	CCamera *pCamera = CApplication::GetCamera();

	for (int nCnt = 0; nCnt < MAX_GASOLENE; nCnt++)
	{
		if (CGame::GetGasoleneGimmick()[nCnt] != nullptr)
		{
			//ギミックの位置
			D3DXVECTOR3 GasolenePos = CGame::GetGasoleneGimmick()[nCnt]->GetPos();
			//ギミックのサイズ
			D3DXVECTOR3 GasoleneSize = CGame::GetGasoleneGimmick()[nCnt]->GetGasoleneSize();
			//ギミックの体力
			int GasoleneLife = CGame::GetGasoleneGimmick()[nCnt]->GetGasoleneLife();

			//弾とギミックの当たり判定
			if (pos.x + 0.5f >= GasolenePos.x - GasoleneSize.x
				&&pos.x - 0.5f <= GasolenePos.x + GasoleneSize.x
				&&pos.y + 0.5f >= GasolenePos.y - GasoleneSize.y
				&&pos.y - 0.5f <= GasolenePos.y + GasoleneSize.y
				&&pos.z + 0.5f >= GasolenePos.z - GasoleneSize.z
				&&pos.z - 0.5f <= GasolenePos.z + GasoleneSize.z)
			{
				//弾の削除
				m_nLife = 0;
				SetLife(m_nLife);

				//float x = 0.0f;
				//float y = 0.0f;
				//float z = 0.0f;

				//if (m_RandFlag == false)
				//{
				//	x = (float)(rand() % (int)(GasolenePos.x * 200) / 100) - GasolenePos.x;		//xの範囲にランダム
				//	y = (float)(rand() % (int)(GasolenePos.y * 200) / 100) - GasolenePos.y;		//yは0.0fに固定
				//	z = (float)(rand() % (int)(GasolenePos.z * 200) / 100) - GasolenePos.z;		//zの範囲にランダム
				//	m_RandFlag = true;
				//}

				GasoleneLife--;
				if (GasoleneLife <= 0)
				{
					//カメラを揺らす
					pCamera->SetShakeCamera(20, 3);
				/*	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
					{
						CGame::GetParticle()[nCnt] = CParticle::Create(CParticle::PARTICLETYPE_BLOOD, D3DXVECTOR3(x, y, z), 0, D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f));
					}*/
					CExplosion::Create(D3DXVECTOR3(GasolenePos.x, GasolenePos.y + 20.0f, GasolenePos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_EXPLOTION);
					CGame::GetGasoleneGimmick()[nCnt]->HitDamage();
					CGame::GetGasoleneGimmick()[nCnt]->Uninit();
					CGame::GetGasoleneGimmick()[nCnt] = nullptr;
				}
				else
				{
					CGame::GetGasoleneGimmick()[nCnt]->SetGasoleneLife(GasoleneLife);
				}
			}
		}
	}
}

//============================================
// 弾とボスの当たり判定
//============================================
void CBullet::HitBoss(D3DXVECTOR3 pos)
{
	//CBoss *pBoss = CSpawn::GetBoss();

	if (CSpawn::GetBoss() != nullptr)
	{
		//ギミックの位置
		D3DXVECTOR3 BossPos = CSpawn::GetBoss()->GetBossPos();
		//ギミックのサイズ
		D3DXVECTOR3 BossSize = CSpawn::GetBoss()->GetBossSize();
		//ギミックの体力
		int BossLife = CSpawn::GetBoss()->GetLife();

		//弾とギミックの当たり判定
		if (pos.x + 0.5f >= BossPos.x - BossSize.x
			&&pos.x - 0.5f <= BossPos.x + BossSize.x
			&&pos.y + 0.5f >= BossPos.y - BossSize.y
			&&pos.y - 0.5f <= BossPos.y + BossSize.y
			&&pos.z + 0.5f >= BossPos.z - BossSize.z
			&&pos.z - 0.5f <= BossPos.z + BossSize.z)
		{
			//弾の削除
			m_nLife = 0;
			SetLife(m_nLife);

			if (m_type == BULLETTYPE_BOMB)
			{
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
			}

			BossLife -= 10;
			if (BossLife <= 0)
			{
				m_BossDeathFlag = true;
				CGame::GetScore()->AddScore(5000000);
				CFade::SetFade(CApplication::MODE_RESULT);
				CResult::SetType(CResult::TYPE_GAMECLEAR);
				CSpawn::GetBoss()->SetBossDeathFlag(true);
				CSpawn::GetBoss()->Uninit();
				CSpawn::SetBoss(nullptr);
				return;
			}
			else
			{
				CSpawn::GetBoss()->SetLife(BossLife);
			}
		}
	}
}

//============================================
// 弾の挙動
//============================================
void CBullet::BulletBehavior()
{
	//============================================
	//  プレイヤーを追従する処理
	//============================================
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();
	//弾の情報取得
	D3DXVECTOR3 BulletPos = GetPos();
	D3DXVECTOR3 BulletMove = GetMove();

	BulletMove = BulletPos - PlayerPos;				//プレイヤーの位置と敵の位置を計算して移動に代入
	D3DXVec3Normalize(&BulletMove, &BulletMove);	//移動の正規化
	BulletMove *= -5.0f;							//移動スピード

	//移動量減衰
	m_BulletPos.x += (0.0f - BulletMove.x) * 0.1f;
	m_BulletPos.y += (0.0f - BulletMove.y) * 0.1f;
	m_BulletPos.z += (0.0f - BulletMove.z) * 0.1f;

	//移動の設定
	SetMove(BulletMove);
}

//============================================
// 弾(爆弾)とボスの当たり判定
//============================================
void CBullet::BombHitBoss(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	D3DXVECTOR3 BossPos = CSpawn::GetBoss()->GetBossPos();
	D3DXVECTOR3 BossSize = CSpawn::GetBoss()->GetBossSize();
	int BossLife = CSpawn::GetBoss()->GetLife();

	if (pos.x + size.x >= BossPos.x - BossSize.x
		&&pos.x - size.x <= BossPos.x + BossSize.x
		&&pos.y + size.y >= BossPos.y - BossSize.y
		&&pos.y - size.y <= BossPos.y + BossSize.y
		&&pos.z + size.z >= BossPos.z - BossSize.z
		&&pos.z - size.z <= BossPos.z + BossSize.z)

	{
		//弾の削除
		m_nLife = 0;
		SetLife(m_nLife);

		BossLife -= 50;
		if (BossLife <= 0)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_BOMB);
			CGame::GetScore()->AddScore(5000000);
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));
			CFade::SetFade(CApplication::MODE_RESULT);
			CResult::SetType(CResult::TYPE_GAMECLEAR);
			CSpawn::GetBoss()->Uninit();
			CSpawn::SetBoss(nullptr);
			return;
		}
		else
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_BOMB);
			CSpawn::GetBoss()->SetLife(BossLife);
		}
	}
}

//============================================
// ボスの弾の攻撃処理
//============================================
void CBullet::BossBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPlayerPos();
	D3DXVECTOR3 PlayerSize = CGame::GetPlayer()->GetPlayerSize();
	int PlayerLife = CGame::GetPlayer()->GetLife();
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_BOSSATTACK);
	CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z), D3DXVECTOR3(25.0f, 25.0f, 0.0f));

	//追従爆発弾の爆発範囲
	if (PlayerPos.x + PlayerSize.x >= pos.x - size.x && PlayerPos.x - PlayerSize.x <= pos.x + size.x
		&& PlayerPos.z + PlayerSize.z >= pos.z - size.z && PlayerPos.z - PlayerSize.z <= pos.z + size.z)
	{
		PlayerLife -= 2;
		if (PlayerLife <= 0)
		{
			CFade::SetFade(CApplication::MODE_RESULT);
			CResult::SetType(CResult::TYPE_GAMEOVER);
		}
		else
		{
			if (m_RandFlag == false)
			{
				for (int nCnt = 0; nCnt < 20; nCnt++)
				{
					float x = (float)(rand() % 1280 + 1);
					float y = (float)(rand() % 720 + 1);
					float sxy = (float)(rand() % 75 + 15);
					CIndication::Create(D3DXVECTOR3(x, y, 0.0f), D3DXVECTOR3(sxy, sxy, 0.0f), CIndication::INDICATIONTYPE_BLOOD);
				}
				m_RandFlag = true;
			}
			CGame::GetPlayer()->SetPlayerLife(PlayerLife);
		}
	}
	//移動の設定
	SetMove(move);
}
//============================================
//
//	hp.cpp
//	Author: saito shian
//
//============================================

//============================================
//インクルード
//============================================
#include <assert.h>
#include "hp.h"
#include "application.h"
#include "renderer.h"
#include "explosion.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "player.h"
#include "game.h"
#include "spawn.h"
#include "boss.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CHp::m_pTexturehp = {};

//============================================
// hpのコンストラクタ
//============================================
CHp::CHp() : CObject(PRIORITY_LEVEL3)
{
	//============================================
	// メンバ変数のクリア
	//============================================
}

//============================================
// hpのデストラクタ
//============================================
CHp::~CHp()
{
	//何も書かない
}

//============================================
// hpの初期化処理
//============================================
HRESULT CHp::Init(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//============================================
	//メンバ変数の初期化
	//============================================
	m_nPlayreLife = 0;
	m_nBossLife = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(1280.0f, 720.0f - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nPlayreLife, 720.0f - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f - LIFE_WIDTH * m_nPlayreLife, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// hpの終了処理
//============================================
void CHp::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//破棄処理
	CObject::Release();
}

//============================================
// hpの更新処理
//============================================
void CHp::Update()
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//============================================
	//　プレイヤーのHP
	//============================================
	if (m_type == HPTYPE::HPTYPE_PLAYER)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		if (pPlayer != nullptr)
		{
			//プレイヤーの体力の取得
			m_nPlayreLife = pPlayer->GetLife();

			//頂点バッファをロックし、頂点情報へのポインタを取得
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(375.0f - LIFE_WIDTH * m_nPlayreLife, 650.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(375.0f, 650.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(375.0f - LIFE_WIDTH * m_nPlayreLife, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(375.0f, 700.0f, 0.0f);

			//頂点バッファをアンロックする
			m_pVtxBuff->Unlock();

			if (m_nPlayreLife <= 5)
			{
				SetColor(1.0f, 1.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife <= 3)
			{
				SetColor(1.0f, 0.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife <= 10 && m_nPlayreLife > 5)
			{
				SetColor(0.0f, 1.0f, 0.0f, 1.0f);
			}
			if (m_nPlayreLife > 10)
			{
				SetColor(0.0f, 0.5f, 1.0f, 1.0f);
				//頂点バッファをロックし、頂点情報へのポインタを取得
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(275.0f - LIFE_WIDTH * 10, 75.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(275.0f, 75.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(275.0f - LIFE_WIDTH * 10, 100.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(275.0f, 100.0f, 0.0f);

				//頂点バッファをアンロックする
				m_pVtxBuff->Unlock();
			}
		}
	}

	//============================================
	//　ボスのHP
	//============================================
	if (m_type == HPTYPE::HPTYPE_BOSS)
	{
		CBoss *pBoss = CSpawn::GetBoss();

		if (pBoss != nullptr)
		{
			//プレイヤーの体力の取得
			m_nBossLife = pBoss->GetLife();

			//頂点バッファをロックし、頂点情報へのポインタを取得
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(550.0f - BOSS_LIFE_WIDTH * m_nBossLife, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(550.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550.0f - BOSS_LIFE_WIDTH * m_nBossLife, 60.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(550.0f, 60.0f, 0.0f);

			//頂点バッファをアンロックする
			m_pVtxBuff->Unlock();

			SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
}

//============================================
// hpの描画処理
//============================================
void CHp::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,									//頂点情報の先頭アドレス
		2);									//プリミティブの数
}

//============================================
// スポーンの生成
//============================================
CHp *CHp::Create(HPTYPE type)
{
	CHp *php = nullptr;

	//クラスの生成
	php = new CHp;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (php != nullptr)
	{
		php->SetHPType(type);
		//初期化処理
		php->Init();
	}
	else
	{
		assert(false);
	}

	return php;
}

//============================================
// 色の設定
//============================================
void CHp::SetColor(float Red, float Green, float Blue, float α)
{
	VERTEX_2D*pVtx;				//頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[1].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[2].col = D3DXCOLOR(Red, Green, Blue, α);
	pVtx[3].col = D3DXCOLOR(Red, Green, Blue, α);

	//頂点バッファをアンロックする
	Buffer->Unlock();
}
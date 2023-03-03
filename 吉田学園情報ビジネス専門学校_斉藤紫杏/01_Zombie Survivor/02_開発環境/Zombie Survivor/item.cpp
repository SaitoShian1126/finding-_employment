//============================================
//
//	item.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "item.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "debug.h"
#include "game.h"
#include "player.h"
#include "ui.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CItem::m_pTextureitem = nullptr;

//============================================
// アイテムのコンストラクタ
//============================================
CItem::CItem()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// アイテムのデストラクタ
//============================================
CItem::~CItem()
{
}

//============================================
// アイテムの初期化処理
//============================================
HRESULT CItem::Init(void)
{
	//============================================
	// メンバ変数の初期化
	//============================================
	m_HitFlag = false;
	
	//オブジェクト基礎の初期化処理
	CObjectBase::Init();

	BindTexture(m_pTextureitem);

	return S_OK;
}

//============================================
// アイテムの終了処理
//============================================
void CItem::Uninit(void)
{
	//オブジェクト基礎の終了処理
	CObjectBase::Uninit();
}

//============================================
// アイテムの更新処理
//============================================
void CItem::Update(void)
{
	HitItem();
}

//============================================
// アイテムの描画処理
//============================================
void CItem::Draw(void)
{
	//オブジェクト基礎の描画処理
	CObjectBase::Draw();
}

//============================================
// アイテムとプレイヤーが当たった時
//============================================
void CItem::HitItem(void)
{
	if (CGame::GetPlayer() != nullptr)
	{
		D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPlayerPos();
		D3DXVECTOR3 PlayerSize = CGame::GetPlayer()->GetPlayerSize();

		D3DXVECTOR3 ItemPos = CGame::GetItem()->GetPos();
		D3DXVECTOR3 ItemSize = CGame::GetItem()->GetSize();

		int BombUseCount = CGame::GetPlayer()->GetBombUseCount();
		bool BombUseCountFlag = CGame::GetPlayer()->GetBombUseFlag();

		if (ItemPos.x + ItemSize.x >= PlayerPos.x - PlayerSize.x && ItemPos.x - ItemSize.x <= PlayerPos.x + PlayerSize.x
			&& PlayerPos.z - PlayerSize.z <= ItemPos.z + ItemSize.x && PlayerPos.z + PlayerSize.z >= ItemPos.z - ItemSize.x && m_HitFlag == false)
		{	//プレイヤーとアイテムが当たったら
			BombUseCount += 3;
			BombUseCountFlag = false;
			CGame::GetPlayer()->SetBombUseCount(BombUseCount);
			CGame::GetPlayer()->GetBombUseFlag(BombUseCountFlag);
			CGame::GetUi()[0]->AddBomb(3);
			m_HitFlag = true;
			Uninit();
			return;
		}
	}
}

//============================================
// アイテムのテクスチャ読み込み
//============================================
HRESULT CItem::Load(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/爆弾.png",
		&m_pTextureitem);

	return S_OK;
}

//============================================
// アイテムのテクスチャ破棄
//============================================
void CItem::Unload(void)
{
	//テクスチャの破棄
	if (m_pTextureitem != nullptr)
	{
		m_pTextureitem->Release();
		m_pTextureitem = nullptr;
	}
}

//============================================
// アイテムの生成
//============================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CItem *pitem = nullptr;

	//アイテムの生成
	pitem = new CItem;				//アイテムのインスタンス生成

	//nullチェック
	if (pitem != nullptr)
	{
		//初期化処理
		pitem->Init();
		pitem->SetPosition(pos);
		pitem->SetSize(size);
	}
	else
	{
		assert(false);
	}
	return pitem;
}
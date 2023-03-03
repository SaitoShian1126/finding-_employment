//============================================
//
//	item.cpp
//	Author: saito shian
//
//============================================

//============================================
// �C���N���[�h
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
// �ÓI�����o�ϐ��錾
//============================================
LPDIRECT3DTEXTURE9 CItem::m_pTextureitem = nullptr;

//============================================
// �A�C�e���̃R���X�g���N�^
//============================================
CItem::CItem()
{
	//============================================
	//�����o�ϐ��̃N���A
	//============================================
}

//============================================
// �A�C�e���̃f�X�g���N�^
//============================================
CItem::~CItem()
{
}

//============================================
// �A�C�e���̏���������
//============================================
HRESULT CItem::Init(void)
{
	//============================================
	// �����o�ϐ��̏�����
	//============================================
	m_HitFlag = false;
	
	//�I�u�W�F�N�g��b�̏���������
	CObjectBase::Init();

	BindTexture(m_pTextureitem);

	return S_OK;
}

//============================================
// �A�C�e���̏I������
//============================================
void CItem::Uninit(void)
{
	//�I�u�W�F�N�g��b�̏I������
	CObjectBase::Uninit();
}

//============================================
// �A�C�e���̍X�V����
//============================================
void CItem::Update(void)
{
	HitItem();
}

//============================================
// �A�C�e���̕`�揈��
//============================================
void CItem::Draw(void)
{
	//�I�u�W�F�N�g��b�̕`�揈��
	CObjectBase::Draw();
}

//============================================
// �A�C�e���ƃv���C���[������������
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
		{	//�v���C���[�ƃA�C�e��������������
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
// �A�C�e���̃e�N�X�`���ǂݍ���
//============================================
HRESULT CItem::Load(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/���e.png",
		&m_pTextureitem);

	return S_OK;
}

//============================================
// �A�C�e���̃e�N�X�`���j��
//============================================
void CItem::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTextureitem != nullptr)
	{
		m_pTextureitem->Release();
		m_pTextureitem = nullptr;
	}
}

//============================================
// �A�C�e���̐���
//============================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CItem *pitem = nullptr;

	//�A�C�e���̐���
	pitem = new CItem;				//�A�C�e���̃C���X�^���X����

	//null�`�F�b�N
	if (pitem != nullptr)
	{
		//����������
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
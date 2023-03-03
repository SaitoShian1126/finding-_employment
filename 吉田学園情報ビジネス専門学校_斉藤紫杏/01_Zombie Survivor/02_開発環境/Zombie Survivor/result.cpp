//============================================
//
//	result.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "result.h"
#include "application.h"
#include "renderer.h" 
#include "input.h"
#include "fade.h"
#include "sound.h"

//============================================
// 静的メンバ変数宣言
//============================================
LPDIRECT3DTEXTURE9 CResult::m_pTextureResult[2] = {};
CResult::TYPE CResult::m_TypeNumber = TYPE_NONE;

//============================================
// リザルトのコンストラクタ
//============================================
CResult::CResult()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// リザルトのデストラクタ
//============================================
CResult::~CResult()
{
	//何も書かない
}

//============================================
// リザルトの初期化処理
//============================================
HRESULT CResult::Init(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameOverResult.png",
		&m_pTextureResult[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameClearResult.png",
		&m_pTextureResult[1]);

	//============================================
	//メンバ変数の初期化
	//============================================
	m_BGMFlag = false;

	m_pObject = CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	switch (m_TypeNumber)
	{
	case CResult::TYPE_GAMEOVER:
		m_pObject->BindTexture(m_pTextureResult[0]);
		break;
	case CResult::TYPE_GAMECLEAR:
		m_pObject->BindTexture(m_pTextureResult[1]);
		break;
	default:
		break;
	}

	return S_OK;
}

//============================================
// リザルトの終了処理
//============================================
void CResult::Uninit(void)
{
	//サウンドの停止
	StopSound();

	CObject::Release();
}

//============================================
// リザルトの更新処理
//============================================
void CResult::Update()
{
	//インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();
	CJoyPad *pJoyPad = CApplication::GetJpyPad();

	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true ||  pJoyPad->GetJoypadTrigger(pJoyPad->JOYKEY_B) && m_pFade->GetFade() == CFade::FADETYPE_NONE && CApplication::GetModeType() == CApplication::MODE_RESULT)
	{
		PlaySound(SOUND_LABEL_SE_BUTTOM);
		CFade::SetFade(CApplication::MODE_RANKING);
	}

	//============================================
	// サウンドの再生
	//============================================
	if (m_BGMFlag == false && m_TypeNumber == CResult::TYPE_GAMECLEAR)
	{
		PlaySound(SOUND_LABEL_GAMECLEAR);
		m_BGMFlag = true;
	}

	//============================================
	// サウンドの再生
	//============================================
	if (m_BGMFlag == false && m_TypeNumber == CResult::TYPE_GAMEOVER)
	{
		PlaySound(SOUND_LABEL_GAMEOVER);
		m_BGMFlag = true;
	}
}

//============================================
// リザルトの描画処理
//============================================
void CResult::Draw()
{

}

//============================================
// リザルトの設定処理
//============================================
void CResult::SetType(TYPE type)
{
	m_TypeNumber = type;
}
//============================================
// リザルトの生成
//============================================
CResult *CResult::Create()
{
	CResult *pResult = nullptr;

	//クラスの生成
	pResult = new CResult;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pResult != nullptr)
	{
		//初期化処理
		pResult->Init();
	}
	else
	{
		assert(false);
	}

	return pResult;
}

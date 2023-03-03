//============================================
//
//	fade.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "fade.h"
#include "application.h"
#include "renderer.h" 
#include "object3d.h"

//============================================
// 静的メンバ変数宣言
//============================================
CFade::FADETYPE CFade::m_Fade = {};
D3DXCOLOR CFade::m_FadeColor = {};
CApplication::MODE CFade::m_ModeNext = {};

//============================================
// フェードのコンストラクタ
//============================================
CFade::CFade() : CObject2D(PRIORITY_FADE)
{
	//============================================
	//メンバ変数のクリア
	//============================================
	SetType(OBJTYPE_MODE);
}

//============================================
// フェードのデストラクタ
//============================================
CFade::~CFade()
{
	//何も書かない
}

//============================================
// フェードの初期化処理
//============================================
HRESULT CFade::Init(CApplication::MODE modenext)
{
	CObject2D::Init();

	//============================================
	//メンバ変数の初期化
	//============================================
	m_Fade = FADETYPE_IN;								//フェードin状態に
	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒いポリゴンにしておく
	m_ModeNext = modenext;								//次の画面を設定

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f)); 
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));

	//モードの設定
	CApplication::SetMode(m_ModeNext);

	return S_OK;
}

//============================================
// フェードの終了処理
//============================================
void CFade::Uninit(void)
{
	CObject2D::Release();
}

//============================================
// フェードの更新処理
//============================================
void CFade::Update()
{
	CObject2D::Update();

	if (m_Fade != FADETYPE_NONE)
	{
		if (m_Fade == FADETYPE_IN)
		{//フェードイン状態に
			m_FadeColor.a -= 1.0f / FADE_TIME;			//ポリゴンを透明にしていく
			if (m_FadeColor.a <= 0.0f)
			{
				m_FadeColor.a = 0.0f;
				m_Fade = FADETYPE_NONE;					//何もしていない状態に
			}
		}
		else if (m_Fade == FADETYE_OUT)
		{
			m_FadeColor.a += 1.0f / FADE_TIME;
			if (m_FadeColor.a >= 1.0f)
			{
				m_FadeColor.a = 1.0f;
				m_Fade = FADETYPE_IN;

				//モードの設定
				CApplication::SetMode(m_ModeNext);
			}
		}
		SetColor(m_FadeColor.r, m_FadeColor.g, m_FadeColor.b, m_FadeColor.a);
	}
}

//============================================
// フェードの設定処理
//============================================
void CFade::SetFade(CApplication::MODE modenext)
{
	m_Fade = FADETYE_OUT;
	m_ModeNext = modenext;

	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//============================================
// フェードの生成
//============================================
CFade *CFade::Create(CApplication::MODE modenext)
{
	CFade *pFade = nullptr;

	//クラスの生成
	pFade = new CFade;				//2Dオブジェクトのインスタンス生成

	//nullチェック
	if (pFade != nullptr)
	{
		//初期化処理
		pFade->Init(modenext);
	}
	else
	{
		assert(false);
	}

	return pFade;
}
//============================================
//
//	light.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include "application.h"
#include "renderer.h"
#include "light.h"

//============================================
// ライトのコンストラクタ
//============================================
CLight::CLight()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// ライトのデストラクタ
//============================================
CLight::~CLight()
{
	//何も書かない
}
//============================================
// ライトの初期化処理
//============================================
HRESULT CLight::Init(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;												//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&m_nLight, sizeof(m_nLight));						//構造体変数をゼロクリアできる便利関数(memset)と同じ

	//============================================
	//	ライト1個目
	//============================================

	//ライトの種類を設定
	m_nLight[0].Type = D3DLIGHT_DIRECTIONAL;					//平行光源

	//ライトの拡散光を設定(色)
	m_nLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//ライトの色

	//ライトの方向を設定(x,y,z)
	vecDir = D3DXVECTOR3(1.0f, -1.0f, -0.5f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[0].Direction = vecDir;

	//ライトを設定する↓0は0番目のライトを設定(何個も置くときはここの数字を増やせばいい)
	pDevice->SetLight(0, &m_nLight[0]);

	//ライトを有効化する
	pDevice->LightEnable(0, TRUE);

	//============================================
	//	ライト2個目
	//============================================

	m_nLight[1].Type = D3DLIGHT_DIRECTIONAL;					//平行光源

	m_nLight[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//ライトの色

	//ライトの方向を設定(x,y,z)
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[1].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(1, &m_nLight[1]);

	//ライトを有効化する
	pDevice->LightEnable(1, TRUE);

	//============================================
	//	ライト3個目
	//============================================

	m_nLight[2].Type = D3DLIGHT_DIRECTIONAL;					//平行光源

	m_nLight[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//ライトの色

	//ライトの方向を設定(x,y,z)
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, -0.0f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[2].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(2, &m_nLight[2]);

	//ライトを有効化する
	pDevice->LightEnable(2, TRUE);

	//============================================
	//	ライト4個目
	//============================================

	m_nLight[3].Type = D3DLIGHT_DIRECTIONAL;					//平行光源

	m_nLight[3].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.5f);	//ライトの色

	//ライトの方向を設定(x,y,z)
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_nLight[3].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(3, &m_nLight[3]);

	//ライトを有効化する
	pDevice->LightEnable(3, TRUE);

	return S_OK;
}

//============================================
// ライトの終了処理
//============================================
void CLight::Uninit(void)
{

}

//============================================
// ライトの更新処理
//============================================
void CLight::Update(void)
{

}


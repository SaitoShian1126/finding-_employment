//============================================
//
//	Sphere.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <assert.h>
#include "sphere.h"
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debug.h"
#include "meshfield.h"
#include "game.h"

//============================================
// オブジェクトのコンストラクタ
//============================================
CSphere::CSphere()
{
	//============================================
	//メンバ変数のクリア
	//============================================
	m_RotDest = {};
	m_Move = {};
}

//============================================
// オブジェクトのデストラクタ
//============================================
CSphere::~CSphere()
{
	//何も書かない
}

//============================================
// オブジェクト(ポリゴン)の初期化処理
//============================================
HRESULT CSphere::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================
	m_RotDest = {};
	m_Move = {};

	CObjectX::Init();

	return S_OK;
}

//============================================
// オブジェクト(ポリゴン)の終了処理
//============================================
void CSphere::Uninit(void)
{
	CObjectX::Uninit();
}

//============================================
// オブジェクト(ポリゴン)の更新処理
//============================================
void CSphere::Update(void)
{
	//インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();
//	CMeshField *pMeshField = CGame::GetMeshField();
	D3DXVECTOR3 CameraRot = CCamera::GetCameraRot();
	D3DXVECTOR3 SpherePos = GetPos();
	D3DXVECTOR3 SphereRot = GetRot();

	CObjectX::Update();

	//上方向
	if (pInput->GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			SpherePos.x -= sinf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//移動量
			SpherePos.z -= cosf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//移動量
			m_RotDest.y = (CameraRot.y + D3DX_PI * 0.75f);						//向く角度
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			SpherePos.x += sinf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//移動量
			SpherePos.z += cosf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//移動量
			m_RotDest.y = (CameraRot.y - D3DX_PI * 0.75f);						//向く角度
		}
		else
		{
			SpherePos.x += sinf(CameraRot.y) * SPHERE_MOVE;						//移動量
			SpherePos.z += cosf(CameraRot.y) * SPHERE_MOVE;						//移動量
			//m_RotDest.y = (CameraRot.y + D3DX_PI);							//向く角度

			SphereRot.x += (cosf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
			SphereRot.z += (sinf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
		}
	}
	//下方向
	else if (pInput->GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			SpherePos.x -= sinf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//移動量
			SpherePos.z -= cosf(CameraRot.y + D3DX_PI * 0.25f) * SPHERE_MOVE;	//移動量
			m_RotDest.y = (CameraRot.y + D3DX_PI * 0.25f);						//向く角度
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			SpherePos.x += sinf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//移動量
			SpherePos.z += cosf(CameraRot.y + D3DX_PI * 0.75f) * SPHERE_MOVE;	//移動量
			m_RotDest.y = (CameraRot.y - D3DX_PI * 0.25f);						//向く角度
		}
		else
		{
			SpherePos.x -= sinf(CameraRot.y) * SPHERE_MOVE;						//移動量
			SpherePos.z -= cosf(CameraRot.y) * SPHERE_MOVE;						//移動量
			//m_RotDest.y = CameraRot.y;										//向く角度

			SphereRot.x -= (cosf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
			SphereRot.z -= (sinf(CameraRot.y) * SPHERE_MOVE) / 10.0f;
		}
	}
	//左方向
	else if (pInput->GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		SpherePos.x -= sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//移動量
		SpherePos.z -= cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//移動量
		//m_RotDest.y = (CameraRot.y + D3DX_PI / 2);							//向く角度

		SphereRot.x -= (cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
		SphereRot.z -= (sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
	}
	//右方向
	else if (pInput->GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		SpherePos.x += sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//移動量
		SpherePos.z += cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE;			//移動量
		//m_RotDest.y = (CameraRot.y - D3DX_PI / 2);							//向く角度

		SphereRot.x += (cosf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
		SphereRot.z += (sinf(CameraRot.y + D3DX_PI / 2) * SPHERE_MOVE) / 10.0f;
	}

	//============================================
	// 目的の角度の正規化
	//============================================
	if (m_RotDest.y - SphereRot.y > D3DX_PI)
	{
		m_RotDest.y = m_RotDest.y - D3DX_PI * 2;
	}
	else if (m_RotDest.y - SphereRot.y < -D3DX_PI)
	{
		m_RotDest.y = m_RotDest.y + D3DX_PI * 2;
	}

	//角度慣性
	//SphereRot.y += (m_RotDest.y - SphereRot.y) * 0.1f;

	//============================================
	// 角度の正規化
	//============================================
	if (SphereRot.y > D3DX_PI)
	{
		SphereRot.y = SphereRot.y - D3DX_PI * 2;
	}
	else if (SphereRot.y < -D3DX_PI)
	{
		SphereRot.y = SphereRot.y + D3DX_PI * 2;
	}

//	pMeshField->GetMeshFieldCollision(&SpherePos);
	SetPosition(SpherePos);
	SetRot(SphereRot);
}

//============================================
// オブジェクト(ポリゴン)の描画処理
//============================================
void CSphere::Draw(void)
{
	CObjectX::Draw();
}

//============================================
// 生成
//============================================
CSphere * CSphere::Create(const D3DXVECTOR3 &pos)
{
	CSphere *pSphere = nullptr;

	//3Dオブジェクトクラスの生成
	pSphere = new CSphere;				//3Dオブジェクトのインスタンス生成

										//nullチェック
	if (pSphere != nullptr)
	{
		//初期化処理
		pSphere->Init();
		pSphere->SetPosition(pos);
	}
	else
	{
		assert(false);
	}
	return pSphere;
}

//============================================
//
//	camera.cpp
//	Author: saito shian
//
//============================================

//============================================
// インクルード
//============================================
#include <time.h>
#include <math.h>
#include <assert.h>
#include "camera.h"
#include "application.h"
#include "renderer.h" 
#include "object3d.h"
#include "fade.h"
#include "input.h"
#include "application.h"
#include "player.h"
#include "debug.h"

//============================================
// 静的メンバ変数宣言
//============================================
D3DXVECTOR3 CCamera::m_Rot = {};

//============================================
// カメラのコンストラクタ
//============================================
CCamera::CCamera()
{
	//============================================
	//メンバ変数のクリア
	//============================================
}

//============================================
// カメラのデストラクタ
//============================================
CCamera::~CCamera()
{
	//何も書かない
}

//============================================
// カメラの初期化処理
//============================================
HRESULT CCamera::Init(void)
{
	//============================================
	//メンバ変数の初期化
	//============================================

	//乱数
	srand((unsigned int)time(nullptr));			//起動時に一回だけ行うため初期化に書く
	m_nQuakeFrameCount = 0;
	m_fQuakeMagnitude = 0;

	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_OffsetV = D3DXVECTOR3(0.0f,75.0f,150.0f);
	m_OffsetR = D3DXVECTOR3(0.0f, 0.0f, -150.0f);

	m_PosVDest = D3DXVECTOR3(0.0f, 100.0f, -150.0f);
	m_PosRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//<-固定で良い

	//三平方の定理(sqrtfはルートの役割)
	m_fDistance = sqrtf(((m_PosRDest.x - m_PosVDest.x) * (m_PosRDest.x - m_PosVDest.x)) + ((m_PosRDest.z - m_PosVDest.z) * (m_PosRDest.z - m_PosVDest.z)));

	return S_OK;
}

//============================================
// カメラの終了処理
//============================================
void CCamera::Uninit(void)
{

}

//============================================
// カメラの更新処理
//============================================
void CCamera::Update()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//インプットのインスタンス生成
	CInput *pInput = CApplication::GetInput();
	D3DXVECTOR3 PlayerRot = CPlayer::GetPlayerRot();	//プレイヤーの向きの取得
	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayerPos();	//プレイヤーの位置の取得

	//============================================
	// カメラの追従処理
	//============================================
	//目的の注視点の設定
	m_PosDest = PlayerPos;

	//視点の減衰処理
	m_pos.x += (m_PosDest.x - m_pos.x) * 1.0f;
	m_pos.y += (m_PosDest.y - m_pos.y) * 1.0f;
	m_pos.z += (m_PosDest.z - m_pos.z) * 1.0f;

	//============================================
	// カメラの回転処理
	//============================================
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);													//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, PlayerRot.y, PlayerRot.x, PlayerRot.z);		//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);								//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);						//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ベクトル変換
	D3DXVec3TransformCoord(&m_PosVDest, &m_OffsetV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_PosRDest, &m_OffsetR, &m_mtxWorld);

	//============================================
	// エイムした時の視点減衰
	//============================================
	//視点の減衰
	m_PosV.x += (m_PosVDest.x - m_PosV.x) * 0.1f;
	m_PosV.y += (m_PosVDest.y - m_PosV.y) * 0.1f;
	m_PosV.z += (m_PosVDest.z - m_PosV.z) * 0.1f;
					
	//注視点の減衰
	m_PosR.x += (m_PosRDest.x - m_PosR.x) * 0.1f;
	m_PosR.y += (m_PosRDest.y - m_PosR.y) * 0.1f;
	m_PosR.z += (m_PosRDest.z - m_PosR.z) * 0.1f;

	//============================================
	// カメラの向いてる方向に移動できる処理
	//============================================
	m_Rot.y = atan2(m_PosR.x - m_PosV.x,m_PosR.z - m_PosV.z);

	//============================================
	// デバック表示
	//============================================
	/*CDebugProc::Print("カメラの視点 : %.3f,%.3f,%.3f\n", m_PosVDest.x, m_PosVDest.y, m_PosVDest.z);
	CDebugProc::Print("カメラの注視点 : %.3f,%.3f,%.3f\n", m_PosRDest.x, m_PosRDest.y, m_PosRDest.z);*/
}

//============================================
// カメラの設定
//============================================
void CCamera::SetCamera()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 adjustPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nQuakeFrameCount > 0)
	{
		m_nQuakeFrameCount--;
		////乱数で揺れの大きさを変える
		adjustPos.x = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.y = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.z = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
	}
	//ビューマトリックの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックの生成
	D3DXVECTOR3 PosV = (adjustPos + m_PosV);
	D3DXVECTOR3 PosR = (adjustPos + m_PosR);

	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,
		&PosR,
		&m_VecU);

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,

		D3DXToRadian(45.0f),									//視野角
		(float)m_Viewport.Width / (float)m_Viewport.Height,		//アスペクト比
		10.0f,													//ニア
		5000.0f);												//ファー

	//プロジェクションマトリックの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//============================================
// 距離の設定
//============================================
void CCamera::SetOffset(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_OffsetV = posV;
	m_OffsetR = posR;
}

//============================================
// 揺れの設定
//============================================
void CCamera::SetShakeCamera(int QuakeFrame, int QuakeMagnitude)
{
	m_nQuakeFrameCount = QuakeFrame;
	m_fQuakeMagnitude = QuakeMagnitude;
}

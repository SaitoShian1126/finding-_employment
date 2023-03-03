//============================================
//
//	camera.h
//	Author: saito shian
//
//============================================

//============================================
// 2重インクルードガード
//============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//============================================
// インクルード
//============================================
#include "main.h"

//============================================
// マクロ定義
//============================================
#define CAMERA_SPEED	(0.5f)	//カメラの速度

//============================================
// カメラクラス
//============================================
class CCamera
{
public:
	CCamera();				//コンストラクタ
	~CCamera();				//デストラクタ

	HRESULT Init(void);		//カメラの初期化処理
	void Uninit(void);		//カメラの終了処理
	void Update(void);		//カメラの更新処理

	void SetCamera();												//カメラの設定処理
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }					//カメラの回転の設定処理
	void SetDistance(float distance) { m_fDistance = distance; }	//カメラの距離処理
	void SetOffset(D3DXVECTOR3 posV, D3DXVECTOR3 posR);				//カメラの距離の設定処理
	void SetShakeCamera(int QuakeFrame, int QuakeMagnitude);		//カメラの揺れの設定処理

	D3DXVECTOR3 GetPosV() { return m_PosVDest; }
	D3DXVECTOR3 GetPosR() { return m_PosRDest; }
	D3DXVECTOR3 GetVecU() { return m_VecU; }
	float GetDistance() { return m_fDistance; }

	static D3DXVECTOR3 GetCameraRot() { return m_Rot; }		//カメラの回転の取得処理	

private:
	static D3DXVECTOR3 m_Rot;		//向き
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_PosVDest;			//視点
	D3DXVECTOR3 m_PosDest;			//目的の視点
	D3DXVECTOR3 m_PosRDest;			//注視点
	D3DXVECTOR3 m_VecU;				//上方向ベクトル
	D3DXVECTOR3 m_OffsetV;			//視点の距離
	D3DXVECTOR3 m_OffsetR;			//注視点の距離
	D3DXVECTOR3 m_PosV;				//目的の視点
	D3DXVECTOR3 m_PosR;				//目的の注視点
	D3DVIEWPORT9 m_Viewport;		//ビューポート
	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス

	int m_nQuakeFrameCount;			//揺らすフレーム数
	int m_fQuakeMagnitude;			//揺れの量

	float m_fDistance;				//視点から注視点の距離		
};

#endif
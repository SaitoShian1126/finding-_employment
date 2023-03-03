//============================================
//
//	rock_gimmick.h
//	Author: saito shian
//
//============================================
#ifndef _ROCK_GIMMICK_H_
#define _ROCK_GIMMICK_H_

//============================================
// インクルードファイル
//============================================
#include "gimmick.h"

//============================================
// マクロ定義
//============================================
#define MAX_PUSH	(5)				//押す最大数

//============================================
// 前方定義
//============================================
class CShadow;

//============================================
// クラスの定義
//============================================
class CRock_gimmick : public CGimmick
{
public:

	enum MODELTYPE
	{
		MODELTYPE_ROCK = 0,				//岩
		MODELTYPE_SUPPORTBAR			//支え棒
	};

	CRock_gimmick();					//コンストラクタ
	~CRock_gimmick() override;			//デストラクタ

	HRESULT Init() override;			//初期化処理
	void Uninit() override;				//終了処理
	void Update() override;				//更新処理
	void Draw() override;				//描画処理

	void HitDamage();					//岩が落ちた時の当たり判定
	void Operation();					//ギミック操作処理

	D3DXVECTOR3 GetGasolenePos(void) { return m_pos; }		//岩の位置の取得
	D3DXVECTOR3 GetGasoleneSize(void) { return m_size; }	//岩のサイズの取得

	void SetModelType(MODELTYPE type);						//モデルの種類の設定

	static CRock_gimmick *Create(D3DXVECTOR3 pos, MODELTYPE type);		//生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	D3DXVECTOR3 m_pos;					//岩の位置
	D3DXVECTOR3 m_move;					//岩の移動
	D3DXVECTOR3 m_size;					//岩のサイズ
	MODELTYPE m_type;					//モデルの種類

	int m_PushCount;					//押したカウント

	bool m_PushCountFlag;				//条件を完了したのかのフラグ
	bool m_UninitFlag;					//ギミックが消えたのかフラグ
};
#endif

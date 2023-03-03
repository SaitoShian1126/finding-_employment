//============================================
//
//	gasolene_gimmick.h
//	Author: saito shian
//
//============================================
#ifndef _GASOLENE_GIMMICK_H_
#define _GASOLENE_GIMMICK_H_

//============================================
// インクルードファイル
//============================================
#include "gimmick.h"

//============================================
// 前方定義
//============================================

//============================================
// クラスの定義
//============================================
class CGasolene_Gimmick : public CGimmick
{
public:
	CGasolene_Gimmick();				//コンストラクタ
	~CGasolene_Gimmick() override;		//デストラクタ

	HRESULT Init() override;			//初期化処理
	void Uninit() override;				//終了処理
	void Update() override;				//更新処理
	void Draw() override;				//描画処理

	void HitDamage();					//ガソリンが爆発した時の当たり判定

	int GetGasoleneLife(void) { return m_nLife; }			//ガソリンの体力の取得

	D3DXVECTOR3 GetGasolenePos(void) { return m_pos; }		//ガソリンの位置の取得
	D3DXVECTOR3 GetGasoleneSize(void) { return m_size; }	//ガソリンのサイズの取得

	void SetGasoleneLife(int life) { m_nLife = life; }		//ガソリンの体力の設定

	static CGasolene_Gimmick *Create(D3DXVECTOR3 pos);		//生成

private:
	D3DXVECTOR3 m_pos;					//ガソリンの位置
	D3DXVECTOR3 m_size;					//ガソリンのサイズ
	int m_nLife;						//ガソリンの体力
};
#endif

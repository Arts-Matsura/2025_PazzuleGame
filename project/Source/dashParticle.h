#pragma once
#include "../Library/gameObject.h"
#include "Transform.h"

//走っている感で作成した、2D用パーティクルマネージャーを雑に改造したもの。

namespace DashParticle
{
	// パーティクルの構造体
	struct Line
	{
		Transform transform;
		Transform parent;
		Vector3 position;	//float startX, startY;	// 開始座標
		Vector3 velocity;		//float speedX, speedY;	// スピード
		Vector3 rotScale;
		float rot;				// 回転角度
		float rotSpeed;			// 回転スピード
		float length;//float height, width;	// 長さ
		float activeTime;		// 残り寿命
		int color;				// 色
		int state;				// 状態

		Line() : /*posX(0), posY(0), startX(0), startY(0), speedX(0), speedY(0),*/ rot(0), rotSpeed(0), length(200.0f), /*height(1.5f), width(30.0f),*/ activeTime(-1), color(0x5a00ffff), state(0) {}
	};

	void Init();
	void Release();
	void Update();
	void Draw();

	int GetID();
	int StartLine(const Transform& parent, float _activeTime);
	Line* GetLine(int id);

	void UpdateDir(int i);
	void UpdateMove(int i);
}

class DashParticleManager : public GameObject
{
public:
	DashParticleManager()	{ DashParticle::Init(); }
	~DashParticleManager()	{ DashParticle::Release(); }

	void Update() override	{ DashParticle::Update(); }
	void Draw() override	{ DashParticle::Draw(); }
};
#pragma once
#include "..//Library/gameObject.h"
#include "Transform.h"

namespace Sparkle
{
	// パーティクルの構造体
	struct Particle
	{
		Transform transform;
		Vector3 velocity;      // スピード
		float size;            // サイズ
		float activeTime;      // 残り寿命
		int color;             // 色
		Vector3 meteorVelocity;  // 流星の速度
		float maxActiveTime;   // 最大寿命
		Particle() : size(5.0f), activeTime(-1), color(0xffffffff), meteorVelocity(VGet(0,0,0)), maxActiveTime(-1) {}
	};
	void Init();
	void Release();
	void Update();
	void Draw();
	int GetID();
	int StartParticle(const Transform& parent, float _activeTime);
	void Emit(const Transform& parent, float _activeTime, int count);
	Particle* GetParticle(int id);
	void UpdateMove(int i);
}

class SparkleManager : public GameObject
{
public:
	SparkleManager() { Sparkle::Init(); }
	~SparkleManager() { Sparkle::Release(); }
	void Update() override{ Sparkle::Update(); }
	void Draw() override { Sparkle::Draw(); }
};
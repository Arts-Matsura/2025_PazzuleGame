#include "sparkle.h"
#include <DxLib.h>

namespace
{
	const int PARTICLE_MAX = 4000;	// パーティクルの最大数
	Sparkle::Particle sparkle[PARTICLE_MAX];	// パーティクルの配列
}

void Sparkle::Init()
{
	for (int i = 0; i < PARTICLE_MAX; i++) {
		sparkle[i] = Particle();
	}
}

void Sparkle::Release()
{
	for (int i = 0; i < PARTICLE_MAX; i++) {
		sparkle[i] = Particle();
	}
}

void Sparkle::Update()
{
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (sparkle[i].activeTime <= 0) continue;
		sparkle[i].activeTime -= (1.0f / 60.0f);
		Sparkle::UpdateMove(i);
	}
}

void Sparkle::Draw()
{
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (sparkle[i].activeTime <= 0) continue;
		int param = (sparkle[i].color >> 24) & 0xFF;

		int red = (sparkle[i].color >> 16) & 0xFF;
		int green = (sparkle[i].color >> 8) & 0xFF;
		int blue = sparkle[i].color & 0xFF;

		SetDrawBlendMode(DX_BLENDMODE_ADD, param * 2 + 16);
		DrawSphere3D(
			VGet(sparkle[i].transform.position.x, sparkle[i].transform.position.y, sparkle[i].transform.position.z),
			sparkle[i].size, 4, GetColor(red, green, blue), GetColor(red, green, blue),true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int Sparkle::GetID()
{
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (sparkle[i].activeTime <= 0) {
			return i;
		}
	}
	return -1;
}

int Sparkle::StartParticle(const Transform& parent, float _activeTime)
{
	int id = Sparkle::GetID();
	sparkle[id].transform.position = parent.position;
	sparkle[id].velocity = Vector3(
		(sinf(GetRand(RAND_MAX)) * 2.0f),
		(sinf(GetRand(RAND_MAX)) * 2.0f),
		(sinf(GetRand(RAND_MAX)) * 2.0f));
	sparkle[id].size = 0.5f + (sinf(GetRand(RAND_MAX)) * 1.5f);
	sparkle[id].activeTime = _activeTime;
	sparkle[id].color = 0xffffffff;
	return id;
}

void Sparkle::Emit(const Transform& parent, float _activeTime, int count)
{
	for (int i = 0; i < count; i++) {
		StartParticle(parent, _activeTime);
	}
}

void Sparkle::UpdateMove(int i)
{
	// 移動する
	sparkle[i].transform.position += sparkle[i].velocity;
	// IntColorを1バイトごとに分解する (0～255)
	int param = (sparkle[i].color >> 24) & 0xFF;
	if (param > 0) {
		int red = (sparkle[i].color >> 16) & 0xFF;
		int green = (sparkle[i].color >> 8) & 0xFF;
		int blue = sparkle[i].color & 0xFF;
		// 色を変化させる
		param -= 4;
		int cl = 8;
		red += cl;
		green += cl;
		blue += cl;
		if (red > 255)		red = 255;
		if (green > 255)	green = 255;
		if (blue > 255)		blue = 255;
		sparkle[i].color = (param << 24) | (red << 16) | (green << 8) | blue;
	}
}

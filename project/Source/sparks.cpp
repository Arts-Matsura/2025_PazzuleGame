#include "sparks.h"
#include "../Library/time.h"

Sparks::Sparks()
{
	position = VGet(0, 0, 500);
	speed.x = GetRand(6) - 3; // -3 ~ 3のランダムな速度
	speed.y = GetRand(7) + 3; // 3 ~ 10のランダムな速度
	speed.z = GetRand(6) - 3; // -3 ~ 3のランダムな速度

	gravity = 0.0f;

	scale = GetRand(4) + 4; // 4 ~ 8のランダムな大きさ
	lifeTime = GetRand(5) + 3;
	randomTime = GetRand(3);

}

Sparks::~Sparks()
{

}

void Sparks::Update()
{
	randomTime -= Time::DeltaTime() * 2.0f;
	// ランダムな周期で横軸移動速度変更
	if (randomTime <= 0.0f)
	{
		speed.x = GetRand(2) - 1; // -1 ~ 1のランダムな速度
		speed.z = GetRand(2) - 1; // -1 ~ 1のランダムな速度
		randomTime = GetRand(3);
	}

	lifeTime -= Time::DeltaTime();
	if (lifeTime <= 0 || scale <= 0.01f)
	{
		GameObject::DestroyMe();
	}

	gravity += 0.1f;
	scale -= 0.05f;
	position += speed;
	position.y -= gravity;

}

void Sparks::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawSphere3D(position, scale, scale, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

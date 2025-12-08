#include "Meteor.h"
#include "dashParticle.h"
#include "sparkle.h"

namespace
{
	const float RADIUS = 25.0f;
	const float GROUND_Y = 90.0f;
	const float SCALE = 1.5f;
}

Meteor::Meteor(int h_mesh)
{
	this->h_mesh = h_mesh;
	transform.scale = Vector3(SCALE, SCALE, SCALE);
}

Meteor::~Meteor()
{
	MV1DeleteModel(h_mesh);
}


void Meteor::Update()
{
	// 判定
	if (transform.position.y <= GROUND_Y + RADIUS)
	{
		OnCollision();
		transform.is_active = false;
		return;
	}

	transform.position += velocity;

	// パーティクル生成
	if (GetRand(RAND_MAX) % 2 == 0)
	{
		DashParticle::StartLine(transform, 1.5f);
		Sparkle::Emit(transform, 0.5f, 10);
	}
}

void Meteor::Draw()
{	
	MV1SetMatrix(h_mesh, transform.GetMatrix());
	MV1DrawModel(h_mesh);

	//sDrawSphere3D(transform.position, RADIUS * 2.0f, 16, Color::Cyan16(), Color::White16(), 0);
}

void Meteor::OnCreate(const Vector3& pos)
{
	transform.SetActive(true);
	transform.position = pos;
	transform.rotation = Vector3(45.0f, -45.0f, 0) * DegToRad;
	life_time = 3.0f;
	velocity = Vector3(0.0f, 0.0f, 6.0f) * MGetRotationZXY(transform.rotation);
}

void Meteor::OnCollision()
{
	//衝突時の処理
}

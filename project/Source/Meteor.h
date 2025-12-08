#pragma once
#include "Transform.h"

/// <summary>
/// 流星のクラス　GameObjectを継承しない
/// </summary>
class Meteor
{
public:
	Meteor(int h_mesh);
	~Meteor();

	void Update();
	void Draw();

	void OnCreate(const Vector3& pos);//パラメーターが必要な場合はここに追加
	void OnCollision();//衝突時の処理

	Transform transform;
private:
	Vector3 velocity;
	float life_time = 1.0f;
	int h_mesh = -1;
};
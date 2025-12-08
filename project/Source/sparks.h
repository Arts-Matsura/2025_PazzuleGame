#pragma once
#include "../Library/gameObject.h"

class Sparks : public GameObject
{
public:
	Sparks();
	~Sparks();
	void Update() override;
	void Draw() override;

private:
	Vector3 position;	// À•W
	Vector3 speed;		// ã¸‘¬“x
	float scale;		// ‘å‚«‚³
	float gravity;		// d—Í
	float lifeTime;
	float randomTime;

};
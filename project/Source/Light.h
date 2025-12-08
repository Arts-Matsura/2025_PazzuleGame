#pragma once
#include "Object3D.h"

class Light : public Object3D {
public:
	Light();
	~Light();
	void Update() override;
	void Draw() override;
private:
	int light1;
	int light2;
	int light3;
};
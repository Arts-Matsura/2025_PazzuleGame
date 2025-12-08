#pragma once
#include "Object3D.h"

class Camera;

class Sky : public Object3D {
public:
	Sky();
	~Sky();
	void Draw() override;
private:
	Camera* camera;
};
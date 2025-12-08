#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR lookTarget; // ’‹“_
	// position‚ÍAObject3D‚É‚ ‚é
};
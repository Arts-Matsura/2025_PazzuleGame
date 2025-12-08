#include "Sky.h"
#include "Camera.h"

Sky::Sky()
{
	hModel = MV1LoadModel("data/Stage/Skydome.mv1");
	camera = nullptr;
	scale = VGet(25.0f, 25.0f, 25.0f);
}

Sky::~Sky()
{
}

void Sky::Draw()
{
	if (camera == nullptr) {
		camera = FindGameObject<Camera>();
	}
	position = camera->Position();
	Object3D::Draw();
}

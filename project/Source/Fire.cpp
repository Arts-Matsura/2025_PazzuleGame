#include "Fire.h"

Fire::Fire()
{
	hModel = MV1LoadModel("data/model/Fire.mv1");
	position = VGet(0, 25, 500);
	scale = VGet(1.0f, 1.0f, 1.0f);
}

Fire::~Fire()
{
	MV1DeleteModel(hModel);
}

void Fire::Draw()
{
	Object3D::Draw();
}

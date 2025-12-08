#include "Object3D.h"

Object3D::Object3D()
{
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	scale = VGet(1.0f, 1.0f, 1.0f);
	hModel = -1;
}

Object3D::~Object3D()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
	}
}

void Object3D::Draw()
{
	if (hModel > 0) {
		MATRIX mPosition = MGetTranslate(position);
		MATRIX mRotX = MGetRotX(rotation.x);
		MATRIX mRotY = MGetRotY(rotation.y);
		MATRIX mRotZ = MGetRotZ(rotation.z);
		MATRIX mScale = MGetScale(scale);
		MATRIX mat = mScale * mRotZ * mRotX * mRotY * mPosition;
		MV1SetMatrix(hModel, mat);
		MV1DrawModel(hModel);
	}
}

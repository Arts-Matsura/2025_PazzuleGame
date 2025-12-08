#include "StageObj.h"
#include "../Library/resourceLoader.h"
StageObj::StageObj()
{
	opacityTarget = 1.0f;
	opacity = 1.0f;
}

StageObj::~StageObj()
{
}

void StageObj::Start()
{
	MATRIX mPosition = MGetTranslate(position);
	MATRIX mRotX = MGetRotX(rotation.x);
	MATRIX mRotY = MGetRotY(rotation.y);
	MATRIX mRotZ = MGetRotZ(rotation.z);
	MATRIX mat = mRotZ * mRotX * mRotY * mPosition;
	MV1SetMatrix(hHitModel, mat);
}

void StageObj::Update()
{
	if (counter > 0) {
		opacity += (opacityTarget - opacity) / counter;
		counter--;
	}
}

void StageObj::Draw()
{
	MV1SetOpacityRate(hModel, opacity);
	Object3D::Draw();
}

void StageObj::LoadModel(std::string name)
{
	std::string folder = "data/Stage/";
	SetTag(name);
	hModel = ResourceLoader::MV1LoadModel((folder + name + ".mv1").c_str());
	hHitModel = ResourceLoader::MV1LoadModel(
					(folder + name + "_c.mv1").c_str());
	MV1SetMaterialDrawAlphaTestAll(hModel, TRUE,
		DX_CMP_GREATER, 128);
}

void StageObj::SetOpacity(float rate)
{
	if (opacityTarget != rate) {
		opacityTarget = rate;
		counter = 10; // 10ÉtÉåÅ[ÉÄÇ≈
	}
}

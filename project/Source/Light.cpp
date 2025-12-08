#include "Light.h"

Light::Light()
{
//	SetGlobalAmbientLight(GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
//	SetLightEnable(FALSE);
//	light1 = CreatePointLightHandle(VGet(10, 200, 100), 2000.0f, 0.0f, 0.002f, 0.0f);
//	SetLightDifColorHandle(light1, GetColorF(1.0f, 1.0f, 0.0f, 0.0f));
//	SetLightEnableHandle(light1, TRUE);
}

Light::~Light()
{
	if (light1>0)
		DeleteLightHandle(light1);
}

void Light::Update()
{
}

void Light::Draw()
{
}

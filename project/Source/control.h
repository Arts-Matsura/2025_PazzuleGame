#pragma once
#include"../Library/gameObject.h"
class Control : public GameObject
{
public:
	Control();
	~Control();
	void Update()override;
	void Draw()override;
private:


};
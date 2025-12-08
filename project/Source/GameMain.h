#pragma once
#include "..\/Library\gameObject.h"

class GameMain : public GameObject 
{
public:
	GameMain();
	~GameMain();

	void Update() override;
	void Draw() override;

private:

};
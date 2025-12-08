#pragma once
#include "../Library/GameObject.h"

class ManagerController : public GameObject {
public:
	ManagerController();
	~ManagerController();
	void Update() override;
	void Draw() override;
};
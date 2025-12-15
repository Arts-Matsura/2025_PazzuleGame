#pragma once
#include "../Library/GameObject.h"

class ManagerController : public GameObject {
public:
	ManagerController(SceneBase* scene);
	~ManagerController();
	void Update() override;
	void Draw() override;
};
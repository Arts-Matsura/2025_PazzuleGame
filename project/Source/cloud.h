#pragma once
#include "../Library/gameObject.h"
#include <vector>

class Cloud :public GameObject {
public:
	Cloud();
	~Cloud();
	void Update()override;
	void Draw()override;

	void Create(int MaxBoard, int sideNum, int verNum);
	void DeleteCloud();
private:

	std::vector<std::vector<bool>> isClouds;
};

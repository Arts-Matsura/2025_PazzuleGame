#pragma once
#include"../Library/gameObject.h"
#include<vector>

class Smoke :public GameObject {
public:
	Smoke();
	~Smoke();
	void Update()override;
	void Draw()override;
private:
	std::vector<int>smokeImage;
	std::vector<Vector3>oldSmokePos;
	std::vector<Vector3>smokePos;
};
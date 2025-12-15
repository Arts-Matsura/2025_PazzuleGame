#pragma once
#include "../Library/gameObject.h"
#include <vector>

#include "cloud.h"

class CloudManager :public GameObject {
public:
	CloudManager();
	~CloudManager();
	void Update()override;
	void Draw()override;

	void Create(int MaxBoard, int sideNum, int verNum);
	void CreateVer(int Num);
	void CreateSide(int Num);

	void DeleteCloud();
private:
	Cloud clouds[4][4];
};

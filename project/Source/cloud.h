#pragma once
#include "../Library/gameObject.h"
#include <vector>

class Cloud :public GameObject {
public:
	Cloud();
	~Cloud();
	void Update()override;
	void Draw()override;

	bool isCloud;
};

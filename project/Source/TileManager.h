#pragma once
#include "../Library/gameObject.h"

class TileManager : public GameObject
{
public:
	TileManager();
	~TileManager();

	void Update() override;
	void Draw() override;

private:
};
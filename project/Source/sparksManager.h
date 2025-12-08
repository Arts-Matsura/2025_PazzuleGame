#pragma once
#include "../Library/gameObject.h"

class SparksManager : public GameObject
{
public:
	SparksManager();
	~SparksManager();
	void Update() override;
	void Draw() override;


private:
	float spawnTime; // ¶¬‚·‚éŠÔ


};
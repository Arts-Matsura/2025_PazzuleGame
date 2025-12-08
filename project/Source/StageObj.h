#pragma once
#include "Object3D.h"

class StageObj : public Object3D {
public:
	StageObj();
	~StageObj();
	void Start() override;
	void Update() override;
	void Draw() override;
	void LoadModel(std::string name);
	int HitModel() { return hHitModel; }
	void SetOpacity(float rate);
private:
	int hHitModel; // “–‚½‚è”»’è—pƒ‚ƒfƒ‹ 
	float opacityTarget;
	float opacity;
	int counter;
};
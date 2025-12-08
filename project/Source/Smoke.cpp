#include "Smoke.h"
#include<assert.h>
#include"../Library/time.h"
namespace {
	int SMOKE_MAX = 7;
	float SMOKE_MAXPOS_Y = 500.0f;
}
Smoke::Smoke()
{
	
	for (int i = 0; i < SMOKE_MAX; i++) {
		smokeImage.push_back(LoadGraph("data\\2D\\smoke_sheet.png"));
		assert(smokeImage[i] > 0);
	}
	for (int i = 0; i < smokeImage.size(); i++) {
		oldSmokePos.emplace_back(0, 100, 500);
		oldSmokePos.emplace_back(0, 120, 500);
		oldSmokePos.emplace_back(0, 140, 500);
		oldSmokePos.emplace_back(0, 160, 500);
		oldSmokePos.emplace_back(0, 180, 500);
		oldSmokePos.emplace_back(0, 200, 500);
		oldSmokePos.emplace_back(0, 210, 500);
	}
	for (int i = 0; i < smokeImage.size(); i++) {
		smokePos.emplace_back(0, 100, 500);
		smokePos.emplace_back(0, 120, 500);
		smokePos.emplace_back(0, 140, 500);
		smokePos.emplace_back(0, 160, 500);
		smokePos.emplace_back(0, 180, 500);
		smokePos.emplace_back(0, 200, 500);
		smokePos.emplace_back(0, 210, 500);
	}
}

Smoke::~Smoke()
{
	smokeImage.clear();
	smokePos.clear();
}

void Smoke::Update()
{
	for (int i = 0; i < smokePos.size();i++) {
		if (smokePos[i].y < SMOKE_MAXPOS_Y) {
			smokePos[i].y += Time::DeltaTime() * 30.0f;
		}
		else if (smokePos[i].y >= SMOKE_MAXPOS_Y) {
			smokePos[i].y = oldSmokePos[i].y;
		}
	}
}

void Smoke::Draw()
{
	for(int i = 0; i < smokeImage.size();i++){
		DrawRotaGraph3D(smokePos[i].x, smokePos[i].y, smokePos[i].z, 2.5f, 1.0f, smokeImage[i], true, false);
	}
}

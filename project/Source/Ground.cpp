#include "Ground.h"
#include <assert.h>
Ground::Ground()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
	assert(hModel > 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	scale.y = 0.2f;

	Object3D::Draw();//モデルに行列のセット
}

Ground::~Ground()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Ground::Draw()
{
	MV1DrawModel(hModel);
}

bool Ground::CollisionLine(VECTOR begin, VECTOR end, VECTOR* hitPos)
{
	MV1_COLL_RESULT_POLY hit;
	hit = MV1CollCheck_Line(hModel, 0, begin, end);
	if (hit.HitFlag > 0) {
		if (hitPos != nullptr) {
			*hitPos = hit.HitPosition;
		}
		return true;
	}
	return false;
}

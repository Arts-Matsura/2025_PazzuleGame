#pragma once
#include "Object3D.h"

class StageObjManager : public Object3D {
public:
	StageObjManager();
	~StageObjManager();

	/// <summary>
	/// カプセルとStageObjの当たり判定をする
	/// </summary>
	/// <param name="p1">カプセルの点１</param>
	/// <param name="p2">カプセルの点２</param>
	/// <param name="r">カプセルの半径</param>
	/// <param name="push">押し返すベクトルを返す</param>
	/// <returns>あたっていればtrue</returns>
	bool CollCheckCapsule(VECTOR p1, VECTOR p2, float r, VECTOR* push);

	bool CollCheckLine(VECTOR pos, VECTOR look, VECTOR* hitPos);
};
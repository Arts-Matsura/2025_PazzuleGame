#pragma once
//Ground.h
#include "Object3D.h"

/// <summary>
/// 地面の管理をする
/// </summary>
/// <author>花井</author>
class Ground : public Object3D
{
public:
	Ground();
	~Ground();

	void Draw() override;

	/// <summary>
	/// 地面モデルと線分との当たり判定をする
	/// </summary>
	/// <param name="begin">線分の始点</param>
	/// <param name="end">線分の終点</param>
	/// <param name="hitPos">当たった場合に座標を返すポインター</param>
	/// <returns>当たったらtrue</returns>
	bool CollisionLine(VECTOR begin, VECTOR end, VECTOR* hitPos = nullptr);
};

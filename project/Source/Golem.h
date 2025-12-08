#pragma once
#include "Object3D.h"
#include "Animator.h"

class Golem : public Object3D
{
public:
	Golem();
	~Golem();
	void Start() override; // 最初にUpdateが呼ばれる前
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーの攻撃に対する判定
	/// </summary>
	/// <param name="n1">今の根元</param>
	/// <param name="n2">今の剣先</param>
	/// <param name="p1">前の根元</param>
	/// <param name="p2">前の剣先</param>
	/// <returns>当たったらtrue</returns>
	bool CollisionAttacked(VECTOR n1, VECTOR n2, VECTOR p1, VECTOR p2);
private:
	enum State {
		sWander,
		sReach,
		sAttack,
		sBack,
		sDead,
		sErase,
	};
	State state;
	void updateWander();
	void updateReach();
	void updateAttack();
	void updateBack();
	void updateDead();
	void updateErase();

	void moveToTarget(VECTOR target);

	float hitPoint;

	Animator* animator;
	enum ANIMID {
		aWAIT = 0,
		aWALK,
		aATTACK1,
		aATTACK2,
		aATTACK3,
		aDOWN,
	};

	VECTOR basePosition;
	int wanderTarget;

	// 足音のハンドル
	int hFootSE;
};

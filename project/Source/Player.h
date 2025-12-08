#pragma once
// Player.h

#include "Object3D.h"
#include "Animator.h"
#include "Locus.h"

class Player : public Object3D {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
private:
	Animator* animator;
	enum ANIMID {
		aWAIT = 0,
		aRUN,
		aATTACK1,
		aATTACK2,
		aATTACK3,
	};

	//ステートパターン
	enum State {
		sNORMAL = 0,
		sATTACK1,
		sATTACK2,
		sATTACK3,
		sBLOW,
	};
	State state; // 状態を持たせる
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
	void UpdateBlow();

	int hSabel; // サーベルのモデル
	void BeforeAttack();
	bool Attack();
	MATRIX matSabel; // サーベルの位置の行列
	VECTOR prevSabelRoot, prevSabelTip; // 前のフレームのサーベルの根元と先端

	struct ATT_TIME {
		float begin;
		float end;
		float cancel;
	};
	ATT_TIME attackTime[3];
	int light;

	VECTOR padInput(); // padとキーを見て、入力値の値を返す
	bool attackButton(); // padとキーの攻撃ボタンを押したかを返す

	Locus* locus;
	int sabelSound;
};

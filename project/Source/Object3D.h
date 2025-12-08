#pragma once
//Object3D.h
#include "../Library/gameObject.h"

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Draw() override;
	int Model() {
		return hModel;
	}
	void SetPosition(VECTOR pos) { position = pos; }
	void SetPosition(float x, float y, float z) { SetPosition(VGet(x, y, z)); }
	void SetRotation(VECTOR rot) { rotation = rot; }
	void SetRotation(float x, float y, float z) { SetRotation(VGet(x, y, z)); }
	void SetScale(VECTOR sca) { scale = sca; }
	void SetScale(float x, float y, float z) { SetScale(VGet(x, y, z)); }
	VECTOR Position() { return position; }
	VECTOR Rotation() { return rotation; }
	VECTOR Scale() { return scale; }
protected:
	int hModel; // ３Dモデル
	VECTOR position; // 座標
	VECTOR rotation; // 各軸の回転（ラジアン）
	VECTOR scale; // 各軸のスケール
};

//GameObject* p = new Object3D();
//p->Update();
//delete p;

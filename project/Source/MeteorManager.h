#pragma once
#include "../Library/gameObject.h"
#include "Meteor.h"
#include <vector>
#include "ActionEvent.h"

/// <summary>
/// Meteorを管理するクラス
/// </summary>
class MeteorManager : public GameObject
{
public:
	MeteorManager();
	~MeteorManager();

	void Start() override;
	void Update() override;
	void Draw() override;

	ActionEvent<const Transform&> OnDestroyMeteor;// 流星が消えたときに呼ばれるイベント(流星のtransform)

private:
	void OnTestEventM(const Transform& _transform);

	std::vector<Meteor*> meteor_pool;
	std::list<Meteor*> meteor_active_list;

	float create_timer = 0.0f;
	int h_meteor_mesh = -1;
};
#include "Animator.h"
#include "../Library/gameObject.h"
#include "Player.h"
#include <assert.h>
#include "../Library/Time.h"
#include "../Library/resourceLoader.h"
namespace {
	static const float MergeTimeMax = 0.1f;
};

Animator::Animator(GameObject* _parent)
{
	parent = _parent;
	parentModel = dynamic_cast<Object3D*>(parent)->Model();
	current.attachID = -1;
	prev.attachID = -1;
	playingID = -1;
	playSpeed = 1.0f;
}

Animator::~Animator()
{
	if (current.attachID >= 1.0f) {
		MV1DetachAnim(parentModel, current.attachID);
	}
	if (prev.attachID >= 1.0f) {
		MV1DetachAnim(parentModel, prev.attachID);
	}
	for (auto a : anims) {
		MV1DeleteModel(a.handle);
	}
	anims.clear();
}

void Animator::Update()
{
	if (current.attachID >= 0) {
		current.frame += Time::DeltaTime() * playSpeed * 30.0f;
		if (current.frame >= current.maxFrame) {
			if (anims[playingID].loop) {
				current.frame -= current.maxFrame;
			}
			else {
				current.frame = current.maxFrame;
			}
		}
		MV1SetAttachAnimTime(parentModel, current.attachID, current.frame);
	}
	if (prev.attachID >= 0) {
		mergeTime += Time::DeltaTime() * playSpeed;
		if (mergeTime >= MergeTimeMax) {
			MV1DetachAnim(parentModel, prev.attachID);
			MV1SetAttachAnimBlendRate(parentModel, current.attachID, 1.0f);
			prev.attachID = -1;
		}
		else {
			float rate = mergeTime / MergeTimeMax;
			MV1SetAttachAnimBlendRate(parentModel, current.attachID, rate);
			MV1SetAttachAnimBlendRate(parentModel, prev.attachID, 1.0f-rate);
		}
	}
}

void Animator::LoadAnimFile(std::string filename, bool loop)
{
	AnimInfo inf;

	inf.handle = ResourceLoader::MV1LoadModel(filename.c_str());
	assert(inf.handle > 0);
	inf.loop = loop;

	anims.push_back(inf);
}

// アニメーション再生は、
// int attachID = MV1AttachAnim(model, 0, animID);
// MV1SetAttachAnimTime(model, attachID, 再生フレーム);
// アニメーションをやめるとき
// MV1DetachAnim(model, animID);
// アニメーションの最大フレームは
// int maxFrame = MV1GetAttachAnimTotalTime(model, animID);

void Animator::Play(int id)
{
	assert(id >= 0 && id < anims.size());

	if (id == playingID) // 同じIDなら無視する
		return;

	if (prev.attachID >= 0) {
		MV1DetachAnim(parentModel, prev.attachID);
	}
	prev = current;
	mergeTime = 0.0f;
	playingID = id;
	int animID = anims[id].handle;
	current.attachID = MV1AttachAnim(parentModel, 0, animID);
	current.frame = 0.0f;
	current.maxFrame = MV1GetAttachAnimTotalTime(parentModel, current.attachID);
}

bool Animator::IsFinished()
{
	if (playingID < 0 || anims[playingID].loop)
		return false;
	if (current.frame >= current.maxFrame)
		return true;
	return false;
}

void Animator::SetPlaySpeed(float speed)
{
	playSpeed = speed;
}

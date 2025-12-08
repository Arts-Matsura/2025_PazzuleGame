#include "Golem.h"
#include <assert.h>
#include "Ground.h"
#include "../Library/resourceLoader.h"
#include "Player.h"
#include "../Library/time.h"
#include "Camera.h"

namespace {
	const float MOVE_SPEED = 300.0f;
	const float ROTATION_SPEED = DegToRad * (180.0f); // 1秒の回転量
};

Golem::Golem()
{
	static const std::string folder = "data/Character/Golem/";
	hModel = ResourceLoader::MV1LoadModel((folder + "Golem.mv1").c_str());
	assert(hModel > 0);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root,
		MGetRotY(DX_PI_F));

	position = VGet(0, 100, 500);

	animator = new Animator(this);
	animator->LoadAnimFile(folder + "Anim_Neutral.mv1", true);
	animator->LoadAnimFile(folder + "Anim_Walk.mv1", true);
	animator->LoadAnimFile(folder + "Anim_Attack1.mv1", false);
	animator->LoadAnimFile(folder + "Anim_Attack2.mv1", false);
	animator->LoadAnimFile(folder + "Anim_Attack3.mv1", false);
	animator->LoadAnimFile(folder + "Anim_Down.mv1", false);
	animator->Play(ANIMID::aWALK);

	state = sWander;
	hitPoint = 1000.0f;
	wanderTarget = 0;
}

Golem::~Golem()
{
}

void Golem::Start()
{
	basePosition = position;
}

void Golem::Update()
{
	switch (state) {
	case sWander: updateWander(); break;
	case sReach:  updateReach();  break;
	case sAttack: updateAttack(); break;
	case sBack:   updateBack();   break;
	case sDead:   updateDead();   break;
	case sErase:  updateErase();  break;
	}

	// 地面に接地させる
	Ground* pGround = FindGameObject<Ground>();
	if (pGround != nullptr) {
		VECTOR hitPos;
		if (pGround->CollisionLine(position + VGet(0, 100, 0), position + VGet(0, -30, 0), &hitPos)) {
			position = hitPos;
		}
	}

	animator->Update();
	if (animator->PlayingID() == aWALK) {
		float frame = animator->CurrentFrame();
		if (frame < 1.0f) {//ここで足音を鳴らす
			hFootSE = ResourceLoader::LoadSoundMem("data/Sound/SE/Golem/MAT_footstep_grass_00.wav");
			PlaySoundMem( hFootSE, DX_PLAYTYPE_BACK);
			// PANとVOLUMEを設定:VOLUMEは、ベクトルの長さを使う
			// PANは、ベクトルの向き
			// ベクトルは、音源はposition、聞く場所はcamera
			Camera* camera = FindGameObject<Camera>();
			VECTOR soundVec = position - camera->Position(); // カメラから見た音源へのベクトル
			int vol = (VSize(soundVec) - 400) / 1600 * -255;
			if (vol < 0) vol = 0;
			if (vol > 255) vol = 255;
			ChangeVolumeSoundMem(vol, hFootSE);

			soundVec = VNorm(soundVec); // 長さを１にする
			float dot = VDot(soundVec, VGet(1, 0, 0) * MGetRotY(camera->Rotation().y));
			int pan = dot * 255; /*ここをsoundVecの向きから求める -255～0～255(右)*/
			ChangePanSoundMem(pan, hFootSE);
		}
	}
}

void Golem::Draw()
{
	Object3D::Draw();
}

bool Golem::CollisionAttacked(VECTOR n1, VECTOR n2, VECTOR p1, VECTOR p2)
{
	if (state == sDead)
		return false;

	MATRIX m = MGetRotY(rotation.y) * MGetTranslate(position);
	VECTOR seg1 = VGet(0, 30, 0) * m;
	VECTOR seg2 = VGet(0, 150, 0) * m;
	float ret1 = Segment_Triangle_MinLength(seg1, seg2,
		n1, n2, p2);
	float ret2 = Segment_Triangle_MinLength(seg1, seg2,
		n1, p2, p1);
	if (ret1 < 30.0f || ret2 < 30.0f) {
		state = sDead;
		animator->Play(aDOWN);
		hitPoint -= 100.0f;
		return true;
	}
	return false;
}

void Golem::updateWander()
{
	// ルート上を歩く
	std::vector<VECTOR> route = {
		VGet(500,0,0),
		VGet(0,0,-500),
		VGet(-500,0,0),
		VGet(0,0,500),
	};
	VECTOR targetPos = route[wanderTarget] + basePosition;
	moveToTarget(targetPos);
	if (VSize(targetPos - position) < 50.0f) {
		//wanderTarget += 1;
		//if (wanderTarget >= route.size()) {
		//	wanderTarget = 0;
		//}
		wanderTarget = (wanderTarget + 1) % route.size();
	}

	animator->Play(aWALK);
	// プレイヤーが近づいたら、sReachにする
	// ①視野（10m以内で、正面から左右30度)に入るか、
	// ②3m以内に入ったら
	// 1mは100
	Player* player = FindGameObject<Player>();
	VECTOR pPos = player->Position();
	VECTOR toPlayer = pPos - position; // プレイヤーへのベクトル
//	if (VSize(toPlayer)<=300.0f) {
//		state = sReach;
//	}
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
	if (VSize(toPlayer) <= 1000.0f && 
		VDot(VNorm(toPlayer),forward) >= cosf(DegToRad * (30.0f))) {
		state = sReach;
	}
}

void Golem::updateReach()
{
	Player* player = FindGameObject<Player>();
	VECTOR pPos = player->Position();
	moveToTarget(pPos);

	if (VSize(position - pPos) < 100.0f) {
		state = sAttack;
		animator->Play(aATTACK1);
	} else if (VSize(position - basePosition) > 1000.0f) {
		state = sBack;
	}
}

void Golem::updateAttack()
{
	if (animator->IsFinished()) {
		state = sWander;
	}
}

void Golem::updateBack()
{
	moveToTarget(basePosition);
	if (VSize(position - basePosition) < 50.0f) {
		state = sWander;
	}
}

void Golem::updateDead()
{
	if (animator->IsFinished()) {
		if (hitPoint > 0) {
			state = sWander;
		}
		else {
			// 消えるエフェクト
			DestroyMe();
		}
	}
}

void Golem::updateErase()
{
}

void Golem::moveToTarget(VECTOR target)
{
	// ここで角度を合わせる 
	// 右か左に、ROTATION_SPEED*Time::DeltaTime()で回る
	VECTOR toBase = target - position;
	toBase.y = 0; // 高低差を吸収する
	VECTOR right = VGet(1, 0, 0) * MGetRotY(rotation.y);
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
	if (VDot(VNorm(toBase), forward ) >= cosf(ROTATION_SPEED * Time::DeltaTime())) {
		rotation.y = atan2(toBase.x , toBase.z );
	}
	else if (VDot(right, toBase) > 0)
		rotation.y += ROTATION_SPEED * Time::DeltaTime();
	else
		rotation.y -= ROTATION_SPEED * Time::DeltaTime();

	VECTOR velocity = VGet(0, 0, MOVE_SPEED) * Time::DeltaTime()
		* MGetRotY(rotation.y);
	position += velocity;
	animator->Play(aWALK);
}

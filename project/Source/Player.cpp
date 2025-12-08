#include "Player.h"
#include <assert.h>
#include "../Library/time.h"
#include "Ground.h"
#include "Golem.h"
#include "CsvReader.h"
#include "StageObjManager.h"
#include "Camera.h"
#include "SingletonSample.h"
#include "../Library/resourceLoader.h"
#include "SoundManager.h"

namespace {
	static const float MOVE_SPEED = 400.0f; // 秒間のcm
};

Player::Player()
{
	static const std::string folder = "data/Character/Player/";
	hModel = MV1LoadModel((folder+"PC.mv1").c_str());
	assert(hModel > 0);

	hSabel = ResourceLoader::MV1LoadModel((folder + "Sabel.mv1").c_str());
	assert(hSabel > 0);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root,
		MGetRotY(DX_PI_F));

	position = VGet(0, 0, 0);

	animator = new Animator(this);
	animator->LoadAnimFile(folder + "Anim_Neutral.mv1", true);
	animator->LoadAnimFile(folder + "Anim_Run.mv1", true);
	animator->LoadAnimFile(folder + "Anim_Attack1.mv1", false);
	animator->LoadAnimFile(folder + "Anim_Attack2.mv1", false);
	animator->LoadAnimFile(folder + "Anim_Attack3.mv1", false);
	animator->Play(ANIMID::aRUN);

	///CsvReaderの実験
	CsvReader* csv = new CsvReader();
	csv->Load("data/Character/Player/Anim_Attack1.csv");
	for (int i = 0; i < csv->Lines(); i++) {
		std::string command = csv->Get(i, 0);
		if (command == "ATTACK") {
			attackTime[0].begin = csv->GetFloat(i, 1);
			attackTime[0].end = csv->GetFloat(i, 2);
		}
		else if (command == "CANCEL") {
			attackTime[0].cancel = csv->GetFloat(i, 1);
		}
	}
	delete csv;

	light = CreateSpotLightHandle(VGet(0, 0, 0), VGet(0, 0, 1), DX_PI_F / 10, DX_PI_F / 10, 800, 0.0f, 0.02f, 0.0f);
	SetLightDifColorHandle(light, GetColorF(1.0f, 0, 0, 1.0f));
	SetLightEnableHandle(light, TRUE);

	locus = Instantiate<Locus>();

	SoundManager::Ready("../BGM/JINGLE_stageclearALL.ogg");
}

Player::~Player()
{
	delete animator;

	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Player::Update()
{
	// 共通の前処理
	switch (state) {
	case sNORMAL:  UpdateNormal();  break;
	case sATTACK1: UpdateAttack1(); break;
	case sATTACK2: UpdateAttack2(); break;
	case sATTACK3: UpdateAttack3(); break;
	case sBLOW:    UpdateBlow();    break;
	}
	// 共通の後処理

	// サードパーソンカメラを設定する
//	VECTOR eye = VGet(0, 300, -300) * MGetRotY(rotation.y) * MGetTranslate(position);
//	VECTOR target = VGet(0, 100, 300) * MGetRotY(rotation.y) + position;
//	SetCameraPositionAndTarget_UpVecY(eye, target);

	animator->Update();
}

void Player::Draw() {
//	DrawSphere3D(VGet(500,0,0), 200, 20, 0xffffff, 0xffffff, FALSE);
//	DrawSphere3D(position, 100, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
	Object3D::Draw(); // 基底クラスのDraw()を呼ぶ

	int wp = MV1SearchFrame(hModel, "wp");
	matSabel = MV1GetFrameLocalWorldMatrix(hModel, wp);

	MV1SetMatrix(hSabel, matSabel);
	MV1DrawModel(hSabel);
	VECTOR p = VGet(0, 0, 0) * matSabel;
	VECTOR d = VGet(0, -1, 0) * matSabel;
	SetLightPositionHandle(light, p);
	SetLightDirectionHandle(light, d);

//	VECTOR sabelRoot = VGet(0, 0, 0) * matSabel;
//	VECTOR sabelTip = VGet(0,-100,0) * matSabel;
	// サーベルの刃の位置に赤線を引く
//	DrawLine3D(sabelRoot, sabelTip, GetColor(255, 0, 0));
}

void Player::UpdateNormal()
{
	VECTOR analog = padInput();
	if (VSize(analog)>0.2f) { // 中心付近の場合は入力していないことにする
		// ここに移動のプログラム
		VECTOR velocity = analog * MOVE_SPEED * Time::DeltaTime();
		Camera* cam = FindGameObject<Camera>();
		velocity *= MGetRotY(cam->Rotation().y);
		position += velocity;
		rotation.y = atan2f(velocity.x, velocity.z);
		animator->Play(aRUN);
	}
	else {
		animator->Play(aWAIT);
	}
	// StageObjManagerとの当たり判定
	StageObjManager* stObj = FindGameObject<StageObjManager>();
	VECTOR push;
	if (stObj->CollCheckCapsule(
		position + VGet(0, 50, 0), position + VGet(0, 150, 0), 10, &push)) {
		push.y = 0;
		position += push;
	}

	// 地面に接地させる
	Ground* pGround = FindGameObject<Ground>();
	if (pGround != nullptr) {
		VECTOR hitPos;
		if (pGround->CollisionLine(position + VGet(0, 100, 0), position + VGet(0, -30, 0), &hitPos)) {
			position = hitPos;
		}
	}

	/* バグるので削除。多分Locusでゼロ除算 */
	//if (attackButton()) { // 攻撃ボタンを押した
	//	sabelSound = SoundManager::Play("../BGM/JINGLE_stageclearALL.ogg");
	//	animator->Play(aATTACK1);
	//	BeforeAttack();
	//	state = sATTACK1;
	//}
	if (CheckHitKey(KEY_INPUT_5)) {
		if (SoundManager::IsPlaying(sabelSound)) {
			SoundManager::Stop(sabelSound);
		}
	}
	if (VSize(position - VGet(500, 0, 0)) < 200) {
		// 環境音を鳴らす（呼ばれている間鳴り続ける）
		SoundManager::PlayEnv("../BGM/BGM_boss.ogg");
	}
}

void Player::UpdateAttack1()
{
	float frame = animator->CurrentFrame();
	if (frame >= attackTime[0].cancel) {
		// 次の攻撃を受け付ける
		if (attackButton()) { // 攻撃ボタンを押した
			animator->Play(aATTACK2);
			state = sATTACK2;
		}
	}
	if (frame >= attackTime[0].begin && frame <= attackTime[0].end) {
		Attack();
	}
	if (animator->IsFinished()) {
		state = sNORMAL;
	}
}

void Player::UpdateAttack2()
{
	if (animator->IsFinished()) {
		state = sNORMAL;
	}
}

void Player::UpdateAttack3()
{
}
void Player::UpdateBlow()
{
}

void Player::BeforeAttack()
{
	prevSabelRoot = VGet(0, 0, 0) * matSabel;
	prevSabelTip = VGet(0, -100, 0) * matSabel;
}

bool Player::Attack()
{
	// 今のサーベルの２点を取得
	VECTOR sabelRoot = VGet(0, 0, 0) * matSabel;
	VECTOR sabelTip = VGet(0, -100, 0) * matSabel;
	locus->SetPosition(sabelRoot, sabelTip);

	bool ret = false;
	std::list<Golem*> golems = FindGameObjects<Golem>();
	for (std::list<Golem*>::iterator itr = golems.begin();
							itr != golems.end(); itr++) {
		Golem* pGolem = *itr;
		if (pGolem != nullptr) {
			ret |= pGolem->CollisionAttacked(sabelRoot, sabelTip, prevSabelRoot, prevSabelTip);
		}
	}
	
	prevSabelRoot = sabelRoot;
	prevSabelTip = sabelTip;
	return ret;
}

VECTOR Player::padInput()
{
	XINPUT_STATE input;
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	//	input.ThumbLX, input.ThumbLYにアナログの状態が入る
	VECTOR analog = VGet(input.ThumbLX / 32767.0f, 0, input.ThumbLY / 32767.0f);
	if (CheckHitKey(KEY_INPUT_W)) {
		analog.z = 1.0f;
	}
	else
		if (CheckHitKey(KEY_INPUT_S)) {
			analog.z = -1.0f;
		}
	if (CheckHitKey(KEY_INPUT_D)) {
		analog.x = 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		analog.x = -1.0f;
	}
	if (VSize(analog) > 1.0f)
		analog = VNorm(analog);
	// 倒した量を0.0～1.0に収める
	// 倒した向き　→　長さ１にする
	return analog;
}

bool Player::attackButton()
{
	XINPUT_STATE input;
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	return (CheckHitKey(KEY_INPUT_P) || input.Buttons[XINPUT_BUTTON_B]);
}

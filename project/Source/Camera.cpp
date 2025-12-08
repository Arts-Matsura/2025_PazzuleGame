#include "Camera.h"
#include "Player.h"
#include "StageObjManager.h"

Camera::Camera()
{
	DxLib::SetupCamera_Perspective(90.0f * DegToRad);
	rotation.x = DegToRad *  (10.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	XINPUT_STATE input;
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	if (input.ThumbRX > 16000 || CheckHitKey(KEY_INPUT_RIGHT)) {
		rotation.y += DegToRad * (3.0);
	}
	else if (input.ThumbRX < -16000 || CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y -= DegToRad * (3.0);
	}
	if (input.ThumbRY > 16000 || CheckHitKey(KEY_INPUT_UP)) {
		rotation.x += DegToRad * (3.0f);
		if (rotation.x > DegToRad * (89.0f))
			rotation.x = DegToRad * (89.0f);
	}
	else if (input.ThumbRY < -16000 || CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x -= DegToRad * (3.0);
		if (rotation.x < DegToRad * (-30.0f))
			rotation.x = DegToRad * (-30.0f);
	}

	Player* player = FindGameObject<Player>();
	//position‚ÆlookTarget‚ðì‚é
	VECTOR pPos = player->Position();
	float pRotY = player->Rotation().y;
	position = VGet(0, 0, -400)
			* MGetRotX(rotation.x)*MGetRotY(rotation.y)
			+ pPos + VGet(0,150,0);
	lookTarget = VGet(0, 200, 0)
			* MGetRotX(rotation.x) * MGetRotY(rotation.y)
			+ pPos;
	StageObjManager* st = FindGameObject<StageObjManager>();
	if (st != nullptr) {
		// ‚±‚±‚ÅáŠQ•¨‚ª‚ ‚é‚©”»’è‚·‚é
		VECTOR hitPos;
		if (st->CollCheckLine(position, lookTarget, &hitPos)) {
			position = VNorm(lookTarget - hitPos)*100.0f + hitPos;
		}
	}
	SetCameraPositionAndTarget_UpVecY(position, lookTarget);
}

void Camera::Draw()
{
}

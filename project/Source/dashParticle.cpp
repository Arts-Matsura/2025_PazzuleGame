#include "dashParticle.h"
#include <DxLib.h>
#include <math.h>

namespace
{
	enum LINE_STATE {
		LINE_ST_DIR = 0,
		LINE_ST_MOVE,
	};

	const int LINE_MAX = 4000;	// パーティクルの最大数
	DashParticle::Line line[LINE_MAX];	// パーティクルの配列
}

static float ToDeg(float deg)
{
	return deg * (DX_PI_F / 180.0f);
}

void DashParticle::Init()
{
	for (int i = 0; i < LINE_MAX; i++) {
		line[i] = Line();
	}
}
	
void DashParticle::Release()
{
	for (int i = 0; i < LINE_MAX; i++) {
		line[i] = Line();
	}
}

void DashParticle::Update()
{
	for (int i = 0; i < LINE_MAX; i++) {
		if (line[i].activeTime <= 0) continue;

		line[i].activeTime -= (1.0f / 60.0f);

		switch (line[i].state) {
		case LINE_STATE::LINE_ST_DIR:
			DashParticle::UpdateDir(i);
			break;
		case LINE_STATE::LINE_ST_MOVE:
			DashParticle::UpdateMove(i);
			break;
		}
	}
}

void DashParticle::Draw()
{
	for (int i = 0; i < LINE_MAX; i++) {
		if (line[i].activeTime <= 0) continue;
		//if (line[i].state == LINE_STATE::LINE_ST_MOVE) continue;

		int param	= (line[i].color >> 24) & 0xFF;
		SetDrawBlendMode(DX_BLENDMODE_ADD, param * 2 + 16);

		int red		= (line[i].color >> 16) & 0xFF;
		int green	= (line[i].color >> 8)	& 0xFF;
		int blue	= line[i].color			& 0xFF;

		//float dir = (line[i].rotSpeed > 0) ? 1.57f : -1.57f;//+-90度回転する
		//float x1 = line[i].posX;
		//float y1 = line[i].posY;
		//float x2 = line[i].posX + (cosf(line[i].rot + dir) * line[i].width);
		//float y2 = line[i].posY + (sinf(line[i].rot + dir) * line[i].width);
		//DrawLineAA(x1, y1, x2, y2, GetColor(red, green, blue), line[i].height);
		Vector3 pos1 = line[i].transform.position;
		Vector3 pos2 = line[i].transform.position + (line[i].velocity.Normalize() * line[i].length);
		//DrawLine3D(pos1, pos2, GetColor(red, green, blue));
		DrawCapsule3D(pos1, pos2, 2.0f, 2, GetColor(red, green, blue), GetColor(red, green, blue), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int DashParticle::GetID()
{
	for (int i = 0; i < LINE_MAX; i++) {
		if (line[i].activeTime < 0) {
			return i;
		}
	}
	return 0;
}

int DashParticle::StartLine(const Transform& parent, float _activeTime)
{
	/* // 生成地点を求める
	* transform.rotation = XYランダム回転を求める
	* 回転移動量 = z+ベクトル * MGetRotX(回転量)
	* 今座標 = velocity + 親座標 + (回転移動量 * 親回転)
	*/
	Vector3 offset = Vector3(0.0f, 0.0f, 500.0f);

	int id = DashParticle::GetID();
	line[id].parent = parent;
	float randRot = (sinf(GetRand(RAND_MAX)) * DX_PI_F);
	line[id].parent.rotation = Vector3(parent.rotation.x, parent.rotation.y, randRot);
	line[id].rot = ToDeg(GetRand(10) - GetRand(10));
	line[id].rotSpeed = ToDeg(12.0f);
	line[id].rotScale = Vector3(sinf(GetRand(RAND_MAX)), 0.0f, cosf(GetRand(RAND_MAX))) * DX_TWO_PI_F;
	Vector3 rotated = offset * MGetRotX(line[id].rot);
	line[id].velocity = Vector3();
	line[id].transform.position = line[id].velocity + line[id].parent.position + (rotated * MGetRotationZXY(line[id].parent.rotation));
	line[id].activeTime = _activeTime;

	return id;
}

DashParticle::Line* DashParticle::GetLine(int id)
{
	return &line[id];
}

void DashParticle::UpdateDir(int i)
{
	line[i].rot += line[i].rotSpeed;	// 回転

	// 今座標を求める
	Vector3 offset = Vector3(0.0f, 0.0f, 50.0f) ;
	Vector3 rotated = offset * MGetRotationZXY(line[i].rotScale * line[i].rot);
	line[i].velocity = Vector3(0, 0, -1) * (MGetRotationZXY(line[i].parent.rotation));
	line[i].transform.position = line[i].velocity + line[i].parent.position + (rotated * MGetRotationZXY(line[i].parent.rotation));

	// 射出角度が決定した
	float random = ToDeg(90) - ToDeg(float(GetRand(30)));
	if (fabsf(line[i].rot) >= random) {
		line[i].state = LINE_STATE::LINE_ST_MOVE;

		Vector3 dir = Vector3(0, 0, -1) * MGetRotationZXY(line[i].parent.rotation);
		float leapSpeed = 15.0f + (fabsf(sinf(GetRand(RAND_MAX))) * 10.0f);
		Vector3 randRot = Vector3(fabsf(sinf(GetRand(RAND_MAX))), fabsf(sinf(GetRand(RAND_MAX))), 0.0f) * ToDeg(5.0f);
		line[i].velocity = (dir * leapSpeed) * MGetRotationZXY(randRot);
		line[i].transform.rotation += line[i].velocity;
		//float spd = 10.0f;
		//line[i].speedX = fabsf(sinf(line[i].rot)) * -spd;
		//line[i].speedY = cosf(line[i].rot) * spd;
		//if (line[i].rot < 0) {
		//	line[i].speedY *= -1;
		//}
	}
}

void DashParticle::UpdateMove(int i)
{
	// 移動する
	line[i].transform.position += line[i].velocity;

	// IntColorを1バイトごとに分解する (0～255)
	int param = (line[i].color >> 24) & 0xFF;
	if (param > 0) {
		int red = (line[i].color >> 16) & 0xFF;
		int green = (line[i].color >> 8) & 0xFF;
		int blue = line[i].color & 0xFF;

		// 色を変化させる
		param -= 6;
		int cl = 12;
		red += GetRand(cl);
		green += GetRand(cl);
		blue += GetRand(cl);

		// 分解したのを再構成する
		line[i].color = (max(0, param) << 24) | (min(255, red) << 16) | (min(255, green) << 8) | min(255, blue);
	}

	// 終了
	if (line[i].activeTime <= 0) {
		line[i].state = LINE_STATE::LINE_ST_DIR;
		line[i].color = 0x5a00ffff;
	}
}

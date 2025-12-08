#include "playScene.h"
#include "../Library/sceneManager.h"
#include <DxLib.h>
#include "Player.h"
#include "Ground.h"
#include "CsvReader.h"
#include "StageObj.h"
#include "StageObjManager.h"
#include "Light.h"
#include "Camera.h"
#include "Sky.h"
#include "SoundManager.h"

// 以降パーティクルプロジェクト追加分

#include "MeteorManager.h"
#include "dashParticle.h"
#include"Smoke.h"
#include "sparkle.h"
#include "sparksManager.h"
#include "Fire.h"

PlayScene::PlayScene()
{
	// regionを閉じて非表示にしよう。
	#pragma region //既存プロジェクト分

	SetCameraPositionAndTarget_UpVecY(VGet(0, 200, -300), VGet(0, 100, 0));
	
	Instantiate<Ground>();
	Instantiate<Light>();
	Camera* cam = Instantiate<Camera>();
	//SetDrawOrder(cam, -1000); // 最初にやる
	Instantiate<Sky>();
	Player* p = Instantiate<Player>();
	Instantiate<Fire>();

#if (false)
	Instantiate<StageObjManager>();

	CsvReader* csv = new CsvReader();
	csv->Load("data/Stage/Stage00.csv");
	for (int i = 0; i < csv->Lines(); i++) {
		std::string category = csv->Get(i, 0);
		if (category == "PLAYER") {
			Player* p = Instantiate<Player>();
			p->SetPosition(csv->GetFloat(i,2), csv->GetFloat(i,3), csv->GetFloat(i,4));
			p->SetRotation(csv->GetFloat(i, 5), csv->GetFloat(i, 6), csv->GetFloat(i, 7));
			p->SetScale(csv->GetFloat(i, 8), csv->GetFloat(i, 9), csv->GetFloat(i, 10));
		}
		else if (category == "CHARA") {
//			if (csv->GetInt(i, 1) == 2) {
//				Goblin* p = Instantiate<Goblin>();
//				p->SetPosition(csv->GetFloat(i, 2), csv->GetFloat(i, 3), csv->GetFloat(i, 4));
//				p->SetRotation(csv->GetFloat(i, 5), csv->GetFloat(i, 6), csv->GetFloat(i, 7));
//				p->SetScale(csv->GetFloat(i, 8), csv->GetFloat(i, 9), csv->GetFloat(i, 10));
//			} else {}
			Goblin* p = Instantiate<Goblin>();
			p->SetPosition(csv->GetFloat(i, 2), csv->GetFloat(i, 3), csv->GetFloat(i, 4));
			p->SetRotation(csv->GetFloat(i, 5), csv->GetFloat(i, 6), csv->GetFloat(i, 7));
			p->SetScale(csv->GetFloat(i, 8), csv->GetFloat(i, 9), csv->GetFloat(i, 10));
		}
		else if (category == "OBJ") {
			StageObj* obj = Instantiate<StageObj>();
			char s[20];
			sprintf_s<20>(s, "Stage_Obj%03d", csv->GetInt(i,1));
			obj->LoadModel(s);
			obj->SetPosition(csv->GetFloat(i, 2), csv->GetFloat(i, 3), csv->GetFloat(i, 4));
			obj->SetRotation(csv->GetFloat(i, 5), csv->GetFloat(i, 6), csv->GetFloat(i, 7));
			obj->SetScale(csv->GetFloat(i, 8), csv->GetFloat(i, 9), csv->GetFloat(i, 10));

		}
	}
#endif

	// シャドウマップを作る
	hShadow = MakeShadowMap(4096, 4096);
	// 影を出すライトを決める
	SetShadowMapLightDirection(hShadow, VGet(0.5f, -1.0f, 0));

	SoundManager::PlayBGM("../BGM/BGM_stg0.ogg");

	#pragma endregion

	Instantiate<MeteorManager>();
	Instantiate<DashParticleManager>();
	Instantiate<Smoke>();
	Instantiate<SparkleManager>();
	Instantiate<SparksManager>();

}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	VECTOR camPos = GetCameraPosition();
	// 影計算をするエリアの範囲
	float r = 2000.0f;
	SetShadowMapDrawArea(hShadow, 
		camPos+VGet(-r, -r, -r),
		camPos+VGet(r, r, r));

	ShadowMap_DrawSetup(hShadow);
	SceneBase::Draw(); // 影を求める
	ShadowMap_DrawEnd();

	SetUseShadowMap(0, hShadow);
	SceneBase::Draw();
	SetUseShadowMap(0, -1);

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));

	DrawFormatString(0, 40, GetColor(255, 255, 255), "FPS:%.1f", GetFPS());
}

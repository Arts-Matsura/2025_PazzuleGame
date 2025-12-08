#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <vector>
#include "../Library/time.h"

struct Menu {
	std::string text;
	std::string scene;
};
std::vector<Menu> menues = {
	{ "NEW GAME", "PlayScene"},
	{ "CONTINUE", "PlayScene"},
	{ "OPTION", "PlayScene"},
};

TitleScene::TitleScene()
{
	cursor = 0;
	hBack = LoadGraph("data/2D/TitleBack.png");
	hLogo = LoadGraph("data/2D/Swordbout_logo.png");
	hDemo = LoadGraph("data/2D/KeyConfigBack.png");
	mode = M_LOGO;
	timer = 1.0f;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	timer -= Time::DeltaTime();
	if (timer <= 0.0f) {
		mode = (Mode)(((int)mode+1)%(int)Mode::M_MAX);
		timer = (mode==M_LOGO)?1.0f : 5.0f;
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		mode = M_MENU;
		timer = 10.0f;
	}
	if (mode==Mode::M_MENU) {
		int c = GetCursorKey();
		if (c < 0) {
			cursor--;
			if (cursor<0)
				cursor = menues.size()-1;
		}
		if (c > 0) {
			cursor++;
			if (cursor >= menues.size() )
				cursor = 0;
		}
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			SceneManager::ChangeScene(menues[cursor].scene);
		}
		if (CheckHitKey(KEY_INPUT_P)) {
			SceneManager::ChangeScene("PlayScene");
		}
	}
	SceneBase::Update();
}

void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));

	switch (mode) {
	case M_LOGO:
		DrawGraph(0, 0, hBack, TRUE);
		DrawGraph(0, 0, hLogo, TRUE);
		break;
	case M_MENU:
		DrawGraph(0, 0, hBack, TRUE);
		DrawGraph(0, 0, hLogo, TRUE);
		menu();
		break;
	case M_DEMO:
		DrawGraph(0, 0, hDemo, TRUE);
		break;
	};
	SceneBase::Draw();
}

void TitleScene::menu() {
	static const unsigned int WHITE = GetColor(255,255,255);

	int font = SetFontSize(30);
	for (int i=0; i<menues.size(); i++) {
		int y = i*50+400;
		DrawString(450, y, menues[i].text.c_str(), WHITE);
		if (i==cursor) {
			DrawString(400, y, ">", WHITE);
		}
	}
	SetFontSize(font);
}

int TitleScene::GetCursorKey()
{
	int ret = 0;
	if (CheckHitKey(KEY_INPUT_W)) {
		ret = -1;
	} else if (CheckHitKey(KEY_INPUT_S)) {
		ret = 1;
	} else {
		repeatCount = 0;
	}
	if (ret == 0)
		return 0;
	repeatCount++;
	if (repeatCount==1 || (
		repeatCount>=20 && (repeatCount-20)%8==0)) {
		return ret;
	}
	return 0;
}

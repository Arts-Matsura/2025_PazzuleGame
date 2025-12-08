#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <vector>
#include "../Library/time.h"
#include "GameMain.h"


TitleScene::TitleScene()
{
	new GameMain();//CoGƒo[ƒWƒ‡ƒ“‚ªˆá‚¤(4.1ˆÈã)
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	
	SceneBase::Update();
}

void TitleScene::Draw()
{
	DrawString(0, 0, "Title Scene", GetColor(255, 255, 255));	
	SceneBase::Draw();
}


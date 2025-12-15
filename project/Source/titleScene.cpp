#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <vector>
#include "../Library/time.h"
#include "GameMain.h"


TitleScene::TitleScene()
{
	new GameMain();
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
	
	SceneBase::Draw();
}


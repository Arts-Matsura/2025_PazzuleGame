#include "GameMain.h"
#include "TileManager.h"
#include "control.h"

GameMain::GameMain()
{
	// ここでマネジャー生成
	TileManager* tileManager = new TileManager();
	Control* control = new Control();

	// 初期化
	control->OnInputEvent += [tileManager](Vector2 dir) { tileManager->OnInputTile(dir); };
}

GameMain::~GameMain()
{
}

void GameMain::Update()
{
}

void GameMain::Draw()
{
}

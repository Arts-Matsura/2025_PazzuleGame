#include "GameMain.h"
#include "TileManager.h"

GameMain::GameMain()
{
	// ここでマネジャー生成
	new TileManager();
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

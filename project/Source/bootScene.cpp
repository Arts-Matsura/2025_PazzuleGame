#include "bootScene.h"
#include "../Library/sceneManager.h"
#include "ManagerController.h"

BootScene::BootScene()
{
	//new ManagerController();
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TitleScene"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}

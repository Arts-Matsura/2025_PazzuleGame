#include "ManagerController.h"
#include "SoundManager.h"

ManagerController::ManagerController(SceneBase* scene) : GameObject(scene)
{
	SoundManager::Init();
}

ManagerController::~ManagerController()
{
	SoundManager::Release();
}

void ManagerController::Update()
{
	SoundManager::Update();
}

void ManagerController::Draw()
{
	SoundManager::Draw();
}

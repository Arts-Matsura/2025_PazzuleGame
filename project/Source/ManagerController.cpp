#include "ManagerController.h"
#include "SoundManager.h"

ManagerController::ManagerController()
{
	this->DontDestroyOnSceneChange();
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

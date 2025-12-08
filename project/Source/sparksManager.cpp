#include "sparksManager.h"
#include "../Library/time.h"

#include "sparks.h"

SparksManager::SparksManager()
{
	spawnTime = 3.0f;
}

SparksManager::~SparksManager()
{

}

void SparksManager::Update()
{
	spawnTime -= Time::DeltaTime();
	if (spawnTime <= 0)
	{
		int random = GetRand(5) + 3;
		for (int i = 0; i < random; i++)
		{
			Instantiate<Sparks>();
		}
		spawnTime = 3.0f;
	}


}

void SparksManager::Draw()
{

}

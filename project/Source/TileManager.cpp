#include "TileManager.h"

TileManager::TileManager()
{
	CreateTiles(4, 4);
}

TileManager::~TileManager()
{
	DeleteTiles();
}

void TileManager::Update()
{
}

void TileManager::Draw()
{
	int test = 0;
	for(int h = 0; h < tile_list.size(); h++)
	{
		for(int w = 0; w < tile_list[h].size(); w++)
		{
			tile_list[h][w]->Draw();
		}
	}
}

void TileManager::CreateTiles(int height, int width)
{
	tile_list.resize(height);
	for (int h = 0; h < height; h++)
	{
		tile_list[h].resize(width);
	}

	int id = 0;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			Tile* p = new Tile(id);
			p->SetTile(Vector2I(w, h), 100.0f);
			tile_list[h][w] = p;

			id++;
		}
	}

	// ÅŒã‚Ìƒ^ƒCƒ‹‚ð”ñ•\Ž¦‚É‚·‚é
	tile_list[height - 1][width - 1]->transform.SetActive(false);
}

void TileManager::DeleteTiles()
{
	for (int h = 0; h < tile_list.size(); h++)
	{
		for (int w = 0; w < tile_list[h].size(); w++)
		{
			delete tile_list[h][w];
		}
		tile_list[h].clear();
	}
	tile_list.clear();
}

void TileManager::OnInputTile(const Vector2I& dir)
{
}

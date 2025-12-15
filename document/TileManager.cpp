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

	// 最後のタイルを非表示にする
	air_tile = tile_list[height - 1][width - 1];
	air_tile->transform.SetActive(false);
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

void TileManager::OnInputTile(Vector2I dir)
{
	if (!air_tile) { return; }

	int height = static_cast<int>(tile_list.size());
	if (height == 0) { return; }
	int width = static_cast<int>(tile_list[0].size());

	// 現在の空タイル位置を保存
	Vector2I air_pos = air_tile->delta;
	int target_y = air_pos.y - dir.y;
	int target_x = air_pos.x - dir.x;

	// 範囲チェック
	if (target_y < 0 || target_y >= height || target_x < 0 || target_x >= width)
	{
		return;
	}

	DebugLog("MOVE!_" + std::to_string(dir.x) + "," + std::to_string(dir.y));

	// 交換対象を取得（位置は保存しておく)
	Tile* target_tile = tile_list[target_y][target_x];
	Vector2I target_pos = target_tile->delta;

	// タイルの位置情報(delta と transform.position) を入れ替える
	// 位置の更新は保存した座標を使い、後で配列自体も入れ替える
	target_tile->SetTile(air_pos, 100.0f);
	air_tile->SetTile(target_pos, 100.0f);

	// 配列内のポインタを入れ替える（保存した air_pos, target_* を使用)
	std::swap(tile_list[air_pos.y][air_pos.x], tile_list[target_y][target_x]);
}

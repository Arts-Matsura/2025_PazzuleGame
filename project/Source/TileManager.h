#pragma once
#include "../Library/gameObject.h"
#include "Tile.h"
#include <vector>

class TileManager : public GameObject
{
public:
	TileManager();
	~TileManager();

	void Update() override;
	void Draw() override;

	void CreateTiles(int height, int width);
	void DeleteTiles();

	void OnInputTile(const Vector2I& dir);

private:
	std::vector<std::vector<Tile*>> tile_list;
};
#pragma once
#include"Transform.h"
#include"../Library/gameObject.h"

class Tile
{
public:
	Tile();
	Tile(int _id);
	~Tile();

	void Draw();

	void SetTile(const Vector2I& _delta, float tileSize);

//private:

	int id;
	Vector2I delta;
	Transform transform;

};
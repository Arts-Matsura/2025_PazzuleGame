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
	void setTile(Vector2I _delta);
	int id;
	Vector2I delta;
	Transform transform;

};
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

	Transform transform;
	Vector2I delta;	//¡‚Ìƒ}ƒX–Ú
	int id;			//©•ª‚Ì”Ô†

};
#include "TIle.h"
#include "Renderer2D.h"

Tile::Tile() : Tile(0)
{
}

Tile::Tile(int _id)
{
	id = _id;
}

Tile::~Tile()
{
}

void Tile::SetTile(const Vector2I& _delta, float tileSize)
{
	delta = _delta;
	transform.position = Vector3(_delta.x, _delta.y, 0.0f) * tileSize;
	//transform.scale = Vector3(tileSize, tileSize, 1.0f) / 2.0f;
}

void Tile::Draw()
{
	Vector2 pos = Vector2(transform.position + transform.scale);
	Renderer::Text(pos, Color::White(), std::to_string(id));
}

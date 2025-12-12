#pragma once
#include"../Library/gameObject.h"
#include "ActionEvent.h"

/// <summary>
/// タイル操作
/// </summary>
class Control : public GameObject
{
public:
	Control();
	~Control();

	void Update()override;
	void Draw()override;

	ActionEvent<Vector2I> OnInputEvent;	// 入力イベント

private:
	void UpdateInput();
	void OnKeyPush(Vector2I dir);


	Vector2I currentKey;	// 今のキー入力
	bool prevPushed;	// 前回の押下状態
};
#include "control.h"

Control::Control()
{
	prevPushed = false;
	OnInputEvent += [this](Vector2I dir) { OnKeyPush(dir); };
}

Control::~Control()
{
}

void Control::Update()
{
	UpdateInput();
}

void Control::Draw()
{
}

void Control::UpdateInput()
{
	// キー入力の更新 (ななめ入力が許可されているので注意)
	currentKey.y = CheckHitKey(KEY_INPUT_DOWN) - CheckHitKey(KEY_INPUT_UP);
	currentKey.x = CheckHitKey(KEY_INPUT_RIGHT) - CheckHitKey(KEY_INPUT_LEFT);

	// 押されているか判定
	if (currentKey.x != 0 || currentKey.y != 0)
	{		
		// 押された瞬間の処理
		if (!prevPushed)
		{
			OnInputEvent.Invoke(currentKey);
		}

		prevPushed = true;
	}
	else
	{
		prevPushed = false;
	}
}

void Control::OnKeyPush(Vector2I dir)
{
	//キーが押されたときの処理
	DebugLog("キーが押されたよ! ");
}

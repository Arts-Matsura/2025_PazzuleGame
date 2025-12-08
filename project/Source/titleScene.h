#pragma once
#include "../Library/sceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	int cursor;
	int repeatCount;
	int GetCursorKey();
	void menu();

	enum Mode {
		M_LOGO,
		M_MENU,
		M_DEMO,
		M_MAX
	};
	Mode mode;
	float timer;

	int hBack;
	int hLogo;
	int hDemo;
};
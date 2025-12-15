#pragma once
#include "../Library/gameObject.h"

// WASD 入力だけを管理するクラス
class Control : public GameObject
{
public:
    Control();
    ~Control();

    void Update() override;
    void Draw() override;

    // 取得（-1 / 0 / +1）
    int GetHorizontal() const { return h; }  // A=-1 / D=+1
    int GetVertical()   const { return v; }  // W=-1 / S=+1

private:
    int h = 0;  // 左右入力
    int v = 0;  // 上下入力
};
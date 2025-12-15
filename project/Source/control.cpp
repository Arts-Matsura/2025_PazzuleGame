#include "Control.h"

Control::Control() {}
Control::~Control() {}

void Control::Update()
{
    h = 0;
    v = 0;

    // ç∂âE
    if (CheckHitKey(KEY_INPUT_A)) h = -1;
    if (CheckHitKey(KEY_INPUT_D)) h = +1;

    // è„â∫
    if (CheckHitKey(KEY_INPUT_W)) v = -1;
    if (CheckHitKey(KEY_INPUT_S)) v = +1;
}

void Control::Draw()
{
    // ï`âÊÇÕïsóv
}
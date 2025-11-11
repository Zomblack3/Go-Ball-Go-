#include "buttons.h"

namespace GoBallGo
{
    Button initButton(float x, float y, float w, float h, bool isPressed)
    {
        Button newButton = { };

        newButton.x = x;
        newButton.y = y;
        newButton.w = w;
        newButton.h = h;
        newButton.isPressed = isPressed;

        return newButton;
    }
}

#pragma once

#include "raylib.h"

namespace GoBallGo
{
	struct Button
	{
		float x;
		float y;
		float w;
		float h;

		bool isPressed;
	};

	Button initButton(float x, float y, float w, float h, bool isPressed);

	const int BUTTONS_WIDTH = 200;
	const int BUTTONS_HEIGHT = 50;
}
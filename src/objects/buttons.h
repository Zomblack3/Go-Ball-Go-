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

		Texture2D texture = { };

		Color buttonTint = WHITE;
		Color textColor = WHITE;

		bool isPressed;
	};

	Button initButton(float x, float y, float w, float h, bool isPressed);

	const int BUTTONS_WIDTH = 192;
	const int BUTTONS_HEIGHT = 64;
}
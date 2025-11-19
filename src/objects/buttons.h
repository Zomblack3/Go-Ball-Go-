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

		int soundTimesPlayed = 0;

		Texture2D texture = { };

		Sound changeStateSound = { };

		Color buttonTint = WHITE;
		Color textColor = WHITE;

		bool isPressed;
	};

	Button initButton(float x, float y, float w, float h, bool isPressed);

	const int BUTTONS_WIDTH = 192;
	const int BUTTONS_HEIGHT = 64;
}
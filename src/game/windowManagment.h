#pragma once

#include "raylib.h"

#include "objects/buttons.h"

enum SCREENS
{
	MENU,
	GAMEPLAY,
	CREDITS,
	EXIT
};

namespace GoBallGo
{
	void mouseClick(Vector2& mouse);
	void mouseSelection(Vector2 mousePos, Button& button);
	bool isMouseInButton(Vector2 mousePos, Button button);

	const int screenWidth = 1024;
	const int screenHeight = 768;

	const int titlesFontSize = 40;
	const int normalFontSize = 20;
}
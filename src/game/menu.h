#pragma once

#include "raylib.h"

#include "windowManagment.h"

namespace GoBallGo
{
	void menu(SCREENS& currentScreen);
}

namespace MenuStructure
{
	void update(SCREENS& currentScreen, Vector2& Mouse, GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton);
	void draw(GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton);
}
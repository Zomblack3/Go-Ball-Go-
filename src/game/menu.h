#pragma once

#include "raylib.h"

#include "windowManagment.h"

namespace GoBallGo
{
	void menu(SCREENS& currentScreen, Sound& music, bool& isMusicOn, bool& wasMusicOn);
}

namespace MenuStructure
{
	void update(SCREENS& currentScreen, Vector2& Mouse, GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D buttonOn, Texture2D buttonOff, bool& isMusicOn, bool& wasMusicOn);
	void draw(GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D background, Texture2D logo);
}
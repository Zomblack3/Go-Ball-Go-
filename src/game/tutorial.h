#pragma once

#include "windowManagment.h"

namespace GoBallGo
{
	void tutorial(SCREENS& currentScreen, Sound& music, bool isMusicOn);
}

namespace TutorialStructure
{
	void update(Vector2& mouse, GoBallGo::Button& exitButton);
	void draw(GoBallGo::Button exitButton, Texture2D backrgound, Texture2D player);
}
#pragma once

#include "windowManagment.h"

namespace GoBallGo
{
	void credits(SCREENS& currentScreen);
}

namespace CreditsStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& exitButton);
	void draw(GoBallGo::Button exitButton);
}
#pragma once

#include <iostream>

#include "windowManagment.h"

namespace GoBallGo
{
	void credits(SCREENS& currentScreen, Sound& music, bool isMusicOn);
}

namespace CreditsStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& exitButton);
	void draw(GoBallGo::Button exitButton, Texture2D background);
	void setTextsPos(Vector2 textPos[], int amountOfTexts, float startingX, float startingY, std::string texts[]);

	int getBiggerText(std::string texts[], int amountOfTexts); // Gets the index of the longest text
}
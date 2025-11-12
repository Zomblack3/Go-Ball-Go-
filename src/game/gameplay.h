#pragma once

#include "windowManagment.h"
#include "objects/player.h"
#include "objects/wall.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen);

	const float G_FORCE = 98.0f;
}

namespace GameplayStructure
{
	void selectGameMode(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Button gameModeButtonSingleplayer, GoBallGo::Button gameModeButtonMultiplayer, Vector2& mouse);
	void update(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround);
	void draw(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround);
}
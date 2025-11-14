#pragma once

#include "windowManagment.h"
#include "objects/player.h"
#include "objects/wall.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen, bool& isMusicOn, bool& wasMusicOn);

	const float G_FORCE = 0.5f;
}

namespace GameplayStructure
{
	void selectGameMode(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Button gameModeButtonSingleplayer, GoBallGo::Button gameModeButtonMultiplayer, Vector2& mouse);
	void update(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, bool& isMusicOn, bool& wasMusicOn);
	void draw(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround);
}
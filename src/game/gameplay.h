#pragma once

#include "windowManagment.h"
#include "objects/player.h"
#include "objects/wall.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen, bool& isMusicOn, bool& wasMusicOn, bool& isGameplayMusicOn);

	const float G_FORCE = 0.000001f;
}

namespace GameplayStructure
{
	void selectGameMode(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Button gameModeButtonSingleplayer, GoBallGo::Button gameModeButtonMultiplayer, Vector2& mouse);
	
	void update(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, int& lastWallPassed, Sound jumpSound, Sound scoreSound, Sound deathSound, bool& isPauseOn, GoBallGo::Button& resumeGameplayButton, GoBallGo::Button& returnMenuGameplayButton, Vector2& mouse, bool& hasStarted);
	void draw(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, bool& isPauseOn, GoBallGo::Button resumeGameplayButton, GoBallGo::Button returnMenuGameplayButton, bool hasStarted, Texture2D scoreboard);
	
	bool arePlayersDead(GoBallGo::Player player, GoBallGo::Player player2);
	
	void endGameScreen(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Vector2& mouse, bool& isMusicOn, bool& wasMusicOn);
}
#include "gameplay.h"

#include <iostream>

#include "windowManagment.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen, bool& isMusicOn, bool& wasMusicOn, bool& isGameplayMusicOn)
	{
		Player player = initPlayer();
		Player player2 = initPlayer();

		Wall wall[MAX_WALLS_IN_SCREEN] = {};

		Vector2 mouse = { };

		Button gameModeButtonSingleplayer = initButton(screenWidth / 2.0f, screenHeight / 3.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button gameModeButtonMultiplayer = initButton(screenWidth / 2.0f, screenHeight / 2.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);

		Button resumeGameplayButton = initButton(screenWidth / 2.0f, screenHeight / 3.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button returnMenuButton = initButton(screenWidth / 2.0f, (screenHeight / 2.0f) - 50, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);

		gameModeButtonSingleplayer.x -= gameModeButtonSingleplayer.w / 2.0f;
		gameModeButtonMultiplayer.x -= gameModeButtonMultiplayer.w / 2.0f;

		resumeGameplayButton.x -= resumeGameplayButton.w / 2.0f;
		returnMenuButton.x -= returnMenuButton.w / 2.0f;

		Texture2D backGround = LoadTexture("res/img/back_ground.png");
		Texture2D midGround = LoadTexture("res/img/mid_ground.png");
		Texture2D foreGround = LoadTexture("res/img/fore_ground.png");

		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");

		Texture2D scoreboardTexture = LoadTexture("res/img/gameplay_scoreboard.png");

		Sound music = LoadSound("res/audio/gameplay_music.mp3");
		Sound jumpSound = LoadSound("res/audio/player_jumping.wav");
		Sound scoreSound = LoadSound("res/audio/score.wav");
		Sound buttonsChangeStateSound = LoadSound("res/audio/button_sound.wav");
		Sound deathSound = LoadSound("res/audio/death_sound.mp3");
		Sound endGameSound = LoadSound("res/audio/end_game_sound.wav");

		player.texture = LoadTexture("res/img/player.png");
		player2.texture = LoadTexture("res/img/player.png");

		gameModeButtonSingleplayer.texture = buttonsTexture;
		gameModeButtonMultiplayer.texture = buttonsTexture;

		resumeGameplayButton.texture = buttonsTexture;
		returnMenuButton.texture = buttonsTexture;

		gameModeButtonSingleplayer.changeStateSound = buttonsChangeStateSound;
		gameModeButtonMultiplayer.changeStateSound = buttonsChangeStateSound;

		resumeGameplayButton.changeStateSound = buttonsChangeStateSound;
		returnMenuButton.changeStateSound = buttonsChangeStateSound;

		int lastWallPassed = 0;

		bool isPauseOn = false;
		bool gameplayHasStarted = false;

		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
			wall[i] = initWall();

		GameplayStructure::selectGameMode(player, player2, gameModeButtonSingleplayer, gameModeButtonMultiplayer, mouse);

		while (!WindowShouldClose() && !GameplayStructure::arePlayersDead(player, player2) && !returnMenuButton.isPressed)
		{
			if (!IsSoundPlaying(music) && isGameplayMusicOn)
				PlaySound(music);

			GameplayStructure::update(player, player2, wall, backGround, midGround, foreGround, lastWallPassed, jumpSound, scoreSound, deathSound, isPauseOn, resumeGameplayButton, returnMenuButton, mouse, gameplayHasStarted);

			GameplayStructure::draw(player, player2, wall, backGround, midGround, foreGround, isPauseOn, resumeGameplayButton, returnMenuButton, gameplayHasStarted, scoreboardTexture);
		}

		if (IsSoundPlaying(music))
			PauseSound(music);

		if (IsSoundPlaying(jumpSound))
			PauseSound(jumpSound);

		if (IsSoundPlaying(scoreSound))
			PauseSound(scoreSound);

		if (returnMenuButton.isPressed)
			currentScreen = MENU;
		else
		{
			PlaySound(endGameSound);

			GameplayStructure::endGameScreen(currentScreen, player, player2, wall, mouse, isMusicOn, wasMusicOn);
		}

		returnMenuButton.isPressed = false;
		resumeGameplayButton.isPressed = false;

		UnloadTexture(backGround);
		UnloadTexture(midGround);
		UnloadTexture(foreGround);
		UnloadTexture(player.texture);
		UnloadTexture(player2.texture);
		
		UnloadSound(jumpSound);
		UnloadSound(music);
		UnloadSound(scoreSound);
		UnloadSound(buttonsChangeStateSound);
		UnloadSound(deathSound);
		UnloadSound(endGameSound);

		player.isActive = false;
		player.isAlive = true;

		player2.isActive = false;
		player2.isAlive = true;
	}
}

namespace GameplayStructure
{
	static float scrollingBack = 0.0f;
	static float scrollingMid = 0.0f;
	static float scrollingFore = 0.0f;

	void selectGameMode(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Button gameModeButtonSingleplayer, GoBallGo::Button gameModeButtonMultiplayer, Vector2& mouse)
	{
		const int buttonsAmount = 2;

		Texture2D background = LoadTexture("res/img/gameModeSelectionBackground.png");

		std::string buttonsTexts[buttonsAmount] = { "SINGLEPLAYER", "MULTIPLAYER" };

		int buttonsTextsLenghts[buttonsAmount] = { };

		for (int i = 0; i < buttonsAmount; i++)
			buttonsTextsLenghts[i] = MeasureText(buttonsTexts[i].c_str(), GoBallGo::normalFontSize);

		while (!WindowShouldClose() && !gameModeButtonSingleplayer.isPressed && !gameModeButtonMultiplayer.isPressed)
		{
			mouse = GetMousePosition();

			GoBallGo::mouseSelection(mouse, gameModeButtonSingleplayer);
			GoBallGo::mouseSelection(mouse, gameModeButtonMultiplayer);

			if (gameModeButtonSingleplayer.isPressed)
				player.isActive = true;

			if (gameModeButtonMultiplayer.isPressed)
			{
				player.isActive = true;
				player2.isActive = true;
			}

			BeginDrawing();

			ClearBackground(DARKGREEN);

			DrawTexture(background, 0, 0, WHITE);

			DrawTexture(gameModeButtonSingleplayer.texture, static_cast<int>(gameModeButtonSingleplayer.x), static_cast<int>(gameModeButtonSingleplayer.y), gameModeButtonSingleplayer.buttonTint);
			DrawTexture(gameModeButtonMultiplayer.texture, static_cast<int>(gameModeButtonMultiplayer.x), static_cast<int>(gameModeButtonMultiplayer.y), gameModeButtonMultiplayer.buttonTint);

			DrawText(buttonsTexts[0].c_str(), static_cast<int>((gameModeButtonSingleplayer.x + gameModeButtonSingleplayer.w / 2.0f) - (buttonsTextsLenghts[0] / 2.0f)), static_cast<int>(gameModeButtonSingleplayer.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, gameModeButtonSingleplayer.textColor);
			DrawText(buttonsTexts[1].c_str(), static_cast<int>((gameModeButtonMultiplayer.x + gameModeButtonMultiplayer.w / 2.0f) - (buttonsTextsLenghts[1] / 2.0f)), static_cast<int>(gameModeButtonMultiplayer.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, gameModeButtonMultiplayer.textColor);

			EndDrawing();
		}
	}

	void update(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, int& lastWallPassed, Sound jumpSound, Sound scoreSound, Sound deathSound, bool& isPauseOn, GoBallGo::Button& resumeGameplayButton, GoBallGo::Button& returnMenuButton, Vector2& mouse, bool& gameplayHasStarted)
	{
		const float scrollingBackSpeed = 50.0f;
		const float scrollingMidSpeed = 50.0f;
		const float scrollingForeSpeed = 250.0f;

		if (!isPauseOn)
		{
			if (gameplayHasStarted)
			{
				scrollingBack -= scrollingBackSpeed * GetFrameTime();
				scrollingMid -= scrollingMidSpeed * GetFrameTime();
				scrollingFore -= scrollingForeSpeed * GetFrameTime();

				if (scrollingBack <= -backGround.width * 2)
					scrollingBack = 0;
				if (scrollingMid <= -midGround.width * 2)
					scrollingMid = 0;
				if (scrollingFore <= -foreGround.width * 2)
					scrollingFore = 0;

				GoBallGo::playerMovment(player, player2, jumpSound);

				GoBallGo::playerScreenCollision(player);

				if (player2.isActive)
					GoBallGo::playerScreenCollision(player2);

				GoBallGo::wallUpdate(wall, lastWallPassed);

				for (int i = 0; i < GoBallGo::MAX_WALLS_IN_SCREEN; i++)
				{
					GoBallGo::wallPlayerCollision(wall[i], player, deathSound);
					GoBallGo::wallPlayerCollision(wall[i], player2, deathSound);
				}

				if (player.isActive && player.isAlive)
					GoBallGo::wallPlayerHasPass(wall, player, lastWallPassed, scoreSound);

				if (player2.isActive && player2.isAlive)
					GoBallGo::wallPlayerHasPass(wall, player2, lastWallPassed, scoreSound);

				if (IsKeyPressed(KEY_P))
					isPauseOn = true;
			}
			else
			{
				if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W))
					gameplayHasStarted = true;
			}
		}
		else
		{
			mouse = GetMousePosition();

			GoBallGo::mouseSelection(mouse, resumeGameplayButton);
			GoBallGo::mouseSelection(mouse, returnMenuButton);

			if (resumeGameplayButton.isPressed)
			{
				isPauseOn = false;

				resumeGameplayButton.isPressed = false;
			}
		}

	}

	void draw(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, bool& isPauseOn, GoBallGo::Button resumeGameplayButton, GoBallGo::Button returnMenuButton, bool gameplayHasStarted, Texture2D scoreboard)
	{
		// Variables ///////////////////////////////////////////////////////////////////////////////////////////////////

		/* Parallax */
		const float texturesScale = 2.0f;

		Vector2 backGroundPos1 = { scrollingBack, -325 };
		Vector2 backGroundPos2 = { backGround.width * 2 + scrollingBack, -325 };

		Vector2 midGroundPos1 = { scrollingMid, 445 };
		Vector2 midGroundPos2 = { midGround.width * 2 + scrollingMid, 445 };

		Vector2 foreGroundPos1 = { scrollingFore, 70 };
		Vector2 foreGroundPos2 = { foreGround.width * 2 + scrollingFore, 70 };
		/* Parallax */

		/* Scoreboard */
		std::string startingText = "Press SPACE / W to start";
		std::string playerOnePoints = TextFormat("%i", player.points);
		std::string playerTwoPoints = TextFormat("%i", player2.points);

		const int pointTextSize = 30;

		Vector2 playerOnePos1 = { (GoBallGo::screenWidth / 2.0f) - (MeasureText(playerOnePoints.c_str(), pointTextSize) / 2.0f), 100 };
		Vector2 playerOnePos2 = { (GoBallGo::screenWidth / 4.0f) - (MeasureText(playerOnePoints.c_str(), pointTextSize) / 2.0f), 100 };
		Vector2 playerTwoPos = { (GoBallGo::screenWidth / 2.0f + GoBallGo::screenWidth / 4.0f) - (MeasureText(playerTwoPoints.c_str(), pointTextSize) / 2.0f), 100 };

		Vector2 scoreboardPosOne = { static_cast<float>((GoBallGo::screenWidth / 2) - (scoreboard.width / 2)), 90.0f };
		Vector2 scoreboardPosTwo = { (GoBallGo::screenWidth / 4.0f) - (scoreboard.width / 2.0f), 90.0f };
		Vector2 scoreboardPosThree = { (GoBallGo::screenWidth / 2.0f + GoBallGo::screenWidth / 4.0f) - (scoreboard.width / 2.0f), 90.0f };
		/* Scoreboard */

		/* Starting Text */
		const int startingTextLenght = MeasureText(startingText.c_str(), GoBallGo::titlesFontSize);
		const int startingTextPosX = static_cast<int>((GoBallGo::screenWidth / 2.0f) - (startingTextLenght / 2.0f));
		const int startingTextPosY = GoBallGo::screenHeight / 2;

		Rectangle startingRec = { };

		startingRec.x = static_cast<float>((GoBallGo::screenWidth / 2) - (startingTextLenght + 20) / 2);
		startingRec.y = static_cast<float>((GoBallGo::screenHeight / 2) - 15);
		startingRec.width = static_cast<float>(startingTextLenght + 20);
		startingRec.height = static_cast<float>(GoBallGo::titlesFontSize + 20);
		/* Starting Text */

		/* Pause */
		std::string pauseText = "PAUSE";

		const int pauseTextLenght = MeasureText("PAUSE", GoBallGo::titlesFontSize);

		Vector2 pausePos = { (GoBallGo::screenWidth / 2.0f) - (pauseTextLenght / 2.0f), resumeGameplayButton.y + GoBallGo::titlesFontSize + 85.0f };

		Rectangle pauseRec = { };

		pauseRec.x = static_cast<float>((GoBallGo::screenWidth / 2) - ((GoBallGo::BUTTONS_WIDTH + 25) / 2));
		pauseRec.y = resumeGameplayButton.y + GoBallGo::normalFontSize - 100.0f;
		pauseRec.width = GoBallGo::BUTTONS_WIDTH + 25;
		pauseRec.height = GoBallGo::BUTTONS_HEIGHT * 4;

		std::string resumeText = "RESUME";
		std::string goToMenuText = "GO TO MENU";

		const int resumeTextLenght = MeasureText("RESUME", GoBallGo::normalFontSize);
		const int goToMenuTextLenght = MeasureText("GO TO MENU", GoBallGo::normalFontSize);

		Vector2 resumePos = { (resumeGameplayButton.x + resumeGameplayButton.w / 2.0f) - (resumeTextLenght / 2.0f), resumeGameplayButton.y + GoBallGo::normalFontSize - 5.0f };
		Vector2 goToMenuPos = { (returnMenuButton.x + returnMenuButton.w / 2.0f) - (goToMenuTextLenght / 2.0f), returnMenuButton.y + GoBallGo::normalFontSize - 5.0f };
		/* Pause */

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Draw ////////////////////////////////////////////////////////////////////////////////////////////////////////
		BeginDrawing();

		ClearBackground(DARKGREEN);

		DrawTextureEx(backGround, backGroundPos1, 0.0f, texturesScale, WHITE);
		DrawTextureEx(backGround, backGroundPos2, 0.0f, texturesScale, WHITE);

		DrawTextureEx(midGround, midGroundPos1, 0.0f, texturesScale, WHITE);
		DrawTextureEx(midGround, midGroundPos2, 0.0f, texturesScale, WHITE);

		DrawTextureEx(foreGround, foreGroundPos1, 0.0f, texturesScale, WHITE);
		DrawTextureEx(foreGround, foreGroundPos2, 0.0f, texturesScale, WHITE);

		if (player.isActive && player.isAlive)
			DrawTexture(player.texture, static_cast<int>(player.x), static_cast<int>(player.y), WHITE);

		if (player2.isActive && player2.isAlive)
			DrawTexture(player2.texture, static_cast<int>(player2.x), static_cast<int>(player2.y), RED);
		
		if (!gameplayHasStarted)
		{
			DrawRectangleRec(startingRec, DARKBLUE);
			DrawText(startingText.c_str(), startingTextPosX, startingTextPosY, GoBallGo::titlesFontSize, YELLOW);
		}

		if (player.isActive && !player2.isActive)
		{
			DrawTexture(scoreboard, static_cast<int>(scoreboardPosOne.x), static_cast<int>(scoreboardPosOne.y), WHITE);

			DrawText(playerOnePoints.c_str(), static_cast<int>(playerOnePos1.x), static_cast<int>(playerOnePos1.y), pointTextSize, YELLOW);
		}
		else
		{
			DrawTexture(scoreboard, static_cast<int>(scoreboardPosTwo.x), static_cast<int>(scoreboardPosTwo.y), WHITE);
			DrawTexture(scoreboard, static_cast<int>(scoreboardPosThree.x), static_cast<int>(scoreboardPosThree.y), WHITE);

			DrawText(playerOnePoints.c_str(), static_cast<int>(playerOnePos2.x), static_cast<int>(playerOnePos2.y), pointTextSize, YELLOW);
			DrawText(playerTwoPoints.c_str(), static_cast<int>(playerTwoPos.x), static_cast<int>(playerTwoPos.y), pointTextSize, YELLOW);
		}

		drawWall(wall);

		if (isPauseOn)
		{
			DrawRectangleRec(pauseRec, DARKBLUE);

			DrawText(pauseText.c_str(), static_cast<int>(pausePos.x), static_cast<int>(pausePos.y), GoBallGo::titlesFontSize, YELLOW);

			DrawTexture(resumeGameplayButton.texture, static_cast<int>(resumeGameplayButton.x), static_cast<int>(resumeGameplayButton.y), resumeGameplayButton.buttonTint);
			DrawTexture(returnMenuButton.texture, static_cast<int>(returnMenuButton.x), static_cast<int>(returnMenuButton.y), returnMenuButton.buttonTint);

			DrawText(resumeText.c_str(), static_cast<int>(resumePos.x), static_cast<int>(resumePos.y), GoBallGo::normalFontSize, resumeGameplayButton.textColor);
			DrawText(goToMenuText.c_str(), static_cast<int>(goToMenuPos.x), static_cast<int>(goToMenuPos.y), GoBallGo::normalFontSize, returnMenuButton.textColor);
		}

		EndDrawing();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	bool arePlayersDead(GoBallGo::Player player, GoBallGo::Player player2)
	{
		if (player.isActive && player2.isActive)
		{
			if (!player.isAlive && !player2.isAlive)
				return true;
		}
		else 
		{
			if (!player.isAlive)
				return true;
		}

		return false;
	}

	void endGameScreen(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Vector2& mouse, bool& isMusicOn, bool& wasMusicOn)
	{
		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");
		Texture2D backgroundOnePlayer = LoadTexture("res/img/endGameOnePlayerBackground.png");
		Texture2D backgroundTwoPlayers = LoadTexture("res/img/endGameTwoPlayersBackground.png");

		GoBallGo::Button replayButton = GoBallGo::initButton(((GoBallGo::screenWidth / 2.0f) - (GoBallGo::screenWidth / 4.0f)) - (GoBallGo::BUTTONS_WIDTH / 2.0f), GoBallGo::screenHeight - (GoBallGo::screenHeight / 8.0f), GoBallGo::BUTTONS_WIDTH, GoBallGo::BUTTONS_HEIGHT, false);
		GoBallGo::Button exitButton = GoBallGo::initButton(((GoBallGo::screenWidth / 2.0f) + (GoBallGo::screenWidth / 4.0f)) - (GoBallGo::BUTTONS_WIDTH / 2.0f), GoBallGo::screenHeight - (GoBallGo::screenHeight / 8.0f), GoBallGo::BUTTONS_WIDTH, GoBallGo::BUTTONS_HEIGHT, false);

		while (!WindowShouldClose() && !replayButton.isPressed && !exitButton.isPressed)
		{
			mouse = GetMousePosition();

			GoBallGo::mouseSelection(mouse, replayButton);
			GoBallGo::mouseSelection(mouse, exitButton);

			if (replayButton.isPressed)
			{
				if (player.isActive)
					GoBallGo::setPlayerDefault(player);

				if (player2.isActive)
					GoBallGo::setPlayerDefault(player2);

				GoBallGo::setWallDefault(wall);
			}

			if (exitButton.isPressed)
			{
				currentScreen = MENU;

				isMusicOn = wasMusicOn;
			}

			BeginDrawing();

			ClearBackground(DARKGREEN);

			if (player.isActive && player2.isActive)
			{
				DrawTexture(backgroundTwoPlayers, 0, 0, WHITE);

				DrawText("GAME OVER", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("GAME OVER", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) - 175), GoBallGo::titlesFontSize, YELLOW);

				DrawText("Player 1", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (GoBallGo::screenWidth / 4.0f) - (MeasureText("Player 1", GoBallGo::normalFontSize) / 2.0f)) - 25, static_cast<int>(GoBallGo::screenHeight / 2.0f) - 75, GoBallGo::titlesFontSize, WHITE);
				DrawText("Player 2", static_cast<int>((GoBallGo::screenWidth / 2.0f) + (GoBallGo::screenWidth / 4.0f) - (MeasureText("Player 2", GoBallGo::normalFontSize) / 2.0f)) - 15, static_cast<int>(GoBallGo::screenHeight / 2.0f) - 75, GoBallGo::titlesFontSize, WHITE);

				DrawText(TextFormat("%i", player.points), static_cast<int>((GoBallGo::screenWidth / 2.0f) - (GoBallGo::screenWidth / 4.0f)) - 25, static_cast<int>(GoBallGo::screenHeight / 2.0f), 60, WHITE);
				DrawText(TextFormat("%i", player2.points), static_cast<int>((GoBallGo::screenWidth / 2.0f) + (GoBallGo::screenWidth / 4.0f)) - 15, static_cast<int>(GoBallGo::screenHeight / 2.0f), 60, WHITE);
			}
			else
			{
				DrawTexture(backgroundOnePlayer, 0, 0, WHITE);

				DrawText("GAME OVER", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("GAME OVER", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) - 175), GoBallGo::titlesFontSize, YELLOW);

				DrawText("Player", static_cast<int>(GoBallGo::screenWidth / 2.0f - (MeasureText("Player", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>(GoBallGo::screenHeight / 2.0f) - 75, GoBallGo::titlesFontSize, WHITE);

				DrawText(TextFormat("%i", player.points), static_cast<int>(GoBallGo::screenWidth / 2.0f - MeasureText(TextFormat("%i", player.points), 60) / 2.0f), static_cast<int>(GoBallGo::screenHeight / 2.0f) + 15, 60, WHITE);
			}

			DrawTexture(buttonsTexture, static_cast<int>(replayButton.x), static_cast<int>(replayButton.y), replayButton.buttonTint);
			DrawTexture(buttonsTexture, static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), exitButton.buttonTint);

			DrawText("RESTART", static_cast<int>((replayButton.x + replayButton.w / 2.0f) - (MeasureText("RESTART", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(replayButton.y + GoBallGo::normalFontSize) - 5, GoBallGo::normalFontSize, replayButton.textColor);
			DrawText("GO TO MENU", static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (MeasureText("GO TO MENU", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize) - 5, GoBallGo::normalFontSize, exitButton.textColor);

			EndDrawing();
		}

		UnloadTexture(buttonsTexture);
		UnloadTexture(backgroundOnePlayer);
		UnloadTexture(backgroundTwoPlayers);
	}
}

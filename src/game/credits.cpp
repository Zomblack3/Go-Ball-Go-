#include "credits.h"

const int gameDevCredits = 2;
const int artCredits = 5;
const int soundCredits = 5;

namespace GoBallGo
{
	void credits(SCREENS& currentScreen, Sound& music, bool isMusicOn)
	{
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 10), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);

		// URL recs
		GoBallGo::Button gameDevURLRec[gameDevCredits] = { };
		GoBallGo::Button artURLRec[artCredits] = { };
		GoBallGo::Button soundURLRec[soundCredits] = { };
		//
		
		Texture2D background = LoadTexture("res/img/creditsBackground.png");
		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");

		Sound buttonsChangeStateSound = LoadSound("res/audio/button_sound.wav");

		exitButton.x -= exitButton.w / 2.0f;
		exitButton.texture = buttonsTexture;
		exitButton.changeStateSound = buttonsChangeStateSound;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !exitButton.isPressed)
		{
			CreditsStructure::update(currentScreen, mouse, exitButton, gameDevURLRec, artURLRec, soundURLRec);

			CreditsStructure::draw(exitButton, background, gameDevURLRec, artURLRec, soundURLRec);

			playGameMusic(music, isMusicOn);
		}

		exitButton.isPressed = false;

		UnloadTexture(background);
		UnloadTexture(buttonsTexture);
		UnloadTexture(exitButton.texture);

		UnloadSound(buttonsChangeStateSound);
	}
}

namespace CreditsStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& exitButton, GoBallGo::Button gameDevURLRec[], GoBallGo::Button artURLRec[], GoBallGo::Button soundURLRec[])
	{
		mouse = GetMousePosition();

		mouseSelection(mouse, exitButton);
		
		for (int i = 0; i < gameDevCredits; i++)
			mouseSelection(mouse, gameDevURLRec[i]);

		for (int i = 0; i < artCredits; i++)
			mouseSelection(mouse, artURLRec[i]);

		for (int i = 0; i < soundCredits; i++)
			mouseSelection(mouse, soundURLRec[i]);

		if (exitButton.isPressed)
			currentScreen = MENU;

		if (gameDevURLRec[0].isPressed || artURLRec[0].isPressed)
		{
			OpenURL("https://github.com/RusheryRL");

			gameDevURLRec[0].isPressed = false;
			artURLRec[0].isPressed = false;
		}

		if (gameDevURLRec[1].isPressed || artURLRec[1].isPressed)
		{
			OpenURL("https://github.com/Zomblack3");

			gameDevURLRec[1].isPressed = false;
			artURLRec[1].isPressed = false;
		}

		if (artURLRec[2].isPressed)
		{
			OpenURL("https://www.istockphoto.com/es/foto/ventiladores-en-el-estadio-gm470755388-63142783?searchscope=image%2Cfilm");

			artURLRec[2].isPressed = false;
		}

		if (artURLRec[3].isPressed)
		{
			OpenURL("https://kenney.nl/assets/ui-pack");

			artURLRec[3].isPressed = false;
		}

		if (artURLRec[4].isPressed)
		{
			OpenURL("https://www.canva.com/dream-lab");

			artURLRec[4].isPressed = false;
		}

		if (soundURLRec[0].isPressed)
		{
			OpenURL("https://youtu.be/8LvxqcSFfd4?si=OWUyFlYaLp5modCT");

			soundURLRec[0].isPressed = false;
		}

		if (soundURLRec[1].isPressed)
		{
			OpenURL("https://youtu.be/sazhlY67UZw?si=2grR5qdrgCGoGWvT");

			soundURLRec[1].isPressed = false;
		}

		if (soundURLRec[2].isPressed)
		{
			OpenURL("https://freesound.org/people/lagerstedt1993/sounds/733383");

			soundURLRec[2].isPressed = false;
		}

		if (soundURLRec[3].isPressed)
		{
			OpenURL("https://pixabay.com/sound-effects/beep-313342");

			soundURLRec[3].isPressed = false;
		}

		if (soundURLRec[4].isPressed)
		{
			OpenURL("https://freesound.org/people/Robinhood76/sounds/692545");

			soundURLRec[4].isPressed = false;
		}
	}

	void draw(GoBallGo::Button exitButton, Texture2D background, GoBallGo::Button gameDevURLRec[], GoBallGo::Button artURLRec[], GoBallGo::Button soundURLRec[])
	{
		const int extraRecPosX = 15;
		const int extraRecPosY = 25;
		const int extraRecSize = 25;
		const int distanceBetweenTexts = 50;

		// Texts
		std::string gameDevCreditsTexts[gameDevCredits] = { "Juan Pablo 'Rushery' Pivetta", "Santiago Agustin 'Zomblack3' Britos" };
		std::string artCreditsTexts[artCredits] = { "Juan Pablo 'Rushery' Pivetta", "Santiago Agustin 'Zomblack3' Britos", "Dmytro Aksonov (iStock) [Menu Background]", "Kenney [Buttons textures]", "Canva AI [Logo]" };
		std::string soundCreditsTexts[soundCredits] = { "El Cyber de Mc Caco [Menu music]", "Tribuna Xeneize (Youtube) [Gameplay music]", "lagerstedt1993 (Freesound) [Score sound]", "Musheran (Pixabay) [Buttons Sound]", "Robinhood76 (Freesound) [End game sound]" };
		//

		// Longer text of Game Dev
		int longerTextGameDev = getBiggerText(gameDevCreditsTexts, gameDevCredits);
		int longerTextGameDevLenght = MeasureText(gameDevCreditsTexts[longerTextGameDev].c_str(), GoBallGo::normalFontSize);
		//

		// Longer text of Art
		int longerTextArt = getBiggerText(artCreditsTexts, artCredits);
		int longerTextArtLenght = MeasureText(artCreditsTexts[longerTextArt].c_str(), GoBallGo::normalFontSize);
		//

		// Longer text of Sound
		int longerTextSound = getBiggerText(soundCreditsTexts, soundCredits);
		int longerTextSoundLenght = MeasureText(soundCreditsTexts[longerTextSound].c_str(), GoBallGo::normalFontSize);
		//

		// Title pos of Game Dev
		int gameDevTitlePosX = static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("GAME DEVELOPERS", GoBallGo::titlesFontSize) / 2.0f));
		int gameDevTitlePosY = static_cast<int>((GoBallGo::screenHeight / 3.0f) - 150.0f);
		//

		// Title pos of Art
		int artTitlePosX = static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f) - MeasureText("ART", GoBallGo::titlesFontSize) / 2.0f));
		int artTitlePosY = static_cast<int>((GoBallGo::screenHeight / 2.5f) - 150.0f);
		//

		// Title pos of Sound
		int soundTitlePosX = static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("SOUND", GoBallGo::titlesFontSize) / 2.0f));
		int soundTitlePosY = static_cast<int>(GoBallGo::screenHeight / 2.0f - 50.0f);
		//

		// Credits texts pos
		Vector2 gameDevCreditsPos[gameDevCredits] = { };
		Vector2 artCreditsPos[artCredits] = { };
		Vector2 soundCreditsPos[soundCredits] = { };
		//

		// Set credits text pos
		setTextsPos(gameDevCreditsPos, gameDevCredits, (GoBallGo::screenWidth / 4.0f), static_cast<float>(gameDevTitlePosY + distanceBetweenTexts), gameDevCreditsTexts);
		setTextsPos(artCreditsPos, artCredits, GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f), static_cast<float>(artTitlePosY + distanceBetweenTexts), artCreditsTexts);
		setTextsPos(soundCreditsPos, soundCredits, (GoBallGo::screenWidth / 4.0f), static_cast<float>(soundTitlePosY + distanceBetweenTexts), soundCreditsTexts);
		//

		// Background contrast recs
		Rectangle gameDevRec = { };
		Rectangle artRec = { };
		Rectangle soundRec = { };
		//

		// Game Dev rec configuration
		gameDevRec.x = ((GoBallGo::screenWidth / 4.0f) - (longerTextGameDevLenght / 2.0f)) - extraRecPosX;
		gameDevRec.y = static_cast<float>(gameDevTitlePosY - extraRecPosY);
		gameDevRec.width = static_cast<float>(longerTextGameDevLenght + extraRecSize);
		gameDevRec.height = static_cast<float>(((gameDevCredits + 1) * distanceBetweenTexts) + extraRecSize);
		//

		// Art rec configuration
		artRec.x = ((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (longerTextArtLenght / 2.0f)) - extraRecPosX;
		artRec.y = static_cast<float>(artTitlePosY - extraRecPosY);
		artRec.width = static_cast<float>(longerTextArtLenght + extraRecSize);
		artRec.height = static_cast<float>(((artCredits + 1) * distanceBetweenTexts) + extraRecSize);
		//

		// Sound rec configuration
		soundRec.x = ((GoBallGo::screenWidth / 4.0f) - (longerTextSoundLenght / 2.0f)) - extraRecPosX;
		soundRec.y = static_cast<float>(soundTitlePosY - extraRecPosY);
		soundRec.width = static_cast<float>(longerTextSoundLenght + extraRecSize);
		soundRec.height = static_cast<float>(((soundCredits + 1) * distanceBetweenTexts) + extraRecSize);
		//

		// URL recs positions
		for (int i = 0; i < gameDevCredits; i++)
		{
			gameDevURLRec[i].x = gameDevCreditsPos[i].x;
			gameDevURLRec[i].y = gameDevCreditsPos[i].y - GoBallGo::normalFontSize / 2.0f;
			gameDevURLRec[i].w = static_cast<float>(MeasureText(gameDevCreditsTexts[i].c_str(), GoBallGo::normalFontSize));
			gameDevURLRec[i].h = static_cast<float>(GoBallGo::normalFontSize);
		}

		for (int i = 0; i < artCredits; i++)
		{
			artURLRec[i].x = artCreditsPos[i].x;
			artURLRec[i].y = artCreditsPos[i].y - GoBallGo::normalFontSize / 2.0f;
			artURLRec[i].w = static_cast<float>(MeasureText(artCreditsTexts[i].c_str(), GoBallGo::normalFontSize));
			artURLRec[i].h = static_cast<float>(GoBallGo::normalFontSize);
		}

		for (int i = 0; i < soundCredits; i++)
		{
			soundURLRec[i].x = soundCreditsPos[i].x;
			soundURLRec[i].y = soundCreditsPos[i].y - GoBallGo::normalFontSize / 2.0f;
			soundURLRec[i].w = static_cast<float>(MeasureText(soundCreditsTexts[i].c_str(), GoBallGo::normalFontSize));
			soundURLRec[i].h = static_cast<float>(GoBallGo::normalFontSize);
		}
		//

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		// Draw recs
		DrawRectangle(static_cast<int>(gameDevRec.x), static_cast<int>(gameDevRec.y), static_cast<int>(gameDevRec.width), static_cast<int>(gameDevRec.height), DARKBLUE);
		DrawRectangle(static_cast<int>(artRec.x), static_cast<int>(artRec.y), static_cast<int>(artRec.width), static_cast<int>(artRec.height), DARKBLUE);
		DrawRectangle(static_cast<int>(soundRec.x), static_cast<int>(soundRec.y), static_cast<int>(soundRec.width), static_cast<int>(soundRec.height), DARKBLUE);
		//

		// Draw titles
		DrawText("GAME DEVELOPERS", gameDevTitlePosX, gameDevTitlePosY, GoBallGo::titlesFontSize, YELLOW);
		DrawText("ART", static_cast<int>(artTitlePosX), static_cast<int>(artTitlePosY), GoBallGo::titlesFontSize, YELLOW);
		DrawText("SOUND", soundTitlePosX, soundTitlePosY, GoBallGo::titlesFontSize, YELLOW);
		//

		// Draw texts
		for (int i = 0; i < gameDevCredits; i++)
			DrawText(gameDevCreditsTexts[i].c_str(), static_cast<int>(gameDevCreditsPos[i].x), static_cast<int>(gameDevCreditsPos[i].y), GoBallGo::normalFontSize, gameDevURLRec[i].textColor);

		for (int i = 0; i < artCredits; i++)
			DrawText(artCreditsTexts[i].c_str(), static_cast<int>(artCreditsPos[i].x), static_cast<int>(artCreditsPos[i].y), GoBallGo::normalFontSize, artURLRec[i].textColor);

		for (int i = 0; i < soundCredits; i++)
			DrawText(soundCreditsTexts[i].c_str(), static_cast<int>(soundCreditsPos[i].x), static_cast<int>(soundCreditsPos[i].y), GoBallGo::normalFontSize, soundURLRec[i].textColor);
		//

		DrawTexture(exitButton.texture, static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), exitButton.buttonTint);

		DrawText("RETURN", static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (MeasureText("RETURN", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, exitButton.textColor);

		EndDrawing();
	}

	void setTextsPos(Vector2 textPos[], int amountOfTexts, float startingX, float startingY, std::string texts[])
	{
		int distanceBetweenTexts = 50;

		for (int i = 0; i < amountOfTexts; i++)
		{
			textPos[i].x = startingX - static_cast<float>(MeasureText(texts[i].c_str(), GoBallGo::normalFontSize)) / 2.0f;
			textPos[i].y = startingY + (distanceBetweenTexts * i);
		}
	}

	int getBiggerText(std::string texts[], int amountOfTexts)
	{
		int biggerText = 0;

		for (int i = 0; i < amountOfTexts; i++)
		{
			if (MeasureText(texts[i].c_str(), GoBallGo::normalFontSize) > MeasureText(texts[biggerText].c_str(), GoBallGo::normalFontSize))
				biggerText = i;
		}

		return biggerText;
	}
}

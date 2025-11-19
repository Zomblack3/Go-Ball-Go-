#include <iostream>

using namespace std;

#include "windowManagment.h"

namespace GoBallGo
{
	void mouseSelection(Vector2 mousePos, Button& button)
	{
		if (isMouseInButton(mousePos, button))
		{
			if (button.soundTimesPlayed < 1)
			{
				if (!IsSoundPlaying(button.changeStateSound))
					PlaySound(button.changeStateSound);

				button.soundTimesPlayed++;
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				button.isPressed = true;
			else
				button.isPressed = false;

			button.buttonTint = BLUE;

			button.textColor = YELLOW;
		}
		else
		{
			button.soundTimesPlayed = 0;

			button.buttonTint = SKYBLUE;

			button.textColor = WHITE;
		}
	}

	void playGameMusic(Sound& music, bool isMusicOn)
	{
		if (!IsSoundPlaying(music))
			PlaySound(music);

		if (!isMusicOn)
			PauseSound(music);
		else
			ResumeSound(music);
	}

	bool isMouseInButton(Vector2 mousePos, Button button)
	{
		if (mousePos.x >= button.x && mousePos.x <= button.x + button.w &&
			mousePos.y >= button.y && mousePos.y <= button.y + button.h)
			return true;
		else
			return false;
	}
}

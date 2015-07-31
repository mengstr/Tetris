#include <svc.h>
#include <Applidl.h>
#include "Shapes.h"
#include "Console.h"
#include "Tetris.h"


Tetris::Tetris() 
  : _score(0)
  , _hiscore(Console::GetIntVariable("#HISCORE"))
{

}


Tetris::~Tetris()
{

}


void Tetris::Play()
{
	bool sound = false;
	key_beeps(sound?1:0);

	while(true)
	{
		// Welcome screen
		WelcomeScreen();
		Console::KeyWait(1, 16);

		int delay     = 500;
		int level     = 0;
		bool restart	= false;
		bool next			= true;
		bool pause		= false;
		unsigned long ticks	= read_ticks();
    Board::GetInstance().Reset();
    Board::GetInstance().HiScore(_hiscore);

		while(!restart)
		{
			_score = Board::GetInstance().Score();
			_hiscore = Board::GetInstance().HiScore();

			// Add a new shape if a new one is required
			if (next)
			{
				// If we cannot add the shape to the board then the game is over
				next = !Board::GetInstance().Add(ShapeFactory::CreateRandomInstance());
				if (next)
				{
					// Game over screen
					GameOverScreen();

					// Print scores
					PrintHiScore();

					// Wait 3 seconds before going to main screen
					SVC_WAIT(3000);
					break;	// Restart
				}
				else if (_score >= (level + 100))
				{
					// Next level
					// We reduce the delay to make things a bit harder ;-)
					level += 100;
					delay -= 50;
				}
				else
				{
					// Update the battery level
					Console::DisplayBattery(1, 16);
				}
			}

			if (!pause)
			{
				// Not in pause mode so check keyboard
				if (Console::HasKey())
				{
					switch (Console::GetKey())
					{
					case KEY4:							Board::GetInstance().Move(false);				break;	// Move Left
					case KEY5:							Board::GetInstance().Rotate();					break;	// Rotate
					case KEY6:							Board::GetInstance().Move(true);				break;	// Move right
					case KEY_BS:						Board::GetInstance().Drop();						break;	// Drop
					case KEY_CR:						pause = !pause;													break;	// Pause
					case KEY_CANCEL:				restart = true;													break;	// Restart
					case 15: case KEY_STR:	sound = !sound; key_beeps(sound?1:0);		break;	// Sound on/off
					}
				}

				// Move the current shaped down 1
				if (read_ticks() > ticks + delay)
				{
					next  = !Board::GetInstance().Gravity();
					ticks = read_ticks();
				}
			}
			else
			{
				// In pause mode so only check for the unpause button
				if (Console::HasKey())
				{
					if (Console::GetKey() == KEY_CR) pause = !pause;
				}
			}
		}

		// Store the new hi score
		Console::SetIntVariable("#HISCORE", _hiscore);
	}
}

void Tetris::WelcomeScreen() const
{
	Console::PositionBMP("F:Tetris.bmp");
	Console::PositionText("PRESS ANY KEY", 12);
	Console::PositionText("TO START", 13);
	Console::PositionText("HI SCORE " + Console::Int2String(_hiscore), 15);
}


void Tetris::GameOverScreen() const
{
	Console::PositionBMP("F:Tetris.bmp");
	Console::PositionText("GAME OVER", 12);
	Console::PositionText("YOUR SCORE " + Console::Int2String(_score), 14);
	Console::PositionText("HI SCORE "   + Console::Int2String(_hiscore),    15);
	Console::DisplayBattery(1, 16);
}


void Tetris::PrintHiScore() const
{
}

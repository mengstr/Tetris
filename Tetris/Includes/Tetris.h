#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <svc.h>
#include <Applidl.h>
#include "Shapes.h"
#include "Console.h"

class Tetris
{
public:

  Tetris();
 ~Tetris();
  void Play();

protected:

  void WelcomeScreen() const;
  void GameOverScreen() const;
  void PrintHiScore() const;

protected:

  int	_score;
  int	_hiscore;
};

#endif

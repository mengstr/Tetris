#include "Board.h"
#include "Console.h"

#include <svc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <logsys.h>

#define RGB16(r, g, b) ((r & 0xF8) << 8) | ((g & 0xFC) << 4) | ((b & 0xF8))
#define WHITE_COLOR RGB16(255,255,255)
#define BLACK_COLOR RGB16(0,0,0)


unsigned int Board::nextid_ = 0;


static unsigned int color(int id)
{
  if (!id)
    return WHITE_COLOR;

  switch(id % 6 + 1)
  {
  case 1: return RGB16(255,0,0);
  case 2: return RGB16(0,255,0);
  case 3: return RGB16(0,0,255);
  case 4: return RGB16(255,255,0);
  case 5: return RGB16(0,255,255);
  case 6: return RGB16(255,0,255);
  }
}


Shape::Shape() : x_(0), y_(0), id_(1), board_(0), bottom_(0)
{}


Shape::~Shape()
{}


bool Shape::Add(Board* board)
{
	board_ = board;
	if (board_ != 0)
	{
		id_ = board_->NextID();
		if (Check(x_, y_))
		{
			Set(x_, y_, id_);
			return true;
		}
	}
	return false;
}


bool Shape::Gravity()
{
	if (!bottom_)
	{
		if (Check(x_, y_ + 1))
		{
			Set(x_, y_, 0);
			Set(x_, ++y_, id_);
		}
		else
		{
			bottom_ = true;
		}
	}
	return !bottom_;
}


bool Shape::Rotate()
{
	if (!bottom_)
	{
		int x = x_;
		int y = y_;

		Set(x_, y_, 0);
		RotateShape(true);
		if (Check(x_, y_))
		{
			Set(x_, y_, id_);
			return true;
		}
		else
		{
			x_ = x;
			y_ = y;
			RotateShape(false);
			Set(x_, y_, id_);
		}
	}
	return false;
}


bool Shape::Move(bool right)
{
	if (!bottom_)
	{
		if (Check(right?x_+1:x_-1, y_))
		{
			Set(x_, y_, 0);
			Set(right?++x_:--x_, y_, id_);
			return true;
		}
	}
	return false;
}


void Shape::Set(int x, int y, unsigned int c)
{
	if (board_ != 0)
	{
		for (int y1 = 0; y1 < Height(); y1++)
		{
			for (int x1 = 0; x1 < Width(); x1++)
			{
				if ((*this)(x1, y1)) 
          (*board_)(x1 + x, y1 + y) = c;
			}
		}
	}
}


bool Shape::Check(int x, int y)
{
	if (board_ != 0)
	{
		for (int y1 = 0; y1 < Height(); y1++)
		{
			for (int x1 = 0; x1 < Width(); x1++)
			{
				if ((*this)(x1, y1))
				{
					if ( x1 + x < 0 || y1 + y < 0 || x1 + x >= board_->Width() || y1 + y >= board_->Height() || ( (*board_)(x1 + x, y1 + y) != id_ && (*board_)(x1 + x, y1 + y) != 0 ) ) 
					{
						// Collision detected
						return false;
					}
				}
			}
		}
	}
	return true;
}


Board::Board() 
  : width_(WIDTH)
  , height_(HEIGHT)
  , size_(SIZE)
  , frame_(FRAME)
  , score_(0)
  , hiscore_(0)
{
	srand((size_t)time(0));
	Reset();
}


Board::~Board()
{}


Board& Board::GetInstance()
{
  static Board board;
	return board;
}


unsigned int& Board::operator()(int x, int y)
{
	return board_[x][y];
}


unsigned int Board::operator()(int x, int y) const
{
	return board_[x][y];
}


void Board::Reset()
{
	Fill(0);
	shape_ = 0;
	score_ = 0;
	nextid_ = 0;
	clrscr();

  Console::coordinate_mode mode(Console::coordinate_mode::mode_pixel);
	Console::PositionBMP("F:background.bmp");

	int scrw = 240;
	int scrh = 320;

	int w     = size_ + frame_;
	int h     = size_ + frame_;
	int left  = (scrw - (width_ * w)) / 2;
	int right = width_ * w + left;
  int top   = (scrh - (height_ * h)) / 2;
  int bot   = height_ * h + top;

	// Draw Frame
  write_pixels(left, top, right - 1, bot - 1, WHITE_COLOR);
	draw_line(left - 1, top - 1,  right - 1, top - 1, 1, BLACK_COLOR);
	draw_line(right - 1, top - 1,  right - 1, bot - 1, 1, BLACK_COLOR);
	draw_line(left - 1, bot - 1,  right - 1, bot - 1, 1, BLACK_COLOR);
	draw_line(left - 1, top - 1,  left - 1, bot - 1, 1, BLACK_COLOR);

}


void Board::HiScore(int hi)
{
  hiscore_ = hi;
}


int Board::Size() const 
{
	return size_;
}


int Board::Frame() const 
{
	return frame_;
}


int Board::Width() const 
{
	return width_;
}


int Board::Height() const 
{
	return height_;
}


int Board::Score() const
{
	return score_;
}


int Board::HiScore() const
{
	return hiscore_;
}


void Board::Draw() const
{
  Console::coordinate_mode mode(Console::coordinate_mode::mode_pixel);

	int scrw = 240;
	int scrh = 320;

	int w     = size_ + frame_;
	int h     = size_ + frame_;
	int left  = (scrw - (width_ * w)) / 2;
	int right = width_ * w + left;
  int top   = (scrh - (height_ * h)) / 2;
  int bot   = height_ * h + top;

	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
			write_pixels(x * w + left, y * h + top, x * w + left + size_, y * h + top + size_, color((*this)(x, y)));
		}
	}

	// Draw Frame
	draw_line(left - 1, top - 1,  right - 1, top - 1, 1, BLACK_COLOR);
	draw_line(right - 1, top - 1,  right - 1, bot - 1, 1, BLACK_COLOR);
	draw_line(left - 1, bot - 1,  right - 1, bot - 1, 1, BLACK_COLOR);
	draw_line(left - 1, top - 1,  left - 1, bot - 1, 1, BLACK_COLOR);
}


bool Board::Add(CountedPointer<Shape> shape)
{
	if (shape != 0)
	{
		if (shape->Add(this))
		{
			shape_ = shape;
			Draw();

			// Increase current score
			score_++;
			if (score_ > hiscore_) 
        hiscore_ = score_;

			// Print current score
			char num[20] = {0};
			sprintf(num, "%d", score_);
			write_at("SC", 2, 1, 1);
			write_at(num, strlen(num), 1, 2);

			// Print current score
			sprintf(num, "%d", hiscore_);
			write_at("HI", 2, 29, 1);
			write_at(num, strlen(num), 31 - strlen(num), 2);

			return true;
		}
	}
	return false;
}


void Board::Fill(unsigned int num)
{
	memset(board_, num, sizeof(board_));
	Draw();
}


bool Board::Gravity()
{
	if (shape_ != 0)
	{
		if (shape_->Gravity())
		{
			// Draw the board
			Draw();
			return true;
		}
		else
		{
			// Check for lines to remove
			if (RemoveLines())
			{
				// Draw the board
				SVC_WAIT(100);
				Draw();
			}
		}
	}
	return false;
}


void Board::Rotate()
{
	if (shape_ != 0)
	{
		if (shape_->Rotate())
		{
			// Draw the board
			Draw();
		}
	}
}


void Board::Move(bool right)
{
	if (shape_ != 0)
	{
		if (shape_->Move(right))
		{
			// Draw the board
			Draw();
		}
	}
}


void Board::Drop()
{
	while(Gravity()) SVC_WAIT(10);
}


bool Board::RemoveLines()
{
	bool removed = false;
	for (int y = 0; y < Height(); y++)
	{
		bool remove = true;
		for (int x = 0; x < Width(); x++)
		{
			if (!(*this)(x, y))
			{
				remove = false;
				break;
			}
		}

		if (remove)
		{
			for (int y1 = y; y1 > 0; y1--)
			{
				for (int x1 = 0; x1 < Width(); x1++)
				{
					(*this)(x1, y1) = (*this)(x1, y1-1);
				}
			}
			removed = true;
		}
	}
	return removed;
}

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Board.h"
#include <stdlib.h>
#include <string.h>


class Square : public Shape
{
public:

	Square() 
	{
		x_ = rand() % (WIDTH - 2); 
		memset(_Square, 1, sizeof(_Square));
	}


	virtual ~Square()
	{
	
	}


	virtual int Width() const
	{
		return 2;
	}


	virtual int Height() const
	{
		return 2;
	}


	virtual bool operator()(int x, int y) const
	{
		return _Square[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
	
	}

private:

	unsigned int	_Square[2][2];
};



class Line : public Shape
{
public:

	Line() : _NextRotate(false)
	{
		x_ = rand() % (WIDTH - 4);
		memset(_Line, 0, sizeof(_Line));
		_Line[0][0] = 1;
		_Line[1][0] = 1; 
		_Line[2][0] = 1; 
		_Line[3][0] = 1;
	}


	virtual ~Line()
	{

	}


	virtual int Width() const
	{
		return 4;
	}


	virtual int Height() const
	{
		return 4;
	}


	virtual bool operator()(int x, int y) const
	{
		return _Line[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			_NextRotate = !_NextRotate;

			if (_NextRotate)
			{
				// x
				// x
				// x
				// x
				memset(_Line, 0, sizeof(_Line));
				_Line[0][0] = 1;
				_Line[0][1] = 1; 
				_Line[0][2] = 1; 
				_Line[0][3] = 1;
			}
			else
			{
				// xxxx
				memset(_Line, 0, sizeof(_Line));
				_Line[0][0] = 1;
				_Line[1][0] = 1; 
				_Line[2][0] = 1; 
				_Line[3][0] = 1;
				if (x_ > board_->Width()-4) x_ = board_->Width()-4;
			}
		}
	}

private:

	unsigned int	_Line[4][4];
	bool					_NextRotate;
};


class LeftElbow : public Shape
{
public:

	LeftElbow() : _NextRotate(0)
	{
		x_ = rand() % (WIDTH - 3);
		memset(_LeftElbow, 0, sizeof(_LeftElbow));
		_LeftElbow[0][0] = 1;
		_LeftElbow[0][1] = 1; 
		_LeftElbow[1][1] = 1; 
		_LeftElbow[2][1] = 1;
	}


	virtual ~LeftElbow()
	{
	
	}


	virtual int Width() const
	{
		return 3;
	}


	virtual int Height() const
	{
		return 3;
	}


	virtual bool operator()(int x, int y) const
	{
		return _LeftElbow[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			if (clockwise)
			{
				_NextRotate++;
				if (_NextRotate > 3) _NextRotate = 0;
			}
			else
			{
				_NextRotate--;
				if (_NextRotate < 0) _NextRotate = 3;
			}

			switch (_NextRotate)
			{
			case 0:
				{
					// x
					// xxx
					memset(_LeftElbow, 0, sizeof(_LeftElbow));
					_LeftElbow[0][0] = 1;
					_LeftElbow[0][1] = 1; 
					_LeftElbow[1][1] = 1; 
					_LeftElbow[2][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 1:
				{
					// xx
					// x
					// x
					memset(_LeftElbow, 0, sizeof(_LeftElbow));
					_LeftElbow[0][0] = 1;
					_LeftElbow[0][1] = 1; 
					_LeftElbow[0][2] = 1; 
					_LeftElbow[1][0] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;

			case 2:
				{
					// xxx
					//   x
					memset(_LeftElbow, 0, sizeof(_LeftElbow));
					_LeftElbow[0][0] = 1;
					_LeftElbow[1][0] = 1; 
					_LeftElbow[2][0] = 1; 
					_LeftElbow[2][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 3:
				{
					//  x
					//  x
					// xx
					memset(_LeftElbow, 0, sizeof(_LeftElbow));
					_LeftElbow[1][0] = 1;
					_LeftElbow[1][1] = 1; 
					_LeftElbow[1][2] = 1; 
					_LeftElbow[0][2] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;
			}
		}	
	}

private:

	unsigned int	_LeftElbow[3][3];
	int						_NextRotate;
};



class RightElbow : public Shape
{
public:

  RightElbow() : _NextRotate(0)
	{
		x_ = rand() % (WIDTH - 3);
		memset(_RightElbow, 0, sizeof(_RightElbow));
		_RightElbow[2][0] = 1;
		_RightElbow[0][1] = 1; 
		_RightElbow[1][1] = 1; 
		_RightElbow[2][1] = 1;
	}


	virtual ~RightElbow()
	{
	
	}


	virtual int Width() const
	{
		return 3;
	}


	virtual int Height() const
	{
		return 3;
	}


	virtual bool operator()(int x, int y) const
	{
		return _RightElbow[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			if (clockwise)
			{
				_NextRotate++;
				if (_NextRotate > 3) _NextRotate = 0;
			}
			else
			{
				_NextRotate--;
				if (_NextRotate < 0) _NextRotate = 3;
			}

			switch (_NextRotate)
			{
			case 0:
				{
					//   x
					// xxx
					memset(_RightElbow, 0, sizeof(_RightElbow));
					_RightElbow[2][0] = 1;
					_RightElbow[0][1] = 1; 
					_RightElbow[1][1] = 1; 
					_RightElbow[2][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 1:
				{
					// x
					// x
					// xx
					memset(_RightElbow, 0, sizeof(_RightElbow));
					_RightElbow[0][0] = 1;
					_RightElbow[0][1] = 1; 
					_RightElbow[0][2] = 1; 
					_RightElbow[1][2] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;

			case 2:
				{
					// xxx
					// x
					memset(_RightElbow, 0, sizeof(_RightElbow));
					_RightElbow[0][0] = 1;
					_RightElbow[1][0] = 1; 
					_RightElbow[2][0] = 1; 
					_RightElbow[0][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 3:
				{
					// xx
					//  x
					//  x
					memset(_RightElbow, 0, sizeof(_RightElbow));
					_RightElbow[0][0] = 1;
					_RightElbow[1][0] = 1; 
					_RightElbow[1][1] = 1; 
					_RightElbow[1][2] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;
			}
		}
	}

private:

	unsigned int	_RightElbow[3][3];
	int						_NextRotate;
};


class Tee : public Shape
{
public:

	Tee() : _NextRotate(0)
	{
		x_ = rand() % (WIDTH - 3);
		memset(_Tee, 0, sizeof(_Tee));
		_Tee[1][0] = 1;
		_Tee[0][1] = 1; 
		_Tee[1][1] = 1; 
		_Tee[2][1] = 1;
	}


	virtual ~Tee()
	{
	
	}


	virtual int Width() const
	{
		return 3;
	}


	virtual int Height() const
	{
		return 3;
	}


	virtual bool operator()(int x, int y) const
	{
		return _Tee[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			if (clockwise)
			{
				_NextRotate++;
				if (_NextRotate > 3) _NextRotate = 0;
			}
			else
			{
				_NextRotate--;
				if (_NextRotate < 0) _NextRotate = 3;
			}

			switch (_NextRotate)
			{
			case 0:
				{
					//  x
					// xxx
					memset(_Tee, 0, sizeof(_Tee));
					_Tee[1][0] = 1;
					_Tee[0][1] = 1; 
					_Tee[1][1] = 1; 
					_Tee[2][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 1:
				{
					// x
					// xx
					// x
					memset(_Tee, 0, sizeof(_Tee));
					_Tee[0][0] = 1;
					_Tee[0][1] = 1; 
					_Tee[0][2] = 1; 
					_Tee[1][1] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;

			case 2:
				{
					// xxx
					//  x
					memset(_Tee, 0, sizeof(_Tee));
					_Tee[0][0] = 1;
					_Tee[1][0] = 1; 
					_Tee[2][0] = 1; 
					_Tee[1][1] = 1;
					if (x_ > board_->Width()-3) x_ = board_->Width()-3;
				}
				break;

			case 3:
				{
					//  x
					// xx
					//  x
					memset(_Tee, 0, sizeof(_Tee));
					_Tee[1][0] = 1;
					_Tee[1][1] = 1; 
					_Tee[1][2] = 1; 
					_Tee[0][1] = 1;
					if (x_ > board_->Width()-2) x_ = board_->Width()-2;
				}
				break;
			}
		}
	}

private:

	unsigned int	_Tee[3][3];
	int						_NextRotate;
};


class LeftStager : public Shape
{
public:

	LeftStager() : _NextRotate(false)
	{
		x_ = rand() % (WIDTH - 3);
		memset(_LeftStager, 0, sizeof(_LeftStager));
		_LeftStager[0][0] = 1;
		_LeftStager[1][0] = 1; 
		_LeftStager[1][1] = 1; 
		_LeftStager[2][1] = 1;
	}


	virtual ~LeftStager()
	{
	
	}


	virtual int Width() const
	{
		return 3;
	}


	virtual int Height() const
	{
		return 3;
	}


	virtual bool operator()(int x, int y) const
	{
		return _LeftStager[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			_NextRotate = !_NextRotate;

			if (!_NextRotate)
			{
				// xx
				//  xx 
				memset(_LeftStager, 0, sizeof(_LeftStager));
				_LeftStager[0][0] = 1;
				_LeftStager[1][0] = 1; 
				_LeftStager[1][1] = 1; 
				_LeftStager[2][1] = 1;
				if (x_ > board_->Width()-3) x_ = board_->Width()-3;
			}
			else
			{
				//  x
				// xx
				// x
				memset(_LeftStager, 0, sizeof(_LeftStager));
				_LeftStager[1][0] = 1;
				_LeftStager[0][1] = 1; 
				_LeftStager[1][1] = 1; 
				_LeftStager[0][2] = 1;
				if (x_ > board_->Width()-2) x_ = board_->Width()-2;
			}
		}
	}

private:

  unsigned int	_LeftStager[3][3];
	bool					_NextRotate;
};



class RightStager : public Shape
{
public:

	RightStager() : _NextRotate(false)
	{
		x_ = rand() % (WIDTH - 3);
		memset(_RightStager, 0, sizeof(_RightStager));
		_RightStager[1][0] = 1;
		_RightStager[2][0] = 1; 
		_RightStager[0][1] = 1; 
		_RightStager[1][1] = 1;
	}


	virtual ~RightStager()
	{
	
	}


	virtual int Width() const
	{
		return 3;
	}


	virtual int Height() const
	{
		return 3;
	}


	virtual bool operator()(int x, int y) const
	{
		return _RightStager[x][y]?true:false;
	}


	virtual void RotateShape(bool clockwise)
	{
		if (board_ != 0)
		{
			_NextRotate = !_NextRotate;

			if (!_NextRotate)
			{
				//  xx
				// xx
				memset(_RightStager, 0, sizeof(_RightStager));
				_RightStager[1][0] = 1;
				_RightStager[2][0] = 1; 
				_RightStager[0][1] = 1; 
				_RightStager[1][1] = 1;
				if (x_ > board_->Width()-3) x_ = board_->Width()-3;
			}
			else
			{
				// x
				// xx
				//  x
				memset(_RightStager, 0, sizeof(_RightStager));
				_RightStager[0][0] = 1;
				_RightStager[0][1] = 1; 
				_RightStager[1][1] = 1; 
				_RightStager[1][2] = 1;
				if (x_ > board_->Width()-2) x_ = board_->Width()-2;
			}
		}
	}

private:

	unsigned int	_RightStager[3][3];
	bool					_NextRotate;
};



namespace ShapeFactory
{
	static CountedPointer<Shape> CreateRandomInstance()
	{
		switch(rand() % 7)
		{
			case 1:		return new Line;
			case 2:		return new LeftElbow;
			case 3:		return new RightElbow;
			case 4:		return new Tee;
			case 5:		return new LeftStager;
			case 6:		return new RightStager;
			default:	return new Square;
		}
	}
};

#endif

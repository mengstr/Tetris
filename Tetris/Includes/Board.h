#ifndef board__H_
#define board__H_

#include "CountedPointer.h"
#include <string>

using namespace std;


#define WIDTH		10
#define HEIGHT	16
#define SIZE		12
#define	FRAME		2


class Board;
class Shape
{
public:

  Shape();
	virtual ~Shape();

	bool Add(Board* board);
	bool Gravity();
	bool Rotate();
	bool Move(bool right);
	void Set(int x, int y, unsigned int c);
	bool Check(int x, int y);

  virtual int Width() const = 0;
  virtual int Height() const = 0;
	virtual bool operator()(int x, int y) const = 0;
	virtual void RotateShape(bool clockwise) = 0;

protected:

	int							x_;
	int							y_;
	unsigned int		id_;
	Board*					board_;
	bool						bottom_;
};


class Board
{
public:

  static Board& GetInstance();

	~Board();

	bool Add(const CountedPointer<Shape> shape);
	bool Gravity();
	void Rotate();
	void Move(bool right);
	void Drop();
	void Reset();
	void HiScore(int);

	int Size() const;
	int Frame() const;
	int Width() const;
	int Height() const;
	int Score() const;
	int HiScore() const;

protected:

	unsigned int NextID() {return ++nextid_;}
	void Draw() const;
	bool RemoveLines();
	unsigned int& operator()(int x, int y);
	unsigned int operator()(int x, int y) const;

private:

	Board();
	Board(const Board&);
  Board& operator=(const Board&);

	void Fill(unsigned int num);

  unsigned int					board_[WIDTH][HEIGHT];
	int										width_;
	int										height_;
	int										size_;
	int										frame_;
	int										score_;
	int										hiscore_;
	CountedPointer<Shape>	shape_;
	static unsigned int		nextid_;

	friend class Shape;
};

#endif

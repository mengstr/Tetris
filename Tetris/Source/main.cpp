#include "Tetris.h"
#include <logsys.h>
#include <SVC.H>
#include <queue>


extern "C" const char DEV_CONSOLE[];    /* keyboard & display */
extern "C" int $Super$$_open(const char*, int);
extern "C" int $Super$$_close(int);
extern "C" int $Super$$_read(int, char*, int);
extern "C" long wait_event(void);

namespace kbd
{
  static std::queue<char> queue;
  static int console_handle = 0;


  static int open(const char* dev, int mode)
  {
    if (dev && !strcmp(dev, DEV_CONSOLE))
      return console_handle = $Super$$_open(dev, mode);
    else
      return $Super$$_open(dev, mode);
  }


  static int close(int handle)
  {
    if (handle == console_handle)
      console_handle = -1;

    return $Super$$_close(handle);
  }


  static int read(int handle, char* ptr, int size)
  {
    if (handle == console_handle && ptr && size && queue.size())
    {
      *ptr++ = queue.front();
      queue.pop();
      return 1;
    }
    return $Super$$_read(handle, ptr, size);
  }


  void push(const char* ptr, int size)
  {
    while(size--) queue.push(*ptr++);
  }
}

extern "C" int $Sub$$_open(const char* dev, int mode)
{
  return kbd::open(dev, mode);
}

extern "C" int $Sub$$_close(int handle)
{
  // Override the malloc symbol
  return kbd::close(handle);
}

extern "C" int $Sub$$_read(int handle, char* buf, int size)
{
  return kbd::read(handle, buf, size);
}


int main()
{
  open(DEV_CONSOLE, 0);
  kbd::push("\r\r\r\r\r\r\r\r\r\r\r",0);

  LOG_INIT( "TETRIS", LOGSYS_COMM, 0xffffffff );
  LOG_PRINTF(("TETRIS started"));
	Tetris().Play();
}

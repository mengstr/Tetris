#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>
using namespace std;


namespace Console
{
  struct coordinate_mode
  {
    enum modes
    {
      mode_character = CHARACTER_MODE,
      mode_pixel     = PIXEL_MODE,
    };

    coordinate_mode(modes mode) 
      : old_(get_display_coordinate_mode()) 
    {
      set_display_coordinate_mode(mode);
    }

   ~coordinate_mode() 
    {
      set_display_coordinate_mode(old_);
    }

  private:

    int old_;
  };


  void PositionText(const string& message, int row);
	void PositionBMP(const string& bmp);
	char KeyWait(int col, int row);
	bool HasKey();
	char GetKey();
	string Int2String(int num);
	void DisplayBattery(int col, int row);
	void SetVariable(const string& key, const string& value);
	void SetIntVariable(const string& key, int value);
	string GetVariable(const string& key);
	int GetIntVariable(const string& key);
}

#endif

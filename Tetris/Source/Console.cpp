#include "Console.h"
#include <aclconio.h>
#include <svc.h>
#include <stdlib.h>
#include <stdio.h>
#include <battery.h>
#include <errno.h>
#include <logsys.h>


namespace Console
{
	void PositionText(const string& message, int row)
	{
    coordinate_mode mode(coordinate_mode::mode_character);

		char coor[2];
		screen_size(coor);
		write_at (message.data(), message.length(), 1 + ((coor[1] - message.length()) / 2), row);
	}


	void PositionBMP(const string& bmp)
	{
		clrscr();
    coordinate_mode mode(coordinate_mode::mode_pixel);
		put_BMP_at(0,0,(char*)bmp.c_str());
	}


	char KeyWait(int col, int row)
	{
		// Clear keyboard and keywait
    get_console(1);
		unsigned t = 0;
		while(!HasKey())
		{
			if (read_ticks() > t + 1000)
			{
				DisplayBattery(col, row);
				t = read_ticks();
			}
			SVC_WAIT(50);
		}

		return GetKey();
	}


	bool HasKey()
	{
		return kbd_pending_count()?true:false;
	}


	char GetKey()
	{
		char key[1];
		read(get_console(0), key, sizeof(key));
		return key[0] & 0x7f;
	}


	string Int2String(int num)
	{
		char n[40] = {0};
		sprintf(n, "%d", num);
		return n;
	}


	void DisplayBattery(int col, int row)
	{
	#ifdef VX670

		char font[256] = {0};
		char bat[2];
		bat[0] = 'a' + (char)((get_battery_charge() * 6) / 100);
		bat[1] = 0;

		int old = get_display_coordinate_mode();
		set_display_coordinate_mode(CHARACTER_MODE);
		get_font(font);
		set_font("F:BATTERY.VFT");

		write_at (bat, 1, col, row);

		set_font(font);
		set_display_coordinate_mode(old);	

	#endif
	}


	void SetVariable(const string& key, const string& value)
	{
		put_env(key.c_str(), value.c_str(), value.length());
	}


	void SetIntVariable(const string& key, int value)
	{
		char buf[40] = {0};
		sprintf(buf, "%d", value);
		SetVariable(key, buf);
	}


	string GetVariable(const string& key)
	{
		char buf[256] = {0};
		get_env(key.c_str(), buf, sizeof(buf));
		return buf;
	}


	int GetIntVariable(const string& key)
	{
		string v = GetVariable(key);
		return atoi(v.c_str());
	}
}

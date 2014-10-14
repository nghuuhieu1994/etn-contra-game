

#include "Support.h"

void init(void)
{
	//title
	SetConsoleTitle("Tank");

	//position
	GSetWindowPosition(200, 200);

	//hide mouse
	GSetCursorVisiable(false);

	//color
	GSetTextColor(GColors::LIGHT_WHITE);
	GSetBGColor(GColors::BLACK);

	//set default font
	//font này là font duy nhất có dạng vuông
	GSetFont(8, 8, 100, GFontFamilys::MODERN);

	//no scroll bar
	GSetNoScroolBar();
}

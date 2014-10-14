
#include "Utils.h"

//VARIANTs

//màu background và màu chữ
GColors g_BackgroundColor = GColors::BLACK;
GColors g_ForegroundColor = GColors::LIGHT_WHITE;

//tổng hợp của background color và foreground color
WORD g_ConsoleColor;

//Lưu những màu tạm thời được sử dụng, không phải màu cho dùng chung
GColors g_TempBackgroundColor = g_BackgroundColor;
GColors g_TempForegroundColor = g_ForegroundColor;

//Lưu màu tạm thời được sử dụng, không phải màu cho dùng chung (kết hợp của g_TempBackgroundColor và g_TempForegroundColor)
WORD g_TempColor;

//mảng buffer dùng để vẽ
CHAR_INFO g_ConsoleBuffer[WIDTH * HEIGH];

//mảng trạng thái của các phím
bool g_ArrKeys[256];

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



//-------------------------------------------------
//các biến dùng cho hàm GIsElapsed
long g_lastTick = timeGetTime();
long g_currentTick = g_lastTick;


//-------------------------------------------------

//các biến dùng để tính FPS, ko dùng để tính delta time
float g_fps;
long g_lastTick_fps = timeGetTime();
long g_currentTick_fps = g_lastTick_fps;

//-------------------------------------------------


//FUNCTIONs

//set no scroll bar
void GSetNoScroolBar()
{
	//set windows first, because can not set screen buffer's size bigger than window's size
	//set windows size
	SMALL_RECT windowSize = {0, 0, WIDTH - 1, HEIGH - 1};
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	
	//can not set buffer's size less than window's size
	//set buffersize
	COORD newSBSize;
	newSBSize.X = WIDTH;
	newSBSize.Y = HEIGH;
	SetConsoleScreenBufferSize(hConsole, newSBSize);

	//////////////////////////////////////////////////////////////////////////
	/// SET AGAIN FOR OK ///
	
	if(!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		MessageBox((HWND)hConsole, "Can not set Window Size!", "Error", MB_OK);
	}

	if(!SetConsoleScreenBufferSize(hConsole, newSBSize))
	{
		MessageBox((HWND)hConsole, "Can not set Screen Buffer Size!", "Error", MB_OK);
	}
}



//set vị trí cho cửa sổ
void GSetWindowPosition(int x, int y)
{
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, x, y, WIDTH, HEIGH, TRUE);
}





// Ẩn hiện con trỏ nhấp nháy trong cửa sổ Console
void GSetCursorVisiable(bool bIsVisiable)
{
	CONSOLE_CURSOR_INFO cursor = {1, bIsVisiable};
	SetConsoleCursorInfo(hConsole, &cursor);
}




// Set font
//fontWidth = 8, fontHeight = 8 is the best way for game
//fontWeigh: 100 -> 1000
void GSetFont(int fontWidth, int fontHeight,  int fontWeight, GFontFamilys fontFamily)
{
	PCONSOLE_FONT_INFOEX lpFontInfo = new CONSOLE_FONT_INFOEX() ;
	
	// set the size of the CONSOLE_FONT_INFOEX
	lpFontInfo->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	// get the current value
	GetCurrentConsoleFontEx(hConsole, TRUE, lpFontInfo);	

	lpFontInfo->nFont = 2; //chỉ số của font trong list font console

	lpFontInfo->FontFamily = fontFamily;

	/*
	FontWeight
	The font weight. The weight can range from 100 to 1000, in multiples of 100. For example, the normal weight is 400, while 700 is bold.
	*/
	if(fontWeight >= 100 && fontWeight <= 1000)
	{
		lpFontInfo->FontWeight = fontWeight;
	}

	// set size to be 8x8, the default size is 8x16
	lpFontInfo->dwFontSize.X = fontWidth;
	lpFontInfo->dwFontSize.Y = fontHeight;

	// submit the settings
	SetCurrentConsoleFontEx(hConsole, 0, lpFontInfo);
}



//cài màu chữ
void GSetTextColor( GColors color )
{
	g_ForegroundColor = color;
	g_TempColor = g_ConsoleColor = (g_ConsoleColor & 0xF0) | (color & 0x0F);
	SetConsoleTextAttribute(
		hConsole,
		g_ConsoleColor
		);
}


//cài màu nền
void GSetBGColor( GColors color )
{
	g_BackgroundColor = color;

	g_TempColor = g_ConsoleColor = (g_ConsoleColor & 0x0F) | ((color & 0x0F) << 4);
	SetConsoleTextAttribute(
		hConsole,
		g_ConsoleColor
		);
}



//play 1 file âm thanh WAV
void GPlaySound(char* fileWAV, bool isLoop)
{
	if(isLoop)
		PlaySound(
			TEXT(fileWAV), 
			NULL, 
			SND_LOOP |	//lặp âm thanh forever cho đến khi gọi hàm PlaySound tiếp theo
			SND_ASYNC	//mở âm thanh, và không dừng chương trình lại
		); 
	else
		PlaySound(
			TEXT(fileWAV), 
			NULL, 
			SND_ASYNC	//mở âm thanh, và không dừng chương trình lại
		); 
}




//Kiểm tra trạng thái phím có đang down
bool GIsKeyDown(int vkCode)
{
	return (GetAsyncKeyState(vkCode) & 0x8000);
}



//Kiểm tra trạng thái phím có đang up
bool GIsKeyUp(int vkCode)
{
	return (!(GetAsyncKeyState(vkCode) & 0x8000));
}



//Kiểm tra xem có phím vKey vừa nhấn ko
bool GIsKeyPress(GKeys vKey)
{
	bool res = false;

	if(vKey < 0 || vKey > 255)
		return false;

	if(GetKeyState(vKey) & 0xff00)
	{
		if(g_ArrKeys[vKey] == false)
			res = true;
		else
			res = false;

		g_ArrKeys[vKey] = true;
	} 
	else
	{
		res = false;
		g_ArrKeys[vKey] = false;
	}

	return res;
}



//Kiểm tra xem có phím vKey vừa thả ra ko
bool GIsKeyRelease(GKeys vKey)
{
	bool res = false;

	if(vKey < 0 || vKey > 255)
		return false;

	if(GetKeyState(vKey) & 0xff00)
	{
		res = false;
		g_ArrKeys[vKey] = true;
	} 
	else
	{
		if(g_ArrKeys[vKey] == true)
			res = true;
		else
			res = false;

		g_ArrKeys[vKey] = false;
	}

	return res;
}



//kiểm tra xem đã qua thời gian elapsedMilisecond kể từ lần gọi trước chưa
bool GIsElapsed(long elapsedMilisecond)
{
	g_currentTick = timeGetTime();

	if(g_currentTick - g_lastTick >= elapsedMilisecond)
	{
		g_lastTick += elapsedMilisecond;
		return true;
	}
	else
	{
		return false;
	}
}




//get fps
float GGetFPS()
{
	long tmpLastTick_fps = g_lastTick_fps;
	g_lastTick_fps = g_currentTick_fps;
	g_currentTick_fps = timeGetTime();

	g_fps = (float)1000 / (float)(g_currentTick_fps - tmpLastTick_fps);

	return g_fps;
}




/*
 *This method draws the rectangle, no background
 *Usage:
 *GDrawRect(1,1,10,10);
 *or
 *GDrawRect(1,1,10,10,20,5);
 */
void GDrawRect(GRectangle rect, GColors borderColor)
{
	float x = rect.x;
	float y = rect.y;
	float width = rect.width;
	float height = rect.height;
	GColors colorBorder = borderColor;

	GPutCharToBuffer(char(178),x,y,colorBorder);

	for(int i = 1; i < width; i++)
	{
		GPutCharToBuffer(char(178),x+i,y,colorBorder);
	}

	GPutCharToBuffer(char(178),x + width,y,colorBorder);
	GPutCharToBuffer(char(178),x,y + height,colorBorder);
	
	for(int i = 1; i < width; i++)
		GPutCharToBuffer(char(178),x +i,y + height,colorBorder);

	GPutCharToBuffer(char(178),x + width,y + height,colorBorder);

	for(int i = 1; i < height ; i++)
	{
		GPutCharToBuffer(char(178),x,y+i,colorBorder);
		GPutCharToBuffer(char(178),x + width,y+i,colorBorder);
	}
}



/*Fill a rectangle
 *
 *Ex: GFillRect(0, 0, 10, 10, GColors::WHITE, GColors::BLACK);
 */
void GFillRect(GRectangle rect, GColors borderColor, GColors foreColor)
{
	float x = rect.x;
	float y = rect.y;
	float width = rect.width;
	float height = rect.height;
	GColors colorBorder = borderColor;
	GColors colorBG = foreColor;


	GPutCharToBuffer(char(178),x,y,colorBorder);

	for(int i = 1; i < width; i++)
	{
		GPutCharToBuffer(char(178),x+i,y,colorBorder);
	}

	for(int i = 1; i < width; i++)
	{
		for(int j = 1; j < height ; j++)
			GPutCharToBuffer(char(178),x+i,y+j,colorBG);
	}

	GPutCharToBuffer(char(178),x + width,y,colorBorder);
	GPutCharToBuffer(char(178),x,y + height,colorBorder);

	for(int i = 1; i < width; i++)
		GPutCharToBuffer(char(178),x +i,y + height,colorBorder);

	GPutCharToBuffer(char(178),x + width,y + height,colorBorder);

	for(int i = 1; i < height ; i++)
	{
		GPutCharToBuffer(char(178),x,y+i,colorBorder);
		GPutCharToBuffer(char(178),x + width,y+i,colorBorder);
	}
}


//kiểm tra 2 hình chữ nhật có va chạm nhau
//tức là có điểm chung nào hay ko
bool GIsIntersect(GRectangle a, GRectangle b)
{
	return !(a.x > b.x + b.width || a.x + a.width < b.x || a.y > b.y + b.height || a.y + a.height < b.y);
}


/////////////////////////////////////////////////////////////////////////////

//BUFFER's FUNCTIONs

//Xóa hết buffer CHAR_INFO
void GClearBuffer()
{
	for (int y = 0; y < HEIGH; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			// An ANSI character is in the range 0-255,
			// so use % to keep it in this range.
			g_ConsoleBuffer[x + WIDTH * y].Char.AsciiChar = ' ';
			
			// The colour is also in the range 0-255,
			// as it is a pair of 4-bit colours.
			g_ConsoleBuffer[x + WIDTH * y].Attributes = g_ConsoleColor;
		}
	}
}



//Viết 1 ký tự lên buffer CHAR_INFO
void GPutCharToBuffer(char c, int x, int y, GColors foregroundColor, GColors backgroundColor)
{
	if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGH)
		return;

	// An ANSI character is in the range 0-255,
	// so use % to keep it in this range.
	g_ConsoleBuffer[x + WIDTH * y].Char.AsciiChar = c;


	if(foregroundColor != g_TempForegroundColor || backgroundColor != g_TempBackgroundColor )
	{
		g_TempForegroundColor = foregroundColor;
		g_TempBackgroundColor = backgroundColor;

		g_TempColor = g_ConsoleColor;

		g_TempColor = (g_TempColor & 0xF0) | (g_TempForegroundColor & 0x0F);
 		g_TempColor = (g_TempColor & 0x0F) | ((g_TempBackgroundColor & 0x0F) << 4);

		// The colour is also in the range 0-255,
		// as it is a pair of 4-bit colours.
		g_ConsoleBuffer[x + WIDTH * y].Attributes =  g_TempColor;
	}
	else
	{
		// The colour is also in the range 0-255,
		// as it is a pair of 4-bit colours.
		g_ConsoleBuffer[x + WIDTH * y].Attributes =  g_TempColor;
	}
}



//Viết 1 chuỗi lên buffer CHAR_INFO
void GPutStringToBuffer(char str[], int x, int y,  GColors foregroundColor, GColors backgroundColor)
{
	int len = strlen(str);

	for (int i = 0; i < len; ++i)
	{
		GPutCharToBuffer(str[i], i + x, y, foregroundColor, backgroundColor);
	}
}



//Flush all buffer CHAR_INFO to screen
void GFlushBuffer()
{
	// Set up the positions:
	COORD charBufSize = {WIDTH, HEIGH};
	COORD characterPos = {0, 0};
	SMALL_RECT writeArea = {0, 0, WIDTH - 1, HEIGH - 1}; 

	// Write the characters:
	WriteConsoleOutputA(hConsole, g_ConsoleBuffer, charBufSize, characterPos, &writeArea);
}




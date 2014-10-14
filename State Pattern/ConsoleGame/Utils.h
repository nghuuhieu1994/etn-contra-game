
#ifndef __UTILS_H__
#define __UTILS_H__
#pragma once

#pragma comment( lib, "winmm.lib" )

#include "conio.h"
#include <windows.h>


//CONSTANSTs

#define WIDTH 80
#define HEIGH 40



//ENUM

//Keys
typedef enum GKeys
{
	KEY_A    =0x41,
	KEY_B    =0x42,
	KEY_C    =0x43,
	KEY_D    =0x44,
	KEY_E    =0x45,
	KEY_F    =0x46,
	KEY_G    =0x47,
	KEY_H    =0x48,
	KEY_I    =0x49,
	KEY_J    =0x4A,
	KEY_K    =0x4B,
	KEY_L    =0x4C,
	KEY_M    =0x4D,
	KEY_N    =0x4E,
	KEY_O    =0x4F,
	KEY_P    =0x50,
	KEY_Q    =0x51,
	KEY_R    =0x52,
	KEY_S    =0x53,
	KEY_T    =0x54,
	KEY_U    =0x55,
	KEY_V    =0x56,
	KEY_W    =0x57,
	KEY_X    =0x58,
	KEY_Y    =0x59,
	KEY_Z    =0x5A,
	KEY_LEFT    =VK_LEFT,
	KEY_RIGHT   =VK_RIGHT,
	KEY_UP      =VK_UP,
	KEY_DOWN    =VK_DOWN,
	KEY_ESC     =VK_ESCAPE,
	KEY_ENTER	=VK_RETURN,
	KEY_SPACE	=VK_SPACE,
	KEY_DELETE	=VK_DELETE,
} GKeys;



//màu sắc
typedef enum GColors
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
	LIGHT_BLACK,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_YELLOW,
	LIGHT_WHITE,	
} GColors;



//hướng di chuyển
typedef enum GDirections
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
} GDirections;



//font Family
typedef enum GFontFamilys
{
	MODERN			=FF_MODERN,
	DECORATIVE		=FF_DECORATIVE,
	DONTCARE		=FF_DONTCARE,
	ROMAN			=FF_ROMAN,
	SCRIPT			=FF_SCRIPT,
	SWISS			=FF_SWISS,
} GFontFamilys;


//STRUCTs

//Điểm
typedef struct GPoint2D
{
	int x;
	int y;
} GPoint2D;


//Hình chữ nhật
typedef struct GRectangle
{
	float x;
	float y;
	float width;
	float height;
} GRectangle;


//VARIANTs

//màu background và màu chữ
extern GColors g_BackgroundColor;// = GColors::BLACK;
extern GColors g_ForegroundColor;// = GColors::LIGHT_WHITE;

//tổng hợp của background color và foreground color
extern WORD g_ConsoleColor;

//Lưu những màu tạm thời được sử dụng, không phải màu cho dùng chung
extern GColors g_TempBackgroundColor;// = g_BackgroundColor;
extern GColors g_TempForegroundColor;// = g_ForegroundColor;

//Lưu màu tạm thời được sử dụng, không phải màu cho dùng chung (kết hợp của g_TempBackgroundColor và g_TempForegroundColor)
extern WORD g_TempColor;

//mảng buffer dùng để vẽ
extern CHAR_INFO g_ConsoleBuffer[WIDTH * HEIGH];

//mảng trạng thái của các phím
extern bool g_ArrKeys[256];

extern HANDLE hConsole;// = GetStdHandle(STD_OUTPUT_HANDLE);

//------------------------------------------------

//các biến dùng cho hàm GIsElapsed
extern long g_lastTick;// = timeGetTime();
extern long g_currentTick;// = g_lastTick;

//------------------------------------------------

//các biến dùng để tính FPS, ko dùng để tính delta time
extern float g_fps;
extern long g_lastTick_fps;// = timeGetTime();
extern long g_currentTick_fps;// = g_lastTick_fps;


//declare
void GSetNoScroolBar();
void GSetWindowPosition(int x, int y);
void GSetCursorVisiable(bool bIsVisiable = false);
void GSetFont(int fontWidth = 8, int fontHeight = 8,  int fontWeight = 100, GFontFamilys fontFamily = GFontFamilys::MODERN);
void GSetTextColor(GColors color);
void GSetBGColor(GColors color);
void GPlaySound(char* fileWAV, bool isLoop);
bool GIsKeyDown(int vkCode);
bool GIsKeyUp(int vkCode);
bool GIsKeyPress(GKeys vKey);
bool GIsKeyRelease(GKeys vKey);
bool GIsElapsed(long elapsedMilisecond);
float GGetFPS();
void GDrawRect(GRectangle rect, GColors borderColor);
void GFillRect(GRectangle rect, GColors borderColor, GColors foreColor);
bool GIsIntersect(GRectangle a, GRectangle b);
void GClearBuffer();
void GPutCharToBuffer(char c, int x, int y, GColors foregroundColor = g_ForegroundColor, GColors backgroundColor = g_BackgroundColor);
void GPutStringToBuffer(char str[], int x, int y,  GColors foregroundColor = g_ForegroundColor, GColors backgroundColor = g_BackgroundColor);
void GFlushBuffer();



#endif //__UTILS_H__

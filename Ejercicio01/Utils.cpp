#include "Utils.h"

bool GoTo(int x, int y)
{

	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	coord.X = x;
	coord.Y = y;

	return SetConsoleCursorPosition(hndl, coord);
}

bool GoTo(mth::Vector2 pos)
{
	return GoTo(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void HideCursor()
{
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cInfo;
	cInfo.dwSize = 1;
	cInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hndl, &cInfo);
}
#include "../includes/utils.hpp"

#pragma comment(lib, "MSIMG32.LIB")
void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void DrawBBox(int x, int y, int width, int height)
{
	line(x, y, x + width, y);
	line(x, y, x , y+ height);
	line(x, y + height, x + width, y + height);
	line(x+ width, y, x + width, y + height);
}

void DrawTipText(int x)
{
	static TCHAR str[64];
	_stprintf_s(str, _T("%d"), x);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 175, 45));
	outtextxy(10, 10, str);
}
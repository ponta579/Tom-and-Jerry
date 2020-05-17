#include "dogClass.h"
dogClass::dogClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img, int k) :myBase(x, y, w, h, dx, dy, score, img)
{
	this->k = k;
}

void dogClass::move(rect winRect)
{
	if (k <= 50)
	{
		x += dx;
		y += dy;
	}
	if (k > 50 && k <= 100)
	{
		x -= dx;
		y -= dy;
	}
	if (x < 0)dx *= -1;
	if (y < 0)dy *= -1;
	if (x > winRect.w - w)dx *= -1;
	if (y > winRect.h - h)dy *= -1;
}
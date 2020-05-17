#include "tuffyClass.h"
tuffyClass::tuffyClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img,int k):myBase(x,y,w,h,dx,dy,score,img)
{
	this->k = k;
}
tuffyClass::tuffyClass(tuffyClass& tuffyclass):myBase(tuffyclass)
{

}
void tuffyClass::move()
{
	if (k <= 20)
	{
		x += dx;
		y += dy;
	}
	if (k > 20 && k <= 40)
	{
		x -= dx;
		y -= dy;
	}
	if (k > 40 && k <= 60)
	{
		x += dx;
		y -= dy;
	}
	if (k > 60 && k <= 80)
	{
		x -= dx;
		y += dy;
	}
	if (k > 80 && k <= 85)
	{
		x += dx;
		y -= 1;
	}
	if (k > 85 && k <= 90)
	{
		x -= dx;
		y += 1;
	}
	if (k > 90 && k <= 95)
	{
		y += dy;
		x += 1;
	}
	if (k > 95 && k <= 100)
	{
		y -= dy;
		x -= 1;
	}
}
int tuffyClass::ifOut(rect winRect)
{
	if (x<0-w || x>winRect.w || y<0-h || y>winRect.h)
		return 1;
	else
		return 0;
}
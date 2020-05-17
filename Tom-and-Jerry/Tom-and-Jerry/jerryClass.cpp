#include "jerryClass.h"
jerryClass::jerryClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img):myBase(x,y,w,h,dx,dy,score,img)
{

}
jerryClass::jerryClass(jerryClass& stillclass):myBase(stillclass)
{

}
void jerryClass::move(rect winRect)
{
	y += dy;
	x += dx;
	if (x < 0)dx *= -1;
	if (y < 0)dy *= -1;
	if (x > winRect.w - w)dx *= -1;
	if (y > winRect.h - h)dy *= -1;
}
jerryClass::~jerryClass()
{

}
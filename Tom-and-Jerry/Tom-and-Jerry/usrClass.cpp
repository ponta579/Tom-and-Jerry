#include "usrClass.h"
usrClass::usrClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img):myBase(x,y,w,h,dx,dy,score,img)
{

}
usrClass::usrClass(usrClass& usr):myBase(usr)
{

}
void usrClass::change(int ww, int hh,int distX,int distY)
{
	w = ww;
	h = hh;
	dx = distX;
	dy = distY;
}
void usrClass::move(int key,rect winRect)
{
	switch (key)
	{
	case VK_UP:
		y -= dy;
		if (y <= 0)y = 0;
		break;
	case VK_DOWN:
		y += dy;
		if (y >= winRect.h - h)y = winRect.h - h;
		break;
	case VK_LEFT:
		x -= dx;
		if (x < 0)x = 0;
		break;
	case VK_RIGHT:
		x += dx;
		if (x > winRect.w - w)x = winRect.w - w;
		break;
	default:
		break;
	}
}
usrClass::~usrClass()
{

}
#include "myBase.h"
myBase::myBase(int x, int y, int w, int h, int dx, int dy, int socre,ACL_Image* img)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->dx = dx;
	this->dy = dy;
	this->img = img;
	this->score = score;
}
myBase::myBase(myBase& mybase)
{
	x = mybase.x;
	y = mybase.y;
	w = mybase.w;
	h = mybase.h;
	dx = mybase.dx;
	dy = mybase.dy;
	img = mybase.img;
	score = mybase.score;
	r = mybase.r;
}
myBase::~myBase()
{

}

void myBase::draw(int w, int h)
{
	putImageTransparent(img, x, y, w, h, RGB(32, 30, 31));
}
void myBase::draw()
{
	putImage(img, x, y);
}
int myBase::collision(rect r2)
{
	r = { this->x,this->y,this->w,this->h };
	int c = 1;//返回c看是否碰撞
	if (r.x<r2.x && r.x + r.w>r2.x)//该矩形在另一个矩形的左边
	{
		if (r.y > r2.y && r.y < r2.y + r2.h)return c;//该矩形在另一个矩形的左下角相碰撞
		if (r.y<r2.y && r.y + r.h>r2.y)return c;
	}
	else {
		if (r.x > r2.x && r2.x + r2.w > r.x)
		{
			if (r.y > r2.y && r2.y + r2.h > r.y)return c;
			if (r.y<r2.y && r.y + r.h>r2.y)return c;
		}
	}
	c = 0;
	return c;
}
rect myBase::getRect()
{
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}
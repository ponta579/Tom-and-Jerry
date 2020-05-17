#pragma once
#include"acllib.h"
class myBase
{
protected:
	int x, y;
	int w, h;
	int dx, dy;
	int score;
	ACL_Image* img;
	rect r;
public:
	virtual ~myBase();
	myBase(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img);
	myBase(myBase& mybase);
	void draw(int w, int h);
	void draw();
	rect getRect();
	int collision(rect r2);//Åö×²¼ì²â
};


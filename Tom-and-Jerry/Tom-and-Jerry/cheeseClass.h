#pragma once
#include "myBase.h"
class cheeseClass :
	public myBase
{
	int k;
public:
	cheeseClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img, int k);
	cheeseClass(cheeseClass& cheeseclass);
	int ifOut(rect winRect);
	void move();
};


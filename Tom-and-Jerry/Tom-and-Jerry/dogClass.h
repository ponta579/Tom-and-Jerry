#pragma once
#include "myBase.h"
class dogClass :
	public myBase
{
	int k;
public:
	dogClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img, int k);
	void move(rect winRect);
};
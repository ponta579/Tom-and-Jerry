#pragma once
#include "myBase.h"
class tuffyClass :
	public myBase
{
	int k;
public:
	tuffyClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img,int k);
	tuffyClass(tuffyClass& tuffyclass);
	int ifOut(rect winRect);
	void move();
};


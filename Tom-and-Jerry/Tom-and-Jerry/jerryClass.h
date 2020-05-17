#pragma once
#include "myBase.h"
class jerryClass :
	public myBase
{
public:
	~jerryClass();
	jerryClass(int x, int y, int w, int h, int dx, int dy, int score, ACL_Image* img);
	jerryClass(jerryClass& stillclass);
	void move(rect winRect);
};


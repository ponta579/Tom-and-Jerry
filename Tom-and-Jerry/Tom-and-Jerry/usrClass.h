#pragma once
#include "myBase.h"
class usrClass :
	public myBase
{
public:
	usrClass(int x, int y, int w, int h, int dx, int dy, int score,ACL_Image* img);
	usrClass(usrClass& usr);
	void move(int key,rect winRect);
	void change(int ww, int hh,int distX,int distY);//�ı��û��Ĵ�С���ƶ��ٶ�
	~usrClass();
};

#include"acllib.h"
#include"tuffyClass.h"
#include"myBase.h"
#include"jerryClass.h"
#include"usrClass.h"
#include"dogClass.h"
#include"cheeseClass.h"
#include<iostream>
#include<conio.h>
#include<ctime>
using namespace std;

rect winRect;
const int maxNum = 300;
jerryClass* jerry[maxNum] = { NULL };
tuffyClass* tuffy[maxNum] = { NULL };
dogClass* dog[maxNum] = { NULL };
cheeseClass* cheese[maxNum] = {NULL};
usrClass* tom = NULL;
int tomWidth , tomHeight , tomDistX , tomDistY ;//tom的初始参数
int tomW , tomH ,tomDx , tomDy ;//tom的即时参数
int jerryNum , tuffyNum ,dogNum,cheeseNum;//各类当前数量
int jerryW, jerryH, jerryDx, jerryDy, jerryScore;
int tuffyW, tuffyH, tuffyDx, tuffyDy, tuffyScore;
int dogW, dogH , dogDx , dogDy, dogScore;
int cheeseW, cheeseH, cheeseDx, cheeseDy, cheeseScore;
int score;//玩家总分
int myClock;//游戏倒计时
int life ;//初始生命
bool gamebegin ;//判定是否在开始界面
bool gameover;//判定游戏是否结束
bool intro;//判定是否在游戏说明界面
ACL_Image tomImg;
ACL_Image jerryImg;
ACL_Image tuffyImg;
ACL_Image startImg;
ACL_Image dogImg;
ACL_Image cheeseImg;
ACL_Image bgImg;
ACL_Image winImg;
ACL_Image failedImg;
ACL_Image introImg;
ACL_Sound getSound;
ACL_Sound ingSound;

void initGame();//初始化游戏
void gameOver();//游戏结束
void creat(usrClass* usrclass);
void creat(jerryClass* stillclass);
void creat(tuffyClass* tuffyclass);
void creat(dogClass* dogclass);
void creat(cheeseClass* cheeseclass);
void keyboardEvent(int key, int event);
void timerEvent(int id);
void charEvent(char c);//开始界面字符读取
void paint();
void picPaint(ACL_Image* img);//开始、结束、说明界面绘制
void scorePaint(int x,int y);
int Setup()
{	
	winRect.x = 220;
	winRect.y = 100;
	winRect.w = 1000;
	winRect.h = 600;
	initWindow("Tom and Jerry", winRect.x, winRect.y, winRect.w,winRect.h);
	loadImage("rsc/jerry.bmp", &jerryImg);
	loadImage("rsc/tom.bmp", &tomImg);
	loadImage("rsc/Tuffy.bmp", &tuffyImg);
	loadImage("rsc/start.jpg", &startImg);
	loadImage("rsc/dog.bmp", &dogImg);
	loadImage("rsc/cheese.bmp", &cheeseImg);
	loadImage("rsc/bg.jpg", &bgImg);
	loadImage("rsc/win.jpg", &winImg);
	loadImage("rsc/failed.jpg", &failedImg);
	loadImage("rsc/intro.jpg", &introImg);
	loadSound("rsc/begin.wav", &ingSound);
	loadSound("rsc/get.wav", &getSound);
	initGame();
	srand((unsigned)time(NULL));
	picPaint(&startImg);
	playSound(ingSound, 1);//循环播放
	registerCharEvent(charEvent);//开始界面 注册字符输入回调函数
	return 0;
}
void initGame()
{
	tomWidth = 100, tomHeight = 100, tomDistX = 2, tomDistY = 2;//tom的初始参数
	tomW = tomWidth, tomH = tomHeight, tomDx = tomDistX, tomDy = tomDistY;//tom的现在参数
	jerryNum = 0, tuffyNum = 0, dogNum = 0, cheeseNum = 0;
	jerryW = 60, jerryH = 60;
	jerryDx = 2, jerryDy = 2, jerryScore = 1;
	tuffyW = 70; tuffyH = 70;
	tuffyDx = 3; tuffyDy = 3; tuffyScore = 4;
	dogW = 100; dogH = 120;
	dogDx = 2; dogDy = 2; dogScore = -5;
	cheeseW = 50, cheeseH = 50;
	cheeseDx = 1, cheeseDy = 1, cheeseScore = 4;
	score = 0;//玩家总分初始化为0
	myClock = 120;//游戏倒计时120s
	life = 5;//初始生命5条
	gamebegin = 1;
	gameover = 0;
	intro = 0;
}
void gameOver()
{
	cancelTimer(0);
	cancelTimer(1);
	cancelTimer(2);
	delete tom;
	tom = NULL;
	for (int i = 0; i < jerryNum; i++)//释放jerry
	{
		if (jerry[i])
		{
			delete jerry[i];
			jerry[i] = NULL;
		}
	}
	for (int i = 0; i < tuffyNum; i++)//释放tuffy
	{
		if (tuffy[i])
		{
			delete tuffy[i];
			tuffy[i] = NULL;
		}
	}
	for (int i = 0; i < dogNum; i++)//释放dog
	{
		if (dog[i])
		{
			delete dog[i];
			dog[i] = NULL;
		}
	}
	for (int i = 0; i < cheeseNum; i++)//释放tuffy
	{
		if (cheese[i])
		{
			delete cheese[i];
			cheese[i] = NULL;
		}
	}
	if (score >= 100 && life > 0)
	{
		picPaint(&winImg);
		scorePaint(825, 537);
	}
	else
	{
		picPaint(&failedImg);
		scorePaint(423, 326);
	}
}
void charEvent(char c)
{
	if ( ( (c == 'p'||c=='P')&&gamebegin==1 )||(c == 'p' && intro == 1) )//在开始界面或说明界面输入p
	{
		creat(tom);
		creat(jerry[jerryNum]);
		registerKeyboardEvent(keyboardEvent);
		registerTimerEvent(timerEvent);
		startTimer(0, 1000);//自动类生成定时器
		startTimer(1, 20);//自动类移动定时器
		startTimer(2, 1000);//倒计时定时器
		gamebegin=0;//此时不在开始界面
		intro = 0;//此时不在说明界面
	}
	if ( (c == 'h' ||c=='H')&& gamebegin == 1)//在游戏初始界面按h键进入游戏说明界面
	{
		picPaint(&introImg);
		intro = 1;//此时在intro界面
		gamebegin = 0;//此时不在begin界面
	}
	if ( (c == 'r' || c == 'R') && intro == 1 )//在游戏说明界面按r
	{
		picPaint(&startImg);
		intro = 0;//不在说明界面
		gamebegin = 1;//又回到了初始界面
	}
	if ( (c == 'r' || c == 'R') && gameover == 1 )//游戏失败界面按r
	{
		picPaint(&startImg);
		initGame();
	}
}
void creat(usrClass* usrclass)
{
	int x = rand() % (winRect.w-tomW);
	int y = rand() % (winRect.h-tomH);
	tom = new usrClass(x, y, tomW, tomH, tomDx, tomDy, 0, &tomImg);
}
void creat(jerryClass* stillclass)
{
	int x = rand() % (winRect.w-jerryW);
	int y = rand() % (winRect.h-jerryH);
	if(jerry[jerryNum]==NULL)
	jerry[jerryNum++] = new jerryClass(x, y, jerryW, jerryH, jerryDx, jerryDy, jerryScore, &jerryImg);
}
void creat(tuffyClass* tuffyclass)
{
	int x = rand() % (winRect.w - tuffyW);
	int y = rand() % (winRect.h - tuffyH);
	int k = rand() % 101;
	if (tuffy[tuffyNum] == NULL)
		tuffy[tuffyNum++] = new tuffyClass(x, y, tuffyW, tuffyH, tuffyDx, tuffyDy, tuffyScore, &tuffyImg, k);
}
void creat(dogClass* dogclass)
{
	int x = rand() % (winRect.w - dogW);
	int y = rand() % (winRect.h - dogH);
	int k = rand() % 101;
	if (dog[dogNum] == NULL)
		dog[dogNum++] = new dogClass(x, y, dogW, dogH, dogDx, dogDy, dogScore, &dogImg, k);
}
void creat(cheeseClass* cheeseclass)
{
	int x = rand() % (winRect.w - cheeseW);
	int y = rand() % (winRect.h - cheeseH);
	int k = rand() % 101;
	if (cheese[cheeseNum] == NULL)
		cheese[cheeseNum++] = new cheeseClass(x, y, cheeseW, cheeseH, cheeseDx, cheeseDy, cheeseScore, &cheeseImg, k);
}
void keyboardEvent(int key, int event)
{
	if (event != KEY_DOWN)return;
	if(tom)
	tom->move(key, winRect);
	for (int i = 0; i < jerryNum; i++)
	{
		if (jerry[i])
		{
			if (tom->collision(jerry[i]->getRect()))
			{
				delete(jerry[i]);
				jerry[i] = NULL;
				score += jerryScore;
				playSound(getSound, 0);
			}
		}
	}
	for (int i = 0; i < tuffyNum; i++)
	{
		if (tuffy[i])
		{
			if (tom->collision(tuffy[i]->getRect()))
			{
				delete(tuffy[i]);
				tuffy[i] = NULL;
				score += tuffyScore;
				playSound(getSound, 0);
			}
		}
	}
	for (int i = 0; i < dogNum; i++)
	{
		if (dog[i])
		{
			if (tom->collision(dog[i]->getRect()))
			{
				delete(dog[i]);
				dog[i] = NULL;
				score += dogScore;
				playSound(getSound, 0);
				life--;
				if (life == 0)
				{
					gameOver();
					gameover = 1;
					return;
				}
			}
		}
	}
	for (int i = 0; i < cheeseNum; i++)
	{
		if (cheese[i])
		{
			if (tom->collision(cheese[i]->getRect()))
			{
				delete(cheese[i]);
				cheese[i] = NULL;
				score += cheeseScore;
				playSound(getSound, 0);
				life++;
				if (life > 5)
					life = 5;
			}
		}
	}
	if(tom)
	paint();
}
void paint()
{
	if (gameover == 0)
	{
		beginPaint();
		clearDevice();
		putImageScale(&bgImg, 0, 0, winRect.w, winRect.h);
		if (tom)
		{
			switch (score / 15)//分数为15的倍数时，tom变大,速度变快.75分时体积最大
			{
			case 0:
				break;
			case 1:tomW = tomWidth + 12;
				tomH = tomHeight + 12;
				tomDx = tomDistX + 1;
				tomDy = tomDistY + 1;
				tom->change(tomW, tomH, tomDx, tomDy);
				break;
			case 2:
				tomW = tomWidth + 24;
				tomH = tomHeight + 24;
				tomDx = tomDistX + 3;
				tomDy = tomDistY + 3;
				tom->change(tomW, tomH, tomDx, tomDy);
				break;
			case 3:
				tomW = tomWidth + 36;
				tomH = tomHeight + 36;
				tomDx = tomDistX + 4;
				tomDy = tomDistY + 4;
				tom->change(tomW, tomH, tomDx, tomDy);
				break;
			case 4:
				tomW = tomWidth + 48;
				tomH = tomHeight + 48;
				tomDx = tomDistX + 5;
				tomDy = tomDistY + 5;
				tom->change(tomW, tomH, tomDx, tomDy);
				break;
			default:
				tomW = tomWidth + 60;
				tomH = tomHeight + 60;
				tomDx = tomDistX + 6;
				tomDy = tomDistY + 6;
				tom->change(tomW, tomH, tomDx, tomDy);
				break;
			}
			tom->draw(tomW, tomH);
		}
		for (int i = 0; i < jerryNum; i++)
		{
			if (jerry[i] != NULL)
				jerry[i]->draw(jerryW, jerryH);
		}
		for (int i = 0; i < tuffyNum; i++)
		{
			if (tuffy[i] != NULL)
				tuffy[i]->draw(tuffyW, tuffyH);
		}
		for (int i = 0; i < dogNum; i++)
		{
			if (dog[i] != NULL)
				dog[i]->draw(dogW, dogH);
		}
		for (int i = 0; i < cheeseNum; i++)
		{
			if (cheese[i] != NULL)
				cheese[i]->draw(cheeseW, cheeseH);
		}
		int lifeX = 250, lifeY = 10;
		for (int i = 0; i < life; i++)//生命值绘制
		{
			lifeX += 40;
			putImageTransparent(&cheeseImg, lifeX, lifeY, 30, 30, WHITE);
		}
		char txt[20];
		if (score < 0)
			score = 0;
		sprintf_s(txt, "score:%d   time:%d", score, myClock);
		setTextSize(20);
		paintText(10, 10, txt);
		endPaint();
	}
}
void picPaint(ACL_Image* img)//开始界面绘制
{
	beginPaint();
	clearDevice();
	putImageScale(img, 0, 0, winRect.w, winRect.h);
	endPaint();
}
void scorePaint(int x,int y)
{
	char txt[10];
	sprintf_s(txt, "%d", score);
	beginPaint();
	setTextSize(50);
	paintText(x, y, txt);
	endPaint();
}
void timerEvent(int id)
{
	int randNum = rand() % 101;
	switch (id)
	{
	case 0://自动类生成
		if (score <= 10)//第一关
		{
			if (randNum <= 90)
			{
				if (jerryNum < maxNum)
				{
					if (jerry[jerryNum] == NULL)
						creat(jerry[jerryNum]);
				}
			}
			else
			{
				if (tuffyNum < maxNum)
				{
					if (tuffy[tuffyNum] == NULL)
						creat(tuffy[tuffyNum]);
				}
			}
		}
		else if (score > 10 && score <= 30)//第二关
		{
			if (randNum <= 72)
			{
				if (jerryNum < maxNum)
				{
					if (jerry[jerryNum] == NULL)
						creat(jerry[jerryNum]);
				}
			}
			else if (randNum > 72 && randNum <= 92)
			{
				if (tuffyNum < maxNum)
				{
					if (tuffy[tuffyNum] == NULL)
						creat(tuffy[tuffyNum]);
				}
			}
			else //if (randNum > 92 && randNum <= 97)
			{
				if (dogNum < maxNum)
				{
					if (dog[dogNum] == NULL)
						creat(dog[dogNum]);
				}
			}
			/*
			else
			{
				if (cheeseNum < maxNum)
				{
					if (cheese[cheeseNum] == NULL)
						creat(cheese[cheeseNum]);
				}
			}
			*/
		}
		else if (score > 30 && score <= 50)//第三关
		{
			if (randNum <= 60)
			{
				if (jerryNum < maxNum)
				{
					if (jerry[jerryNum] == NULL)
						creat(jerry[jerryNum]);
				}
			}
			else if (randNum > 60 && randNum <= 89)
			{
				if (tuffyNum < maxNum)
				{
					if (tuffy[tuffyNum] == NULL)
						creat(tuffy[tuffyNum]);
				}
			}
			else if (randNum > 89 && randNum <= 97)
			{
				if (dogNum < maxNum)
				{
					if (dog[dogNum] == NULL)
						creat(dog[dogNum]);
				}
			}
			else
			{
				if (cheeseNum < maxNum)
				{
					if (cheese[cheeseNum] == NULL)
						creat(cheese[cheeseNum]);
				}
			}
		}
		else if (score > 50&&score<=70)//第四关
		{
			if (randNum <= 57)
			{
				if (jerryNum < maxNum)
				{
					if (jerry[jerryNum] == NULL)
						creat(jerry[jerryNum]);
				}
			}
			else if (randNum > 57 && randNum <= 87)
			{
				if (tuffyNum < maxNum)
				{
					if (tuffy[tuffyNum] == NULL)
						creat(tuffy[tuffyNum]);
				}
			}
			else if (randNum > 87 && randNum <= 95)
			{
				if (dogNum < maxNum)
				{
					if (dog[dogNum] == NULL)
						creat(dog[dogNum]);
				}
			}
			else
			{
				if (cheeseNum < maxNum)
				{
					if (cheese[cheeseNum] == NULL)
						creat(cheese[cheeseNum]);
				}
			}
		}
		else if (score>70)//第五关
		{
			if (randNum <= 45)
			{
				if (jerryNum < maxNum)
				{
					if (jerry[jerryNum] == NULL)
						creat(jerry[jerryNum]);
				}
			}
			else if (randNum > 45 && randNum <= 85)
			{
				if (tuffyNum < maxNum)
				{
					if (tuffy[tuffyNum] == NULL)
						creat(tuffy[tuffyNum]);
				}
			}
			else if (randNum > 85 && randNum <= 90)
			{
				if (dogNum < maxNum)
				{
					if (dog[dogNum] == NULL)
						creat(dog[dogNum]);
				}
			}
			else
			{
				if (cheeseNum < maxNum)
				{
					if (cheese[cheeseNum] == NULL)
						creat(cheese[cheeseNum]);
				}
			}
		}
		break;
	case 1://自动类移动
		for (int i = 0; i < jerryNum; i++)//jerry移动
		{
			if (jerry[i] != NULL)
			{
				jerry[i]->move(winRect);
				if (jerry[i]->collision(tom->getRect()))
				{
					delete (jerry[i]);
					jerry[i] = NULL;
					score += jerryScore;
					playSound(getSound, 0);
				}
			}
		}
		for (int i = 0; i < tuffyNum; i++)//tuffy移动
		{
			if (tuffy[i] != NULL)
			{
				tuffy[i]->move();
				if (tuffy[i]->collision(tom->getRect()))
				{
					delete (tuffy[i]);
					tuffy[i] = NULL;
					score += tuffyScore;
					playSound(getSound, 0);
				}
				if (tuffy[i] != NULL&&tuffy[i]->ifOut(winRect))
				{
					delete tuffy[i];
					tuffy[i] = NULL;
				}
			}
		}
		for (int i = 0; i < dogNum; i++)//dog move
		{
			if (dog[i] != NULL)
			{
				dog[i]->move(winRect);
				if (dog[i]->collision(tom->getRect()))
				{
					delete (dog[i]);
					dog[i] = NULL;
					score += dogScore;
					playSound(getSound, 0);
					life--;
					if (life == 0)
					{
						gameOver();
						gameover = 1;
					}
				}
			}
		}
		for (int i = 0; i < cheeseNum; i++)//cheese move
		{
			if (cheese[i] != NULL)
			{
				cheese[i]->move();
				if (cheese[i]->collision(tom->getRect()))
				{
					delete (cheese[i]);
					cheese[i] = NULL;
					score += cheeseScore;
					playSound(getSound, 0);
					life++;
					if (life > 5)
						life = 5;
				}
				if (cheese[i] != NULL&&cheese[i]->ifOut(winRect))
				{
					delete cheese[i];
					cheese[i] = NULL;
				}
			}
		}
		break;
	case 2://倒计时
		myClock -= 1;
		if (myClock == 0)
		{
			gameOver();
			gameover = 1;
		}
		break;
	}
	if(myClock>0)
	paint();
}

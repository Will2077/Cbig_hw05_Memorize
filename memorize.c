#include <windows.h>
#include <winuser.h>
#include "extgraph.h"
#include "random.h"
#include "card.h"
#include "imgui.h"
#include <time.h>

Card cards[CARDN];
int firstClickIndex, secondClickIndex, curIndex;
int matchedCount,tryTimes;
char* tryTimeStr[80]={0};
char* matchedCountStr[80]={0};
clock_t start, finish;

//初始化卡牌 
void InitCards()
{
	double windowWidth = GetWindowWidth();
	double windowHeight = GetWindowHeight()-1.0;
	double cardWidth = (windowWidth - GAPX * (CARDX + 1)) / CARDX;
	double cardHeight = (windowHeight - GAPY * (CARDY + 1)) / CARDY;

	int i, j;
	char *colors[] = {"Red", "Green", "Blue", "Brown", "Orange", "Yellow", "Violet", "Magenta", "Cyan", "River Blue", "Light Yellow"};
	void (*drawFuncs[])(Card * pCard) = {DrawSquare, DrawRect, DrawTriangle, DrawCircle, DrawTrapezoid, DrawParallellogram, DrawClip, DrawTree, DrawFace, DrawArcheryTarget, DrawDiagram, DrawDice};

	for (i = 0; i < CARDX; i++)
	{
		double x = GAPX + (cardWidth + GAPX) * i;
		for (j = 0; j < CARDY; j++)
		{
			double y = GAPY + (cardHeight + GAPY) * j;
			int index = j * CARDX + i;
			cards[index].x = x;
			cards[index].y = y;
			cards[index].width = cardWidth;
			cards[index].height = cardHeight;
			cards[index].state = STATE_HIDE;
			if (index % 2 == 0)
			{
				int sf = RandomInteger(0, sizeof(drawFuncs) / sizeof(drawFuncs[0]) - 1);
				int sc = RandomInteger(0, sizeof(colors) / sizeof(colors[0]) - 1);
				cards[index].drawFunc = drawFuncs[sf];
				cards[index].colorName = colors[sc];
			}
			else
			{
				cards[index].drawFunc = cards[index - 1].drawFunc;
				cards[index].colorName = cards[index - 1].colorName;
			}
		}
	}

	/* Step 4 shuffle cards(ok) */
	for (i = 0; i < CARDN; i++)
	{
		int j = RandomInteger(i, CARDN - 1);
		char *temp_colorName = cards[i].colorName;
		cards[i].colorName = cards[j].colorName;
		cards[j].colorName = temp_colorName;

		void (*temp_drawFunc)(struct Card * pCard) = cards[i].drawFunc;
		cards[i].drawFunc = cards[j].drawFunc;
		cards[j].drawFunc = temp_drawFunc;
	}

	firstClickIndex = -1;
	secondClickIndex = -1;
	curIndex = -1;
}
// define timer event
void TimerEventProcess(int timerID)
{
	if (timerID == 1)
	{ // 翻牌
		if (cards[firstClickIndex].colorName == cards[secondClickIndex].colorName && cards[firstClickIndex].drawFunc == cards[secondClickIndex].drawFunc)
		{
			cards[firstClickIndex].state = STATE_MATCHED;
			cards[secondClickIndex].state = STATE_MATCHED;
			matchedCount+=2;
		}
		else
		{
			cards[firstClickIndex].state = STATE_HIDE;
			cards[secondClickIndex].state = STATE_HIDE;
		}
		firstClickIndex = -1;
		secondClickIndex = -1;
		cancelTimer(1);
	}

	if (timerID == 2)
	{ // 提示
		int i;
		for (i = 0; i < CARDN; i++)
		{
			if (cards[i].state == STATE_HINT)
			{
				cards[i].state = STATE_HIDE;
			}
		}
		Display();
		cancelTimer(2);
	}
/*不断刷新（已弃用）*/
	if(timerID==3){
		Display();
	}
/*结算*/ 
	if(timerID==4){
		
		if(matchedCount==CARDN){
			
			finish=clock();
			MovePen(2.5,11.1);
			SetPenColor("Red");
			DrawTextString("恭喜你赢得了游戏！用时：");
			double duration=(double)(finish-start)/CLOCKS_PER_SEC;
			char* durationStr[80]={0};
			sprintf(durationStr,"%.2f",duration);
			DrawTextString(durationStr);
			cancelTimer(4);
		}
	}
}

// define key event
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event);
	//S键查看所有卡牌 
	if (key == 'S' && event == KEY_DOWN)
	{
		int i;
		for (i = 0; i < CARDN; i++)
		{
			if (cards[i].state == STATE_SHOW)
			{
				cards[i].state = STATE_HIDE;
			}
			else if (cards[i].state == STATE_HIDE)
			{
				cards[i].state = STATE_SHOW;
			}
		}
		Display();
	}
	//F5重新开始游戏 
	if (key == VK_F5 && event == KEY_DOWN)
	{
		InitGame();
		Display();
	}
	//esc退出游戏 
	if (key == VK_ESCAPE && event == KEY_DOWN)
	{
		exit(0);
	}
	//X提示一秒 
	if (key == 'X' && event == KEY_DOWN)
	{
		int i;
		for (i = 0; i < CARDN; i++)
		{
			if (cards[i].state == STATE_HIDE)
			{
				cards[i].state = STATE_HINT;
			}
		}
		startTimer(2, 1000);

		Display();
	}
	Display();
}

// define mouse event
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event);
	
	//翻牌 
	if (button== LEFT_BUTTON && event == BUTTON_DOWN && (firstClickIndex == -1 || secondClickIndex == -1))
	{
		int i;
		double xx = ScaleXInches(x);
		double yy = ScaleYInches(y);
		for (i = 0; i < CARDN; i++)
		{
			if (xx >= cards[i].x && xx <= cards[i].x + cards[i].width &&
				yy >= cards[i].y && yy <= cards[i].y + cards[i].height)
			{
				if (cards[i].state == STATE_HIDE)
				{
					cards[i].state = STATE_SHOW;
					if (firstClickIndex == -1)
					{
						firstClickIndex = i;
					}
					else
					{
						secondClickIndex = i;
						tryTimes++;
						Display();
						startTimer(1, 1000);
					}
				}
				break;
			}
		}
		Display();
	}
	//高亮显示鼠标移动区域 
	if (event == MOUSEMOVE)
	{
		int i;
		double xx = ScaleXInches(x);
		double yy = ScaleYInches(y);
		curIndex = -1;
		for (i = 0; i < CARDN; i++)
		{
			if (xx > cards[i].x && xx < cards[i].x + cards[i].width &&
				yy > cards[i].y && yy < cards[i].y + cards[i].height)
			{
				curIndex = i;
				break;
			}
		}
		Display();
	}
	Display();
}

// define char event
void CharEventProcess(char ch)
{
	uiGetChar(ch);
	Display();
}


void InitGame()
{
	tryTimes = 0;
	matchedCount = 0;
	Randomize();

	start=clock();
	/* Step 3 define two colors (ok)*/
	DefineColor("River Blue", 0, .75, 1);
	DefineColor("Light Yellow", 1, 1, .5);
	InitCards();
	
	//注册回调函数 
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
	registerCharEvent(CharEventProcess);
	//startTimer(3,100);
	startTimer(4,100); //用于不断查询是否胜利并显示最终界面 
}

void Display()
{
	DisplayClear();

	int i;
	for (i = 0; i < CARDN; i++)
	{
		if (cards[i].state == STATE_HIDE)
		{
			DrawBlindCard(cards + i);
		}
		else if (cards[i].state == STATE_SHOW || cards[i].state == STATE_HINT)
		{
			cards[i].drawFunc(cards + i);
		}
		DrawCardBoundary(cards + i, i == curIndex ? "Red" : "Black");
	}

	//GUI 
	double ww = GetWindowWidth();
	double wh = GetWindowHeight();
	double w=1,h=0.5,x=3,y=wh-0.5;
	
	/*显示尝试次数和解开次数*/
	MovePen(7, 11.5);
	DrawTextString("尝试次数:");
	MovePen(8.25, 11.5);
	itoa(tryTimes, tryTimeStr, 10);
	DrawTextString(tryTimeStr);

	MovePen(7, 11.1);
	DrawTextString("翻开牌数:");
	MovePen(8.25, 11.1);
	itoa(matchedCount, matchedCountStr, 10);
	DrawTextString(matchedCountStr);
	
	
	{
	/*菜单栏*/
	static char * menuListFile[] = {"菜单",  
		"魔法  | Ctrl-F", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		"重开 | Ctrl-R",
		"关闭   | Ctrl-E"
	};
	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = wh;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListFile[0])*2; // 控件宽度
	double wlist = TextStringWidth(menuListFile[3])*1.2;
	double xindent = wh/20; // 缩进
	int    selection;
	
	// 菜单子列 
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection==1 )
	{
		// 魔法
		int i;
		for (i = 0; i < CARDN; i++)
		{
			if (cards[i].state == STATE_SHOW)
			{
				cards[i].state = STATE_HIDE;
			}
			else if (cards[i].state == STATE_HIDE)
			{
				cards[i].state = STATE_SHOW;
			}
		}
		Display();
	}
	else if( selection==2 )
	{
		// 重开
		InitGame();
		Display();
	}
	else
	if( selection==3 )
	exit(-1); // choose to exit
	}
}


void Main()
{
	SetWindowTitle("Memorize");
	SetWindowSize(9, 11+1.0);
	InitGraphics();
	// InitConsole();
	InitGame();
	Display();
}

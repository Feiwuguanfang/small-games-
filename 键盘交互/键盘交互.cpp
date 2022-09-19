#include<stdio.h>
#include<easyx.h>
#include<conio.h>
int main()
{
	initgraph(800, 600);
	setorigin(400, 300);
	setaspectratio(1, -1);
	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	setfillcolor(GREEN);
	setpolyfillmode(WINDING);
	int x = 0; int y = 0;
	solidcircle(x, y, 50);
	while (1)
	{
		char c = _getch();
		switch (c)
		{
		case'w':
			y = y + 50;
			break;
		case's':
			y = y - 50;
			break;
		case'a':
			x = x - 50;
			break;
		case'd':
			x = x + 50;
			break;
		}
		cleardevice();
		solidcircle(x, y, 50);
	}
	getchar();
	closegraph();
	
	return 0;


}
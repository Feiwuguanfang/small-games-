#include<easyx.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define NODE_WIDTH 40

typedef struct {
	int x;
	int y;
}node;

void paintGrid()
{
	for (int y = 0; y < 600; y += NODE_WIDTH)
	{
		line(0, y, 800, y);
	}
	for (int x = 0; x < 800; x += NODE_WIDTH)
	{
		line(x, 0, x, 600);
	}

}
void paintSnake(node* snake, int n)
{
	int left, top, right, bottom;
	for (int i = 0; i < n; i++)
	{
		left = snake[i].x * NODE_WIDTH;
		top = snake[i].y * NODE_WIDTH;
		right = (snake[i].x + 1) * NODE_WIDTH;
		bottom = (snake[i].y + 1) * NODE_WIDTH;
		solidrectangle(left, top, right, bottom);
	}
	IMAGE img_h;
	loadimage(&img_h, _T("IMAGE"),_T("huchuanchun"), 40, 40, false);
	putimage(snake[0].x * NODE_WIDTH, snake[0].y * NODE_WIDTH, &img_h);
	IMAGE img_huang;
	loadimage(&img_huang, _T("IMAGE"), _T("HUANGGUOLIANG"), 40, 40, false);
	putimage(snake[1].x * NODE_WIDTH, snake[1].y * NODE_WIDTH, &img_huang);
	IMAGE img_liang;
	loadimage(&img_liang, _T("IMAGE"), _T("LIANGCHANGLONG"), 40, 40, false);
	putimage(snake[2].x * NODE_WIDTH, snake[2].y * NODE_WIDTH, &img_liang);
	IMAGE img_zhu;
	loadimage(&img_zhu, _T("IMAGE"), _T("ZHUCHUANXI"), 40, 40, false);
	putimage(snake[3].x * NODE_WIDTH, snake[3].y * NODE_WIDTH, &img_zhu);
	IMAGE img_zhang;
	loadimage(&img_zhang, _T("IMAGE"), _T("ZHANGCAIJU"), 40, 40, false);
	putimage(snake[4].x * NODE_WIDTH, snake[4].y * NODE_WIDTH, &img_zhang);
}
enum direction
{
	eup,
	edown,
	eleft,
	eright
};
node snakemove(node* snake, int length, int direction)
{
	node tail = snake[length - 1];

	for (int i = length - 1; i > 0; i--)
	{
		snake[i] = snake[i - 1];
	}
	node newhead;
	newhead = snake[0];
	if (direction == eup)
	{
		newhead.y--;
	}
	else if (direction == edown)
	{
		newhead.y++;
	}
	else if (direction == eleft)
	{
		newhead.x--;
	}
	else
	{
		newhead.x++;
	}
	snake[0] = newhead;
	return tail;
}
void changedirection(enum direction* pD)
{
	if (_kbhit() != 0)
	{
		char c = _getch();
		switch (c)
		{
		case 'w':
			if (*pD != edown)
				*pD = eup;
			break;
		case 's':
			if (*pD != eup)
				*pD = edown;
			break;
		case 'a':
			if (*pD != eright)
				*pD = eleft;
			break;
		case 'd':
			if (*pD != eleft)
				*pD = eright;
			break;
		}
	}

}
void paintfood(node food)
{
	int left, top, right, bottom;
	left = food.x * NODE_WIDTH;
	top = food.y * NODE_WIDTH;
	right = (food.x + 1) * NODE_WIDTH;
	bottom = (food.y + 1) * NODE_WIDTH;
	setfillcolor(YELLOW);
	solidrectangle(left, top, right, bottom);
	IMAGE img_li;
	loadimage(&img_li,_T("IMAGE"),_T("LIPENG"), 40, 40, false);
	putimage(food.x * NODE_WIDTH, food.y * NODE_WIDTH, &img_li);

	setfillcolor(WHITE);

}

node creatfood(node* snake, int length)
{
	node food;
	while (1)
	{
		food.x = rand() % (800 / NODE_WIDTH);
		food.y = rand() % (600 / NODE_WIDTH);
		int i;
		for (i = 0; i < length; i++)
		{
			if (snake[i].x == food.x && snake[i].y == food.y)
			{
				break;
			}
		}
		if (i < length)
			continue;
		else
			break;
	}
	return food;
}

bool isgameover(node* snake, int length)
{
	if (snake[0].x < 0 || snake[0].x>800 / NODE_WIDTH)
		return true;
	if (snake[0].y < 0 || snake[0].y>600 / NODE_WIDTH)
		return true;
	for (int i = 1; i < length; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}
	return false;
}

void reset(node* snake, int* plength, enum direction* d)
{
	snake[0] = node{ 5,7 };
	snake[1] = node{ 4,7 };
	snake[2] = node{ 3,7 };
	snake[3] = node{ 2,7 };
	snake[4] = node{ 1,7 };
	*plength = 5;
	*d = eright;

}
int main()
{
	initgraph(800, 600);
	setbkcolor(RGB(164, 225, 202));
	cleardevice();
	node snake[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int length = 5;
	enum direction d = eright;


	srand(unsigned int(time(NULL)));
	node food = creatfood(snake, length);
	while (1)
	{
		cleardevice();
		paintGrid();
		paintSnake(snake, length);
		paintfood(food);
		settextstyle(30, 20, "微软雅黑");
		settextcolor(RED);
		const char* zhong = "中";
		outtextxy(0, 0, zhong);
		const char* jia = "马";
		outtextxy(760, 560, jia);
		const char* niu = "加";
		outtextxy(760, 0, niu);
		const char* ma = "牛";
		outtextxy(0, 560, ma);

		for (int x = 5; x < length && length>5; x++)
		{
			IMAGE img_wu;
			loadimage(&img_wu,_T("IMAGE"),_T("WUYUNHUI"), 40, 40, false);
			putimage(snake[x].x * NODE_WIDTH, snake[x].y * NODE_WIDTH, &img_wu);


		}

		Sleep(400);
		changedirection(&d);



		node lasttail = snakemove(snake, length, d);
		if (snake[0].x == food.x && snake[0].y == food.y)
		{
			if (length < 100)
			{
				snake[length] = lasttail;


				length++;
			}
			food = creatfood(snake, length);
		}
		if (isgameover(snake, length) == true)
		{
			reset(snake, &length, &d);
			food = creatfood(snake, length);
		}
	}

	getchar();
	closegraph();
	return 0;


}

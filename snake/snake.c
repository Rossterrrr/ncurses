#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int DELAY = 120000;

struct {
	int y;
	int x;
}snake[100];

struct{
	int y;
	int x;
	int extra;
}eda;

void draw(int y,int x)
{
	mvprintw(y , x ,"o");
}
void draw_eda(int y,int x,int extra)
{
	if (extra == 1)
	{
		mvprintw(y , x ,"M");
	}else if (extra == 2)
	{
		mvprintw(y , x ,"A");
	}else if (extra == 3)
	{
		mvprintw(y , x ,"X");
	}else 
		mvprintw(y , x ,"p");
}

int logic(int y_g, int x_g,int y,int x,int y_max,int x_max) 
{
	int m = 0;
	if ((y_g == y) && (x_g == x))
	{
		m = 1;
	}
	if ((y_g == y_max ) || (y_g == 1) || (x_g == x_max ) || (x_g == 0))
	{
		m = 1;
	}
	return m;
	
}
int logic_eda(int y_g,int x_g,int y_eda,int x_eda,int extra)
{
	if((y_g == y_eda) && (x_g == x_eda))
	{
		return extra;
	}
}

void draw_pole(int x,int y)
{
	int i ,j;
	for(i = 0;i < x;i++)
	{
		for(j = 0;j<y;j++)
		{
			if((j == 1) || (j == y-1) ||(i == 0) || i == x-1)
			mvprintw(j , i ,"#");
			
		}
	}
}

void draw_score(int rost,int x,int y,int hard)
{
	mvprintw(0 , (x/2)-30, "Hardcore level : %d" , hard );
	mvprintw(0 , (x/2)-11, "of 6" );
	mvprintw(0 , (x/2)-5, "Your score : %d" , rost);
}

	


int main(){
	srand(time(NULL));
	bool gameover;
	int x,y,xn,yn,i;
	int ch,ch2,lng=3;
	int exit;
	int rost = 3;
	int hard = 1;
	
	initscr();
	x = getmaxx(stdscr);   
	y = getmaxy(stdscr);
	xn=x/2;
	yn=y/2;
	int tmpy1,tmpy2,tmpx1,tmpx2;
	ch2 = KEY_UP;
	eda.y = (rand() % (y-3))+2;
	eda.x = (rand() % (x-2))+1;
	eda.extra = (rand() % 3)+1;
	draw_eda(eda.y,eda.x,eda.extra);
	
	for (i = 0;i < rost;i++)
	{
		snake[i].y = yn+i;
		snake[i].x = xn;
	}
	for (i = 0;i < rost;i++)
	{
		draw(snake[i].y,snake[i].x);
	}
 	noecho();
 	nodelay(stdscr, TRUE);
 	curs_set(FALSE);
 	keypad(stdscr, TRUE);

 	while (gameover!=1)
	{
		if ((rost > 7) && (rost <= 15))
		{
			hard = 2;
			DELAY = 90000;
		}else if ((rost > 15) && (rost <= 25))
			{
				hard = 3;
				DELAY = 60000;
			}else if ((rost > 25) && (rost <= 40))
					{
						hard = 4;
						DELAY = 40000;
					}else if ((rost > 40) && (rost <=70))
							{
								hard = 5;
								DELAY = 25000;
							}else if((rost > 70) && (rost <= 90))
									{
										hard = 6;
										DELAY = 15000;
									}
	 	usleep(DELAY);
		ch = getch();	
		switch(ch)
		{
			case ERR:
			{
				switch(ch2)
				{
					case KEY_LEFT:
					{
						tmpy1 = snake[0].y;
						tmpx1 = snake[0].x;
						snake[0].x--;
						for (i = 1;i<rost;i++)
						{
							tmpy2 = snake[i].y;
							tmpx2 = snake[i].x;
							snake[i].y = tmpy1;
							snake[i].x = tmpx1;
							tmpy1 = tmpy2;
							tmpx1 = tmpx2;
						}
						clear();
						for(i = 1;i<rost;i++)
						{
							gameover = gameover + logic(snake[0].y,snake[0].x,snake[i].y,snake[i].x,y,x);
						}
						for (i = 0;i < rost;i++)
						{
							draw(snake[i].y,snake[i].x);
						}
						draw_pole(x,y);
						draw_eda(eda.y,eda.x,eda.extra);
						if (logic_eda(snake[0].y,snake[0].x,eda.y,eda.x,eda.extra) == eda.extra)
						{
							rost = rost + eda.extra;
							eda.y = (rand() % (y-3))+2;
							eda.x = (rand() % (x-2))+1;
							eda.extra = (rand() % 3)+1;
						}
						draw_score(rost,x,y,hard);
						refresh();
						break;
					}
					case KEY_RIGHT:
					{
						tmpy1 = snake[0].y;
						tmpx1 = snake[0].x;
						snake[0].x++;
						for (i = 1;i<rost;i++)
						{
							tmpy2 = snake[i].y;
							tmpx2 = snake[i].x;
							snake[i].y = tmpy1;
							snake[i].x = tmpx1;
							tmpy1 = tmpy2;
							tmpx1 = tmpx2;
						}
						clear();
						for(i = 1;i<rost;i++)
						{
							gameover = gameover + logic(snake[0].y,snake[0].x,snake[i].y,snake[i].x,y,x);
						}
						for (i = 0;i < rost;i++)
						{
							draw(snake[i].y,snake[i].x);
						}
						draw_pole(x,y);
						draw_eda(eda.y,eda.x,eda.extra);
						if (logic_eda(snake[0].y,snake[0].x,eda.y,eda.x,eda.extra) == eda.extra)
						{
							rost = rost + eda.extra;		
							eda.y = (rand() % (y-3))+2;
							eda.x = (rand() % (x-2))+1;
							eda.extra = (rand() % 3)+1;
						}
						draw_score(rost,x,y,hard);
						refresh();
						break;
					}
					case KEY_UP:
					{
						tmpy1 = snake[0].y;
						tmpx1 = snake[0].x;
						snake[0].y--;
						for (i = 1;i<rost;i++)
						{
							tmpy2 = snake[i].y;
							tmpx2 = snake[i].x;
							snake[i].y = tmpy1;
							snake[i].x = tmpx1;
							tmpy1 = tmpy2;
							tmpx1 = tmpx2;
						}
						clear();
						for(i = 1;i<rost;i++)
						{
							gameover = gameover + logic(snake[0].y,snake[0].x,snake[i].y,snake[i].x,y,x);
						}
						for (i = 0;i < rost;i++)
						{
							draw(snake[i].y,snake[i].x);
						}
						draw_pole(x,y);
						draw_eda(eda.y,eda.x,eda.extra);
						if (logic_eda(snake[0].y,snake[0].x,eda.y,eda.x,eda.extra) == eda.extra)
						{
							rost = rost + eda.extra;
							eda.y = (rand() % (y-3))+2;
							eda.x = (rand() % (x-2))+1;
							eda.extra = (rand() % 3)+1;
						}
						draw_score(rost,x,y,hard);
						refresh();
						break;
					}
					case KEY_DOWN:
					{
						tmpy1 = snake[0].y;
						tmpx1 = snake[0].x;
						snake[0].y++;
						for (i = 1;i<rost;i++)
						{
							tmpy2 = snake[i].y;
							tmpx2 = snake[i].x;
							snake[i].y = tmpy1;
							snake[i].x = tmpx1;
							tmpy1 = tmpy2;
							tmpx1 = tmpx2;
						}
						clear();
						for(i = 1;i<rost;i++)
						{
							gameover = gameover + logic(snake[0].y,snake[0].x,snake[i].y,snake[i].x,y,x);
						}
						for (i = 0;i < rost;i++)
						{
							draw(snake[i].y,snake[i].x);
						}
						draw_pole(x,y);
						draw_eda(eda.y,eda.x,eda.extra);
						if (logic_eda(snake[0].y,snake[0].x,eda.y,eda.x,eda.extra) == eda.extra)
						{
							rost = rost + eda.extra;		
							eda.y = (rand() % (y-3))+2;
							eda.x = (rand() % (x-2))+1;
							eda.extra = (rand() % 3)+1;
						}
						draw_score(rost,x,y,hard);
						refresh();
						break;	
					}
				}
			break;	
			}
			case KEY_LEFT:
			{
				if (ch2 != KEY_RIGHT)
				{
					ch2=ch;
				}
				break;
			}
			case KEY_RIGHT:
			{
				if (ch2 != KEY_LEFT)
				{
					ch2=ch;
				}
				break;
			}
			case KEY_UP:
			{
				if (ch2 != KEY_DOWN)
				{
					ch2=ch;
				}
				break;
			}
			case KEY_DOWN:
			{
				if (ch2 != KEY_UP)
				{
					ch2=ch;
				}
				break;
			}
		}
	}
	mvprintw(y/2 , x/2 ,"GAME OVER");
	mvprintw((y/2)+1,x/2, "Your score : %d" , rost);
	mvprintw((y/2)+2,x/2, "Try again(0)");
	mvprintw((y/2)+3,x/2, "1 - Exit; 0 - NO");
	refresh(); 
	sleep(10);
	endwin();
	return 0;
}

//第一个图形窗口程序
#include <graphics.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
 
int jiemian[4][4] = {0};
int i,j;
int score=0;

void left()
{	
	for(j=0;j<4;j++)
				{
					for(i=3;i>0;i--)
					{
						if(jiemian[j][i-1]==0)
						{
							jiemian[j][i-1]=jiemian[j][i];//右面移动到左面
							jiemian[j][i]=0;//清空
						}
						else
						{
							if(jiemian[j][i-1]==jiemian[j][i])
							{
								jiemian[j][i-1]=2*jiemian[j][i];
								jiemian[j][i]=0;
								score=score+jiemian[j][i-1];

							}
						}
					}
				}
}

void down()
{
	for(j=0;j<4;j++)
				{
					for(i=0;i<4;i++)
					{
						if(jiemian[j+1][i]==0)
						{
							jiemian[j+1][i]=jiemian[j][i];//上面移动到下面
							jiemian[j][i]=0;//清空
						}
						else
						{
							if(jiemian[j+1][i]==jiemian[j][i])
							{
								jiemian[j+1][i]=jiemian[j+1][i]+jiemian[j][i];
								jiemian[j][i]=0;
								score=score+jiemian[j+1][i];

							}
						}
					}
				}
}

void up()
{

for(j=3;j>0;j--)
				{
					for(i=0;i<4;i++)
					{
						if(jiemian[j-1][i]==0)
						{
							jiemian[j-1][i]=jiemian[j][i];//下面移动到上面
							jiemian[j][i]=0;//清空
						}
						else
						{
							if(jiemian[j-1][i]==jiemian[j][i])
							{
								jiemian[j-1][i]=jiemian[j-1][i]+jiemian[j][i];
								jiemian[j][i]=0;
								score=score+jiemian[j-1][i];

							}
						}
					}
				}
}

void right()
{
	for(j=0;j<4;j++)
				{
					for(i=0;i<3;i++)
					{
						if(jiemian[j][i+1]==0)
						{
							jiemian[j][i+1]=jiemian[j][i];//左面移动到右面
							jiemian[j][i]=0;//清空
						}
						else
						{
							if(jiemian[j][i+1]==jiemian[j][i])
							{
								jiemian[j][i+1]=jiemian[j][i+1]+jiemian[j][i];
								jiemian[j][i]=0;
								score=score+jiemian[j][i+1];
							}
						}
					}
				}
}

void restart()
{
        int i,j;
        for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                        jiemian[i][j]=0; 
                }
        }
}


void rand_map()
{
	int x,y;
do{
	y= rand()%4;
	x= rand()%4;
	}
	while(jiemian[y][x]!=0);
	jiemian[y][x]=2;
	
}

void show_map()
{
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			char png_name[20]={0};
			sprintf(png_name,"D:\\2048\\image\\%d.png",jiemian[i][j]);
			
			PIMAGE img = newimage();
            getimage(img, png_name);
            putimage(j*103+90, i*60+175, img);
            delimage(img);
		}
	 } 
} 

void s_core()
{
			
            //文字颜色
	setcolor(EGERGB(0xF7,0xB1,0x08));

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x33,0x33,0x33));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(50, 0, "宋体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	
	char s[5]={0};//声明数组，用来存放字符串
	sprintf(s, "%d", score);//将整形a转换成字符串	
	
	outtextxy(680, 130, s);
	//outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");

	//设置文字背景填充方式为TRANSPARENT透明，默认为OPAQUE不透明
	setbkmode(OPAQUE);

}

int do_check(int *map){
	int b = 0;
	for(int i = 0;i < 16;i++)
	{
		if(map[i] == 0)
			return 0;
		else
			b++;
		if(b == 16)
			return -1;
	}
	return 0;
}


int main()
{
	
	srand(time(0));
	
	//初始化为640*480大小
	initgraph(800,480);
	
	//读取D:\\20048\\20048\\image\\2048_bg.png绘制在屏幕上 
	PIMAGE img = newimage();
	getimage(img, "D:\\2048\\image\\2048_bg.png");
	putimage(0, 0, img);
	delimage(img);
	rand_map();
	while(1)
	{
	s_core();
	int *pmap = &jiemian[0][0];
	int e = do_check(pmap);
	if (e != 0)
	{
			setfontbkcolor(EGERGB(0x80,0x00,0x80));
			setfont(72, 0, "宋体");
		outtextxy(150, 150, "Game over!");
		//system("pause");
		//getch();
		return 0; 
	}
	//生成随机位置 
	rand_map();
	//显示4*4数字方格
	show_map(); 

		char str[32];
		int x,y;
		mouse_msg msg = { 0 };
		while (mousemsg()) 
		{
			msg = getmouse();
		}
		/*if (msg.is_left() && msg.is_down()) {
				//标志位置位，记录点击位置
				
				xClick = msg.x;
				yClick = msg.y;
			}*/
		//获取鼠标坐标，此函数不等待。若鼠标移出了窗口，那么坐标值不会更新
		//特殊情况是，你按着鼠标键不放，拖出窗口，这样坐标值会依然更新
		mousepos(&x, &y);
		sprintf(str, "%4d %4d", x, y);
		//格式化输出为字符串，用于后面 
		//outtextxy(0, 0, str);
	//	delay_fps(60);
			if((int)msg.is_left() && (int)msg.is_up())
			{
				/*if((560 <= x && x < 560 + 40)
				&& (280 <= y && y < 280 + 65))
				{
				//outtextxy(150, 150, "鼠标点击了");
				left();
				}*/
				if((x>600 && x<700)&& (y<300 && y>250) )
				{	
 				up();
 				}
 				if((x>600 && x<700)&& (y>350 && y<400) )
				{
				down();
				}
 				if((x>550 && x<610)&& (y<370 && y>280))
				{ 
 				left();
 				}
 				if((x>690 && x<750)&& (y<370 && y>270))
				{ 
 				right();
 				}
 				if((x>620 && x<690)&& (y<340 && y>310))
				{ 
 				restart();
 				show_map();
 				}
				rand_map();
			}	
	
	//key_msg getkey();
			
			char cmd=0;
			if(kbhit())
			{
			cmd=getch();
			rand_map();
		switch(cmd)
			{
			case 'a':
				left();
				break;
			case 's':
				down();
				break;
			case 'w':
				up();
				break;
			case 'd':
				right();
				break;
			case 'r':
				restart();
				break;
			default:
				printf("输入错误\n");
				break;
		}
}




	//等待用户按键
	//getch();
	
		}//死循环	

	//关闭图形界面
	closegraph();
	return 0;
}

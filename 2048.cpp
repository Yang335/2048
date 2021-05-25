//��һ��ͼ�δ��ڳ���
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
							jiemian[j][i-1]=jiemian[j][i];//�����ƶ�������
							jiemian[j][i]=0;//���
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
							jiemian[j+1][i]=jiemian[j][i];//�����ƶ�������
							jiemian[j][i]=0;//���
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
							jiemian[j-1][i]=jiemian[j][i];//�����ƶ�������
							jiemian[j][i]=0;//���
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
							jiemian[j][i+1]=jiemian[j][i];//�����ƶ�������
							jiemian[j][i]=0;//���
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
			
            //������ɫ
	setcolor(EGERGB(0xF7,0xB1,0x08));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x33,0x33,0x33));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(50, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	
	char s[5]={0};//�������飬��������ַ���
	sprintf(s, "%d", score);//������aת�����ַ���	
	
	outtextxy(680, 130, s);
	//outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");

	//�������ֱ�����䷽ʽΪTRANSPARENT͸����Ĭ��ΪOPAQUE��͸��
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
	
	//��ʼ��Ϊ640*480��С
	initgraph(800,480);
	
	//��ȡD:\\20048\\20048\\image\\2048_bg.png��������Ļ�� 
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
			setfont(72, 0, "����");
		outtextxy(150, 150, "Game over!");
		//system("pause");
		//getch();
		return 0; 
	}
	//�������λ�� 
	rand_map();
	//��ʾ4*4���ַ���
	show_map(); 

		char str[32];
		int x,y;
		mouse_msg msg = { 0 };
		while (mousemsg()) 
		{
			msg = getmouse();
		}
		/*if (msg.is_left() && msg.is_down()) {
				//��־λ��λ����¼���λ��
				
				xClick = msg.x;
				yClick = msg.y;
			}*/
		//��ȡ������꣬�˺������ȴ���������Ƴ��˴��ڣ���ô����ֵ�������
		//��������ǣ��㰴���������ţ��ϳ����ڣ���������ֵ����Ȼ����
		mousepos(&x, &y);
		sprintf(str, "%4d %4d", x, y);
		//��ʽ�����Ϊ�ַ��������ں��� 
		//outtextxy(0, 0, str);
	//	delay_fps(60);
			if((int)msg.is_left() && (int)msg.is_up())
			{
				/*if((560 <= x && x < 560 + 40)
				&& (280 <= y && y < 280 + 65))
				{
				//outtextxy(150, 150, "�������");
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
				printf("�������\n");
				break;
		}
}




	//�ȴ��û�����
	//getch();
	
		}//��ѭ��	

	//�ر�ͼ�ν���
	closegraph();
	return 0;
}

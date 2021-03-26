#include "task.h"
#include "usart.h"

//黑色返回1，白色返回0
void  qianjin(int a) //前进a条白线
{
	int i=0,flag=0;int sum=0;
	while(i<a)
	{
		go_forward(500);
		sum=xunji_1+xunji_2+xunji_3+xunji_4+xunji_5+xunji_6+xunji_7+xunji_8;
		//printf(" %d\r\n\r\n",sum);
		printf("\r\n  %d   \r\n\r\n",flag);
		if(sum<=2)
			flag=1;
		if((flag==1)&&((xunji_L==0)||(xunji_R==0)))
		{
			i++;
			//printf(" %d\r\n",i);
			flag=0;
		}
	}
}


void  houtui(int a) //前进a条白线
{
	int i=0,flag=0;int sum=0;
	while(i<a)
	{
		go_back(500);
		sum=xunji_a+xunji_b+xunji_c+xunji_d;
		//printf(" %d\r\n\r\n",sum);
		printf("\r\n  %d   \r\n\r\n",flag);
		if(sum<=1)
			flag=1;
		if((flag==1)&&((xunji_L==0)||(xunji_R==0)))
		{
			i++;
			//printf(" %d\r\n",i);
			flag=0;
		}
	}
}


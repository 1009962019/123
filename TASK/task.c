#include "task.h"
#include "usart.h"

//黑色返回1，白色返回0
void  qianjin(int a)
{
	int i=0,flag=0;int sum=0;
	while(i<a)
	{
		go(500);
		sum=xunji_1+xunji_2+xunji_3+xunji_4+xunji_5+xunji_6+xunji_7+xunji_8;
		//printf(" %d\r\n\r\n",sum);
		printf("\r\n  %d   \r\n\r\n",flag);
		if(sum<=2)
			flag=1;
		if(flag==1&&huidu_left==0&&huidu_right==0)
		{
			i++;
			//printf(" %d\r\n",i);
			flag=0;
		}
	}
}


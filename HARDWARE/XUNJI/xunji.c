#include "xunji.h"
#include "encoder.h"
#include "motor.h"
#include "delay.h"
int error=0;

extern int leftSpeedNow;
extern int rightSpeedNow;
void xunji_config(void)	//初始化所有灰度传感器，包括两侧灰度传感器
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOF, ENABLE); // 使能PC端口时钟
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 |GPIO_Pin_6 | GPIO_Pin_5| GPIO_Pin_4| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;	//选择对应的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);  //初始化PC端口
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);  //初始化PC端口
	
}


void Read_xunji_Date(void)
{
 xunji_1;
 xunji_2;
 xunji_3;
 xunji_4;
 xunji_5;
 xunji_6;
 xunji_7;
 xunji_8;
 
 xunji_a;
 xunji_b;
 xunji_c;
 xunji_d;
}


int xuanze(void)//             黑色返回1，白色返回0
{
	Read_xunji_Date();
	if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==0&&xunji_5==0&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{
		error=0;//11100111
	}
	
	//两个灯检测到（左偏）
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==0&&xunji_6==0&&xunji_7==1&&xunji_8==1)
	{ 
		error=-100;//11110011左偏为负数
	}
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==0&&xunji_7==0&&xunji_8==1)
	{ 
		error=-200;//11111001
	}
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==0&&xunji_8==0)
	{ 
		error=-300;//11111100
	}
	//一个灯检测到（左偏）
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==0&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=-50;//11110111左偏为负数
	}
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==0&&xunji_7==1&&xunji_8==1)
	{ 
		error=-150;//11111011
	}
	else if(xunji_1==1&&xunji_2==1&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==0&&xunji_8==1)
	{ 
		error=-250;//11111101
	}
	
	//两个灯检测到（右偏）
	else if(xunji_1==1&&xunji_2==1&&xunji_3==0&&xunji_4==0&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=100;//11001111
	}	 
	else if(xunji_1==1&&xunji_2==0&&xunji_3==0&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=200;//10011111
	}
	else if(xunji_1==0&&xunji_2==0&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=300;//00111111
	}
	
	//一个灯检测到（右偏）
	else if(xunji_1==1&&xunji_2==1&&xunji_3==0&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=50;//11101111右偏为正数
	}
	else if(xunji_1==1&&xunji_2==1&&xunji_3==0&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=150;//11011111
	}
	else if(xunji_1==1&&xunji_2==0&&xunji_3==1&&xunji_4==1&&xunji_5==1&&xunji_6==1&&xunji_7==1&&xunji_8==1)
	{ 
		error=250;//10111111
	}
	
	
	else
	error=0;
	
	return error;
	
}


void go(int initial_speed)
{		
	int error=0;
	int left_pwm,right_pwm;
	error=xuanze();
	left_pwm= initial_speed - error;
  right_pwm= initial_speed + error;
	//printf("\r\n您发送的消息为:\r\n\r\n");
	//printf("\r\n  %d   %d\r\n\r\n",left_pwm,right_pwm);
	TIM_SetTIM3Compare1(left_pwm,right_pwm);
}


void  turn_right(void)
{
	PWML1=600;
	PWML2=600;//越大转速越快
	PWMR1=200;
	PWMR2=200;
	PWMForward_M1();
	PWMForward_M2();
	delay_ms(1000);
}

void  turn_left(void)
{
	PWML1=200;
	PWML2=200;
	PWMR1=600;
	PWMR2=600;
	PWMForward_M1();
	PWMForward_M2();
	delay_ms(1000);
}

void  stop(void)
{
	PWML1=0;
	PWML2=0;
	PWMR1=0;
	PWMR2=0;
	PWMSTOP_M1();
	PWMSTOP_M2();
	delay_ms(1000);

}








#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "encoder.h"
#include "motor.h"
#include "adc.h"
#include "xunji.h"
#include "task.h"


 int main(void)
 {	
	delay_init();
	MOTOR_Init();
	xunji_config();
	uart_init(115200);	 //串口初始化为115200
	TIM3_PWM_Init(999,7200);//1000
  while(1)
	{
    
		//printf("\r\n您发送的消息为:\r\n\r\n");
		//printf("\r\n%d  %d  %d  %d   %d  %d  %d  %d  \r\n\r\n",xunji_1,xunji_2,xunji_3 ,xunji_4 ,xunji_5 ,xunji_6 ,xunji_7, xunji_8);
		//go(300);

	}
 }

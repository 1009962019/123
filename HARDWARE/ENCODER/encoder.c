//TIM2,TIM4�����ٶ�
// ����TIM2:PA0,PA1     ���֣TTIM4:PB6,PB7
#include "encoder.h"

int leftSpeedNow=0;
int rightSpeedNow=0;
/**************************************************************************
�������ܣ���TIM2��ʼ���ɱ�����ģʽ
**************************************************************************/
void Encoder_Init_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //?????2???
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //??PA????

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //????
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//?????????GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //???? 
	TIM_TimeBaseStructure.TIM_Period = 65535;  //??????????
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????:???
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM????  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                   //���TIM2�жϱ�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	//===============================================
	TIM2->CNT = 0x7fff;
	//===============================================
	TIM_Cmd(TIM2, ENABLE); 
}
/**************************************************************************
�������ܣ���TIM4��ʼ���ɱ�����ģʽ
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //?????4???
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //??PB????

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //????
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//?????????GPIOB

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              // ???? 
	TIM_TimeBaseStructure.TIM_Period = 65535;  //??????????
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????:???
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM????  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//???????3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);                   //���TIM4�жϱ�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM4,0);
	//===============================================
	TIM4->CNT = 0;
	//===============================================
	TIM_Cmd(TIM4, ENABLE); 
}

/**************************************************************************
�������ܣ���ȡ�����������ֵ����ȡ��λʱ��������仯ֵ
????:TIM_TypeDef * TIMx
??  ?:?
**************************************************************************/
s16 getTIMx_DetaCnt(TIM_TypeDef * TIMx)
{
	s16 cnt;
	cnt = TIMx->CNT;
	TIMx->CNT = 0;
	return cnt;
}

/**************************************************************************
????:??????
????:int *leftSpeed,int *rightSpeed
??  ?:?
		//?????????,??????? ,???????,?????1000????? mm/s
		//????????????*???(?????????m)*200s(5ms????) ?? m/s *1000???int??

		??????:
			?:1560
			?:1560
		????:0.03m
		????:2*pi*r
		???????:
			?:0.000120830m
			?:0.000120830m
		?????:
			?: 0.0240m/s 
			?: 0.0240m/s 
			200  5ms???
			1000 ?????
**************************************************************************/

//void Get_Motor_Speed(int *leftSpeedNow,int *rightSpeedNow)
//{
//	//5ms?? 5ms?????????  	
//	*leftSpeedNow   = getTIMx_DetaCnt(TIM4)*1000*200*0.000120830/2;  
//	*rightSpeedNow  = getTIMx_DetaCnt(TIM2)*1000*200*0.000120830/2;
//}//��λmm/swwwwwwwwwwwwwp

//5ms��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)   //TIM3??
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //?????TIM??????:TIM ??? 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);   //??TIMx???????:TIM ??? 
		leftSpeedNow=getTIMx_DetaCnt(TIM2);
		rightSpeedNow=getTIMx_DetaCnt(TIM4);
		
	}
}






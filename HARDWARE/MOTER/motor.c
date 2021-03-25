#include "motor.h"
//////////////////////////////////////////////////////////////////////////////////	 
//X  M1		����  	PC0|1|8|9   PA6|PA7
//Y  M2   ����    PE2|3|4|5   PB0|PB1
////////////////////////q//////////////////////////////////////////////////////////  
void MOTOR_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PC,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9);						 //PB.5 �����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);						 //PB.5 �����

 GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//����JTAG ���� SWD
}   	  


//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  |RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7; //TIM3_CH1|CH2->PA6|PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
   ////���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1; //TIM3_CH3|CH4->PB0|PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	

}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

void TIM_SetTIM3Compare1(int32_t comparex,int32_t comparey)
{
	if(comparex >= 0)          //M1_pwm>=0ʱ�������ת
	{
		PWMForward_M1();
		TIM3->CCR1=comparex; 
		TIM3->CCR2=comparex; 
	}
	else   //M1_pwm<0ʱ�������ת��M1_pwmȡ����ֵ
	{
		PWMBack_M1();
		TIM3->CCR1=(myabs(comparex)); 
		TIM3->CCR2=(myabs(comparex)); 
	}
	if(comparey >= 0)          //M2_pwm>=0ʱ�������ת
	{
		PWMForward_M2();
		TIM3->CCR3=comparey; 
		TIM3->CCR4=comparey;
	}
	else    //M2_pwm<0ʱ�������ת��M2_pwmȡ����ֵ
	{
		PWMBack_M2();
		TIM3->CCR3=(myabs(comparey)); 
		TIM3->CCR4=(myabs(comparey));
	}
}



void PWMForward_M1(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_0);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	
}
void PWMBack_M1(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	
}
void PWMSTOP_M1(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
}




void PWMForward_M2(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_2);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	GPIO_SetBits(GPIOE,GPIO_Pin_4);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	

}
void PWMBack_M2(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);	
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
void PWMSTOP_M2(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_2);	
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}


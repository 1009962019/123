#ifndef __XUNJI__H
#define __XUNJI__H

#include "sys.h"
#include "stm32f10x.h"

//��ͷ�Ҷ�
#define xunji_1 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)
#define xunji_2 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define xunji_3 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)
#define xunji_4 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)//��
#define xunji_5 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)
#define xunji_6 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)
#define xunji_7 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define xunji_8 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)//��

#define xunji_L GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_0)//��ͷ��ǰ����
#define xunji_R GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1)

//��β�Ҷ�
#define xunji_a GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//���
#define xunji_b GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)
#define xunji_c GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)
#define xunji_d GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)//�ұ�


void xunji_config(void);
void Read_xunji_Date(void);  //��ѭ��ģ�鷵�ص�ֵ
int  xuanze_qian(void);
int  xuanze_hou(void);
void go_forward(int initial_speed);
void go_back(int initial_speed);
void  turn_right(void);
void  turn_left(void);
void  stop(void);
#endif
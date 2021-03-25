#ifndef __TASK_H
#define __TASK_H
#include "sys.h"
#include "xunji.h"
#include "usart.h"


#define huidu_left GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_0)
#define huidu_right GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1)




void  qianjin(int a);


#endif
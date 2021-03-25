#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#include "stdio.h"
#include "stdlib.h"


#define PWML1 TIM3->CCR1
#define PWML2 TIM3->CCR2
#define PWMR1 TIM3->CCR3
#define PWMR2 TIM3->CCR4

void TIM3_PWM_Init(u16 arr,u16 psc);
void MOTOR_Init(void);
void TIM_SetTIM3Compare1(int32_t comparex,int32_t comparey);
void PWMForward_M1(void);
void PWMBack_M1(void);
void PWMSTOP_M1(void);
void PWMForward_M2(void);
void PWMBack_M2(void);
void PWMSTOP_M2(void);
int myabs(int a);
#endif

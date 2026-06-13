#ifndef __CAR_H
#define __CAR_H
#include "stm32f10x.h"
void Car_Init(void);
void Self_Right(uint8_t Speed);
void Self_Left(uint8_t Speed);
void Turn_Right(uint8_t Speed);
void Turn_Left(uint8_t Speed);
void Go_Back(uint8_t Speed);
void Go_Ahead(uint8_t Speed);
void Car_Stop(void);
#endif

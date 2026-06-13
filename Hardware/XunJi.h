#ifndef _XUNJI_H_
#define _XUNJI_H_

#include "stm32f10x.h"
#include "CAR.h"
#include "Track.h"


#define Track_1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
#define Track_2 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
#define Track_3 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)
#define Track_4 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)

#define Track_Go ((Track_1<<3)|(Track_2<<2)|(Track_3<<1)|(Track_4))

void XunJi_Init(void);
	
#endif

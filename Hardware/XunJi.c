#include "stm32f10x.h"
#include "CAR.h"
#include "Track.h"

#define XunJi_Speed 85

#define Track_1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
#define Track_2 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
#define Track_3 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)
#define Track_4 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)

#define Track_Go ((Track_1<<3)|(Track_2<<2)|(Track_3<<1)|(Track_4))

void XunJi_Init(void)
{
		switch (Track_Go)
		{
			case 0x04://0100
				Go_Ahead(XunJi_Speed);
				break; 
			case 0x02://0010
				Go_Ahead(XunJi_Speed);
				break; 
			case 0x06://0110
				Go_Ahead(XunJi_Speed);
				break; 
			case 0x01://0001
				Turn_Right(XunJi_Speed);
				break;
			case 0x08://1000
				Turn_Left(XunJi_Speed);
				break;					
			case 0x00://0000
				Turn_Left(XunJi_Speed);
				break;
			default: 
				Go_Ahead(XunJi_Speed);
				break;
		}
}

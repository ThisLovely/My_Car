	#ifndef __RED_H
#define __RED_H 
#include "sys.h"   
/*****************铎宝电子******************
											STM32
 * 文件			:	红外遥控实验                   
 * 版本			: V1.0
 * 日期			: 2024.8.12
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	铎宝电子
 * 作者			:	恋爱脑_涵涵

**********************BEGIN***********************/ 

#define RDATA 	PBin(9)	 	//红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0   

#define		Remote_GPIO_PORTGPIO_CLK								RCC_APB2Periph_GPIOB
#define		Remote_TIM_PORTGPIO_CLK								RCC_APB1Periph_TIM4
#define 	Remote_GPIO_PORT							GPIOB
#define 	Remote_GPIO_PIN								GPIO_Pin_9
#define 	Remote_TIM							TIM4
#define 	Remote_TIM_Channel							TIM_Channel_4
#define 	Remote_TIM_IT            TIM_IT_CC4

extern u8 RmtCnt;			//按键按下的次数
void Remote_Init(void);    	//红外传感器接收头引脚初始化
u8 Remote_Scan(void);	    
#endif
















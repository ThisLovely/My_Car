#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "Remote_delay.h"
#include "usart.h"
#include "led.h"
#include "OLED.h"
#include "remote.h"
#include "PWM.h"
#include "Motor.h"
#include "Car.h"
#include "PWMServo.h"
#include "Servo.h"
#include "Ultrasound.h"
#include "BiZhang.h"

enum State 
{
	Car_GO_Ahead,
	Car_Go_Back,
	Car_Self_Left,
	Car_Self_Right,
	Car_Car_Stop
};
enum State Car_Run_State=Car_Car_Stop;

uint8_t a=0;
uint8_t Remotr_Speed=60;
uint8_t Motor_Run_Flag=0;//是否进入避障模式 0否 1是

#define LED_BiZhang_Light  GPIO_SetBits(GPIOB,GPIO_Pin_6);		//亮起-避障模式-超声波检测到
#define LED_BiZhang_Drown  GPIO_ResetBits(GPIOB,GPIO_Pin_6);	//熄灭-避障模式-超声波未检测到

#define LED_XingShi_Light	 do{GPIO_SetBits(GPIOB,GPIO_Pin_7);Delay_ms(100);}while(0) 		//亮起-行驶模式-超声波未检测到
#define LED_XingShi_Drown	 GPIO_ResetBits(GPIOB,GPIO_Pin_7);	//熄灭-行驶模式-超声波检测到

#define LED_Remote_Light	 do{GPIO_SetBits(GPIOB,GPIO_Pin_5);Delay_ms(100);}while(0) 		//亮起-接收到红外信号
#define LED_Remote_Drown	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);	//熄灭-未接受到红外信号

#define JuLi 20    // 避障阈值（cm）

u8 key,lele,sys_time;

uint16_t Dance_JuLi;

int main(void)
{	
	LED_Init();
	Car_Init();
	Servo_Init();
	HCSR04_Init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	Remote_Init();			//红外接收初始化
		
	while(1)
	{
		if(Motor_Run_Flag)
		{
//			Motor_Run_Flag=0;
			LED_BiZhang_Light;
			
			BiZhang_Init();
		}
		else 
		{
			LED_BiZhang_Drown;
			switch(Car_Run_State)
			{
				case Car_GO_Ahead:		Go_Ahead(Remotr_Speed);		break;//上	前进	
				case Car_Go_Back:			Go_Back(Remotr_Speed);		break;//下	后退   
				case Car_Self_Left:		Self_Left(Remotr_Speed);	break;	//左  左转 
				case Car_Self_Right:	Self_Right(Remotr_Speed);	break;  //右	右转
				case Car_Car_Stop:		Car_Stop();		break;	//ok	停止  
			}
		}
		
		lele=Remote_Scan();
				

		LED_XingShi_Drown;
		LED_Remote_Drown;
		
		switch(lele)
			{
				case 24:	Car_Run_State=Car_GO_Ahead;		LED_Remote_Light;		break;//上	前进			   
				case 74:	Car_Run_State=Car_Go_Back;		LED_Remote_Light;		break;//下	后退    
				case 16:	Car_Run_State=Car_Self_Left;	LED_Remote_Light;		break;	//左  左转  
				case 90:	Car_Run_State=Car_Self_Right;	LED_Remote_Light;		break;  //右	右转	 
				case 56: 	Car_Run_State=Car_Car_Stop;		LED_Remote_Light;		break;	//ok	停止  
				case 104: Remotr_Speed=(Remotr_Speed+20)<=100?Remotr_Speed+20:100; LED_XingShi_Light;	break;	//* 加速  
				case 176: Remotr_Speed=(Remotr_Speed-20)>=0?Remotr_Speed-20:0; LED_XingShi_Light;	break;	//#	减速
				case 162:	key=1;		Motor_Run_Flag=0;		break;		  
				case 98:	key=2;		Motor_Run_Flag=1;		break;	   
//				case 226:	key=3;		OLED_ShowNum(3,9,key,2);break;	    
//				case 34:	key=4;		OLED_ShowNum(3,9,key,2);break;		    
//				case 2:		key=5;		OLED_ShowNum(3,9,key,2);break;		    
//				case 194:	key=6;		OLED_ShowNum(3,9,key,2);break;		  
//				case 224:	key=7;		OLED_ShowNum(3,9,key,2);break;			   					
//				case 168:	key=8;		OLED_ShowNum(3,9,key,2);break;	 
//				case 144:	key=9;		OLED_ShowNum(3,9,key,2);break;
//				case 152:	key=0;		OLED_ShowNum(3,9,key,2);break;	 
			}
			

//			
//		if(sys_time>200)
//			{
//				sys_time=0;
//				lele=Remote_Scan();
//			}
//		Remote_delay_ms(5);
//		sys_time++;
	}
}
	
	
	

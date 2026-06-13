#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "CAR.h"
#include "Servo.h"
#include "Ultrasound.h"

// 舵机角度参数
#define Servo_Left 180    // 左偏角度
#define Servo_Center 90   // 居中角度
#define Servo_Right 0     // 右偏角度

// 避障相关参数
#define JuLi 20    // 避障阈值（cm）
#define Motor_Speed 85
#define Servo_Delay 200  // 舵机旋转到位延迟（ms）
#define Car_Turn_Delay 500     // 小车转向延迟（ms）

#define LED_BiZhang_Light GPIO_SetBits(GPIOB,GPIO_Pin_4);		//亮起-避障模式-超声波检测到
#define LED_BiZhang_Drown GPIO_ResetBits(GPIOB,GPIO_Pin_4);	//熄灭-避障模式-超声波未检测到

#define LED_XingShi_Light GPIO_SetBits(GPIOB,GPIO_Pin_3);		//亮起-行驶模式-超声波未检测到
#define LED_XingShi_Drown GPIO_ResetBits(GPIOB,GPIO_Pin_3);	//熄灭-行驶模式-超声波检测到

uint16_t Distance;
uint16_t Center_cm, Right_cm, left_cm;

void BiZhang_Init(void)
{

	Center_cm = HCSR04_GetValue();
	while(Center_cm==0)
	{
		Car_Stop();		
		Center_cm = HCSR04_GetValue(); // 前方测距
	}

	
	// 过滤异常值（小于2cm或大于400cm均视为无效，重新测距）
	while (Center_cm < 2 || Center_cm > 400)
	{
		Center_cm = HCSR04_GetValue();
		Delay_ms(50);
	}
	
	// 避障		
	if (Center_cm > JuLi)
	{
		Go_Ahead(Motor_Speed);
	}
	else
	{		
		Car_Stop();
		
		Servo_SetAngle(Servo_Right);		//舵机右转
		Delay_ms(Servo_Delay+120);					//舵机转动时间
		Servo_SetAngle(Servo_Center);		//舵机舵机静止
		Delay_ms(Servo_Delay+120);					////舵机转动时间
		
		Center_cm = HCSR04_GetValue(); 	// 右方测距
		if (Center_cm > JuLi)
		{
			Servo_SetAngle(Servo_Left);		//回到正前方-舵机左转
			Delay_ms(Servo_Delay+120);				//舵机转动时间
			Servo_SetAngle(Servo_Center);	//舵机静止
			Delay_ms(Servo_Delay+120);				//舵机转动时间
			
			Self_Right(Motor_Speed);
			Delay_ms(Car_Turn_Delay);
			Go_Ahead(Motor_Speed);
		}
		else
		{
			Servo_SetAngle(Servo_Left);		//舵机朝向右方时左转朝向左
			Delay_ms(Servo_Delay*2+120);			
			Servo_SetAngle(Servo_Center);
			Delay_ms(Servo_Delay*2+120);
			
			Center_cm = HCSR04_GetValue(); // 左方测距
			if (Center_cm > JuLi)
			{
				Servo_SetAngle(Servo_Right);//舵机朝左时右转回到正前方
				Delay_ms(Servo_Delay+120);
				Servo_SetAngle(Servo_Center);
				Delay_ms(Servo_Delay+120);
				
				Self_Left(Motor_Speed);
				Delay_ms(Car_Turn_Delay);
				Go_Ahead(Motor_Speed);
			}
			else
			{
				Servo_SetAngle(Servo_Right);//舵机朝左时右转回到正前方
				Delay_ms(Servo_Delay+120);
				Servo_SetAngle(Servo_Center);
				Delay_ms(Servo_Delay+120);
				
//				Go_Back(Motor_Speed);
//				Delay_ms(2000);
				Car_Stop();
			}
		}
	}
}

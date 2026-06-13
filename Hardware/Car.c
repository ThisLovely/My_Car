#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"
#include "PWMServo.h"

void Car_Init(){
	Motor_Init();
}
void Go_Ahead(uint8_t Speed){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(Speed);
}
void Go_Back(uint8_t Speed){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(-Speed);
}
void Turn_Left(uint8_t Speed){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(0);
}
void Turn_Right(uint8_t Speed){
	Motor_SetRightSpeed(Speed);
	Motor_SetLeftSpeed(0);
	
}
void Self_Left(uint8_t Speed){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(-Speed);
}
void Self_Right(uint8_t Speed){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(Speed);
}
void Car_Stop(){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}

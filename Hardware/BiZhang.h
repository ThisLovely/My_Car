#ifndef _BIZHANG_H_
#define _BIZHANG_H_

#include "stm32f10x.h"
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
#define Servo_Delay 700  // 舵机旋转到位延迟（ms）
#define Car_Turn_Delay 1300     // 小车转向延迟（ms）


//uint16_t Distance;
//uint16_t Center_cm, Right_cm, left_cm;

void BiZhang_Init(void);

#endif

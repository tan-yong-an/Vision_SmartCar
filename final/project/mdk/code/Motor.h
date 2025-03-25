#ifndef  _Motor_h_
#define  _Motor_h_

#include "zf_common_typedef.h"

#define MOTOR4_DIR               (D0 )
#define MOTOR4_PWM               (PWM2_MODULE3_CHA_D2)

#define MOTOR3_DIR               (D1 )
#define MOTOR3_PWM               (PWM2_MODULE3_CHB_D3)

#define MOTOR2_DIR               (D15 )
#define MOTOR2_PWM               (PWM1_MODULE0_CHB_D13)

#define MOTOR1_DIR               (D14 )
#define MOTOR1_PWM               (PWM1_MODULE0_CHA_D12)

void Motor_Init(void);

void Set_Motor1(float Speed);
void Set_Motor2(float Speed);
void Set_Motor3(float Speed);
void Set_Motor4(float Speed);

void Car_Stop(void);

int McNamm1(int straight,int spin,int translation);
int McNamm2(int straight,int spin,int translation);
int McNamm3(int straight,int spin,int translation);
int McNamm4(int straight,int spin,int translation);

//运动转换 决定角速度
#define k_r_x_y 1   //(0.18/2+0.21/2) //500

//电机结构体
typedef struct{
	float vel_ex;   //期望速度
	float vel_ac;   //实际速度
	float duty; 
	float dis;//距离
	float duty_p;
//可以参考上交代码 加个模式选择	
}_Motor;
extern _Motor motor1, motor2, motor3, motor4;
extern float error1,error2,error3_,error4;

void turn_control();
void pid_motor_set();
void motor_set(float motor1_duty,float motor2_duty,float motor3_duty,float motor4_duty);
void wheel_control(float x,float y,float w);

#endif
#include "zf_common_headfile.h"
#include "zf_driver_pwm.h"

#include "Motor.h"
#include "PID.h"

float error1=0,error2=0,error3_=0,error4=0;
//左前为1号 其余顺时针
_Motor motor1 = {.vel_ex = 0,\
                 .vel_ac = 0,\
                 .duty=0,\
				 .dis=0,\
				 .duty_p=0};
_Motor motor2 = {.vel_ex = 0,\
                 .vel_ac = 0,\
                 .duty=0,\
				 .dis=0,\
				 .duty_p=0};
_Motor motor3 = {.vel_ex = 0,\
                 .vel_ac = 0,\
                 .duty=0,\
				 .dis=0,\
				 .duty_p=0};
_Motor motor4 = {.vel_ex = 0,\
                 .vel_ac = 0,\
                 .duty=0,\
				 .dis=0,\
				.duty_p=0}; 

void Motor_Init(void)
{
    gpio_init(MOTOR1_DIR, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR3_DIR, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR3_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR4_DIR, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR4_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0
}

void Set_Motor1(float Speed)
{
        if(Speed >= 0)                                                           // 左侧正转
        {
            gpio_set_level(MOTOR1_DIR, 1);                                         // DIR输出高电平
            pwm_set_duty(MOTOR1_PWM,Speed);                   // 计算占空比
        }
        else                                                                    // 左侧反转
        {
            gpio_set_level(MOTOR1_DIR,0);                                          // DIR输出低电平
            pwm_set_duty(MOTOR1_PWM, (-Speed));                // 计算占空比
        }
}

void Set_Motor2(float Speed)
{
        if(Speed >= 0)                                                           // 左侧正转
        {
            gpio_set_level(MOTOR2_DIR, 0);                                         // DIR输出高电平
            pwm_set_duty(MOTOR2_PWM,Speed);                   // 计算占空比
        }
        else                                                                    // 左侧反转
        {
            gpio_set_level(MOTOR2_DIR, 1);                                          // DIR输出低电平
            pwm_set_duty(MOTOR2_PWM, (-Speed));                // 计算占空比
        }
}

void Set_Motor3(float Speed)
{
        if(Speed >= 0)                                                           // 左侧正转
        {
            gpio_set_level(MOTOR3_DIR, 1);                                         // DIR输出高电平
            pwm_set_duty(MOTOR3_PWM,Speed);                   // 计算占空比
        }
        else                                                                    // 左侧反转
        {
            gpio_set_level(MOTOR3_DIR, 0);                                          // DIR输出低电平
            pwm_set_duty(MOTOR3_PWM, (-Speed));                // 计算占空比
        }
}

void Set_Motor4(float Speed)
{
        if(Speed >= 0)                                                           // 左侧正转
        {
            gpio_set_level(MOTOR4_DIR, 0);                                         // DIR输出高电平
            pwm_set_duty(MOTOR4_PWM,Speed);                   // 计算占空比
        }
        else                                                                    // 左侧反转
        {
            gpio_set_level(MOTOR4_DIR, 1);                                          // DIR输出低电平
            pwm_set_duty(MOTOR4_PWM, (-Speed));                // 计算占空比
        }
}

void Car_Stop(void)
{
	Set_Motor1(0);
	Set_Motor2(0);
	Set_Motor3(0);
	Set_Motor4(0);
}

float b = 0.9,c = 4.5;
	
int McNamm1(int straight,int spin,int translation)
{
	float temp = 0; 
	temp = straight+b*translation+c*spin;
//	if(PID1_target>PWM_DUTY_MAX||PID1_target<-(PWM_DUTY_MAX)) PID1_target=0;
	return temp;
}
int McNamm2(int straight,int spin,int translation)
{
	float temp = 0;
	temp = straight-b*translation-c*spin;
//	if(PID2_target>PWM_DUTY_MAX||PID2_target<-(PWM_DUTY_MAX)) PID2_target=0;

	return temp;
}
int McNamm3(int straight,int spin,int translation)
{
	float temp = 0;
	temp = straight+b*translation-c*spin;
//	if(PID3_target>PWM_DUTY_MAX||PID3_target<-(PWM_DUTY_MAX)) PID3_target=0;

	return temp;
}
int McNamm4(int straight,int spin,int translation)
{
	float temp = 0;
	temp = straight-b*translation+c*spin;
//	if(PID4_target>PWM_DUTY_MAX||PID4_target<-(PWM_DUTY_MAX)) PID4_target=0;

	return temp;
}

//pid速度闭环控制
void pid_motor_set(){
	
	float k=1;	
	
	error1 = motor1.vel_ex - motor1.vel_ac;
	error2 = motor2.vel_ex - motor2.vel_ac;
	error3_ = motor3.vel_ex - motor3.vel_ac;
	error4 = motor4.vel_ex - motor4.vel_ac;
	
	motor1.duty += increment_pid(&pid1, error1);
	motor2.duty += increment_pid(&pid2, error2);
	motor3.duty += increment_pid(&pid3, error3_);
	motor4.duty += increment_pid(&pid4, error4);
	
	motor1.duty=limit(motor1.duty,200);   //152
	motor2.duty=limit(motor2.duty,200);
	motor3.duty=limit(motor3.duty,200);   //132
	motor4.duty=limit(motor4.duty,200);

	  motor_set(((motor1.duty*k)+((1-k)*motor1.duty_p))/*+motor1.vel_ex/0.0078*/,\
		((motor2.duty*k)+((1-k)*motor2.duty_p))/*+motor2.vel_ex/0.0078*/,((motor3.duty*k)+((1-k)*motor3.duty_p))/*+motor3.vel_ex/0.0078*/,\
		((motor4.duty*k)+((1-k)*motor4.duty_p))/*+motor4.vel_ex/0.0078*/);
	
	motor1.duty_p=((motor1.duty*k)+((1-k)*motor1.duty_p));
	motor2.duty_p=((motor2.duty*k)+((1-k)*motor2.duty_p));
	motor3.duty_p=((motor3.duty*k)+((1-k)*motor3.duty_p));
	motor4.duty_p=((motor4.duty*k)+((1-k)*motor4.duty_p));
}

void turn_control()
{	
	float w = turn_Yaw();
	w=limit(w,10);
	wheel_control(0,0,w);
}

//控制车运动 输入为 xyw三个方向的期望速度
void wheel_control(float y,float x,float w)
{
	//在此添加角度闭环
	w1=turn_Yaw();
    //前馈   
	motor1.vel_ex = (float)(y + x + k_r_x_y*(w+w1) ); //一号轮 左前轮
	motor2.vel_ex = (float)(-y + x - k_r_x_y*(w+w1)); //二号轮 右前轮

	motor3.vel_ex = (float)(y + x - k_r_x_y*(w+w1)); //三号轮 右后轮
	motor4.vel_ex = (float)(-y + x +k_r_x_y*(w+w1)); //四号轮 左后轮

}
//给四个电机pwm
void motor_set(float motor1_duty1,float motor2_duty1,float motor3_duty1,float motor4_duty1)
{
	int32 motor1_duty = (int32) motor1_duty1;
	int32 motor2_duty = (int32) motor2_duty1;
	int32 motor3_duty = (int32) motor3_duty1;
	int32 motor4_duty = (int32) motor4_duty1;
		
	Set_Motor1(motor1_duty);
	Set_Motor2(motor2_duty);
	Set_Motor3(motor3_duty);
	Set_Motor4(motor4_duty);
}

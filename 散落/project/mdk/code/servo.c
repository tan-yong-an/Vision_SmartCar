#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

void servo_Init(void)
{
	pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, 0);
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, 0);
	
	gpio_init(B23, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // B23口接电磁铁

	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));   //初始化给40
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120));  //初始化给120

}

void take_picture(void)  //捡图片
{
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(-13));   //数值减小，往内收，再小就一直收
	system_delay_ms(100);
	gpio_set_level(B23, GPIO_HIGH);                                  //电磁铁高电平吸图片
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(195));   //数值减小，大臂上抬	
	system_delay_ms(1000);
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));  
	system_delay_ms(100);	
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120)); 
	system_delay_ms(1000);	
	gpio_set_level(B23, GPIO_LOW);                                  //电磁铁低电平放图片
}

void put_picture(void)
{	
	  motor1.duty=0;
	  motor2.duty=0;
	  motor3.duty=0;
	  motor4.duty=0;
	  wheel_control(0,0,0);
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(14)); 
	system_delay_ms(100);
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(105)); 
	system_delay_ms(100);
	gpio_set_level(B23, GPIO_HIGH);                                  //电磁铁高电平吸图片
	system_delay_ms(1000);
	
	  motor1.duty=0;
	  motor2.duty=0;
	  motor3.duty=0;
	  motor4.duty=0;
	  wheel_control(0,0,0);
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(180));
	system_delay_ms(100);	
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(-10));  
	system_delay_ms(1000);
	gpio_set_level(B23, GPIO_LOW);                                  //电磁铁低电平放图片
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));   //初始化给40
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120));  //初始化给120		
}
		
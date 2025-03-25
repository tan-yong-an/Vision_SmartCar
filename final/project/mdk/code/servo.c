#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

int take_times = 0;   //��ͼƬ����
int put_times = 0;

void servo_Init(void)
{
	pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, 0);
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, 0);
	
	gpio_init(B23, GPO, GPIO_LOW, GPO_PUSH_PULL);                            // B23�ڽӵ����

	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));   //��ʼ����40
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120));  //��ʼ����120

}

void take_picture(void)  //��ͼƬ
{
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(-12));   //��ֵ��С�������գ���С��һֱ��
	system_delay_ms(100);
	gpio_set_level(B23, GPIO_HIGH);                                  //������ߵ�ƽ��ͼƬ
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(195));   //��ֵ��С�������̧	
	system_delay_ms(1000);
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));  
	system_delay_ms(100);	
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120)); 
	system_delay_ms(1000);	
	gpio_set_level(B23, GPIO_LOW);                                  //������͵�ƽ��ͼƬ
}

void put_picture(void)
{	
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(110)); 
	system_delay_ms(1000);
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(14)); 
	system_delay_ms(100);
	gpio_set_level(B23, GPIO_HIGH);                                  //������ߵ�ƽ��ͼƬ

	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(180));
	system_delay_ms(100);	
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(-10));  
	system_delay_ms(1000);
	gpio_set_level(B23, GPIO_LOW);                                  //������͵�ƽ��ͼƬ
	
	pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY(40));   //��ʼ����40
	pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY(120));  //��ʼ����120
	
	put_times = 1;
	
}
		
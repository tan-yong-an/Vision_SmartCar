#ifndef _servo_h_
#define _servo_h_

#define SERVO_MOTOR_PWM2             (PWM4_MODULE2_CHA_C30)                 // ���������϶����Ӧ����
#define SERVO_MOTOR_PWM1             (PWM1_MODULE3_CHA_B10)
#define SERVO_MOTOR_FREQ            (150 )                                           // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300

#define SERVO_MOTOR_L_MAX           (0 )                                           // ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX           (180)                                           // ���������϶�����Χ �Ƕ�

// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
// 
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
// 
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
// 
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
// 
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))

//#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>300)
//    #error "SERVO_MOTOR_FREQ ERROE!"
extern int take_times;
extern int put_times;
void servo_Init(void);
void take_picture(void);
void put_picture(void);
	
#endif 
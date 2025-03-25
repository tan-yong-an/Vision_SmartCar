#ifndef _imu_h_
#define _imu_h_
#include "zf_common_headfile.h"

void cal_rollAngle();
//IMU��ʼ��
void imu_init();
float fabs_(float a);
typedef struct 
{
	//���ٶȼƼ�����ٶ�
	float  acc_x;
	float  acc_y;
	float  acc_z;
	//���ٶ�
	float gyro_x;
	float gyro_y;
	float gyro_z;
	//�Ƕ�
	float Pitch;
	float Yaw;
	float Roll;
	float ex_yaw;   //��������
	float enc_update;
	//λ��
	float now_x;
	float now_y;
	//�Լ�
	float gyro_bias;  //��������ƫ
	float acc_x_bias;  //���ٶȼ�x����ƫ
	float acc_y_bias;  //���ٶȼ�y����ƫ
	//�ǶȻ�pid
	float kpid_in[3];
	float kpid_out[3];
	float kpid_out1[3];
	//��Ҫ�ܵľ���
	float ex_x;
	float ex_y;

}IMU_;
extern IMU_ IMU;

void yaw_clear();
float turn_Yaw();
void spin_angle(int angle);

#endif

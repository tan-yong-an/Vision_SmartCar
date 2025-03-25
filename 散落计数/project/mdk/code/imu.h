#ifndef _imu_h_
#define _imu_h_
#include "zf_common_headfile.h"

void cal_rollAngle();
//IMU初始化
void imu_init();
float fabs_(float a);
typedef struct 
{
	//加速度计计算加速度
	float  acc_x;
	float  acc_y;
	float  acc_z;
	//角速度
	float gyro_x;
	float gyro_y;
	float gyro_z;
	//角度
	float Pitch;
	float Yaw;
	float Roll;
	float ex_yaw;   //期望方向
	float enc_update;
	//位置
	float now_x;
	float now_y;
	//自检
	float gyro_bias;  //陀螺仪零偏
	float acc_x_bias;  //加速度计x轴零偏
	float acc_y_bias;  //加速度计y轴零偏
	//角度环pid
	float kpid_in[3];
	float kpid_out[3];
	float kpid_out1[3];
	//需要跑的距离
	float ex_x;
	float ex_y;

}IMU_;
extern IMU_ IMU;

void yaw_clear();
float turn_Yaw();
void spin_angle(int angle);

#endif

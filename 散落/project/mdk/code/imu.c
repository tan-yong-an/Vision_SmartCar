#include "imu.h"
#include <math.h>

#define M_PI        3.1415926f

IMU_ IMU; 

float fabs_(float a){
	return (float)(fabs((double) a));
}

void imu_init()
{
	IMU.acc_x = 0;
	IMU.acc_y = 0;
	IMU.acc_z = 0;
	//���ٶ�
	IMU.gyro_x = 0;
	IMU.gyro_y = 0;
	IMU.gyro_z = 0;
	//�Ƕ�
	IMU.Pitch = 0;
	IMU.Yaw = 0;
	IMU.Roll = 0;
	//��������
	IMU.ex_yaw = 0;
	//����λ��
	IMU.now_x = 0;
	IMU.now_y = 0;
	//�ǶȻ�pid����14
	float kpid_out[3] = {0.15,0,0.63};
	float kpid_in[3] = {0.0f,0.f,0.f};
	IMU.kpid_in[0] = kpid_in[0];
	IMU.kpid_in[1] = kpid_in[1];
	IMU.kpid_in[2] = kpid_in[2];
	IMU.kpid_out[0] = kpid_out[0];
	IMU.kpid_out[1] = kpid_out[1];
	IMU.kpid_out[2] = kpid_out[2];
	//imu�Լ�
	for(uint16_t i = 0;i<1000;i++)
	{
		imu660ra_get_gyro();     
		imu660ra_get_acc(); 
		IMU.gyro_bias += imu660ra_gyro_z;
		IMU.acc_x_bias += imu660ra_acc_x;
		IMU.acc_y_bias += imu660ra_acc_y;
		system_delay_ms(2);
		
	}
    IMU.gyro_bias /= 1000.f;
  	IMU.acc_x_bias /= 1000.f;
	  IMU.acc_y_bias /= 1000.f;

}
void cal_rollAngle()
{
	//ȡֵ���ʱ��
	static uint32 dt_ = 0;
	int32 dt;
	static int16 gyro_z_p = 0;
	static int16 acc_y_p = 0;
	
	imu660ra_get_gyro();
	imu660ra_get_acc();
	IMU.gyro_z = -(imu660ra_gyro_z - IMU.gyro_bias);     //M:21.85   H:1.769
	
	IMU.acc_y = imu660ra_acc_y - IMU.acc_y_bias;
	//��ͨ�˲�
	float alpha = 0.7;
	IMU.gyro_z = IMU.gyro_z*alpha + (1-alpha)*gyro_z_p;
	gyro_z_p = IMU.gyro_z;
	IMU.gyro_z = imu660ra_gyro_transition(IMU.gyro_z);
	
	//���ֳ��Ƕ�
	IMU.Yaw +=  -IMU.gyro_z*0.010;           //5.20 �Ƿ��ж�ʱ��Ļ���
	//IMU.now_y += IMU.acc_y*0.001;
	if(IMU.Yaw >= 360) 	IMU.Yaw -= 360;
	if(IMU.Yaw < 0 )   IMU.Yaw = 360 + IMU.Yaw;
	Car.car_yaw=IMU.Yaw;
}

void yaw_clear()     //�Ƕ���Ϣ����
{
	IMU.acc_x = 0;
	IMU.acc_y = 0;
	IMU.acc_z = 0;
	//���ٶ�
	IMU.gyro_x = 0;
	IMU.gyro_y = 0;
	IMU.gyro_z = 0;
	//�Ƕ�
	IMU.Pitch = 0;
	IMU.Yaw = 0;
	IMU.Roll = 0;
	//��������
	IMU.ex_yaw = 0;
	//����λ��
	IMU.now_x = 0;
	IMU.now_y = 0;
}

float turn_Yaw()
{   
	//�⻷λ��ʽ
	if(IMU.ex_yaw >= 360) 	IMU.ex_yaw -= 360;
	if(IMU.ex_yaw < 0 )   IMU.ex_yaw = 360 + IMU.ex_yaw;
	float *kpid_out = IMU.kpid_out;
	//�ڻ�����ʽ
	float *kpid_in = IMU.kpid_in;
	static float error_p_out = 0.f;
//	static float error_p_p_out = 0.f;
	static float d_out = 0.f;
	static float d_out_p = 0.f;
	static float pid_value = 0.f;
	float error = 0.f;
	float dpid = 0.f;
	//����������ת����
	IMU.ex_yaw = ((int16)(IMU.ex_yaw*10) % 3600)/10.0f;
	error = (Car.car_yaw - IMU.ex_yaw);
	if(fabs_(360 - fabs_(Car.car_yaw - IMU.ex_yaw)) >= fabs_(Car.car_yaw - IMU.ex_yaw))
		error = -(Car.car_yaw - IMU.ex_yaw);
	else{
		error = ((error/fabs_(error)) * (360 - fabs_(Car.car_yaw - IMU.ex_yaw)));
	}
	//�⻷λ��ʽ   D�ӵ�ͨ  ϵ����������0.7
	float output = kpid_out[0] * error + kpid_out[2] *(error-error_p_out);
	error_p_out = error;
	d_out_p=(1* (d_out)+0*(d_out_p));
    pid_value=output;
   	return limit(pid_value,20);
}

// ����������ȷ���Ƕ���0��360��֮��
int normalize_angle(int angle) {
    while (angle >= 360) angle -= 360;
    while (angle < 0) angle += 360;
    return angle;
}

//ֱ�Ӵ���Ҫת�ĽǶȣ�˳ʱ��Ϊ+,��ʱ��Ϊ-
void spin_angle(int angle) 
{
    MCX_switch = 0;    //�ر�MCX	
    MCX_flag = 0;	
	
//	int current_yaw = Car.car_yaw;
    int target_yaw = normalize_angle(angle);
    
    // ���������Ƕ�
    IMU.ex_yaw = target_yaw;
    
    // ��ת��Ŀ��Ƕ�
    while (fabs_(Car.car_yaw - IMU.ex_yaw) > 6) 
	{
		turn_control();
	}
   
	motor1.duty=0;
	motor2.duty=0;
	motor3.duty=0;
	motor4.duty=0;
	wheel_control(0, 0, 0);
	
	Car.car_yaw = IMU.ex_yaw;
	system_delay_ms(500);
}

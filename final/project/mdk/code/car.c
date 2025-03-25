#include "zf_common_headfile.h"
#include <math.h>

#define pi 3.14159265358979323846

int state = 0;
bool xy_flag = true;

int lie = 0;

float car_now_x[5];
float car_now_y[5];

float velocity_global_lim_max=20;
float velocity_global_lim=0;
float ac_vel_y;
float ac_vel_x;
float vx;
float vy;
float w1=0;
float w=0;

//����״̬��λ�� Vx Vy Vw �Ƕȣ� ex ��������ֵ  
//������x������  ��ǰΪy������ ˳ʱ��Ϊw������  
_Car_state Car = 
{
	.vel_x = 0,
    .vel_y = 0,
    .vel_w = 0,
	
    .car_x =0,
	.car_y =0,
	.car_yaw = 0,
	
	.ex_vel_x = 0,
    .ex_vel_y = 0,
    .ex_vel_w = 0,
	
    .ex_car_x = 0,
	.ex_car_y = 0,		//���Ը�����
	.ex_car_yaw = 0,   
	
	.straight=0,
	
	.ex_straight=0,
	.ex_car_x_p=0,
	.ex_car_y_p=0
}; 

int8 current_x[5];
int8 current_y[5];

void cal_dis()
{   
	vx=(motor1.dis-motor2.dis+motor3.dis-motor4.dis)/1.414/4.0;
	vy=(motor1.dis+motor2.dis+motor3.dis+motor4.dis)/1.414/4.0;
	ac_vel_y=(motor1.vel_ac+motor2.vel_ac+motor3.vel_ac+motor4.vel_ac)/1.414/4.0;
	ac_vel_x=(motor1.vel_ac-motor2.vel_ac+motor3.vel_ac-motor4.vel_ac)/1.414/4.0;
	float imu_yaw=IMU.Yaw*pi/180;
	Car.car_x+=0.95*(vy*sin(imu_yaw)+vx*cos(imu_yaw));
	Car.car_y += vy*cos(imu_yaw)-vx*sin(imu_yaw);
	Car.straight+=(motor1.dis+motor2.dis+motor3.dis+motor4.dis)/1.414/4.0;
}

void plan_vel()
{  
	static float vel_toge_p=0; // ֮ǰ���ٶ�
	
// ���㲻ͬ����֮��ľ���
	float dis_x = Car.ex_car_x -  Car.car_x;
	float dis_y = Car.ex_car_y -  Car.car_y;
	float dis_x1 = Car.ex_car_x_p -  Car.car_x;
	float dis_y1 = Car.ex_car_y_p -  Car.car_y;
	float dis_x2 = Car.ex_car_x_p -  Car.ex_car_x;
	float dis_y2 = Car.ex_car_y_p -  Car.ex_car_y;
	
// ����ŷ����þ���
	float dis=(float)sqrt((double)(dis_x*dis_x + dis_y*dis_y));
	float dis_ago=(float)sqrt((double)(dis_x1*dis_x1 + dis_y1*dis_y1));
	float dis_all=(float)sqrt((double)(dis_x2*dis_x2 + dis_y2*dis_y2));  //���������֮��
	//�⻷2ms �ڻ�1ms
	float vel_toge;
	
// ���ú��������������ٶȵĹ�ϵ
	speeed_area_up(dis_ago,30,5);
	
// ʹ��PID�������������ٶ�
	vel_toge=common_pid(&pid5,dis);
	
// ���㳵����x��y�����ϵ��ٶȷ���
	Car.ex_vel_x=vel_toge*dis_x/dis;
	Car.ex_vel_y=vel_toge*dis_y/dis;
	
// ���浱ǰ�ٶ��Թ���һ��ʹ��
	vel_toge_p=vel_toge;

}	
//���䷽ʽ����
void speeed_area_up(float now, float area, int stay)
{    float k_up;
	float  k_down;
	k_up=now/area;
	if(now<=area&&now>=0)                                  //�ٶȷֶη���
	velocity_global_lim=(int)(k_up*(velocity_global_lim_max-stay)+stay);
	else 
	velocity_global_lim=velocity_global_lim_max;
}

void approach_img()
{	
	static float vel_p[2]={0};
	//�쳣ֵ��ȥ
	if(abs(MINI_x) > 30 || abs(MINI_y) >30)  return;
	
	float vel_x,vel_y;
	
    vel_x=new_common_pid(&pid6,MINI_x);
    vel_y=new_common_pid(&pid7,MINI_y);
	
	vel_x=0.7*vel_x+0.3*vel_p[0];
	vel_y=0.7*vel_y+0.3*vel_p[1];
	Car.ex_vel_x=limit(vel_x,10);
	Car.ex_vel_y=limit(vel_y,10);
	vel_p[0]=vel_x;vel_p[1]=vel_y;	
}

void run_translation(float dis_cm_x,float dis_cm_y)
{  
	Car.ex_car_x=dis_cm_x;
	Car.ex_car_y=dis_cm_y;
	Car.ex_vel_y=0;
	Car.ex_vel_x=0;
	Car.ex_car_yaw=0;
	return;
}

void go_next(float next_x,float next_y)
{
	static float next_x_p=0;
	static float next_y_p=0;
	run_translation(next_x,next_y);
	next_x_p=next_x;
	next_y_p=next_y;
	xy_flag = false;
	
	if ((fabs_(Car.ex_car_y-Car.car_y)<4)&&(fabs_(Car.ex_car_x-Car.car_x)<4))
	{			  
		Car.ex_car_x_p=Car.ex_car_x;
		Car.ex_car_y_p=Car.ex_car_y;
		motor1.duty=0;
		motor2.duty=0;
		motor3.duty=0;
		motor4.duty=0;
		wheel_control(0,0,0);	
		arrived_flag = 1;
	}			  
	else
	{  
	plan_vel();
	wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
	}
}  

void go_to(float next_x,float next_y)
{
	static float next_x_p=0;
	static float next_y_p=0;
	run_translation(next_x,next_y);
	next_x_p=next_x;
	next_y_p=next_y;
	if ((fabs_(Car.ex_car_y-Car.car_y)<4)&&(fabs_(Car.ex_car_x-Car.car_x)<4))
	{			  
		Car.ex_car_x_p=Car.ex_car_x;
		Car.ex_car_y_p=Car.ex_car_y;
		
		motor1.duty=0;
		motor2.duty=0;
		motor3.duty=0;
		motor4.duty=0;
		wheel_control(0,0,0);
		
		arrived_flag = 1;
	}			  
	else
	{  
	plan_vel();
	wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
	}
}

void xy_move(float delta_x, float delta_y) 
{
//    float next_x = Car.car_x + delta_x;
//    float next_y = Car.car_y + delta_y;
    
    Car.ex_car_x = delta_x;
    Car.ex_car_y = delta_y;

    run_translation(delta_x,delta_y);

	while(1)
	{
	tft180_show_int(16*2, 16*2, Car.car_x, 3);
	tft180_show_int(16*2, 16*3, Car.car_y, 3);
	tft180_show_int(16*2, 16*4,Car.car_yaw, 3);

	tft180_show_int(16*2, 16*6, Car.ex_car_x, 3);
	tft180_show_int(16*2, 16*7, Car.ex_car_y, 3);
	tft180_show_int(16*2, 16*8, IMU.ex_yaw, 3);
		if ((fabs_(Car.ex_car_y - Car.car_y) < 20) && (fabs_(Car.ex_car_x - Car.car_x) < 20)) 
		{
			Car.ex_car_x_p = Car.ex_car_x;
			Car.ex_car_y_p = Car.ex_car_y;
			
			motor1.duty = 0;
			motor2.duty = 0;
			motor3.duty = 0;
			motor4.duty = 0;
			wheel_control(0,0,0);			
			arrived_flag = 1;
			break;
			
		} else 
		{  
			plan_vel();
			wheel_control(Car.ex_vel_x, Car.ex_vel_y, 0);
		}		
	}
}

void run_point(float next_x,float next_y)
{
	MCX_switch = 0;   //�ܵ�ر�MCX	
	MCX_flag = 0;	
	
	static float next_x_p=0;
	static float next_y_p=0;
	run_translation(next_x,next_y);
	next_x_p=next_x;
	next_y_p=next_y;
	if ((fabs_(Car.ex_car_y-Car.car_y)<4)&&(fabs_(Car.ex_car_x-Car.car_x)<4))
	{			  
		Car.ex_car_x_p=Car.ex_car_x;
		Car.ex_car_y_p=Car.ex_car_y;
		motor1.duty=0;
		motor2.duty=0;
		motor3.duty=0;
		motor4.duty=0;
		wheel_control(0,0,0);
		
		arrived_flag = 1;
	}			  
	else
	{  
	plan_vel();
	wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
	}
} 

//Բ��ɨ��
void scan()
{
	switch(lie)
	{
		case 0:
			if(xy_flag)
			{
				current_x[lie] = Car.car_x;
				current_y[lie] = Car.car_y;
			}
			go_next(current_x[lie],current_y[lie]-100);
			if(arrived_flag == 1)
			{
				xy_flag = true;
				lie++;
				arrived_flag = 0;
				MCX_switch = 1;
				
			}
		break;
		case 1:
			if(xy_flag)
			{
				current_x[lie] = Car.car_x;
				current_y[lie] = Car.car_y;
			}
			go_next(current_x[lie]+70,current_y[lie]+30);
			if(arrived_flag == 1)
			{
				xy_flag = true;
				lie++;
				arrived_flag = 0;
				MCX_switch = 1;		
			}
		break;
			
		case 2:
			if(xy_flag)
			{
				current_x[lie] = Car.car_x;
				current_y[lie] = Car.car_y;
			}
			go_next(current_x[lie],current_y[lie]+120);
			if(arrived_flag == 1)
			{
				xy_flag = true;
				lie++;
				arrived_flag = 0;
				MCX_switch = 1;		
			}
			break;		
		case 3:
			if(xy_flag)
			{
				current_x[lie] = Car.car_x;
				current_y[lie] = Car.car_y;
			}
			go_next(current_x[lie]-90,current_y[lie]+10);
			if(arrived_flag == 1)
			{
				xy_flag = true;
				lie++;
				arrived_flag = 0;
				MCX_switch = 1;		
			}
		break;
		case 4:
			if(xy_flag)
			{
				current_x[lie] = Car.car_x;
				current_y[lie] = Car.car_y;
			}
			go_next(current_x[lie]-80,current_y[lie]-60);
			if(arrived_flag == 1)
			{
				xy_flag = true;
				lie++;
				arrived_flag = 0;
				MCX_switch = 1;
			}
		break;
	}
}

//��ʮ�ֻ���ת��ͼ,����Բ�����ͼ�Ϳ�ʼ��ͼ����ͼҪ�����״̬��ɨ��ĸ������ҲҪ����ûͼ��ʱ��zimu_count = 0
void right_cross_scan()
{
	switch(zimu_count)
	{
		case 0:  //ת��ͷ��ͼ
			spin_angle(-45); //��ת160��					
			xy_move(-20,20);
//			if(arrived_flag == 1)   //תͷ�Ϳ�����ͷ
//			{
//				MCX_switch = 1;
//				system_delay_ms(10000);			
//			}	
		zimu_count++;
		break;
			
		case 1:  
			spin_angle(45); 
			xy_move(20,20);
//			if(arrived_flag == 1) 
//			{
//				MCX_switch = 1;
//				system_delay_ms(1000);			
//			}	
		zimu_count++;

		break;
			
		case 2:  
			spin_angle(45); 
			xy_move(20,-20);
			if(arrived_flag == 1) 
			{
				MCX_switch = 1;
				system_delay_ms(1000);			
			}	
		break;
			
		case 3:  
			spin_angle(45);
			xy_move(-70,0);
			if(arrived_flag == 1) 
			{
				MCX_switch = 1;
				system_delay_ms(1000);			
			}	
		break;
			
		case 4:  
			spin_angle(-60); //��ʱ��ת60��
			xy_move(-70,0);
			if(arrived_flag == 1) 
			{
				MCX_switch = 1;
				system_delay_ms(1000);			
			}	
		break;
	}		
}

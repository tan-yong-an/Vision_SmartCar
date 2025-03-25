#ifndef _car_h_
#define _car_h_

#include "zf_common_headfile.h"
//车况结构体

extern int state;
extern bool xy_flag;
extern int lie;

typedef struct{
	float car_x, car_y, car_yaw;//车当前x，y坐标和角度
	float vel_x,vel_y,vel_w;//三个方向的车速
	float ex_car_x, ex_car_y, ex_car_yaw;//车期望x，y坐标和角度
	float ex_vel_x,ex_vel_y,ex_vel_w;//三个方向的期望车速
	float straight,ex_straight;
	float ex_car_x_p,ex_car_y_p;
}_Car_state;
extern _Car_state Car;

extern int8 current_x[5];
extern int8 current_y[5];
extern float car_now_x[5];
extern float car_now_y[5];

extern float w;
extern float velocity_global_lim;
extern float ac_vel_y;
extern float ac_vel_x;

extern  float vx;
extern  float vy;
extern float w1;

void cal_dis();
void speeed_area_up(float now, float area, int stay);
void plan_vel();
void approach_img();
void run_translation(float dis_cm_x,float dis_cm_y);

void go_next(float next_x,float next_y);
void go_to(float next_x,float next_y);
void xy_move(float delta_x, float delta_y);
void run_point(float next_x,float next_y);

void scan();
void right_cross_scan();

#endif
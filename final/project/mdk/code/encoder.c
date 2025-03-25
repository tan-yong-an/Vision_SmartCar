#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

//编码器状态  dis记录距离  vel记录编码器返回速度   暂时没用
_Encoder encoder1 = {.dis=0,.vel=0},encoder2={.dis=0,.vel=0},\
            encoder3={.dis=0,.vel=0},encoder4={.dis=0,.vel=0};
						
int16 PID1_actual = 0;
int16 PID2_actual = 0;
int16 PID3_actual = 0;
int16 PID4_actual = 0;

void encoder_Init(void)
{
	  encoder_dir_init(ENCODER_1, ENCODER_1_LSB, ENCODER_1_DIR);                  // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_2, ENCODER_2_LSB, ENCODER_2_DIR);                  // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_3, ENCODER_3_LSB, ENCODER_3_DIR);                  // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_4, ENCODER_4_LSB, ENCODER_4_DIR);                  // 初始化编码器模块与引脚 方向编码器模式
}

void encoder_get(void)
{
    PID1_actual = -encoder_get_count(ENCODER_4);                              // 获取编码器计数
    PID2_actual = encoder_get_count(ENCODER_3);                              // 获取编码器计数    
    PID3_actual = encoder_get_count(ENCODER_2);                              // 获取编码器计数
    PID4_actual = -encoder_get_count(ENCODER_1);                              // 获取编码器计数
	
	    encoder_clear_count(ENCODER_1);                                             // 清空编码器计数
	    encoder_clear_count(ENCODER_2);                                             // 清空编码器计数
	    encoder_clear_count(ENCODER_3);                                             // 清空编码器计数
	    encoder_clear_count(ENCODER_4);                                             // 清空编码器计数
}

//单位时间的脉冲数
void get_wheel_vel(void)
{
	static float last_enc_value[4] = {0,0,0,0};//上次enc 用于低通
	//计算速度 即单位时间脉冲数
	encoder1.vel=(float)(PID1_actual*k_enc+(1-k_enc)*last_enc_value[0]);
	encoder2.vel=(float)(PID2_actual*k_enc+(1-k_enc)*last_enc_value[1]);
	encoder3.vel=(float)(PID3_actual*k_enc+(1-k_enc)*last_enc_value[2]);
	encoder4.vel=(float)(PID4_actual*k_enc+(1-k_enc)*last_enc_value[3]);
	motor1.vel_ac=encoder1.vel/(10);  //5.20 是否与中断时间有关
	motor2.vel_ac=encoder2.vel/(10);
	motor3.vel_ac=encoder3.vel/(10);
	motor4.vel_ac=encoder4.vel/(10);
	
	last_enc_value[0]=encoder1.vel;
	last_enc_value[1]=encoder2.vel;
	last_enc_value[2]=encoder3.vel;
	last_enc_value[3]=encoder4.vel;
//  计算距离
    motor1.dis=(encoder1.vel*0.00828)*50/35.4;            //M车轮直径6.3cm，齿轮数70，编码器齿轮数30；19.782/(1024*2.333)
	motor2.dis=(encoder2.vel*0.00828)*50/35.4;
	motor3.dis=(encoder3.vel*0.00828)*50/35.4;
	motor4.dis=(encoder4.vel*0.00828)*50/35.4;
}
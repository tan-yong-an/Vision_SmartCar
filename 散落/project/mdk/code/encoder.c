#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

//������״̬  dis��¼����  vel��¼�����������ٶ�   ��ʱû��
_Encoder encoder1 = {.dis=0,.vel=0},encoder2={.dis=0,.vel=0},\
            encoder3={.dis=0,.vel=0},encoder4={.dis=0,.vel=0};
						
int16 PID1_actual = 0;
int16 PID2_actual = 0;
int16 PID3_actual = 0;
int16 PID4_actual = 0;

void encoder_Init(void)
{
	  encoder_dir_init(ENCODER_1, ENCODER_1_LSB, ENCODER_1_DIR);                  // ��ʼ��������ģ�������� ���������ģʽ
    encoder_dir_init(ENCODER_2, ENCODER_2_LSB, ENCODER_2_DIR);                  // ��ʼ��������ģ�������� ���������ģʽ
    encoder_dir_init(ENCODER_3, ENCODER_3_LSB, ENCODER_3_DIR);                  // ��ʼ��������ģ�������� ���������ģʽ
    encoder_dir_init(ENCODER_4, ENCODER_4_LSB, ENCODER_4_DIR);                  // ��ʼ��������ģ�������� ���������ģʽ
}

void encoder_get(void)
{
    PID1_actual = -encoder_get_count(ENCODER_4);                              // ��ȡ����������
    PID2_actual = encoder_get_count(ENCODER_3);                              // ��ȡ����������    
    PID3_actual = encoder_get_count(ENCODER_2);                              // ��ȡ����������
    PID4_actual = -encoder_get_count(ENCODER_1);                              // ��ȡ����������
	
	    encoder_clear_count(ENCODER_1);                                             // ��ձ���������
	    encoder_clear_count(ENCODER_2);                                             // ��ձ���������
	    encoder_clear_count(ENCODER_3);                                             // ��ձ���������
	    encoder_clear_count(ENCODER_4);                                             // ��ձ���������
}

//��λʱ���������
void get_wheel_vel(void)
{
	static float last_enc_value[4] = {0,0,0,0};//�ϴ�enc ���ڵ�ͨ
	//�����ٶ� ����λʱ��������
	encoder1.vel=(float)(PID1_actual*k_enc+(1-k_enc)*last_enc_value[0]);
	encoder2.vel=(float)(PID2_actual*k_enc+(1-k_enc)*last_enc_value[1]);
	encoder3.vel=(float)(PID3_actual*k_enc+(1-k_enc)*last_enc_value[2]);
	encoder4.vel=(float)(PID4_actual*k_enc+(1-k_enc)*last_enc_value[3]);
	motor1.vel_ac=encoder1.vel/(10);  //5.20 �Ƿ����ж�ʱ���й�
	motor2.vel_ac=encoder2.vel/(10);
	motor3.vel_ac=encoder3.vel/(10);
	motor4.vel_ac=encoder4.vel/(10);
	
	last_enc_value[0]=encoder1.vel;
	last_enc_value[1]=encoder2.vel;
	last_enc_value[2]=encoder3.vel;
	last_enc_value[3]=encoder4.vel;
//  �������
    motor1.dis=(encoder1.vel*0.00828)*50/35.4;            //M����ֱ��6.3cm��������70��������������30��19.782/(1024*2.333)
	motor2.dis=(encoder2.vel*0.00828)*50/35.4;
	motor3.dis=(encoder3.vel*0.00828)*50/35.4;
	motor4.dis=(encoder4.vel*0.00828)*50/35.4;
}
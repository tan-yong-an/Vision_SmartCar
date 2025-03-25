#ifndef _IMAGE_H
#define _IMAGE_H

#include "zf_common_headfile.h"

//��ɫ���� 
#define uesr_RED     0XF800    //��ɫ
#define uesr_GREEN   0X07E0    //��ɫ
#define uesr_BLUE    0X001F    //��ɫ

//�궨��
#define image_h	80 //ͼ��߶�   80
#define image_w	128 //ͼ����   128

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//�����ĵ���
#define border_max	image_w-2 //�߽����ֵ
#define border_min	1	//�߽���Сֵ	

extern volatile int8 spin ;
extern volatile int8 translation ;

typedef struct {
    int spin;
    int translation;
} ImageProcessResult;

extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//ͼ������

extern ImageProcessResult image_process(void); //ֱ�����жϻ�ѭ������ô˳���Ϳ���ѭ��ִ����

#endif

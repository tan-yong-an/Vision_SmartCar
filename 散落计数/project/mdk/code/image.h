#ifndef _IMAGE_H
#define _IMAGE_H

#include "zf_common_headfile.h"

//颜色定义 
#define uesr_RED     0XF800    //红色
#define uesr_GREEN   0X07E0    //绿色
#define uesr_BLUE    0X001F    //蓝色

//宏定义
#define image_h	80 //图像高度   80
#define image_w	128 //图像宽度   128

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//跳过的点数
#define border_max	image_w-2 //边界最大值
#define border_min	1	//边界最小值	

extern volatile int8 spin ;
extern volatile int8 translation ;

typedef struct {
    int spin;
    int translation;
} ImageProcessResult;

extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//图像数组

extern ImageProcessResult image_process(void); //直接在中断或循环里调用此程序就可以循环执行了

#endif

#ifndef _classify_h_
#define _classify_h_

extern bool distribution_random_complete;

//记录图像信息
extern uint8 all_picture_count;   //看到图片的数量

extern int8_t random_picture_count;
extern char Random_picture[30];

void clear_picture();

//记录数字坐标
extern uint8 number;
extern int8 temp_num_x[3];
extern int8 temp_num_y[3];
typedef struct {
    int num_x;
    int num_y;
    char num_type; 
} Num;
extern Num num_map[3];  //三个数字坐标及种类
void record_num(int i,int x, int y, char target);
void calculate_third_point();

void distribute_random_pictures(char random_picture[], int *size);

#endif
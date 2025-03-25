#ifndef _classify_h_
#define _classify_h_


extern bool distribution_random_complete;
extern bool distribution_ring_complete;

//记录图像信息
extern uint8 all_picture_count;   //看到图片的数量

extern int8_t random_picture_count;
extern char Random_picture[30];

extern int8_t ring_picture_count;
extern char Ring_picture[30];

void clear_picture();
void clear_ring_picture();

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

//记录字母坐标
extern uint8 zimu_count;
extern int8 temp_letter_x[5];
extern int8 temp_letter_y[5];
typedef struct {
    int letter_x;
    int letter_y;
	int letter_z;
    char letter_type; 
} map;
extern map map_letter[5];  //五个字母坐标 及种类
void record_letter(int i,int x, int y, int z, char target);
void clear_letters();

void distribute_random_pictures(char random_picture[], int *size);
void distribute_ring_pictures(char ring_picture[], int *size);

#endif
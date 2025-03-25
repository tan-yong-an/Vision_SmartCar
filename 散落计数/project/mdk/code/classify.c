#include "zf_common_headfile.h"

bool distribution_random_complete = false;  //直线放图完成标志位

//记录图像信息
uint8 all_picture_count = 0;          //看到图片的数量
int8_t random_picture_count = 0;    //随机图片数量
char Random_picture[30];

void clear_picture()      //清空现在的图片类型
{
    for (int i = 0; i <= 64; i++) 
	{
		picture_type[i] = '\0';
    }
}

//记录数字坐标
uint8 number = 0;
int8 temp_num_x[3];
int8 temp_num_y[3];
Num num_map[3];
void record_num(int i,int x, int y, char target) 
{
	num_map[i].num_x = x;
	num_map[i].num_y = y;
	num_map[i].num_type = target;
}

// 计算并记录第三个点的信息
void calculate_third_point() {
    // 计算第三个点的坐标
    num_map[2].num_x = num_map[1].num_x;
    num_map[2].num_y = num_map[1].num_y + 45;

    // 查找剩下的字符
    char remaining_char;
    if (num_map[0].num_type != 'X' && num_map[1].num_type != 'X') {
        remaining_char = 'X';
    } else if (num_map[0].num_type != 'Y' && num_map[1].num_type != 'Y') {
        remaining_char = 'Y';
    } else {
        remaining_char = 'Z';
    }
    // 记录第三个点的类型
    num_map[2].num_type = remaining_char;
}

//直线放图片
void distribute_random_pictures(char random_picture[], int *size) {
    while (*size > 0) {
        char current = random_picture[*size - 1];  // 取最后一个元素
        (*size)--;  // 减少数组大小
        
        if (current >= 'a' && current <= 'e') {
            // 分配到 X 坐标
            for (int j = 0; j < 3; j++) {
                if (num_map[j].num_type == 'X') {
					while(1)
					{
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
							break;
						}
					}                    
					break;  // 放置后退出循环
				}
            }
        } else if (current >= 'f' && current <= 'k') {
            // 分配到 Y 坐标
            for (int j = 0; j < 3; j++) {
                if (num_map[j].num_type == 'Y') {
					while(1)
					{
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
							break;
						}
					}                    
                    break;  // 放置后退出循环
                }
            }
        } else if (current >= 'l' && current <= 'o') {
            // 分配到 Z 坐标
            for (int j = 0; j < 3; j++) {
                if (num_map[j].num_type == 'Z') {
					while(1)
					{
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
							break;
						}
					}                    
                    break;  // 放置后退出循环
                }
            }
        }
    }
	distribution_random_complete = true;
}
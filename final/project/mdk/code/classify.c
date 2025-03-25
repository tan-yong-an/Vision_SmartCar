#include "zf_common_headfile.h"

bool distribution_random_complete = false;  //直线放图完成标志位
bool distribution_ring_complete = false;  //圆环放图完成标志位

//记录图像信息
uint8 all_picture_count = 0;          //看到图片的数量
int8_t random_picture_count = 0;    //随机图片数量
char Random_picture[30];
int8_t ring_picture_count = 0;      //圆环图片数量
char Ring_picture[30];

void clear_picture()      //清空现在的图片类型
{
    for (int i = 0; i <= 64; i++) 
	{
		picture_type[i] = '\0';
    }
}

void clear_ring_picture()      //清空圆环数组
{
    for (int i = 0; i < 20; i++) 
	{
		Ring_picture[i] = '\0';
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


//记录字母坐标以及转角
uint8 zimu_count = 0;
int8 temp_letter_x[5];
int8 temp_letter_y[5];
map map_letter[5];
void record_letter(int i,int x, int y, int z, char target) 
{
	map_letter[i].letter_x = x;
	map_letter[i].letter_y = y;
	map_letter[i].letter_z = z;
	map_letter[i].letter_type = letter_type[i];
}
// 清空所有字母信息的函数
void clear_letters() 
{
    for (int i = 0; i < 5; i++) 
	{
        map_letter[i].letter_x = 0;
        map_letter[i].letter_y = 0;
        map_letter[i].letter_type = '\0';
    }
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
						run_point(num_map[j].num_x-5,num_map[j].num_y-5);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							system_delay_ms(1000);
							put_picture();
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
						run_point(num_map[j].num_x-5,num_map[j].num_y-5);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							system_delay_ms(1000);
							put_picture();
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
						run_point(num_map[j].num_x-5,num_map[j].num_y-5);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							system_delay_ms(1000);
							put_picture();
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


//圆环放图片
void distribute_ring_pictures(char ring_picture[], int *size) {
    while (*size > 0) {
        char current = ring_picture[*size - 1];  // 取最后一个元素
        (*size)--;  // 减少数组大小 
		int matched = 0;  // 记录是否找到匹配的坐标		
		put_times = 0;
        if (current == 'a') {
            // 分配到 A 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'A') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}                    
					break;  // 放置后退出循环
				}
            }
        } else if (current == 'b') {
            // 分配到 B 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'B') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}                    
                    break;  // 放置后退出循环
                }
            }
        } else if (current == 'c') {
            // 分配到 C 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'C') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}                    
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'd') {
            // 分配到 D 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'D') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}                    
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'e') {
            // 分配到 E 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'E') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'f') {
            // 分配到 F 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'F') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'g') {
            // 分配到 G 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'G') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'h') {
            // 分配到 H 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'H') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'i') {
            // 分配到 I 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'I') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'j') {
            // 分配到 J 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'J') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'k') {
            // 分配到 K 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'K') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'l') {
            // 分配到 L 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'L') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'm') {
            // 分配到 M 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'M') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'n') {
            // 分配到 N 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'N') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }else if (current == 'o') {
            // 分配到 O 坐标
            for (int j = 0; j < 5; j++) {
                if (map_letter[j].letter_type == 'O') {
					while(1)
					{
						run_point(map_letter[j].letter_x,map_letter[j].letter_y-8);
						if(arrived_flag == 1 && put_times == 0)
						{
							arrived_flag = 0;
							matched = 1;							
							system_delay_ms(1000);
							put_picture();
							break;
						}
					}
                    break;  // 放置后退出循环
                }
            }
        }
		
        if (matched == 0) {						//如果图片和字母没有匹配的，就随便放在一个点
            int random_index = rand() % 5;
            while(1) {
                run_point(map_letter[random_index].letter_x, map_letter[random_index].letter_y-8);
                if(arrived_flag == 1 && put_times == 0) {
                    arrived_flag = 0;
                    system_delay_ms(1000);
                    put_picture();
                    break;
                }    
			}
		}
	}
	distribution_ring_complete = true;
}
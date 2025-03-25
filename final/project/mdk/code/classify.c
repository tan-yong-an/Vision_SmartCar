#include "zf_common_headfile.h"

bool distribution_random_complete = false;  //ֱ�߷�ͼ��ɱ�־λ
bool distribution_ring_complete = false;  //Բ����ͼ��ɱ�־λ

//��¼ͼ����Ϣ
uint8 all_picture_count = 0;          //����ͼƬ������
int8_t random_picture_count = 0;    //���ͼƬ����
char Random_picture[30];
int8_t ring_picture_count = 0;      //Բ��ͼƬ����
char Ring_picture[30];

void clear_picture()      //������ڵ�ͼƬ����
{
    for (int i = 0; i <= 64; i++) 
	{
		picture_type[i] = '\0';
    }
}

void clear_ring_picture()      //���Բ������
{
    for (int i = 0; i < 20; i++) 
	{
		Ring_picture[i] = '\0';
    }
}

//��¼��������
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

// ���㲢��¼�����������Ϣ
void calculate_third_point() {
    // ����������������
    num_map[2].num_x = num_map[1].num_x;
    num_map[2].num_y = num_map[1].num_y + 45;

    // ����ʣ�µ��ַ�
    char remaining_char;
    if (num_map[0].num_type != 'X' && num_map[1].num_type != 'X') {
        remaining_char = 'X';
    } else if (num_map[0].num_type != 'Y' && num_map[1].num_type != 'Y') {
        remaining_char = 'Y';
    } else {
        remaining_char = 'Z';
    }
    // ��¼�������������
    num_map[2].num_type = remaining_char;
}


//��¼��ĸ�����Լ�ת��
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
// ���������ĸ��Ϣ�ĺ���
void clear_letters() 
{
    for (int i = 0; i < 5; i++) 
	{
        map_letter[i].letter_x = 0;
        map_letter[i].letter_y = 0;
        map_letter[i].letter_type = '\0';
    }
}


//ֱ�߷�ͼƬ
void distribute_random_pictures(char random_picture[], int *size) {
    while (*size > 0) {
        char current = random_picture[*size - 1];  // ȡ���һ��Ԫ��
        (*size)--;  // ���������С
        
        if (current >= 'a' && current <= 'e') {
            // ���䵽 X ����
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
					break;  // ���ú��˳�ѭ��
				}
            }
        } else if (current >= 'f' && current <= 'k') {
            // ���䵽 Y ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        } else if (current >= 'l' && current <= 'o') {
            // ���䵽 Z ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }
    }
	distribution_random_complete = true;
}


//Բ����ͼƬ
void distribute_ring_pictures(char ring_picture[], int *size) {
    while (*size > 0) {
        char current = ring_picture[*size - 1];  // ȡ���һ��Ԫ��
        (*size)--;  // ���������С 
		int matched = 0;  // ��¼�Ƿ��ҵ�ƥ�������		
		put_times = 0;
        if (current == 'a') {
            // ���䵽 A ����
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
					break;  // ���ú��˳�ѭ��
				}
            }
        } else if (current == 'b') {
            // ���䵽 B ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        } else if (current == 'c') {
            // ���䵽 C ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'd') {
            // ���䵽 D ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'e') {
            // ���䵽 E ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'f') {
            // ���䵽 F ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'g') {
            // ���䵽 G ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'h') {
            // ���䵽 H ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'i') {
            // ���䵽 I ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'j') {
            // ���䵽 J ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'k') {
            // ���䵽 K ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'l') {
            // ���䵽 L ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'm') {
            // ���䵽 M ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'n') {
            // ���䵽 N ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }else if (current == 'o') {
            // ���䵽 O ����
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
                    break;  // ���ú��˳�ѭ��
                }
            }
        }
		
        if (matched == 0) {						//���ͼƬ����ĸû��ƥ��ģ���������һ����
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
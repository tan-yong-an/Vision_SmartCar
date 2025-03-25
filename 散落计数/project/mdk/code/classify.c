#include "zf_common_headfile.h"

bool distribution_random_complete = false;  //ֱ�߷�ͼ��ɱ�־λ

//��¼ͼ����Ϣ
uint8 all_picture_count = 0;          //����ͼƬ������
int8_t random_picture_count = 0;    //���ͼƬ����
char Random_picture[30];

void clear_picture()      //������ڵ�ͼƬ����
{
    for (int i = 0; i <= 64; i++) 
	{
		picture_type[i] = '\0';
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
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
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
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
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
						run_point(num_map[j].num_x-12,num_map[j].num_y-12);
						if(arrived_flag == 1)
						{
							arrived_flag = 0;
							put_picture();
							system_delay_ms(1000);
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
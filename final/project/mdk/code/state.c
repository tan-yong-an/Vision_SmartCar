#include "zf_common_headfile.h"

int MCX_flag = 0;		
int MINI_flag = 0;
int	game_state = 0;
int take_flag = 0;
int taked = 0;
int MCX_switch = 0;   //�ر�MCX���ȴ���һ�ο���			 
int arrived_flag = 0;    //go_to ��λ��־λ

void car_status_update()
{  
	if((MCX_flag ==1 && game_state == 0)||(MCX_flag ==1 && game_state == 5)||(MCX_flag ==1 && game_state == 6))  //Ѳ�ߺͽ�ͼ��ʱ��Ҫ��MCX
		state = 1;
}

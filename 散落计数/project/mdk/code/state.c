#include "zf_common_headfile.h"

int MCX_flag = 0;		
int	game_state = 0;
int MCX_switch = 0;   //关闭MCX，等待下一次开启			 
int arrived_flag = 0;    //go_to 到位标志位
int32 cnt=0;
int open_flag = 0;

void car_status_update()
{  
	if(open_flag == 1)
	{
		if((MCX_flag ==1 && game_state == 0)||(MCX_flag ==1 && game_state == 5))  //巡线和建图的时候要用MCX
			state = 1;
	}
}

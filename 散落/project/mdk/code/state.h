#ifndef _state_h_
#define _state_h_

extern int MCX_flag;		
extern int game_state;
extern int MCX_switch;   //到位关闭MCX，等待下一次置一			 
extern int arrived_flag;
void car_status_update();

#endif
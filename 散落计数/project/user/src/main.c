#include "zf_common_headfile.h"

#define BEEP_PIN                (B11) 
bool tft_clear_flag = true;


void main(void)
{
	clock_init(SYSTEM_CLOCK_600M);  // 不可删除
	debug_init();                   // 调试端口初始化

	// 初始化
	
	gpio_init(BEEP_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);

    tft180_init();
	mt9v03x_init();
	
	Motor_Init();
	encoder_Init();
	imu660ra_init();       //陀螺仪零漂矫正
	imu_init();			
	servo_Init();
		
	pit_ms_init(PIT_CH0, 10);
	pit_ms_init(PIT_CH1, 10);
	
	fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区
	uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // 初始化串口
	uart_rx_interrupt(UART_INDEX, ZF_ENABLE);                                   // 开启 UART_INDEX 的接收中断
	
	fifo_init(&uart1_data_fifo, FIFO_DATA_8BIT, uart1_get_data, 64);              // 初始化 fifo 挂载缓冲区
	uart_init(UART1_INDEX, UART1_BAUDRATE, UART1_TX_PIN, UART1_RX_PIN);             // 初始化串口
	uart_rx_interrupt(UART1_INDEX, ZF_ENABLE);                                   // 开启 UART_INDEX 的接收中断
	
	interrupt_set_priority((PIT_IRQn), 0);  
    interrupt_set_priority(UART_PRIORITY, 1);                                   // 设置对应 UART_INDEX 的中断优先级为 1
    interrupt_set_priority(UART1_PRIORITY, 1);                                   // 设置对应 UART_INDEX 的中断优先级为 1	
	
	interrupt_global_enable(0);
	
	while(1)
	{
	//	左上角显示当前状态
		tft180_show_int(16*0, 16*0,game_state,1);
		tft180_show_char(16*0, 16*1,picture);	
	//车身姿态	
		tft180_show_int(16*4, 16*3, Car.car_x, 3);
		tft180_show_int(16*4, 16*4, Car.car_y, 3);
		tft180_show_int(16*4, 16*5,Car.car_yaw, 3);

		tft180_show_int(16*6, 16*3, Car.ex_car_x, 3);
		tft180_show_int(16*6, 16*4, Car.ex_car_y, 3);
		tft180_show_int(16*6, 16*5, IMU.ex_yaw, 3);
		
	//摄像头回传坐标数据	
		tft180_show_int(16*4, 16*7,a,2);	
		tft180_show_int(16*4, 16*8,MINI_x,2);	
		tft180_show_int(16*4, 16*9,MINI_y,2);	
		
		tft180_show_int(16*6, 16*8,adjust_x,2);	
		tft180_show_int(16*6, 16*9,adjust_y,2);	
		
	//  提取到的数字坐标	
		tft180_show_int(16*3, 16*0,num_map[0].num_x,3);   
		tft180_show_int(16*5, 16*0,num_map[0].num_y,3);
		tft180_show_char(16*7, 16*0,num_map[0].num_type);
	
		tft180_show_int(16*3, 16*1,num_map[1].num_x,3);
		tft180_show_int(16*5, 16*1,num_map[1].num_y,3);
		tft180_show_char(16*7, 16*1,num_map[1].num_type);
		
		tft180_show_int(16*3, 16*2,num_map[2].num_x,3);
		tft180_show_int(16*5, 16*2,num_map[2].num_y,3);
		tft180_show_char(16*7, 16*2,num_map[2].num_type);

		//提取到的图像分类信息
		tft180_show_int(16*0, 16*3,random_picture_count,1);	
		tft180_show_char(16*0, 16*4,Random_picture[0]);
		tft180_show_char(16*0, 16*5,Random_picture[1]);
		tft180_show_char(16*0, 16*6,Random_picture[2]);
		tft180_show_char(16*0, 16*7,Random_picture[3]);
		tft180_show_char(16*0, 16*8,Random_picture[4]);	
		tft180_show_char(16*0, 16*9,Random_picture[5]);
		
		tft180_show_char(16*2, 16*4,picture_type[0]);
		tft180_show_char(16*2, 16*5,picture_type[1]);
		tft180_show_char(16*2, 16*6,picture_type[2]);
		tft180_show_char(16*2, 16*7,picture_type[3]);
		tft180_show_char(16*2, 16*8,picture_type[4]);	
		tft180_show_char(16*2, 16*9,picture_type[5]);

		if(picture_type[1] != '\0')
		{
			picture_type[1] = '\0';
		}
		switch(state)
		{
			case 0:   //循迹
				tft_clear_flag = true;				
				game_state = 0;	
				MCX_flag = 0;
				MCX_switch = 1;  
				spin_ok = 1;
			
				if(mt9v03x_finish_flag)
				{
					ImageProcessResult result = image_process();				
					spin = result.spin;
					translation = result.translation;				
					mt9v03x_finish_flag = 0;
				}	
				
				int straight=90;			
				int PID1_target = McNamm1(straight,spin,translation);
				int PID2_target = McNamm2(straight,spin,translation);
				int PID3_target = McNamm3(straight,spin,translation);
				int PID4_target = McNamm4(straight,spin,translation);

				float output1 = PID_Set(PID1_target,PID1_actual); 
				float output2 = PID_Set(PID2_target,PID2_actual); 
				float output3 = PID_Set(PID3_target,PID3_actual); 
				float output4 = PID_Set(PID4_target,PID4_actual);
				
				motor_set(output1,output2,output3,output4);
//				motor_set(150,130,130,130);           //调试代码
				
				Car.car_x = 0;  //位置信息重置
				Car.car_y = 0;			
				yaw_clear();    //角度信息重置
				
				cnt++;
				
				if(cnt>=200)
					open_flag = 1;
			break;
				
				
		  case 1: //MCX靠近目标	
			  		  
			if(tft_clear_flag)
			{
				tft180_clear();
				tft_clear_flag = false;
			}			  
			  game_state = 1;
		  
			  arrived_flag = 0;
					
			  Car.ex_car_x =Car.car_x+adjust_x;   //MCX提取到的矩形中点坐标
			  Car.ex_car_y =Car.car_y+adjust_y;
			  		  
			  if(Random_picture[3]=='\0')    //不够4张散图    
			  {
				  if(spin_ok == 0)
				  {
					  if (fabs_(adjust_x)<3 && fabs_(adjust_y)<3)
					  {
						  Car.ex_car_x_p=Car.ex_car_x;
						  Car.ex_car_y_p=Car.ex_car_y;
						  
						  motor1.duty=0;
						  motor2.duty=0;
						  motor3.duty=0;
						  motor4.duty=0;
						  wheel_control(0,0,0);
						  
						  gpio_set_level(BEEP_PIN, 1);                                            // BEEP 响
						  system_delay_ms(50);
						  gpio_set_level(BEEP_PIN, 0);   
						  
						  state = 2;    //找到图片之后一定要微调并识别是什么								  
					  }
					  else
					  {  
					  plan_vel();
					  wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
					  }						
				  }			  			  
				  else
				  {
					if(adjust_y<18)    // 靠近
				   {
					  if(adjust_x<0 && adjust_x>-40)   // 左边
					  {
							spin_angle(-90);
							spin_ok = 0;
						  
					  }
					  else if(adjust_x>0 && adjust_x<40)        // 右边
					  {
							spin_angle(90);
							spin_ok = 0;						
					  }
				   }	  
				  else
					  state = 0;				  
				  }			  
			  }
			  else
			  {
				  if ((fabs_(adjust_x)<4)&&(fabs_(adjust_y)<4))
				  {
					  Car.ex_car_x_p=Car.ex_car_x;
					  Car.ex_car_y_p=Car.ex_car_y;
					  motor1.duty=0;
					  motor2.duty=0;
					  motor3.duty=0;
					  motor4.duty=0;
					  wheel_control(0,0,0);
					  
					  gpio_set_level(BEEP_PIN, 1);                                            // BEEP 响
					  system_delay_ms(50);
					  gpio_set_level(BEEP_PIN, 0);   
					  
					  state = 2;    //找到图片之后一定要微调并识别是什么
								  
				  }
				  else
				  {  
				  plan_vel();
				  wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
				  }						
			  }			  		  
			break;
				
			case 2:    //微调+识别	
				
				open_flag = 0;
			
				game_state = 2;
			
				MCX_flag = 0;		
				MCX_switch = 0;   //关闭MCX
			
				spin_ok = 1;
			
				approach_img();
				wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
				
				if(picture_type[0]!='\0')  //看到图片就抓
				{		
					motor1.duty=0;
					motor2.duty=0;
					motor3.duty=0;
					motor4.duty=0;			
					wheel_control(0,0,0);	
					if(picture_type[0]>='a'&& picture_type[0]<='e')
					{
						gpio_set_level(BEEP_PIN, 1);        //1大类                                  
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
					}
					else if(picture_type[0]>='f'&& picture_type[0]<='k')
					{
						gpio_set_level(BEEP_PIN, 1);        //2大类                                  
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 1);                                         
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
					}
					else if(picture_type[0]>='l'&& picture_type[0]<='o')
					{
						gpio_set_level(BEEP_PIN, 1);        //3大类                                  
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 1);                                         
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 1);                                         
						system_delay_ms(50);
						gpio_set_level(BEEP_PIN, 0);
					}
					
					Random_picture[random_picture_count] = picture_type[0];
					picture_type[0] = '\0';
					random_picture_count ++;
					
					state = 7;     //是图片就要抓
				}						
				else if(num_type[number]!='\0')  //看到数字
				{
					motor1.duty=0;   //停车
					motor2.duty=0;
					motor3.duty=0;
					motor4.duty=0;
					wheel_control(0,0,0);
					
					temp_num_x[number] =  Car.car_x;
					temp_num_y[number] =  Car.car_y;
					record_num(number,temp_num_x[number],temp_num_y[number],num_type[number]);
					
					number ++;
					
					gpio_set_level(BEEP_PIN, 1);      //是数字叫1
					system_delay_ms(100);
					gpio_set_level(BEEP_PIN, 0);
				
					state = 5;	
				}
				
			break;
				
			case 4:  //x方向回到原点
				game_state = 4;
			
				open_flag = 0;
			
				MCX_switch = 0;   //关闭MCX
				MCX_flag = 0;		
			
				if(spin_ok)
				{
					spin_angle(0);
					spin_ok = 0;
					state = 0;
					cnt = 0;

				}				
			break;
			  
			case 5:  //直线建图	
				
			  open_flag = 1;
			
			  tft180_clear();
			
			  MCX_flag = 0;		
			  MCX_switch = 0;    //往前挪一点，一定要关闭MCX	
			
			  game_state = 5;
							  
			  if(number<2)     //看完前两个框要往前走一点   
			  {
				  go_to(num_map[number-1].num_x,num_map[number-1].num_y+25);	//往前走25；go_to到位arrived_flag = 1
				  if(arrived_flag == 1)  //往前走到位
					  MCX_switch = 1;    //打开MCX
			  }
			  if(num_map[1].num_type != '\0')  //识别到两个了
			  {
				  calculate_third_point();     //第三个直接得
			  }
			  if(num_map[2].num_type != '\0')       //三个数字坐标已经建图完毕，跳直线放置图片的状态
			  {
				  MCX_switch = 0;//关闭MCX
				  MCX_flag = 0;
				  state = 8;			  
			  }		  
			break;
			 
			case 7://抓一次图片
				
				open_flag = 0;
			
				game_state = 7;	
				MCX_switch = 0;//关闭MCX
				MCX_flag = 0;
					
				motor1.duty=0;
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;
				wheel_control(0,0,0);
			
				take_picture();    //是图片一定要抓的
						
				system_delay_ms(500);
			
				state = 4;      //回赛道
			
			break;
						
			case 8://直线放图片
				
				game_state = 8;
			
				open_flag = 0;
			
				MCX_flag = 0;			
				MCX_switch = 0;   //关闭MCX
					
				int random_picture_size = sizeof(Random_picture) / sizeof(Random_picture[0]); 	
				distribute_random_pictures(Random_picture, &random_picture_size);
				
				if(distribution_random_complete)    //随机图片放置完成
					state = 10;
				
			break;
						
			case 10://完赛冲线			
				game_state = 10;
			
				open_flag = 0;
			
				arrived_flag = 0;		
				MCX_switch = 0;   //关闭MCX
				MCX_flag = 0;			
			
				go_to(num_map[2].num_x-50,num_map[2].num_y+100);
				
				if(arrived_flag == 1)
				{
					motor1.duty=0;
					motor2.duty=0;
					motor3.duty=0;
					motor4.duty=0;
					wheel_control(0,0,0);
				}
			break;
				
//			case 11:
//				put_picture();
//				system_delay_ms(1000);
//				take_picture();
//				system_delay_ms(2000);
//			break;
		}																		  		 			
	}
}

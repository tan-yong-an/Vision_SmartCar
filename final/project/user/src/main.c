#include "zf_common_headfile.h"
#include <ctype.h> // ����toupper������ͷ�ļ�

#define BEEP_PIN                (B11) 

int circle = 1;    //ͨ����Բ������

int spin_ok = 1;

bool hasValue = false;

//char Random_picture[] = {'a', 'f', 'l'};

void main(void)
{
	clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
	debug_init();                   // ���Զ˿ڳ�ʼ��

	// ��ʼ��
	
	gpio_init(BEEP_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);

    tft180_init();
	mt9v03x_init();
	
	Motor_Init();
	encoder_Init();
	imu660ra_init();       //��������Ư����
	imu_init();			
	servo_Init();
		
	pit_ms_init(PIT_CH0, 10);
	pit_ms_init(PIT_CH1, 10);
	
	fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
	uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // ��ʼ������
	uart_rx_interrupt(UART_INDEX, ZF_ENABLE);                                   // ���� UART_INDEX �Ľ����ж�
	
	fifo_init(&uart1_data_fifo, FIFO_DATA_8BIT, uart1_get_data, 64);              // ��ʼ�� fifo ���ػ�����
	uart_init(UART1_INDEX, UART1_BAUDRATE, UART1_TX_PIN, UART1_RX_PIN);             // ��ʼ������
	uart_rx_interrupt(UART1_INDEX, ZF_ENABLE);                                   // ���� UART_INDEX �Ľ����ж�
	
	interrupt_set_priority((PIT_IRQn), 0);  
    interrupt_set_priority(UART_PRIORITY, 1);                                   // ���ö�Ӧ UART_INDEX ���ж����ȼ�Ϊ 1
    interrupt_set_priority(UART1_PRIORITY, 1);                                   // ���ö�Ӧ UART_INDEX ���ж����ȼ�Ϊ 1	
	
	interrupt_global_enable(0);
	
while(1)
{
//	���Ͻ�ʵʱ��ʾ��ǰ״̬
	tft180_show_int(16*0, 16*1,game_state,1);
	tft180_show_char(16*0, 16*2,picture);	
//	tft180_show_int(16*0, 16*2,random_picture_count,1);	
	tft180_show_char(16*0, 16*3,Q_flag);
	
//	tft180_show_int(16*2, 16*2, Car.car_x, 3);
//	tft180_show_int(16*2, 16*3, Car.car_y, 3);
//	tft180_show_int(16*2, 16*4,Car.car_yaw, 3);

//	tft180_show_int(16*2, 16*6, Car.ex_car_x, 3);
//	tft180_show_int(16*2, 16*7, Car.ex_car_y, 3);
//	tft180_show_int(16*2, 16*8, IMU.ex_yaw, 3);
	
//  ��ȡ������������	
//	tft180_show_int(16*2, 16*3,num_map[0].num_x,3);   
//	tft180_show_int(16*5, 16*3,num_map[0].num_y,3);
//	tft180_show_char(16*7, 16*3,num_map[0].num_type);
//	
//	tft180_show_int(16*2, 16*4,num_map[1].num_x,3);
//	tft180_show_int(16*5, 16*4,num_map[1].num_y,3);
//	tft180_show_char(16*7, 16*4,num_map[1].num_type);
//	
//	tft180_show_int(16*2, 16*5,num_map[2].num_x,3);
//	tft180_show_int(16*5, 16*5,num_map[2].num_y,3);
//	tft180_show_char(16*7, 16*5,num_map[2].num_type);

//  ��ȡ������ĸ����	
//	tft180_show_int(16*2, 16*3,map_letter[0].letter_x,3);  
//	tft180_show_int(16*5, 16*3,map_letter[0].letter_y,3);
//	tft180_show_char(16*7, 16*3,map_letter[0].letter_type);
//	
//	tft180_show_int(16*2, 16*4,map_letter[1].letter_x,3);
//	tft180_show_int(16*5, 16*4,map_letter[1].letter_y,3);
//	tft180_show_char(16*7, 16*4,map_letter[1].letter_type);
//	
//	tft180_show_int(16*2, 16*5,map_letter[2].letter_x,3);
//	tft180_show_int(16*5, 16*5,map_letter[2].letter_y,3);
//	tft180_show_char(16*7, 16*5,map_letter[2].letter_type);
//	
//	tft180_show_int(16*2, 16*6,map_letter[3].letter_x,3);
//	tft180_show_int(16*5, 16*6,map_letter[3].letter_y,3);
//	tft180_show_char(16*7, 16*6,map_letter[3].letter_type);
//	
//	tft180_show_int(16*2, 16*7,map_letter[4].letter_x,3);
//	tft180_show_int(16*5, 16*7,map_letter[4].letter_y,3);
//	tft180_show_char(16*7, 16*7,map_letter[4].letter_type);

	//��ȡ����ͼ�������Ϣ
	tft180_show_char(16*1, 16*2,Random_picture[0]);
	tft180_show_char(16*1, 16*3,Random_picture[1]);
	tft180_show_char(16*1, 16*5,Random_picture[2]);
	tft180_show_char(16*1, 16*6,Random_picture[3]);
	tft180_show_char(16*1, 16*7,Random_picture[4]);	
	tft180_show_char(16*1, 16*8,Random_picture[5]);

//	tft180_show_char(16*2, 16*2,Ring_picture[0]);
//	tft180_show_char(16*2, 16*3,Ring_picture[1]);
//	tft180_show_char(16*2, 16*5,Ring_picture[2]);
//	tft180_show_char(16*2, 16*6,Ring_picture[3]);
//	tft180_show_char(16*2, 16*7,Ring_picture[4]);	
//	tft180_show_char(16*2, 16*8,Ring_picture[5]);
//	
//	tft180_show_int(16*3, 16*2,MINI_x,3);	
//	tft180_show_int(16*3, 16*3,MINI_y,3);					
//	tft180_show_int(16*3, 16*4,a,3);
//	
	
	tft180_show_char(16*6, 16*3,picture_type[0]);
	tft180_show_char(16*6, 16*3,picture_type[1]);
	tft180_show_char(16*6, 16*5,picture_type[2]);
	tft180_show_char(16*6, 16*6,picture_type[3]);
	tft180_show_char(16*6, 16*7,picture_type[4]);	
	tft180_show_char(16*6, 16*8,picture_type[5]);

	switch(state)
	{
		case 0:   //ѭ��	
			tft180_clear();
			MCX_flag = 0;
			game_state = 0;		
			MCX_switch = 1;  
			spin_ok = 1;
		
			if(mt9v03x_finish_flag)
			{
				ImageProcessResult result = image_process();
				
				spin = result.spin;
				translation = result.translation;
				
				tft180_show_int(0, 16*8, spin, 3);
				tft180_show_int(0, 16*9,translation, 3);

				mt9v03x_finish_flag = 0;
			}				
		
			int straight=100;
			
			int PID1_target = McNamm1(straight,spin,translation);
			int PID2_target = McNamm2(straight,spin,translation);
			int PID3_target = McNamm3(straight,spin,translation);
			int PID4_target = McNamm4(straight,spin,translation);

			float output1 = PID_Set(PID1_target,PID1_actual); 
			float output2 = PID_Set(PID2_target,PID2_actual); 
			float output3 = PID_Set(PID3_target,PID3_actual); 
			float output4 = PID_Set(PID4_target,PID4_actual);
					
			motor_set(output1,output2,output3,output4);
//			motor_set(152,130,133,130);
			
			tft180_show_int(16*2, 16*6, PID1_actual, 3);
			tft180_show_int(16*2, 16*7, PID2_actual, 3);
			tft180_show_int(16*2, 16*8, PID3_actual, 3);
			tft180_show_int(16*2, 16*9, PID4_actual, 3);

			tft180_show_int(16*4, 16*6, PID1_target, 3);
			tft180_show_int(16*4, 16*7, PID2_target, 3);
			tft180_show_int(16*4, 16*8, PID3_target, 3);
			tft180_show_int(16*4, 16*9, PID4_target, 3);
					
			tft180_show_int(16*6, 16*6, output1, 3);
			tft180_show_int(16*6, 16*7, output2, 3);
			tft180_show_int(16*6, 16*8, output3, 3);
			tft180_show_int(16*6, 16*9, output4, 3);
						
			Car.car_x = 0;  //λ����Ϣ����
			Car.car_y = 0;
			
			yaw_clear();    //�Ƕ���Ϣ����	

			Q_flag = 'R';
			
			Q_RX = 0;
		break;
					
	  case 1: //MCX����Ŀ��	
		  tft180_clear();
		  game_state = 1;
	  
	      arrived_flag = 0;
	  	  
     	  tft180_show_int(16*3, 16*3, Car.car_x, 3);
		  tft180_show_int(16*3, 16*4, Car.car_y, 3);
		  tft180_show_int(16*3, 16*5, Car.car_yaw, 3);
	  	  
		  tft180_show_int(16*4, 16*6, Car.ex_car_x, 3);
		  tft180_show_int(16*4, 16*7, Car.ex_car_y, 3);
		
		  Car.ex_car_x =Car.car_x+adjust_x;   //MCX��ȡ���ľ����е�����
		  Car.ex_car_y =Car.car_y+adjust_y;
	  	  
		  tft180_show_int(16*5, 16*6, adjust_x, 3);
		  tft180_show_int(16*5, 16*7, adjust_y, 3);
	  
		  if(Random_picture[2]=='\0')    //����3��ɢͼ
		  {
			  if(spin_ok == 0)
			  {
				  if ((fabs_(Car.ex_car_y-Car.car_y)<4)&&(fabs_(Car.ex_car_x-Car.car_x)<4))
				  {
					  Car.ex_car_x_p=Car.ex_car_x;
					  Car.ex_car_y_p=Car.ex_car_y;
					  motor1.duty=0;
					  motor2.duty=0;
					  motor3.duty=0;
					  motor4.duty=0;
					  wheel_control(0,0,0);
					  
					  gpio_set_level(BEEP_PIN, 1);                                            // BEEP ��
					  system_delay_ms(100);
					  gpio_set_level(BEEP_PIN, 0);   
					  system_delay_ms(100);
					  
					  state = 2;    //�ҵ�ͼƬ֮��һ��Ҫ΢����ʶ����ʲô
								  
				  }
				  else
				  {  
				  plan_vel();
				  wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
				  }						
			  }			  			  
			  if(adjust_y<10)    // ����
			  {
				  if(adjust_x<0)   // ���
				  {
					  if(spin_ok)
					  {
						spin_angle(-90);
						spin_ok = 0;
					  }
				  }
				  else        // �ұ�
				  {
					  if(spin_ok)
					  {
						spin_angle(90);
						spin_ok = 0;
					  }
				  }
			  }	  
			  else
				  state = 0;			  
		  }
		  else
		  {
			  if ((fabs_(Car.ex_car_y-Car.car_y)<4)&&(fabs_(Car.ex_car_x-Car.car_x)<3))
			  {
				  Car.ex_car_x_p=Car.ex_car_x;
				  Car.ex_car_y_p=Car.ex_car_y;
				  motor1.duty=0;
				  motor2.duty=0;
				  motor3.duty=0;
				  motor4.duty=0;
				  wheel_control(0,0,0);
				  
				  gpio_set_level(BEEP_PIN, 1);                                            // BEEP ��
				  system_delay_ms(100);
				  gpio_set_level(BEEP_PIN, 0);   
				  system_delay_ms(100);
				  
				  state = 2;    //�ҵ�ͼƬ֮��һ��Ҫ΢����ʶ����ʲô
							  
			  }
			  else
			  {  
			  plan_vel();
			  wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
			  }						
		  }			  		  
		break;
			
		case 2:    //΢��+ʶ��
					
			tft180_clear();
		    game_state = 2;
		
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;		
			spin_ok = 1;
		
			approach_img();
			wheel_control(Car.ex_vel_x,Car.ex_vel_y,0);
							
			if(fabs_(MINI_x)<=2 && fabs_(MINI_y)<=2)
			{
				motor1.duty=0;
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;			
				wheel_control(0,0,0);
				Q_RX = 1;							
			}
			
			if(picture_type[all_picture_count]!='\0'&& fabs_(MINI_x)<=3 && fabs_(MINI_y)<=1)  //����ͼƬ���Ҷ�׼
			{
				motor1.duty=0;
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;			
				wheel_control(0,0,0);	
				
				gpio_set_level(BEEP_PIN, 1);        //��ͼƬ��1                                   
				system_delay_ms(50);
				gpio_set_level(BEEP_PIN, 0);        //��ͼƬ��1                                  

				all_picture_count++;
				
				state = 7;     //��ͼƬ��Ҫץ
			}			
			else if(Q_flag == 'Q' && picture_type[2]=='\0')      //������Q,û�еڶ���ͼƬ,�ж�Ϊ���
			{  
				Random_picture[random_picture_count] = picture_type[0];  //�����Ŵ������ͼƬ����
				random_picture_count++;   //���ͼƬ����һ				
				clear_picture();   //������ڴ��ͼƬ				
				all_picture_count = 0;    //������ڵ�ͼƬ����	
				Q_flag = 'R';				
				state = 4;                //������
			}	
			else  if(Q_flag == 'Q' && picture_type[2]!='\0')      //������Q,�����еڶ���ͼƬ,�ж�ΪԲ��
			{
				for(int i=0;i<=all_picture_count;i++)
				{
					Ring_picture[i] = picture_type[i];     //���������е�ͼ����Բ��������
				}
				clear_picture();   //������ڴ��ͼƬ				
				all_picture_count = 0;    //������ڵ�ͼƬ����				
				state = 6;                //���꿪ʼԲ����ͼ
			}			
			else if(letter_type[zimu_count]!='\0')//������ĸ����̫׼
			{
				motor1.duty=0;   //ͣ��
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;			
				wheel_control(0,0,0);
				
				zimu_count ++;
				
				gpio_set_level(BEEP_PIN, 1);     //����ĸ������                             
				system_delay_ms(50);
				gpio_set_level(BEEP_PIN, 0);
				system_delay_ms(50);	
				gpio_set_level(BEEP_PIN, 1);                            
				system_delay_ms(50);
				gpio_set_level(BEEP_PIN, 0);
				system_delay_ms(50);	
				state = 6;
			}
			
			else if(num_type[number]!='\0')  //�������ֲ��ú�׼
			{
				motor1.duty=0;   //ͣ��
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;
				wheel_control(0,0,0);
				
				temp_num_x[number] =  Car.car_x;
				temp_num_y[number] =  Car.car_y;
				record_num(number,temp_num_x[number],temp_num_y[number],num_type[number]);
				
				number ++;
				
				gpio_set_level(BEEP_PIN, 1);      //�����ֽ�����
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
				system_delay_ms(50);	
				state = 5;
			}				
											
		break;
			  
		case 3: //Բ��������
			tft180_clear();
			game_state = 3;
						
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;		
			
		break;
		  
		case 4:  //x����ص�ԭ��
		    tft180_clear();
		    game_state = 4;
			Q_RX = 0;
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;
		
			tft180_show_int(16*1, 16*3, Car.car_x, 3);
			tft180_show_int(16*1, 16*4, Car.car_y, 3);
			tft180_show_int(16*1, 16*5,Car.car_yaw, 3);

			tft180_show_int(16*4, 16*6, Car.ex_car_x, 3);
			tft180_show_int(16*4, 16*7, Car.ex_car_y, 3);
		
			if(spin_ok)
			{
				spin_angle(0);
				spin_ok = 0;
				state = 0;
			}				
		break;
		  
		case 5:  //ֱ�߽�ͼ			
		  tft180_clear();
		
		  MCX_switch = 0;    //��ǰŲһ�㣬һ��Ҫ�ر�MCX	
		  MCX_flag = 0;
		
		  game_state = 5;
						  
		  if(number<2)     //����ǰ������Ҫ��ǰ��һ��   
		  {
		      go_to(num_map[number-1].num_x,num_map[number-1].num_y+25);	//��ǰ��25��go_to��λarrived_flag = 1
			  if(arrived_flag == 1)  //��ǰ�ߵ�λ
				  MCX_switch = 1;    //��MCX
		  }
		  if(num_map[1].num_type != '\0')  //ʶ��������
		  {
			  calculate_third_point();     //������ֱ�ӵ�
		  }
		  if(num_map[2].num_type != '\0')       //�������������Ѿ���ͼ��ϣ���ֱ�߷���ͼƬ��״̬
		  {
			  MCX_switch = 0;//�ر�MCX
			  MCX_flag = 0;
			  state = 8;			  
		  }
		  
		break;
		 
		case 6:  //Բ��ͼ			
//		  tft180_clear();
		  game_state = 6;	
		
		  right_cross_scan();  //��һ��Բ������ʮ��Բ��
				  		  
		  if(map_letter[4].letter_type != 0)   //ɨ�����
			  state = 9;  //Բ����ͼƬ

		break;

		case 7://ץһ��ͼƬ
			game_state = 7;	
		    MCX_switch = 0;//�ر�MCX
		    MCX_flag = 0;
				
			motor1.duty=0;
			motor2.duty=0;
			motor3.duty=0;
			motor4.duty=0;
			wheel_control(0,0,0);
		
			take_picture();    //��ͼƬһ��Ҫץ��
		
			take_times++;    //ץ�Ĵ�����һ
			
			system_delay_ms(500);				
			state = 2;      //��״̬2����ʶ��
		
		break;
					
		case 8://ֱ�߷�ͼƬ
		    tft180_clear();
			game_state = 8;
		
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;	
				
			int random_picture_size = sizeof(Random_picture) / sizeof(Random_picture[0]); 	
			distribute_random_pictures(Random_picture, &random_picture_size);
			
			if(distribution_random_complete)    //���ͼƬ�������
				state = 10;
		break;
			
		case 9://Բ����ͼƬ
			game_state = 9;	
			yaw_clear();       //���ýǶ�
		
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;
				
			int ring_picture_size = sizeof(Ring_picture) / sizeof(Ring_picture[0]); 	
			distribute_ring_pictures(Ring_picture, &ring_picture_size);	
			if(distribution_random_complete)    //���ͼƬ�������
			{
				clear_ring_picture();      //���Բ������
				state = 3;                 //����Բ��������
			}
		break;
		
		case 10://��������
			
		    tft180_clear();
			game_state = 10;
		
			arrived_flag = 0;		
			MCX_switch = 0;   //�ر�MCX
			MCX_flag = 0;	
		
		
			go_to(num_map[2].num_x-50,num_map[2].num_y+120);
			
			if(arrived_flag == 1)
			{
				motor1.duty=0;
				motor2.duty=0;
				motor3.duty=0;
				motor4.duty=0;
				wheel_control(0,0,0);
			}
		break;	
		}
	}	
}


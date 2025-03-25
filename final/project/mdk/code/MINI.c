#include "zf_common_headfile.h"
#include "MINI.h"
#define BEEP_PIN                (B11) 

uint8 uart1_get_data[64];                            // 串口接收数据缓冲区
uint8 fifo1_get_data[64];                            // fifo 输出读出缓冲区

fifo_struct uart1_data_fifo;

char picture_type[64] = {0};      //图片类型
char letter_type[64] = {0};		//字母类型
char num_type[64] = {0};		//数字类型
char Q_flag;         //识别不到的标志
int Q_RX = 1;
uint8 picture_count = 0;
uint8 letter_count = 0;
uint8 num_count = 0;
int a = 0;
volatile od_result_t1  od_result1;
int8 MINI_x = 0;
int8 MINI_y = 0;
char picture;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     UART_INDEX 的接收中断处理函数 这个函数将在 UART_INDEX 对应的中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     uart_rx_interrupt_handler();
//-------------------------------------------------------------------------------------------------------------------
void uart1_rx_interrupt_handler (void)
{ 
    uint8 get_data = 0;                                                             // 接收数据变量
    uint32 temp_length = 0;
    uint8 od_num = 0;
    uart_query_byte(UART1_INDEX, &get_data);  
    {
        fifo_write_buffer(&uart1_data_fifo, &get_data, 1);   
    }
    
    if(0xAA == get_data)
    {
        // 读取第1个数据，用于判断帧头，使用完清除此数据
        temp_length = 6;
		fifo_read_buffer(&uart1_data_fifo, fifo1_get_data, &temp_length, FIFO_READ_AND_CLEAN);
		
        if(0xBB == fifo1_get_data[4])
        {
			od_result1.res_x1 = (fifo1_get_data[1] << 8) | fifo1_get_data[0];
			od_result1.res_y1 = (fifo1_get_data[3] << 8) | fifo1_get_data[2];			
        }
		if(0xBB == fifo1_get_data[5]){
			judge_type(fifo1_get_data[0]);
			picture = fifo1_get_data[0];
			a++;
			od_result1.res_x1 = (fifo1_get_data[2] << 8) | fifo1_get_data[1];
			od_result1.res_y1 = (fifo1_get_data[4] << 8) | fifo1_get_data[3];			
		}
			MINI_x = od_result1.res_x1;
			MINI_y = od_result1.res_y1;

        fifo_clear(&uart1_data_fifo);
		for(int i=0;i<6;i++)
			fifo1_get_data[i] = '\0';
    }
}

int compare_type(char receive_type, char type_list[],uint8 type_count)
{
	for(int i=0;i<type_count;i++){
		if (receive_type == type_list[i] || type_list[i]==0)
		{
			type_count--;
			return i;
		}
	}
	return type_count;
}

void judge_type(char receive_type)
{
	int judge_value;
	if(receive_type>= 'a'&& receive_type<= 'o'){
		judge_value = compare_type(receive_type, picture_type, picture_count);
		picture_type[judge_value] = receive_type;
		picture_count++;
	}
	else if(receive_type>='A' && receive_type<='O'){
		judge_value = compare_type(receive_type, letter_type, letter_count);
		letter_type[judge_value] = receive_type;
		letter_count++;		
	}
	else if(receive_type>='X' && receive_type<='Z'){
		judge_value = compare_type(receive_type, num_type, num_count);
		num_type[judge_value] = receive_type;
		num_count++;
	}	
	else 
	{
		if(Q_RX == 1)
			Q_flag = receive_type;
	}
}

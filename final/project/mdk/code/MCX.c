#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

#define BEEP_PIN                (B11)

uint8 uart_get_data[64];                            // 串口接收数据缓冲区
uint8 fifo_get_data[64];                            // fifo 输出读出缓冲区
                    
uint32 fifo_data_count = 0;                         // fifo 数据个数
fifo_struct uart_data_fifo;

int16_t x = 0;
int16_t y = 0;
int16_t x1 = 0;

int16_t adjust_x = 0;
int16_t adjust_y = 0;

uint8 s = 0;//面积
uint8 yx = 0;//两边之差
uint8 xy = 0;
int8 x12 = 0;
int8 y12 = 0;
int8 my_MCX = 0;  

volatile od_result_t od_result[10];

void uart_rx_interrupt_handler (void)
{ 
    uint8 get_data = 0;                                                              // 接收数据变量，用于存储接收到的字节数据
    uint32 temp_length = 0;                                                          // 临时变量，用于存储要读取的数据长度
    uint8 od_num = 0;                                                                // 目标序号变量，用于标识接收到的数据属于哪个目标
		
    uart_query_byte(UART_INDEX, &get_data);                                          // 从UART接口读取一个字节数据，并存储到get_data变量中

    // 将接收到的数据写入FIFO缓冲区
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);   
     
    // 判断接收到的数据是否为0xFF（帧头标识）
    if(0xFF == get_data)
    {
        // 读取第1个数据，用于判断帧头，读取完后清除该数据
        temp_length = 1;
        fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
        if(0xAA == fifo_get_data[0])                                                // 判断读取到的数据是否为0xAA（实际帧头）
        {
            // 读取下一个数据，用于获取目标序号，读取完后清除该数据
            temp_length = 1;
            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
            od_num = fifo_get_data[0];                                              // 将读取到的目标序号存储到od_num变量中

            // 读取接下来的8个数据，用于获取目标数据，然后将其存储到目标结构体数组中
            temp_length = 8;
            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
            memcpy((uint8*)(&od_result[od_num]), fifo_get_data, 8);                 // 将读取到的8个数据复制到目标结果结构体数组中
        }
        fifo_clear(&uart_data_fifo);                                                // 清空FIFO缓冲区		
    }
	
	      x = 0.5 * od_result[0].res_x1 + 0.5 * od_result[0].res_x2 - 160;
	 	  y = ( 240 - 0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2);
	      x1 = 24  + 64* y /180;
	  		
		  adjust_x = x1 *  ( x - 10) / 240;
          adjust_y = (( 240 - 0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) - 50)*0.2223333333333 - 4;
	
	
	s = (0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) * (0.5 * od_result[0].res_x1 - 0.5 * od_result[0].res_x2);//面积
	yx = (0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) - (0.5 * od_result[0].res_x1 - 0.5 * od_result[0].res_x2);//两边之差
	xy = (0.5 * od_result[0].res_x1 - 0.5 * od_result[0].res_x2) - (0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2);
	x12 = (0.5 * od_result[1].res_x1 + 0.5 * od_result[1].res_x2) - (0.5 * od_result[0].res_x1 + 0.5 * od_result[0].res_x2);
	y12 = (0.5 * od_result[1].res_y1 + 0.5 * od_result[1].res_y2) - (0.5 * od_result[0].res_y1 + 0.5 * od_result[0].res_y2);
	if(yx < 30 && xy < 30)   //s < 30 * 30 && 
	{
		if((x12)^2 + (y12)^2 < 400 && MCX_switch == 1)
			{
		        MCX_flag = 1;	
            }				
	}
}

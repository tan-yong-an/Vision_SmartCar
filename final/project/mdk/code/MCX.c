#include "zf_common_headfile.h"
#include "zf_common_typedef.h"

#define BEEP_PIN                (B11)

uint8 uart_get_data[64];                            // ���ڽ������ݻ�����
uint8 fifo_get_data[64];                            // fifo �������������
                    
uint32 fifo_data_count = 0;                         // fifo ���ݸ���
fifo_struct uart_data_fifo;

int16_t x = 0;
int16_t y = 0;
int16_t x1 = 0;

int16_t adjust_x = 0;
int16_t adjust_y = 0;

uint8 s = 0;//���
uint8 yx = 0;//����֮��
uint8 xy = 0;
int8 x12 = 0;
int8 y12 = 0;
int8 my_MCX = 0;  

volatile od_result_t od_result[10];

void uart_rx_interrupt_handler (void)
{ 
    uint8 get_data = 0;                                                              // �������ݱ��������ڴ洢���յ����ֽ�����
    uint32 temp_length = 0;                                                          // ��ʱ���������ڴ洢Ҫ��ȡ�����ݳ���
    uint8 od_num = 0;                                                                // Ŀ����ű��������ڱ�ʶ���յ������������ĸ�Ŀ��
		
    uart_query_byte(UART_INDEX, &get_data);                                          // ��UART�ӿڶ�ȡһ���ֽ����ݣ����洢��get_data������

    // �����յ�������д��FIFO������
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);   
     
    // �жϽ��յ��������Ƿ�Ϊ0xFF��֡ͷ��ʶ��
    if(0xFF == get_data)
    {
        // ��ȡ��1�����ݣ������ж�֡ͷ����ȡ������������
        temp_length = 1;
        fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
        if(0xAA == fifo_get_data[0])                                                // �ж϶�ȡ���������Ƿ�Ϊ0xAA��ʵ��֡ͷ��
        {
            // ��ȡ��һ�����ݣ����ڻ�ȡĿ����ţ���ȡ������������
            temp_length = 1;
            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
            od_num = fifo_get_data[0];                                              // ����ȡ����Ŀ����Ŵ洢��od_num������

            // ��ȡ��������8�����ݣ����ڻ�ȡĿ�����ݣ�Ȼ����洢��Ŀ��ṹ��������
            temp_length = 8;
            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &temp_length, FIFO_READ_AND_CLEAN);
            memcpy((uint8*)(&od_result[od_num]), fifo_get_data, 8);                 // ����ȡ����8�����ݸ��Ƶ�Ŀ�����ṹ��������
        }
        fifo_clear(&uart_data_fifo);                                                // ���FIFO������		
    }
	
	      x = 0.5 * od_result[0].res_x1 + 0.5 * od_result[0].res_x2 - 160;
	 	  y = ( 240 - 0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2);
	      x1 = 24  + 64* y /180;
	  		
		  adjust_x = x1 *  ( x - 10) / 240;
          adjust_y = (( 240 - 0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) - 50)*0.2223333333333 - 4;
	
	
	s = (0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) * (0.5 * od_result[0].res_x1 - 0.5 * od_result[0].res_x2);//���
	yx = (0.5 * od_result[0].res_y1 - 0.5 * od_result[0].res_y2) - (0.5 * od_result[0].res_x1 - 0.5 * od_result[0].res_x2);//����֮��
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

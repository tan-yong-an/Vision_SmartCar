#ifndef _MINI_h
#define _MINI_h

#define UART1_INDEX              (UART_1)                             
#define UART1_BAUDRATE           (115200)                                
#define UART1_TX_PIN             (UART1_TX_B12  )                        
#define UART1_RX_PIN             (UART1_RX_B13  )                        
#define UART1_PRIORITY           (LPUART1_IRQn)                                  

extern uint8 uart1_get_data[64];                            // 串口接收数据缓冲区
extern uint8 fifo1_get_data[64];                            // fifo 输出读出缓冲区
extern char picture_type[64];      //图片类型
extern char num_type[64];			//数字类型
extern fifo_struct uart1_data_fifo;

extern uint8 picture_count;
extern uint8 letter_count;

extern int a;
extern int8 MINI_x;
extern int8 MINI_y;
extern int a;
extern char picture;

typedef struct
{
	
     int16 res_x1;
     int16 res_y1;
    
}od_result_t1;
extern volatile od_result_t1  od_result1;

void uart1_rx_interrupt_handler (void);
void judge_type(char receive_type);
int compare_type(char receive_type, char type_list[], uint8 type_count);

#endif
#ifndef _MCX_h_
#define _MCX_h_

#define UART_INDEX              (UART_4   )                             
#define UART_BAUDRATE           (115200)                                
#define UART_TX_PIN             (UART4_TX_C16  )                        
#define UART_RX_PIN             (UART4_RX_C17  )                        
#define UART_PRIORITY           (LPUART4_IRQn)                                  

#include "zf_common_typedef.h"

typedef struct {
    int16 res_x1;
    int16 res_y1;
    int16 res_x2;
    int16 res_y2;
} od_result_t;
extern volatile od_result_t od_result[10];

extern fifo_struct uart_data_fifo;
extern uint8 uart_get_data[64];                            // 串口接收数据缓冲区

extern int16_t x;
extern int16_t y;
extern int16_t x1;
extern int8 my_MCX;  

extern int16_t adjust_x;
extern int16_t adjust_y;

void uart_rx_interrupt_handler (void);

#endif
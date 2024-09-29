#ifndef __UART_H__
#define __UART_H__

#include "config.h"



void Uart1_Init(void);
void Uart2_Init(void);
void Uart3_Init(void);
void Uart4_Init(void);





//#define UART1_ENABLE
//#define UART2_ENABLE
//#define UART3_ENABLE
//#define UART4_ENABLE

//#ifndef UART1_TX_BUFF_SIZE
//#define UART1_TX_BUFF_SIZE      50
//#endif
//#ifndef UART1_RX_BUFF_SIZE
//#define UART1_RX_BUFF_SIZE      50
//#endif
//#define UART1_RX_WAIT_TIME      5       // unit: ms

//#ifndef UART2_TX_BUFF_SIZE
//#define UART2_TX_BUFF_SIZE      250
//#endif
//#ifndef UART2_RX_BUFF_SIZE
//#define UART2_RX_BUFF_SIZE      250
//#endif
//#define UART2_RX_WAIT_TIME      5       // unit: ms

////#ifndef UART3_TX_BUFF_SIZE
////#define UART3_TX_BUFF_SIZE      50
////#endif
////#ifndef UART3_RX_BUFF_SIZE
////#define UART3_RX_BUFF_SIZE      50
////#endif
////#define UART3_RX_WAIT_TIME      5        // unit: ms

////#ifndef UART4_TX_BUFF_SIZE
////#define UART4_TX_BUFF_SIZE      50
////#endif
////#ifndef UART4_RX_BUFF_SIZE
////#define UART4_RX_BUFF_SIZE      50
////#endif
////#define UART4_RX_WAIT_TIME      5        // unit: ms

//#define S2RI  0x01              // S2CON.0
//#define S2TI  0x02              // S2CON.1
//#define S3RI  0x01              // S3CON.0
//#define S3TI  0x02              // S3CON.1
//#define S4RI  0x01              // S4CON.0
//#define S4TI  0x02              // S4CON.1

//#define UARTX_STRUCT_DEF(x)    			struct uart##x##_t
//#define UARTX_STRUCT(x)         		UARTX_STRUCT_DEF(x)
//#define UARTX_GET_RX_PACKET_DEF(x) 	uart##x##_get_rx_packet
//#define UARTX_GET_RX_PACKET(x)  		UARTX_GET_RX_PACKET_DEF(x)
//#define UARTX_SEND_DEF(x)       		uart##x##_send
//#define UARTX_SEND(x)           		UARTX_SEND_DEF(x)

//struct uart_rx_time_t
//{
//    uint8_t en;
//    uint8_t time;
//};

//struct uart1_t
//{
//    uint8_t     tx_buff[UART1_TX_BUFF_SIZE];
//    uint8_t     tx_len;
//    uint16_t    tx_index;
//    uint8_t     rx_buff[UART1_RX_BUFF_SIZE];
//    uint8_t     rx_len;
//    uint32_t    rx_tick;
//};

////struct uart2_t
////{
////    uint8_t     tx_buff[UART2_TX_BUFF_SIZE];
////    uint8_t     tx_len;
////    uint16_t    tx_index;
////    uint8_t     rx_buff[UART2_RX_BUFF_SIZE];
////    uint8_t     rx_len;
////    uint32_t    rx_tick;
////};

////struct uart3_t
////{
////    uint8_t     tx_buff[UART3_TX_BUFF_SIZE];
////    uint8_t     tx_len;
////    uint16_t    tx_index;
////    uint8_t     rx_buff[UART3_RX_BUFF_SIZE];
////    uint8_t     rx_len;
////    uint32_t    rx_tick;
////};

////struct uart4_t
////{
////	uint8_t     tx_buff[UART4_TX_BUFF_SIZE];
////	uint8_t     tx_len;
////	uint16_t    tx_index;
////	uint8_t     rx_buff[UART4_RX_BUFF_SIZE];
////	uint8_t     rx_len;
////	uint32_t    rx_tick;
////};

//void uart_init( void );

//void uart1_send( uint8_t *packet, uint16_t len );
//void uart2_send( uint8_t *packet, uint16_t len );
//void uart3_send( uint8_t *packet, uint16_t len );
//void uart4_send( uint8_t *packet, uint16_t len );

//struct uart1_t * uart1_get_rx_packet( void );
//struct uart2_t * uart2_get_rx_packet( void );
//struct uart3_t * uart3_get_rx_packet( void );
//struct uart4_t * uart4_get_rx_packet( void );

#endif



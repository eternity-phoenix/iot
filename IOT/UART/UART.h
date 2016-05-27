/*****************************************************
** 功能模块：  串口收发
** 硬件相关：  MCU使用STC89C52RC,硬件连接对应如下： 
**             TXD--->P31
**             RXD--->P30		
/*****************************************************/

#ifndef _UART_
#define _UART_

#define uchar 					unsigned char
#define uint					unsigned int


#define UART_RCV_BUF_LEN		256
#define UART_RCV_END_TIME		10					//串口接收结束时间判断

extern void UartInit(void);
extern void UartSendData(uchar senddata);
extern void UartSendString(uchar *string);
extern void UartSendBuf(uchar *bufp,uint len);
extern void UartClaer(void);

extern uchar UartRcvByte;
extern uchar xdata UartRcvBuf[UART_RCV_BUF_LEN];
extern uchar UartRcvEnd;
extern uchar UartRcvStart;
extern uchar UartRcvTimeCount;
#endif
/*****************************************************
** 功能模块：  串口收发
** 硬件相关：  MCU使用STC89C52RC,硬件连接对应如下： 
**             TXD--->P31
**             RXD--->P30		
/*****************************************************/

#include "UART.h"
#include <REG52.H>
#include <string.h>

uchar xdata UartRcvBuf[UART_RCV_BUF_LEN];			//串口接收BUF
uchar UartRcvByte = 0;								//串口接收标志位：1：接收到字节数据，0：未接收到数据
uchar UartRcvStart = 0;								//串口开始接收数据标志位：1：开始接收数据，0：未开始接收数据
uint UartRcvBufP = 0;								//串口接收buf指针
uchar UartRcvEnd = 0;								//串口接收结束标志位，1：串口接收数据完成，0：串口数据处理完成
uchar UartRcvTimeCount = 0;							//串口接收数据间隔计数

/*****************************************************
** 函数名称：UartInit
** 函数功能：串口初始化
** 参    数：无
** 函数返回：无
******************************************************/
void UartInit(void)									//F3 2400bps@12MHz//FD 9600bps@11.0592MHz
{
		PCON &= 0x7F;									//波特率不倍速
		SCON = 0x50;									//8位数据,可变波特率
		TMOD &= 0x0F;									//清除定时器1模式位
		TMOD |= 0x20;									//设定定时器1为8位自动重装方式
		TL1 = 0xFD;										//设定定时初值
		TH1 = 0xFD;										//设定定时器重装值
		ET1 = 0;										//禁止定时器1中断
		TR1 = 1;										//启动定时器1
		ES = 1;											//允许串口中断
		EA = 1;											//开总中断
}

/*****************************************************
** 函数名称：UartIntPro
** 函数功能：串口中断处理
** 参    数：无
** 函数返回：无
******************************************************/
void UartIntPro(void)	interrupt 4 using 1
{
		if(RI)
		{
				RI = 0;

				if(UartRcvBufP == UART_RCV_BUF_LEN - 1)		//保持最后接收缓存最后1个字节为0
				{
						return;
				}

				//UartRcvByte = 1;
				if(SBUF == '\n') {
						//memset(UartRcvBuf, 0, UART_RCV_BUF_LEN);
					  UartRcvBufP = 0;
					  return;
				}
				//if((UartRcvEnd == 0) && (UartRcvStart == 1))
				{
						UartRcvBuf[UartRcvBufP++] = SBUF;	
					  if(UartRcvBuf[5] == 'G' && UartRcvBuf[6] == 'O') {
							UartRcvEnd = 1;
						}
				}
		}
}


/*****************************************************
** 函数名称：UartClaer
** 函数功能：清零串口接收缓存BUF、相关标志位
** 参    数：无
** 函数返回：无
******************************************************/
void UartClaer(void)
{
		memset(UartRcvBuf, 0, UART_RCV_BUF_LEN);
		UartRcvByte = 0;
		UartRcvBufP = 0;
		UartRcvEnd = 0;
		UartRcvStart = 0;
}

/*****************************************************
** 函数名称：UartSendChar
** 函数功能：串口发送单字节
** 参    数：senddata：需要发送的字节
** 函数返回：无
******************************************************/
void UartSendData(uchar senddata)
{
		SBUF = senddata;
		while(!TI);			//等待字节发送完成
		TI = 0;
}

/*****************************************************
** 函数名称：UartSendString
** 函数功能：串口发送字符串
** 参    数：*string：指向需要发送的字符串指针
** 函数返回：无
******************************************************/
void UartSendString(uchar *string)
{

		while((*string) != '\0')
		{
				SBUF = *string;
				while(!TI);
				TI = 0;
				string++;
		}
}

/*****************************************************
** 函数名称：UartSendBuf
** 函数功能：串口发送数组
** 参    数：*bufp：指向需要发送的数组指针
			 len：需要发送的数组长度
** 函数返回：无
******************************************************/
void UartSendBuf(uchar *bufp,uint len)
{
		uint i;

		for(i = 0;i < len;i++)
		{
				SBUF = *bufp;
				while(!TI);
				TI = 0;
				bufp++;
		}
}


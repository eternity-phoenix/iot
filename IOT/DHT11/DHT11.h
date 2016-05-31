/*****************************************************
** 功能模块：  DHT11操作
** 硬件相关：  MCU使用STC89C52RC,硬件连接对应如下： 
**             DHT11_DATA--->P0^0
/*****************************************************/

#ifndef _DHT11_
#define _DHT11_

#define uchar 					unsigned char
#define uint					unsigned int


void Delay_10us(void);
void DHT11_ReadValue(void);
extern void Delay_100us(uint j);
extern void DHT11_ReadTempAndHumi(void);

#endif
#include <REG52.H>  
#include "UART.h"
#include "DHT11.h"
#include "ESP8266.h"

#define uchar unsigned char
#define uint unsigned int

extern uchar T_data_H, RH_data_H, UartRcvEnd;

void delay_1s(unsigned int delay)	
// 延时子程序 对应12M晶振
{	
		unsigned int ms, i;
		
		while(delay--) {
				ms = 1000;
				while(ms--) //每一次循环1ms
				{
						for(i = 0; i < 120; i++);
				}
		}
}

void SendData()
{
		ESP8266CmdSend(AT_CIPSTART,SERVER_IP_PORT,"OK");
		delay_1s(1);
	
	  ESP8266CmdSend(AT_CIPSEND,"=45","OK");
	  Delay_100us(100);
	
	  UartSendString("DHT11");
		UartSendData('|');
		UartSendString("temperature");
		UartSendData('~');
	  UartSendData(T_data_H);
		UartSendData('~');
		UartSendString("℃");
		UartSendData('~');
		UartSendString("DEC");
		UartSendData('|');
		UartSendString("humidity");
		UartSendData('~');
	  UartSendData(RH_data_H);
		UartSendData('~');
		UartSendString("RH");
		UartSendData('~');
		UartSendString("DEC");
	  Delay_100us(300);
	
	  ESP8266CmdSend(AT_CIPCLOSE,NULL,"OK");
}
//----------------------------------------------  
void main (void)  
{  
		UartInit();
		//EA = 0;
		delay_1s(3);
		ESP8266Init();
	  //while(!UartRcvEnd);
	//UartSendData(UartRcvEnd);
		//UartRcvEnd = 0;
		//EA = 0;
		while(1){
			
				delay_1s(2);
				UartRcvEnd = 0;
			  //UartSendData('l');
				do {
						DHT11_ReadTempAndHumi();
				} while(!UartRcvEnd);
				//EA = 0;
				SendData();
		}

}  
//----------------------------------------------  

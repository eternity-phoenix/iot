//硬件连接： P2.0口为通讯口连接DHT1
#include <reg52.h>
#include "DHT11.h"

#define uchar unsigned char
#define uint unsigned int

sbit DHT11_DATA = P0^0;

uchar FLAG;
uchar T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;
uchar T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;
uchar DATA_TEMP; 

void Delay_100us(uint j)
{   
	uchar i;
	for(; j > 0; j--){  
		for(i = 0; i < 27; i++); 
	}
}

void  Delay_10us(void)
{
	uchar i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}
//串行总线  
void DHT11_ReadValue(void)
{
	uchar i, value;
	for(i = 0; i < 8; i++){
		FLAG = 2;
		while((!DHT11_DATA) && FLAG++);
		Delay_10us();
		Delay_10us();
		value=0;
		if(DHT11_DATA){
			value++;
		}
		FLAG = 2;
		while(DHT11_DATA && FLAG++);
		//超时则跳出for循环    
		if(FLAG == 1){
			break;
		}
		//判断数据位是0还是1  
		// 如果高电平高过预定0高电平值则数据位为 1 
		DATA_TEMP <<= 1;
		DATA_TEMP |= value;
	}
}

 //--------------------------------
 //-----湿度读取子程序 ------------
 //--------------------------------
 //----以下变量均为全局变量--------
 //----温度高8位== T_data_H------
 //----温度低8位== T_data_L------
 //----湿度高8位== RH_data_H-----
 //----湿度低8位== RH_data_L-----
 //----校验 8位 == checkdata-----
 //----调用相关子程序如下----------
 //---- Delay();, Delay_10us();,DHT11_ReadValue(); 
 //--------------------------------

void DHT11_ReadTempAndHumi(void)
{
	uchar value;
	
	//主机拉低18ms 
	DHT11_DATA = 0;
	Delay_100us(180);
	DHT11_DATA = 1;
	
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	
	//主机设为输入 判断从机响应信号 
	DHT11_DATA = 1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行   
	if(!DHT11_DATA)   //T !   
	{
		FLAG = 2;
		//判断从机是否发出 80us 的低电平响应信号是否结束  
		while((!DHT11_DATA) && FLAG++);
		FLAG = 2;
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while(DHT11_DATA && FLAG++);
		//数据接收状态   
		DHT11_ReadValue();
		RH_data_H_temp = DATA_TEMP;
		DHT11_ReadValue();
		RH_data_L_temp = DATA_TEMP;
		DHT11_ReadValue();
		T_data_H_temp = DATA_TEMP;
		DHT11_ReadValue();
		T_data_L_temp = DATA_TEMP;
		DHT11_ReadValue();
		checkdata_temp = DATA_TEMP;
		DHT11_DATA = 1;
		//数据校验 

		value = T_data_H_temp + T_data_L_temp + RH_data_H_temp + RH_data_L_temp;
		if(value == checkdata_temp)
		{
			RH_data_H = RH_data_H_temp;
			RH_data_L = RH_data_L_temp;
			T_data_H = T_data_H_temp;
			T_data_L = T_data_L_temp;
			checkdata = checkdata_temp;
		}
	}
}

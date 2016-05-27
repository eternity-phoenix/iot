/*****************************************************
** 功能模块：  ESP8266-01串口wifi模块，AT指令集021
** 硬件相关：  MCU使用STC89C52RC,硬件连接对应如下：         
**             ESP8266_URXD--->P31
**             ESP8266_UTXD--->P30
******************************************************/

#include <REG52.h>
#include "esp8266.h"
#include "UART.h"
#include <string.h>

/*ESP8266使用到的IO引脚定义*/
sbit ESP8266_CHPD = P2^0;					  //高电平工作，低电平关闭模块供电
sbit ESP8266_RESET = P2^1;				  //外部复位信号，低电平复位，高电平工作
sbit ESP8266_GPIO2 = P2^2;				  //开机上电时必须为高电平，禁止硬件下拉
sbit ESP8266_GPIO0 = P2^3;				  //悬空：FLASH BOOT,工作模式；下拉：UART DOWNLOAD,下载模式


/*****************************************************
** 函数名称：Delay1000ms
** 函数功能：延时1S
** 参    数：无
** 函数返回：无
******************************************************/
void Delay1000ms()		//@11.0592MHz
{
		unsigned char i, j, k;

		//	_nop_();
		i = 8;
		j = 1;
		k = 243;
		do
		{
				do
				{
						while(--k);
				}while(--j);
		}while(--i);
}

/*****************************************************
** 函数名称：Delay50ms
** 函数功能：延时50MS
** 参    数：无
** 函数返回：无
******************************************************/
void Delay50ms()		//@11.0592MHz
{
		unsigned char i, j;

		i = 90;
		j = 163;
		do
		{
				while(--j);
		}while(--i);
}

/*****************************************************
** 函数名称：ESP8266CmdSend
** 函数功能：向ESP8266发送AT命令，并判断返回
** 参    数：1.cmd：需发送的AT命令
**           2.parameter：AT命令后续参数，当值为NULL时，AT命令无参数
**			 		 3.cmdchack：需判断的AT命令返回，当值为NULL时，无需判断AT命令返回
** 函数返回：无
******************************************************/
void ESP8266CmdSend(char *cmd,char *parameter,char *cmdchack)
{
		//char *atcheack;
		uint i = 1024;
		//UartClaer();						//清空串口相关缓存和标志位
		UartSendString(cmd); 				//发送AT命令

		if(parameter != NULL)				//判断是否有参数发送
		{
				UartSendString(parameter);		//发送AT命令参数
		}
		UartSendData(0x0D);				//发送回车换行
		UartSendData(0x0A);
		
		if(cmdchack == NULL) return;			//若无需判断AT命令返回，退出函数
		while(!RI && i--);
		RI = 0;
		/*while(1)				    		//等待AT命令返回
		{
				if(UartRcvByte >= 6)
				{
						break;
				}
		//此处可增加接收返回超时判断
		}*/
		//Delay1000ms();
		//Delay1000ms();
		//UartSendString("123456");
		//atcheack = strstr(UartRcvBuf, cmdchack); 			//检测AT命令返回
		
		/*if(atcheack==NULL)
		{																					   
		DisplayChar_12X06(6,96,"Error");			//OLED显示当前命令执行状态，如果没有OLED可以屏蔽
		}
		else
		{
		DisplayChar_12X06(6,96,"Ok");		 		//OLED显示当前命令执行状态，如果没有OLED可以屏蔽
		}	
		*/
}

/*****************************************************
** 函数名称：QuitPassThroughMode
** 函数功能：退出透传模式
** 参    数：无
** 函数返回：无
******************************************************/
void QuitPassThroughMode(void)
{
		UartSendString(QUIT_PASS_THROUGH);	  	//发送退出透传模式编码

		/*以下操作为避免模块不是在透传模式下，发送了退出透传模式编码后，影响下一条指令正常工作*/
		Delay50ms();							
		UartSendData(0x0D);				//发送回车换行
		UartSendData(0x0A);
}

/*****************************************************
** 函数名称：ESP8266Init
** 函数功能：初始化ESP8266各引脚，使其进入工作状态，设置工作模式参数
** 参    数：无
** 函数返回：无
******************************************************/
void ESP8266Init(void)
{
		//uchar idata staipbuf[22],i=0;
		//char *p;

		//Delay1000ms();
		//memset(staipbuf,0,22);
		/*IO引脚配置，确保ESP8266进入工作状态*/
		//ESP8266_CHPD=1;
		//ESP8266_RESET=1;
		//ESP8266_GPIO2=1;
		//ESP8266_GPIO0=1;

		/*以下工作模式参数配置*/
		ESP8266CmdSend(ATE0,NULL,"OK");			//关闭回显
		//QuitPassThroughMode();						//退出透传模式
		ESP8266CmdSend(AT_CWAUTOCONN,"=0","OK");	//关闭模块STA自动连接
		//ESP8266CmdSend(AT,NULL,"OK");				//测试AT命令
		ESP8266CmdSend(AT_CWMODE,"=3","OK");		//设置ESP8266工作模式：STA+AP
		ESP8266CmdSend(AT_CWJAP,ROUTE_USER_PASSWORD,"OK");		//连接无线路由器

		//ESP8266CmdSend(AT_CIFSR,0,"OK");			//获取ESP8266 IP地址
		/*以下if-else部分为更新OLED显示STAIP,没有OLED可以屏蔽
		p=strstr(UartRcvBuf,"STAIP,");
		if(p)										//更新OLED显示STAIP
		{
		while(1)
		{
			staipbuf[i]=*(p+7+i);	
			i++;
			if(*(p+7+i)=='"')	break;
		}
		//DisplayChar_12X06(4,36,staipbuf);	
		}
		else
		{
		//DisplayChar_12X06(4,60,"NONE");
		}
		*/
		//ESP8266CmdSend(AT_CIPSERVER,"=0",NULL);		//关闭ESP8266服务器模式
		//ESP8266CmdSend(AT_CIPMUX,"=0","OK");		//设置ESP8266位单连接模式
		//ESP8266CmdSend(AT_CIPSTART,SERVER_IP_PORT,"OK");		//ESP8266连接上位机服务器，请自行修改服务器IP和端口号
		//ESP8266CmdSend(AT_CIPMODE,"=1","OK");		//开启透传模式
		//ESP8266CmdSend(AT_CIPSEND,NULL,NULL);		//开始发送数据
}

/*****************************************************
** 函数名称：ESP8266ConnectServer
** 函数功能：ESP8266连接远端服务器
** 参    数：无
** 函数返回：无
******************************************************/
//void ESP8266ConnectServer(uchar *ip,uchar *port)
//{
//
//}

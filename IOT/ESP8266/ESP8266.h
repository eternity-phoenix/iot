/*****************************************************
** 功能模块：  ESP8266-01串口wifi模块，AT指令集021
** 硬件相关：  MCU使用STC89C52RC,硬件连接对应如下：         
**             ESP8266_URXD--->P31
**             ESP8266_UTXD--->P30
******************************************************/

#ifndef _ESP8266_H
#define _ESP8266_H

#define uchar	unsigned char
#define uint	unsigned int

/*ESP8266 基础AT命令定义*/
#define AT					"AT"	  							//AT测试指令，正常返回OK
#define AT_RST				"AT+RST"							//模块复位指令
#define AT_GMR				"AT+GMR"							//查看版本信息
/*ESP8266 wifi功能AT指令*/
#define	AT_CWMODE			"AT+CWMODE"							//选择wifi应用模式，参数：1、STATION模式；2、AP模式；3、AP+STATION模式
#define AT_CWLAP			"AT+CWLAP"							//列出当前接入点
#define AT_CWJAP			"AT+CWJAP"							//加入接入点，参数：ssid：接入点名称；pwd：密码
#define AT_CWQAP			"AT+CWQAP"							//退出接入点
#define AT_CWSAP			"AT+CWSAP"							//设置AP模式下的参数，ecn：加密方式；ssid：接入点名称；pwd：密码；chl：通道号
#define AT_CWLIF			"AT+CWLIF"							//查看已接入设备IP
#define AT_CWAUTOCONN		"AT+CWAUTOCONN"						//关闭开机STA自动连接功能，参数0
/*ESP8266 TCP/IP功能AT指令*/
#define AT_CIPSTART			"AT+CIPSTART"						//建立TCP/UDP连接，参数：id（多路连接时）：连接序号；TYPE：连接类型；
																//addr：远程服务器IP地址；port：端口
#define AT_CIPSTATUS		"AT+CIPSTATUS" 						//获取TCP/UDP连接状态
#define AT_CIPMUX			"AT+CIPMUX"							//启动多连接,参数：1、多连接模式；0、单连接模式
#define AT_CIPSEND			"AT+CIPSEND"						//发送数据，参数：id：连接序号；length：发送数据长度
#define AT_CIPCLOSE			"AT+CIPCLOSE"						//关闭连接，参数：n（多路连接时）：需要关闭的连接序号；id：关闭模式
#define AT_CIFSR			"AT+CIFSR" 							//获取本地IP地址
#define AT_CIPSERVER		"AT+CIPSERVER"						//配置为服务器模式。参数：1、开启；0、关闭
#define AT_CIPMODE			"AT+CIPMODE"						//设置传输模式，参数：1、透传模式；0、非透传模式
#define AT_CIPSTO			"AT+CIPSTO"							//设置服务器超时时间，参数范围：0-28800s
#define AT_CIUPDATE			"AT+CIUPDATE"						//网络固件升级
#define _IPD				"+IPD"								//接收到网络数据，参数：id（多连接时）：收到连接的ID号；len：数据长度
																//data：收到的数据
/*AT增补指令集*/
#define ATE0				"ATE0"								//关闭AT命令回显
#define ATE1				"ATE1"								//开启AT命令回显
#define AT_CIOBAUD			"AT+UART"						//波特率设置命令，波特率范围：9600-921600 AT+UART=9600,8,1,0,0
#define AT_CSYSWDTENABLE	"AT+CSYSWDTENABLE"	 				//打开看门狗
#define AT_CSYSWDTDISABLE	"AT+CSYSWDTDISABLE"					//关闭看门狗
#define QUIT_PASS_THROUGH	"+++"								//退出透传

/*其他宏定义*/
#define ROUTE_USER_PASSWORD	"=\"ESP8266\",\"123456789\""			//设置自己所使用的无线路由用户名、密码
#define SERVER_IP_PORT		"=\"TCP\",\"192.168.1.111\",8080" 	//上位机服务器通讯协议、IP地址、端口
																//可根据自己实际情况修改，连接服务器前请先连接路由
#define NULL				0									//定义指针空值

/*提供给外部的功能函数接口*/
extern void ESP8266Init(void);
extern void ESP8266CmdSend(char *cmd,char *parameter,char *cmdchack);

#endif
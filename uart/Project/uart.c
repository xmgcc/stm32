#include "uart.h"
#include "stm32f10x.h"
#include "stdio.h"

// 初始化gpio
// txd pa9
// rxd pa10
void init_uart_gpio(void)
{
	GPIO_InitTypeDef pa9;
	GPIO_InitTypeDef pa10;
	
	// 第一步，启用GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 第二步，GPIO_Init初始化
	
	// 2.1 txd
	pa9.GPIO_Mode = GPIO_Mode_AF_PP;
	pa9.GPIO_Pin = GPIO_Pin_9;
	pa9.GPIO_Speed = GPIO_Speed_50MHz;
	
	// 2.2 rxd
	pa10.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	pa10.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA, &pa9);
	GPIO_Init(GPIOA, &pa10);
}


// 初始化串口配置 115200, 8-N-1
void init_uart1(void)
{
	USART_InitTypeDef usart;
	
	// 第一步，打开串口外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// 第二步，设置串口的工作参数，波特率，数据格式
	usart.USART_BaudRate = 115200;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart);
}

// 初始化串口中断
void init_uart_it(void)
{
	// 启用串口
	USART_Cmd(USART1, ENABLE);
	
	// 接收到数据，产生中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

// 初始化总中断
void init_uart_nvic(void)
{
	NVIC_InitTypeDef nvic;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// 串口1中断源
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&nvic);
}

// 发送一个字节
void usart_sendbyte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	// 第一步，发送一个字节
	USART_SendData(USART1, ch);
	
	// 第二步，等待发送完成
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {
	}
}

void usart_sendstring(USART_TypeDef * pUSARTx, char *data)
{
	// 发送每个字符，不包括结束符'\0'
	while(*data != '\0') {
		usart_sendbyte(pUSARTx, *data);
		
		data++;
	}
}

// 实现fputc
int fputc(int ch, FILE *f)
{
	usart_sendbyte(USART1, ch);
	return ch;
}

// 禁用半主机模式，没有勾选MicroLib
#pragma import(__use_no_semihosting)
struct __FILE
{
	int a;
};
 
FILE __stdout;
void _sys_exit(int x)
{
	
}


void init_uart(void)
{
	init_uart_gpio();
	init_uart1();
	init_uart_it();
	init_uart_nvic();
}

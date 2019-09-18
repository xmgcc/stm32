#include "uart.h"
#include "stm32f10x.h"
#include "stdio.h"

// ��ʼ��gpio
// txd pa9
// rxd pa10
void init_uart_gpio(void)
{
	GPIO_InitTypeDef pa9;
	GPIO_InitTypeDef pa10;
	
	// ��һ��������GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// �ڶ�����GPIO_Init��ʼ��
	
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


// ��ʼ���������� 115200, 8-N-1
void init_uart1(void)
{
	USART_InitTypeDef usart;
	
	// ��һ�����򿪴�������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// �ڶ��������ô��ڵĹ��������������ʣ����ݸ�ʽ
	usart.USART_BaudRate = 115200;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart);
}

// ��ʼ�������ж�
void init_uart_it(void)
{
	// ���ô���
	USART_Cmd(USART1, ENABLE);
	
	// ���յ����ݣ������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

// ��ʼ�����ж�
void init_uart_nvic(void)
{
	NVIC_InitTypeDef nvic;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	// ����1�ж�Դ
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&nvic);
}

// ����һ���ֽ�
void usart_sendbyte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	// ��һ��������һ���ֽ�
	USART_SendData(USART1, ch);
	
	// �ڶ������ȴ��������
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {
	}
}

void usart_sendstring(USART_TypeDef * pUSARTx, char *data)
{
	// ����ÿ���ַ���������������'\0'
	while(*data != '\0') {
		usart_sendbyte(pUSARTx, *data);
		
		data++;
	}
}

// ʵ��fputc
int fputc(int ch, FILE *f)
{
	usart_sendbyte(USART1, ch);
	return ch;
}

// ���ð�����ģʽ��û�й�ѡMicroLib
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

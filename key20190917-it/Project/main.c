#include "stm32f10x.h"


// pa8
void init_led()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		// 把GPIOA的第四个引脚，设置位OUTPUT，50MHz
		// 找到对应引脚
		// GPIOA 8
	    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;

		// 配置为输出OUTPUT
	    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

		// SPEED
	    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void key_init()
{
		GPIO_InitTypeDef key0;
	GPIO_InitTypeDef key1;
	// pc5
	key0.GPIO_Pin = GPIO_Pin_5;
	key0.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOC, &key0);
	
	// pa15
	key1.GPIO_Pin = GPIO_Pin_15;
	key1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA, &key1);
}

void init_nvic()
{
	NVIC_InitTypeDef pc5;
			NVIC_InitTypeDef pa15;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);



	pc5.NVIC_IRQChannel = EXTI9_5_IRQn;
	pc5.NVIC_IRQChannelCmd = ENABLE;
	pc5.NVIC_IRQChannelPreemptionPriority = 0;
	pc5.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&pc5);
	
	
	pa15.NVIC_IRQChannel = EXTI15_10_IRQn;
	pa15.NVIC_IRQChannelCmd = ENABLE;
	pa15.NVIC_IRQChannelPreemptionPriority = 0;
	pa15.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&pa15);
}

void init_exit()
{
	EXTI_InitTypeDef pc5;
		EXTI_InitTypeDef pa15;

	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	// 使用PC5作为外部中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
	pc5.EXTI_Line = EXTI_Line5;
	pc5.EXTI_LineCmd = ENABLE;
	pc5.EXTI_Mode = EXTI_Mode_Interrupt;
	pc5.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&pc5);
	
	
	// 使用pa15作为外部中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
	pa15.EXTI_Line = EXTI_Line15;
	pa15.EXTI_LineCmd = ENABLE;
	pa15.EXTI_Mode = EXTI_Mode_Interrupt;
	pa15.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&pa15);
}
void delay()
{
	int i = 100;
	int j = 100;
	for ( i = 10; i > 0; i--) {
		for ( j = 100; j > 0; j--) {
		}
	}
}
	// 中断处理函数
void EXTI9_5_IRQHandler(void)
{
	delay();
	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

void EXTI15_10_IRQHandler(void)
{
	delay();
	if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}

int main()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	
	// 初始化led
	init_led();
	
	// 初始化按键，
	key_init();
	
	// 外部中断
	init_exit();
	
	// 总中断NVIC
	init_nvic();
	
	

	
	while(1) {
	}
}

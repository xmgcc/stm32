#include "stm32f10x.h"
#include "stm32f10x_it.h"
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

void init_timer()
{
	SysTick_Config(SystemCoreClock / 100000);
}

void delay_us(uint32_t time)
{
	g_timer_count = time;
	
	// 等待g_timer_count为0
	while(g_timer_count != 0) {
	}
}

int main()
{
	init_led();
	
	init_timer();
	
	while(1) {
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		delay_us(1000*100);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		delay_us(1000*100);
	}
}

#include "stm32f10x.h"
#include "stm32f10x_it.h"
// pa8
void init_led()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		// ��GPIOA�ĵ��ĸ����ţ�����λOUTPUT��50MHz
		// �ҵ���Ӧ����
		// GPIOA 8
	    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;

		// ����Ϊ���OUTPUT
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
	
	// �ȴ�g_timer_countΪ0
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

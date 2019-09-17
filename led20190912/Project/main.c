#include "stm32f10x.h"
int main()
{
			// 启用GPIO对应的时钟
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	
		// 把GPIOA的第四个引脚，设置位OUTPUT，50MHz
		// 找到对应引脚
		// GPIOA 4
	    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;

		// 配置为输出OUTPUT
	    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

		// SPEED
	    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	
    GPIO_Init(GPIOA,&GPIO_InitStructure);

		// 低电平
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	
	// 设置为高电平
	// 哪一组的GPIO
	// 哪一个引脚
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
		// while(1)
		while(1) {
		}
    //return 0;
}

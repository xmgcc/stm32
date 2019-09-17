#include "stm32f10x.h"


void delay()
{
	int i = 100;
	int j = 100;
	for ( i = 100; i > 0; i--) {
		for ( j = 100; j > 0; j--) {
		}
	}
}

// 获取引脚的电平
// return Bit_SET高电平，Bit_RESET低电平
uint16_t key_scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint16_t ret;
	
	ret = GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
	
	if (ret == Bit_RESET) {
		// 处理前抖动
		delay();
		
		// 按键一直按着，等待用户松手
		while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET) {
		}
		
		// 处理后抖动
		delay();
		return Bit_RESET;
	}
	
	return Bit_SET;
}

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

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr &0x00ffffff)<<5)+(bitnum<<2))  
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
#define GPIOA_ODR_Addr (GPIOA_BASE+12) //0x4001080C
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr,n) 
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr,n)  

int main()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	
	init_led();
	
	key_init();
	
	
	while(1) {
		// 判断key1，gpioa15是否按下
		if (key_scan(GPIOA, GPIO_Pin_15) == Bit_RESET) {
			//GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			PAout(8) = 0;
		}
		
		// 判断key0
		if (key_scan(GPIOC, GPIO_Pin_5) == Bit_RESET) {
			//GPIO_SetBits(GPIOA, GPIO_Pin_8);
			PAout(8) = 1;
		}
	}
}

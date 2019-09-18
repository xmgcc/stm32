#include "stm32f10x.h"
#include "stdio.h"
#include "uart.h"

void delay()
{
	int i;
	int j;
	for (i = 100; i > 0; i--)
	{
		for (j = 100; j > 0; j--)
		{
		}
	}
}

int main()
{
	init_uart();
	
	while(1) {
		delay();
		printf("hello\n");
	}
}

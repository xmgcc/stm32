#include "stm32f10x.h"
int main()
{
			// ����GPIO��Ӧ��ʱ��
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	
		// ��GPIOA�ĵ��ĸ����ţ�����λOUTPUT��50MHz
		// �ҵ���Ӧ����
		// GPIOA 4
	    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;

		// ����Ϊ���OUTPUT
	    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

		// SPEED
	    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	
    GPIO_Init(GPIOA,&GPIO_InitStructure);

		// �͵�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	
	// ����Ϊ�ߵ�ƽ
	// ��һ���GPIO
	// ��һ������
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
		// while(1)
		while(1) {
		}
    //return 0;
}

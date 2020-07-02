
/*
	使用寄存器的方法点亮LED灯
  */
#include "stm32f4xx.h" 


/**
  *   主函数
  */
int main(void)
{	
	/*开启 GPIOA 时钟，使用外设时都要先开启它的时钟*/
	RCC_AHB1ENR |= ((unsigned int)1<<0);	
	
	/* LED 端口初始化 */
	
	/*GPIOA MODER15清空*/
	GPIOA_MODER  &= ~( (unsigned int)0x3<< (2*15));	
	/*PA15 MODER15 = 01b 输出模式*/
	GPIOA_MODER |= ((unsigned int)1<<2*15);
	
	/*GPIOA OTYPER15清空*/
	GPIOA_OTYPER &= ~((unsigned int)1<<1*15);
	/*PA15 OTYPER15 = 0b 推挽模式*/
	GPIOA_OTYPER |= ((unsigned int)0<<1*15);
	
	/*GPIOA OSPEEDR15清空*/
	GPIOA_OSPEEDR &= ~((unsigned int)0x3<<2*15);
	/*PA15 OSPEEDR15 = 0b 速率2MHz*/
	GPIOA_OSPEEDR |= ((unsigned int)0<<2*15);
	
	/*GPIOA PUPDR15清空*/
	GPIOA_PUPDR &= ~((unsigned int)0x3<<2*15);
	/*PA15 PUPDR15 = 01b 上拉模式*/
	GPIOA_PUPDR |= ((unsigned int)1<<2*15);
	
	/*PA15 BSRR寄存器的 BR15置1，使引脚输出低电平*/
	GPIOA_BSRR |= ((unsigned int)1<<16<<15);
	
	/*PA15 BSRR寄存器的 BS15置1，使引脚输出高电平*/
//	GPIOA_BSRR |= ((unsigned int)1<<15);

	while(1);

}

// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{	
}






/*********************************************END OF FILE**********************/


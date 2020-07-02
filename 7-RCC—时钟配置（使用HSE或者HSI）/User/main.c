/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   RCC--时钟配置(使用HSE或HSI)
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 战擎开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./rcc/bsp_clkconfig.h"

void Delay(__IO uint32_t nCount); 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

    // 程序来到main函数之前，启动文件：statup_stm32f407xx.s已经调用
    // SystemInit()函数把系统时钟初始化成16MHZ
    // SystemInit()在system_stm32f4xx.c中定义
    // 如果用户想修改系统时钟，可自行编写程序修改	
    // 重新设置系统时钟，这时候可以选择使用HSE还是HSI
  
    //系统时钟标准设置为168M，最高是216M，不推荐
    HSE_SetSysClock(25, 336, 2, 7);
    // 使用HSI，配置系统时钟为168M，切换时钟时，如果PLL已经使能作为系统时钟输出，需要先复位RCC->CFGR寄存器才能切换时钟
	// RCC->CFGR = 0x00000000;
    // HSI_SetSysClock(25, 336, 2, 7);
        
    // LED 端口初始化 
    LED_GPIO_Config();
        
    // MCO1 输出PLLCLK	
    HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_2);
        
    // MCO2 输出SYSCLK
    HAL_RCC_MCOConfig(RCC_MCO2,RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_2);

    while (1)
    {
        LED_ALLON;			 // 亮 
        Delay(0x5FFFFF);
        LED_ALLOFF;		 // 灭
        Delay(0x5FFFFF);
    }
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   18-液晶显示
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include <stdlib.h>
#include "./led/bsp_led.h" 
#include "./lcd/bsp_ili9341_lcd.h"

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );
void Printf_Charater(void)   ;



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  /* 系统时钟初始化成168MHz */
  SystemClock_Config();
  /* LED 端口初始化 */
  LED_GPIO_Config();	 
  /* 初始化串口 */
  DEBUG_USART_Config();
  ILI9341_Init ();         //LCD 初始化
	printf("\r\n ********** 液晶屏英文显示程序*********** \r\n"); 
	printf("\r\n 本程序不支持中文，显示中文的程序请学习下一章 \r\n"); 
	//其中0、3、5、6 模式适合从左至右显示文字，
 //不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
 //其中 6 模式为大部分液晶例程的默认显示方向  
  ILI9341_GramScan ( 6 ); 

	while ( 1 )
	{
		LCD_Test();
	}
}


/*用于测试各种液晶的函数*/
void LCD_Test(void)
{
	/*演示显示变量*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;	
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	/********显示字符串示例*******/
  ILI9341_DispStringLine_EN(LINE(0),"YH 3.2 inch LCD");
  ILI9341_DispStringLine_EN(LINE(2),"resolution:240x320px");
  ILI9341_DispStringLine_EN(LINE(3),"LCD driver:ili9341");
  ILI9341_DispStringLine_EN(LINE(4),"Touch driver:XPT2406");
  
	/********显示变量示例*******/
	LCD_SetTextColor(GREEN);

	/*使用c标准库把变量转化成字符串*/
	sprintf(dispBuff,"Count : %d ",testCNT);
  ILI9341_ClearLine(LINE(5));	/* 清除单行文字 */
	
	/*然后显示该字符串即可，其它变量也是这样处理*/
	ILI9341_DispStringLine_EN(LINE(5),dispBuff);

	/*******显示图形示例******/
  /* 画直线 */
  
  ILI9341_ClearLine(LINE(5));/* 清除单行文字 */
	LCD_SetTextColor(BLUE);

  ILI9341_DispStringLine_EN(LINE(5),"Draw line:");
  
	LCD_SetTextColor(RED);
  ILI9341_DrawLine(25,165,210,160);  
  ILI9341_DrawLine(25,180,210,220);
  
	LCD_SetTextColor(GREEN);
  ILI9341_DrawLine(25,215,210,275);  
  ILI9341_DrawLine(25,230,210,275);
	
	LCD_SetTextColor(BLUE);
  ILI9341_DrawLine(25,240,210,190);  
  ILI9341_DrawLine(25,255,210,230);
	
  Delay(0x2FFFFFF);
  
  ILI9341_Clear(0,32*5,LCD_X_LENGTH,LCD_Y_LENGTH-32*5);	/* 清屏，显示全黑 */
  
  
  /*画矩形*/

  ILI9341_ClearLine(LINE(5));	/* 清除单行文字 */
	LCD_SetTextColor(BLUE);

  ILI9341_DispStringLine_EN(LINE(5),"Draw Rect:");

	LCD_SetTextColor(RED);
  ILI9341_DrawRectangle(25,200,100,50,1);
	
	LCD_SetTextColor(GREEN);
  ILI9341_DrawRectangle(50,200,100,60,0);
	
	LCD_SetTextColor(BLUE);
  ILI9341_DrawRectangle(125,200,100,75,1);
  
  
  Delay(0x2FFFFFF);
	
	ILI9341_Clear(0,32*5,LCD_X_LENGTH,LCD_Y_LENGTH-32*5);	/* 清屏，显示全黑 */

  /* 画圆 */
  ILI9341_ClearLine(LINE(5));	/* 清除单行文字 */
	LCD_SetTextColor(BLUE);
	
  ILI9341_DispStringLine_EN(LINE(5),"Draw Cir:");

	LCD_SetTextColor(RED);
	ILI9341_DrawCircle(75,220,30,1);

	LCD_SetTextColor(GREEN);
	ILI9341_DrawCircle(125,220,30,0);

	LCD_SetTextColor(BLUE);
	ILI9341_DrawCircle(175,220,30,1);


  Delay(0x2FFFFFF);
  
  ILI9341_Clear(0,32*5,LCD_X_LENGTH,LCD_Y_LENGTH-32*5);	/* 清屏，显示全黑 */

}


/**
  * @brief  简单延时函数
  * @param  nCount ：延时计数值
  * @retval 无
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
 void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1) {};
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1) {};
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

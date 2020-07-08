/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   USB文件系统例程，基于SD卡烧录例程和USB读取U盘例程修改
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407-骄阳 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./led/bsp_led.h" 
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_spi_flash.h"
#include "./key/bsp_key.h" 
//#include "./delay/core_delay.h"  
/* FatFs includes component */
#include "ff.h"
#include "./res_mgr/RES_MGR.h"
#include "./USBAPP/usbh_bsp.h"
/**
  ******************************************************************************
  *                              定义变量
  ******************************************************************************
  */
DIR dir; 
FIL fnew;													/* 文件对象 */
UINT fnum;            			  /* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
BYTE WriteBuffer[] =              /* 写缓冲区*/
"欢迎使用野火STM32 F407骄阳开发板 今天是个好日子，新建文件系统测试文件\r\n";  
char SDPath[4]; /* SD逻辑驱动器路径 */
extern FATFS sd_fs[];	
FRESULT res_sd;                /* 文件操作结果 */
extern char src_dir[];
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
uint8_t state = 0;

/* 如果你的U盘有多个分区，文件系统默认挂载的分区没有字库文件，请定义这两个宏(#define Other_Part)(#define Cheak_file) */
/* 通过挂载不同的盘符(如main函数Other_Part中挂载的"1:")，找到字库文件，才将宏注释掉，并修改正确的盘符进行烧录 */
/* 注意要同步修改RES_MGR.h中的RESOURCE_DIR盘符，才能扫描修改后的盘符路径下的文件 */
#if 1
PARTITION VolToPart[]=
{
	{0,1},/* "0:" */
	{0,2},/* "1:" */
	{0,3}	/* "2:" */
};
#endif
int main(void)
{
    /* 系统时钟初始化成400MHz */
  
    LED_GPIO_Config();
    LED1_ON;	
    /* 初始化USART1 配置模式为 115200 8-N-1 */
    Debug_USART_Config();	
	/* 初始化USB */
	USBH_Init(&USB_OTG_Core,
		USB_OTG_FS_CORE_ID,
		&USB_Host,
		&USBH_MSC_cb,
		&USR_cb);
	
    Key_GPIO_Config();
    SPI_FLASH_Init();
	printf("插入U盘后，提示“Device Attached”字样，表示U盘已检测到，按下KEY1继续操作\n");
	 while(1)
	 {
		 /* USB状态检测处理函数，在检测设备插入时使用 */
		USBH_Process(&USB_OTG_Core, &USB_Host);
		 
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			//在外部SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
			res_sd = f_mount(&sd_fs[0],"0:",1);  
			if(res_sd != FR_OK)
			{
			  printf("f_mount 1ERROR!请给开发板插入U盘然后重新复位开发板!");
			  LED3_ON;
			  while(1);
			}
#ifdef Other_Part
			res_sd = f_mount(&sd_fs[1],"1:",1);
		  
			if(res_sd != FR_OK)
			{
			  printf("f_mount 2ERROR!请给开发板插入U盘然后重新复位开发板!");
			  LED3_ON;
			  while(1);
			}

			res_sd = f_chdrive("1:");
			if(res_sd != FR_OK)
			{
			  printf("f_chdir ERROR!!");
			  LED3_ON;
			  while(1);
			}

			FRESULT fr;
			TCHAR str [100];
			fr = f_getcwd(str,100);  /*获取当前目录路径*/
			printf("%s\n",str);
#endif
#if 1    
			printf("\r\n 按一次KEY1开始烧写字库并复制文件到FLASH。 \r\n"); 
			printf("\r\n 注意该操作会把FLASH的原内容会被删除！！ \r\n"); 

			while(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_OFF);
			printf("\r\n 正在进行整片擦除，时间很长，请耐心等候...\r\n"); 
#ifndef Cheak_file
			SPI_FLASH_BulkErase();
#endif
			/* 第一次执行Make_Catalog函数时删除旧的烧录信息文件 */
			res_sd = f_unlink(BURN_INFO_NAME_FULL);
			if ( res_sd == FR_OK )
			{
			  printf("！！删除文件成功：(%d)\n",res_sd);
			}
			else
			{
			  printf("！！删除文件失败：(%d)\n",res_sd);
			}
			
			/* 生成烧录目录信息文件 */
			Make_Catalog(src_dir,0);
#ifndef Cheak_file
			/* 烧录 目录信息至FLASH*/
			Burn_Catalog();
			 /* 根据 目录 烧录内容至FLASH*/
			Burn_Content();
			/* 校验烧录的内容 */
			Check_Resource(); 
#endif
			LED_ALLTOGGLE;
		}
	}
#endif    
}
	  


#include "stm32f10x.h"
#include "delay.h"
#include "HX711.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "string.h"
# include <stdio.h>
# include <stdlib.h>

char str_int[30];
char *str;
u32 temp;

int main(void)
{		
	Init_HX711pin();
	delay_init();
	LED_Init();
	OLED_Init();			//初始化OLED  

	OLED_Clear();
	
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	
	Get_Maopi();				//称毛皮重量
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();		   //重新获取毛皮重量

	
	
	while(1)
	{
						
		Get_Weight();
		if(Weight_Shiwu > 0){
			OLED_ShowCHinese(0,0,3);//显示蓝牙符号
			str = myitoa(Weight_Shiwu, str_int, 10);
			//OLED_ShowNum(20,0,Weight_Shiwu,4,20);
			Uart2SendStr((u8*)str);
			//体重部分
			OLED_ShowCHinese(0,3,0);//中文体
			OLED_ShowCHinese(18,3,1);//中文重
			OLED_ShowString(36,3,"=");
			OLED_ShowNum(40,3,(Weight_Shiwu%10000/1000-8 + 0x30),1,10);
			OLED_ShowString(51,3,".");
			OLED_ShowNum(52,3,(Weight_Shiwu%1000/100-8 + 0x30),1,10);
			OLED_ShowNum(62,3,(Weight_Shiwu%100/10-8 + 0x30),1,10);
			OLED_ShowNum(72,3,(Weight_Shiwu%10-8 + 0x30),1,10);
			OLED_ShowString(83,3,"Kg");
			//体脂部分
			OLED_ShowCHinese(0,6,0);
			OLED_ShowCHinese(18,6,2);
			OLED_ShowString(36,6,"=");
			OLED_ShowNum(40,6,2,1,10);
			OLED_ShowNum(51,6,0,1,10);
			OLED_ShowString(62,6,"%");
			//if(Weight_Shiwu == temp){
				str = myitoa(Weight_Shiwu, str_int, 10);
				Uart2SendStr(str);
			//}
			temp = Weight_Shiwu;
			delay_ms(1000);
		}else{
			//delay_ms(1000);
			//delay_ms(1000);
			OLED_Clear();	
		}
	
		printf("净重量 = %d g\r\n",Weight_Shiwu); //打印

	}
	

}







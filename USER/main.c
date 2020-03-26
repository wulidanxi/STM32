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
	OLED_Init();			//��ʼ��OLED  

	OLED_Clear();
	
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	
	Get_Maopi();				//��ëƤ����
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();		   //���»�ȡëƤ����

	
	
	while(1)
	{
						
		Get_Weight();
		if(Weight_Shiwu > 0){
			OLED_ShowCHinese(0,0,3);//��ʾ��������
			str = myitoa(Weight_Shiwu, str_int, 10);
			//OLED_ShowNum(20,0,Weight_Shiwu,4,20);
			Uart2SendStr((u8*)str);
			//���ز���
			OLED_ShowCHinese(0,3,0);//������
			OLED_ShowCHinese(18,3,1);//������
			OLED_ShowString(36,3,"=");
			OLED_ShowNum(40,3,(Weight_Shiwu%10000/1000-8 + 0x30),1,10);
			OLED_ShowString(51,3,".");
			OLED_ShowNum(52,3,(Weight_Shiwu%1000/100-8 + 0x30),1,10);
			OLED_ShowNum(62,3,(Weight_Shiwu%100/10-8 + 0x30),1,10);
			OLED_ShowNum(72,3,(Weight_Shiwu%10-8 + 0x30),1,10);
			OLED_ShowString(83,3,"Kg");
			//��֬����
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
	
		printf("������ = %d g\r\n",Weight_Shiwu); //��ӡ

	}
	

}







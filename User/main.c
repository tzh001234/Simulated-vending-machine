#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h"
#include "time.h"
#include "key.h"
#include "ball.h"
#include "beep.h"



int shuliang_Coca_Cola=100;
int shuliang_Pepsi=2;


unsigned char dis_shuliang_Coca_Cola[30];
unsigned char dis_shuliang_Pepsi[30];

int xuanze_flag=0;   //控制选择按键



int main()  //主函数
{
	u8 i;
	u16 j;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	LED_Init();                //各种初始化函数
	USART1_Init(115200);
	TFTLCD_Init();			
	KEY_Init(); 
	BEEP_Init();
	
	LCD_Clear(BLUE);  //选择lcd屏幕颜色
	
	for (j=0;j<229;j=j+12)  //清空页面
	{
		LCD_ShowString(0,2*j,tftlcd_data.width,tftlcd_data.height,24, "                           ");
	}
	LCD_ShowString(0,408,tftlcd_data.width,tftlcd_data.height,24,   "          HELLO!           ");
	
	
	while(1)
	{
		LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Coca_Cola");      //显示商品信息
		LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Pepsi");


	
		sprintf(dis_shuliang_Coca_Cola ,"num:%2d",shuliang_Coca_Cola);        //商品数量
		sprintf(dis_shuliang_Pepsi ,"num:%2d",shuliang_Pepsi);		
		LCD_ShowString(140,10,tftlcd_data.width,tftlcd_data.height,24,dis_shuliang_Coca_Cola);
		LCD_ShowString(140,50,tftlcd_data.width,tftlcd_data.height,24,dis_shuliang_Pepsi);
	
	
		LCD_ShowString(240,10,tftlcd_data.width,tftlcd_data.height,24,"RMB:3");       //商品价格
		LCD_ShowString(240,50,tftlcd_data.width,tftlcd_data.height,24,"RMB:3");
		
		
		if(KEY_UP==1)       //检测是否按下KEY_UP键
		{
			while(KEY_UP==1);
			xuanze_flag++;
			if(xuanze_flag>2)
			{
				xuanze_flag=1;
			}
		}
		
		
		if(xuanze_flag==1)
		{
			LCD_ShowString(10,130,tftlcd_data.width,tftlcd_data.height,24,"Coca_Cola  RMB:3 ");
			LCD_ShowString(10,190,tftlcd_data.width,tftlcd_data.height,24,"Confirm payment?  ");
		}


		if(xuanze_flag==2)
		{
			LCD_ShowString(10,130,tftlcd_data.width,tftlcd_data.height,24,"Pepsi      RMB:3 ");
			LCD_ShowString(10,190,tftlcd_data.width,tftlcd_data.height,24,"Confirm payment?  ");
		}	


		if(KEY0==0)
		{
			while(KEY0==0);
			xuanze_flag=0;
			LCD_ShowString(10,130,tftlcd_data.width,tftlcd_data.height,24,"                           ");
			LCD_ShowString(10,190,tftlcd_data.width,tftlcd_data.height,24,"                           ");
			LCD_ShowString(10,220,tftlcd_data.width,tftlcd_data.height,24,"                           ");
			LCD_ShowString(10,260,tftlcd_data.width,tftlcd_data.height,24,"                           ");
		}

		if(KEY1==0)
		{
			while(KEY1==0);
			
			
			if(xuanze_flag!=0){
				LCD_ShowString(10,10 ,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				LCD_ShowString(10,50 ,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				LCD_ShowString(10,130 ,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				LCD_ShowString(10,190,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				if(xuanze_flag==1)
				{
					shuliang_Coca_Cola--;
					if(shuliang_Coca_Cola<0)
					{
						LCD_ShowString(10,220,tftlcd_data.width,tftlcd_data.height,24,"Coca_Cola is not enough");
						LCD_ShowString(100,260,tftlcd_data.width,tftlcd_data.height,24,"Please Add");
						BEEP=!BEEP;
						delay_ms(1000);
						BEEP=!BEEP;
						shuliang_Coca_Cola=100;
					}else
					{
						LCD_ShowString(70,220,tftlcd_data.width,tftlcd_data.height,24,"Payment success");
						LCD_ShowString(100,260,tftlcd_data.width,tftlcd_data.height,24,"Thank You~");
						led_on(0);
						delay_ms(1000);
						led_off(0);
					}
				}
				if(xuanze_flag==2)
				{
					shuliang_Pepsi--;
					if(shuliang_Pepsi<0)
					{
						LCD_ShowString(48,220,tftlcd_data.width,tftlcd_data.height,24,"Pepsi is not enough");
						LCD_ShowString(100,260,tftlcd_data.width,tftlcd_data.height,24,"Please Add");
						BEEP=!BEEP;
						delay_ms(1500);
						BEEP=!BEEP;
						shuliang_Pepsi=2;
						
					}else
						{
						LCD_ShowString(70,220,tftlcd_data.width,tftlcd_data.height,24,"Payment success");
						LCD_ShowString(100,260,tftlcd_data.width,tftlcd_data.height,24,"Thank You~");
						led_on(1);
						delay_ms(1000);
						led_off(1);
					}
				}
				xuanze_flag=0;
				while(1)
				{
					if(KEY0==0)
					{
						goto fanhui;
					}
				}
			}
			if(xuanze_flag==0){
				LCD_ShowString(10,10 ,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				LCD_ShowString(10,50 ,tftlcd_data.width,tftlcd_data.height,24,"                           ");
				LCD_ShowString(30,220,tftlcd_data.width,tftlcd_data.height,24,"Please chose commodity");
				while(1)
				{
					if(KEY0==0)
					{
						goto fanhui;
					}
				}
			}
			xuanze_flag=0;
		}
		fanhui:		delay_ms(10);		
	}
}

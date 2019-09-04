
//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : led_dispaly.c
// Description: JPD-BFS200 LED dispaly function
//     Author : ghg
//   Customer : 京柏(JingBai)
//Targer Board: 京柏(JingBai):JPD-BFS200
//     Note   :Initial on 20190821
//*********************************************************************/
#include "common.h"

volatile unsigned char gu8v_weight_unit; /* weight unit */
volatile unsigned char gu8v_led_buffer[C_LED_BUFF_MAX];
volatile __byte_type   gu8v_led_buffer_point;

volatile unsigned char LEDScan_Cnt;	/* led scan dispaly */
#if 0
const unsigned char lu8_led_char_buffer[C_LED_CHAR_NUM] = {\
			//0,   1,   2,	 3,	  4,   5,   6,   7,   8,   9,   //数组下标
			 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, //显示字符
			//'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

			//10,  11,  12,	 13,     14		  15		16,    17,	  18,	19
    		 0x76,0x38,0x5C,0x40,	0xFF,    0x00,		0x77,	0x73, 0x71, 0x30
    	   //'H', 'L', 'O', '-',  'all on', 'all off',	'A',	'P',  'F',  'I'
    	 };
 /*
	 ______________________________________
 	 |	   1	 	2		 3	 	 4	  |
 	 |	   A		A		 A	 	 A	  |
 	 |	 F	 B	  F   B    F   B   F   B  |
 	 |	   G		G		 G	 	 G	  |
 	 |	 E	 C	  E   C    E   C   E   C  |
 	 |	   D		D	o	 D	 o	 D	  |
 	 |____________________________________|
 */
#endif

 const unsigned char lu8_led_char_buffer[C_LED_CHAR_NUM] = {\
			 //0,	1,	 2,   3,   4,	5,	 6,   7,   8,	9,	 //数组下标
			  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, //显示字符
			 //'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

			 //10,	11,   12,   13,	  14	15	 16,
			 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00,	// A~F,off

			 //17,	 18,   19,   20,   21,    22,   23,    24
			 0x76, 0x30, 0x38, 0x5C,  0x73,  0x50, 0x40,   0xFF
			 //'H',  'I',  'L',  'O', 'P',   'r',  '-',   'all on',
		  };

/**************************************************************
*Function name:led_display_scan
*Description  :The led scan dispaly function is called intrrupted.
*Parameter    :none
*Return	      :none
***************************************************************/
void led_display_scan(void)
{
	u8 display_char = 0;

	LEDCOM1 = HIGH;
	LEDCOM2 = HIGH;
	LEDCOM3 = HIGH;
	LEDCOM4 = HIGH;
	LEDCOMC1 = OUTPUT;
	LEDCOMC2 = OUTPUT;
	LEDCOMC3 = OUTPUT;
	LEDCOMC4 = OUTPUT;
	LEDSEGC	 = OUTPUT;
	if(!fg_led_flash){

		switch (LEDScan_Cnt)
		{
			case 0:
				display_char = gu8v_led_buffer[LED_NUM_QIAN];
				LEDSEG = lu8_led_char_buffer[display_char];
				LEDCOM1 = LOW;
				LEDScan_Cnt = 1;
				break;

			case 1:
				display_char = gu8v_led_buffer[LED_NUM_BAI];
				LEDSEG = lu8_led_char_buffer[display_char];
				LEDCOM2 = LOW;
				LEDScan_Cnt = 2;
				break;

			case 2:
				display_char = gu8v_led_buffer[LED_NUM_SHI];
				LEDSEG = lu8_led_char_buffer[display_char];
			    if(fg_led_point2){
					LEDSEG8 = HIGH;
				}
				LEDCOM3 = LOW;
				LEDScan_Cnt = 3;
				break;

			case 3:
				display_char = gu8v_led_buffer[LED_NUM_GE];
				LEDSEG = lu8_led_char_buffer[display_char];
			    if(fg_led_point1){
					LEDSEG8 = HIGH;
				}
				LEDCOM4 = LOW;
				LEDScan_Cnt = 0;
				break;

	 		default:
	 			LEDScan_Cnt = 0;
	 			break;
		}

	}else{
		//turn off all led
		LEDSEG = LOW;
	}

}

/*******************************************************************************
*Function name:led_init
*Description  :initial LED port,all led off
*Parameter    :none
*Return       :none
*******************************************************************************/
void led_init(void)
{
	LEDCOM1 = HIGH ;
	LEDCOM2 = HIGH ;
	LEDCOM3 = HIGH ;
	LEDCOM4 = HIGH ;
	LEDSEG = LOW;
	LEDCOMC1 = OUTPUT ;
	LEDCOMC2 = OUTPUT ;
	LEDCOMC3 = OUTPUT ;
	LEDCOMC4 = OUTPUT ;
	LEDSEGC  = OUTPUT ;
}

/*******************************************************************************
*Function name:set_led_all_buffer
*Description  :all led OFF or ON
*Parameter    :none
*Return       :none
*******************************************************************************/
void set_led_all_buffer(u8 OnOff)
{
	u8 i;
	if(OnOff){
		for(i = 0; i < C_LED_BUFF_MAX; i++){
			gu8v_led_buffer[i] = LED_CHAR_ALL;
		}
	}else{
		for(i = 0; i < C_LED_BUFF_MAX; i++){
			gu8v_led_buffer[i] = LED_CHAR_OFF;
		}
	}
}

/*******************************************************************************
*Function name:fun_HEX2BCD
*Description  :set display buffer content
*Parameter    :none
*Return       :none
*******************************************************************************/
void fun_HEX2BCD(u16 DisplayNum)
{
	u8 i = 0,j = 4;

	if(fg_adc_inside_code){

		/* display inside code: ADC data */
		fun_DisplayLEDADCData();

	}else{

    	if(DisplayNum < 10){
    			fg_led_point1 = 1;
    			fg_led_point2 = 0;
    			gu8v_led_buffer[LED_NUM_QIAN] = LED_CHAR_OFF;
    			gu8v_led_buffer[LED_NUM_BAI]= LED_CHAR_OFF;
    			gu8v_led_buffer[LED_NUM_SHI]= DisplayNum/10;
    			gu8v_led_buffer[LED_NUM_GE] = DisplayNum%10;
    	}else{
    		fg_led_point1 = 1;
    		fg_led_point2 = 0;
    		if (DisplayNum < 100){
    			gu8v_led_buffer[LED_NUM_QIAN] = LED_CHAR_OFF;
    			gu8v_led_buffer[LED_NUM_BAI] = LED_CHAR_OFF;
    			j = LED_NUM_BAI;
    		}else if (DisplayNum < 1000){
    			gu8v_led_buffer[LED_NUM_QIAN] = LED_CHAR_OFF;
    			j = LED_NUM_QIAN;
    		}
    		else if (DisplayNum >= 1000)
    		{
    	//		DisplayNum %= 1000;
    		}

    		for(i=0;i<j;)
    		{
    			gu8v_led_buffer[i] = DisplayNum%10;
    			DisplayNum /= 10;
    			i++;
    		}
    	}
	}
}


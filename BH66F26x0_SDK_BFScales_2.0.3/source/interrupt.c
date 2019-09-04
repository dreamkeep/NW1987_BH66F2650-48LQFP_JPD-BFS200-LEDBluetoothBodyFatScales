//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : interrupt.c
// Description: BH66F26X0 interrupt function:for timing & LED scan.
//     Author : ghg
//   Customer : æ©∞ÿ(JingBai)
//Targer Board: æ©∞ÿ(JingBai):JPD-BFS200
//     Note   :Initial on 20190821
//*********************************************************************/

#include "common.h"
/**************************************************************

*Function name:isr_mf0
*Description  :interrupt: 2ms
*Parameter    :none
*Return       :none
***************************************************************/
DEFINE_ISR(isr_mf0, MuFunction0_VECTOR)
{
	_mf0f = 0;
	if(_stmaf){
        _stmaf = 0;

		fg_time_2ms = 1;

		gu8v_time_100ms++;
	    if(C_TIME_100MS <= gu8v_time_100ms){
		    gu8v_time_100ms = 0;
		    fg_time_100ms = 1;

		    fg_time_200ms_t = 1;

			/* ‰∏≤Âè£ÂèëÈÄÅÂë®ÊúüËÆ°Êï?*/
			if(C_TIMEING_CYCLE100MS >= gu8v_UartTxCycle){
				gu8v_UartTxCycle++;
			}else{
				gbv_IsBusyUartTx = 0;
			}

			/* ‰∏≤Âè£Êé•Êî∂Ë∂ÖÊó∂Ê£ÄÊµ?*/
			if(!gbv_UartRxSuccess && fg_uart_rec_start){
				if(gu8v_TBRxTimeOutCnt){
					gu8v_TBRxTimeOutCnt--;
				}else{
					//gbv_UartRxSuccess = 1;
					fg_uart_rec_start = 0;
				}
			}

            /* scale power on:  all the led turn on for 3s*/
			if(!fg_time_3s){
				gu8v_led_delay3s++;
				if(C_TIME_3S <= gu8v_led_delay3s){
					gu8v_led_delay3s = 0;
					fg_time_3s = 1;
				}
			}

			if(fg_led_timing){
				if(!fg_led_delay){
					if(gu8v_led_delay)
						gu8v_led_delay--;
					else
						fg_led_delay = 1;
				}
				if(fg_led_delay){
					gu8v_time_dalay++;
					if(gu8v_led_speed <= gu8v_time_dalay){
						gu8v_time_dalay = 0;
						if(gu8v_howtimes){
							fg_led_flash = !fg_led_flash;
							if(fg_led_flash){
								fg_led_change = !fg_led_change;
							}
							gu8v_howtimes--;
						}else{
							fg_led_delay = 0;
							fg_led_timing = 0;
							fg_led_flash = 0;
							fg_led_change = 0;
						}
					}
				}
			}else{
				if(gu8v_timed_shutdown){
					gu8v_timed_shutdown--;
					fg_time_10s = 0;
					fg_led_flash = 0;
				}else{
					fg_time_10s = 1;
				}
			}
	    }


	    //*********** LED *************/
        led_display_scan();


	}
}




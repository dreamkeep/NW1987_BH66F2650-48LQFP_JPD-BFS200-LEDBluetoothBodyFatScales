
#include "common.h"

#define P_MOVEKEY            _pa4
#define P_MOVEKEY_C          _pac4
#define P_MOVEKEY_PU         _papu4

#define C_KEY_DEBOUNCED      30   /* 30*2MS = 60MS */
#define C_KEY_LONG_PRESS     1000 /* 1000*2MS = 2S */
#define C_KEY_COUNT          3
#define C_KEY_TIME_xS        2500 /* 2500*2MS = 5S */

volatile bit gbv_key_press;
volatile bit gbv_key_long_press;
volatile bit gbv_repeat_timing;

u16 u16_key_debounced;
u16 u16_key_timing;
u8 u8_key_press_cnt; /* short key count*/


/*******************************************************************************
*Function name:key_scan
*Description  :1.unit change;  2.display inside code.(ADC data:Hex)
*Parameter    :none
*Return       :none
*******************************************************************************/
void key_scan(void)
{

	if(fg_time_2ms){
		fg_time_2ms = 0;

        /* Pull up input */
		P_MOVEKEY_C = 1;
		P_MOVEKEY_PU = 1;

    	if(!P_MOVEKEY){
            u16_key_debounced++;
    		if(C_KEY_DEBOUNCED <= u16_key_debounced){
    			if(!gbv_key_press){
    				gbv_key_press = 1;
    			}else{
    			    if(C_KEY_LONG_PRESS <= u16_key_debounced){
						if(!gbv_key_long_press){
							gbv_key_long_press = 1;
							if(u8_key_press_cnt >= C_KEY_COUNT){
								u8_key_press_cnt = 0;
								fg_adc_inside_code ^= 1;
							}
						}
    				}
    			}
    		}
    	}else{
    	    if(gbv_key_long_press){
//    			if(u8_key_press_cnt >= C_KEY_COUNT){
//    				u8_key_press_cnt = 0;
//    				fg_adc_inside_code ^= 1;
//    			}

    		}else if(gbv_key_press){

                /* weight unit change */
        		if(UNIT_KG == gu8_weigh_targeunit){
        			gu8_weigh_targeunit = UNIT_LB;
        		}else{
        			gu8_weigh_targeunit = UNIT_KG;
        		}
        		fun_weight_unit_change(gu16_weigh);

    			if(!gbv_repeat_timing){
    				u8_key_press_cnt = 1;;
    				gbv_repeat_timing = 1;
    			}else{
    				u8_key_press_cnt++;
    			}
				u16_key_timing = 0;
    		}
            u16_key_debounced = 0;
    		gbv_key_press = 0;
    		gbv_key_long_press = 0;
    	}

    	if(gbv_repeat_timing){
    		u16_key_timing++;
            if(C_KEY_TIME_xS <= u16_key_timing){
    			gbv_repeat_timing = 0;
    		}
    	}else{
    		u16_key_timing = 0;
    		u8_key_press_cnt = 0;
    	}
	}

}



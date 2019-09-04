
#include "common.h"

u8  gu8_display_mode;//LED鏄剧ず妯″紡.
u16 gu16_display_weight;//宸茬粡杞崲鍗曚綅鍚庣殑鏄剧ず浣撻噸鏁版嵁.
u8 gu8_weigh_targeunit;//鐩爣浣撻噸鍗曚綅.

/* LED 闂儊锛屾樉绀猴紝瀹氭椂绛夊彉閲? */
volatile u8  gu8v_time_dalay; //寤舵椂gu8v_time_dalay*100Ms鍚庡紑濮嬫墽琛岄棯鐑?
volatile u8  gu8v_howtimes;  //LED闂儊娆℃暟.
volatile u8  gu8v_led_speed; //闂儊鐨勫揩鎱?
volatile u8  gu8v_led_delay; //寤舵椂delay鏃堕棿鍚庢墠鎵ц闂儊.
volatile u8  gu8v_led_delay3S;//寮�鏈篖ED鍏ㄦ樉3s璁℃椂.
volatile u8  gu8v_timed_shutdown;//瀹氭椂鍏虫満璁℃椂.


#if(_BH66F26X0_LIB_V == ENABLE)

/*******************************************************************************
*Function name:fun_weight_unit_change
*Description  :unit:50g(0.1jin).
*Parameter    :input:weigh,x*50g.
*Return       :none
*******************************************************************************/
void fun_weight_unit_change(u16 weigh)
{
	gu16_weigh = weigh;
	if(UNIT_KG == gu8_weigh_targeunit)
	{
		gu16_display_weight = (u32)weigh/2;//KG換算 符号强制转换，防止溢出
	}
	else if(UNIT_LB == gu8_weigh_targeunit)
	{
		gu16_display_weight = ((u32)weigh/2*(u32)22046/1000+5)/10 & 0xfffe;
	}
}

#else

/*******************************************************************************
*Function name:fun_weight_unit_change
*Description  :unit:10g(0.02jin).
*Parameter    :input:weigh;x*10g.
*Return       :none
*******************************************************************************/
void fun_weight_unit_change(u16 weigh)
{
	gu16_weigh = weigh;
	if(UNIT_KG == gu8_weigh_targeunit)
	{
		gu16_display_weight = (u32)weigh/10;
	}
	else if(UNIT_LB == gu8_weigh_targeunit)
	{
		gu16_display_weight = (u32)weigh*1000/4535; //LB換算
		/*说明:
			10(g) = 0.0220462(lb),0.1(lb) = 45.359237(g)

			 eg:
			 	若:weigh = 55
			 	则:weigh=55=550(g) -->因为此合泰库精度为10g，即1代表1*10=10(g);x*10=10x(g)
			 	计算:weigh*10000/45359=55*10000/45359
			 		取整数位等于12，代表1.2(lb)
		*/
	}
}
#endif


/*******************************************************************************
*Function name:fun_DisplayLEDADCData
*Description  :Internal code display.
*Parameter    :none
*Return       :none
*******************************************************************************/
void fun_DisplayLEDADCData()
{
	if (fg_time_200ms_t)
	{
		fg_time_200ms_t = 0;
		volatile __32_type displayADC;
		displayADC.u32 = SDKADCFilterData.Current;
		displayADC.u32 = displayADC.u32 / 16; //取16位
		fg_led_buffer_point_byte = 0x00;
		unsigned char i;
		for (i = 0; i < 4; i++)
		{
			gu8v_led_buffer[i] = displayADC.u32 % 16;
			displayADC.u32 /= 16;
		}
		//四位数码管，显示16进制内码值
	}
}


/*******************************************************************************
*Function name:set_led_flash_mode
*Description  :LED flash control.
*Parameter    :1.mode:dispaly mode.
*              2.ledflash: on or off，=0 no flash, =1 flash.
*              3.count:number of led flashes,=count*100MS.
*              4.speed:LED flashing speed.
*              5.delay:Delay to flash, =delay*100MS.
*              6.overtime:Timed shutdown, =100ms*(overtime+delay).
*Return       :none
*******************************************************************************/
void set_led_flash_mode(u8 mode, u8 ledflash, u8 count, u8 speed, u8 delay, u8 overtime)
{
	static u8 dispmode_backup = 0xaa;
	if(dispmode_backup != mode){
		dispmode_backup = mode;

		if(C_LED_FLASH_ON == ledflash){
			fg_led_delay = 0;
			fg_led_timing = 1;
			gu8v_time_dalay = 0;
			gu8v_howtimes = count;
			gu8v_led_speed = speed;
			gu8v_led_delay = delay;
		}else{
			fg_led_timing = 0;
			if(overtime)fg_led_flash = 0;
		}
		fg_led_change = 0;
		set_overtime2poweroff(overtime);
	}
}


/*******************************************************************************
*Function name:get_led_flash_status
*Description  :LED flash control.
*Parameter    :none
*Return       :led flash status
*******************************************************************************/
u8 get_led_flash_status(void)
{
	return fg_led_timing;
}


/*******************************************************************************
*Function name:set_display_mode
*Description  :Set LED display mode.
*Parameter    :dismode: display mode
*Return       :none
*******************************************************************************/
void set_display_mode(u8 dismode)
{
	gu8_display_mode = dismode;
}

//===============================================================
//function: 鑾峰彇鏄剧ず妯″紡.
//input   : NULL.
//output  : DISPLAY_POWERON ~ DISPLAY_XXX.
//description:.
//===============================================================
//u8 Get_DisplayMode(void)
//{
//	return gu8_display_mode;
//}


/*******************************************************************************
*Function name:fun_diaplay_mode
*Description  :LED display content.
*Parameter    :none
*Return       :none
*******************************************************************************/
void fun_diaplay_mode(void)
{
	switch(gu8_display_mode)
	{
		case DISPLAY_POWERON:
            set_led_all_buffer(1);
            /* Not shutdown, updata time. */
			set_overtime2poweroff(C_TIME_10S);
			set_led_flash_mode(DISPLAY_POWERON,C_LED_FLASH_OFF,0,0,C_TIME_3S,C_TIME_10S);
			break;

		case DISPLAY_LOWBATTERY:
			set_led_flash_mode(DISPLAY_LOWBATTERY,C_LED_FLASH_OFF,0,0,0,C_TIME_3S);
			gu8v_led_buffer[0] = LED_CHAR_OFF;
			gu8v_led_buffer[1] = LED_CHAR_O;
			gu8v_led_buffer[2] = LED_CHAR_L;
			gu8v_led_buffer[3] = LED_CHAR_OFF;
			fg_led_buffer_point_byte = 0x00;
			break;

		case DISPLAY_NOLOAD:
			fun_HEX2BCD(gu16_display_weight);
			set_led_flash_mode(DISPLAY_NOLOAD,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			break;

		case DISPLAY_LOADUP:
			fun_HEX2BCD(gu16_display_weight);
			set_led_flash_mode(DISPLAY_LOADUP,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			set_overtime2poweroff(C_TIME_10S);
			break;

		case DISPLAY_LOADFIX:
			fun_HEX2BCD(gu16_display_weight);
			if(fg_loadok){
				set_led_flash_mode(DISPLAY_LOADFIX,C_LED_FLASH_ON,C_LED_FLASH_CNT,C_TIME_05S,C_LED_FLASH_DELAY,C_TIME_10S);
				if(0 == get_led_flash_status()){
					fg_loadok = 0;
					if(fg_led_ble){
					    set_BHSDKState(ENTER_IMPEDANCE);
					    SDKImpedance.Channel = IMPEDANCE_CHANNEL_TWOLEGS;
					   SDKImpedance.flag.b.IsUseTwoArms = 0;
					}else{
						set_BHSDKState(ENTER_WEIGHT_NORMAL);
					}
				}
			}
			break;

		case DISPLAY_LOADDOWN:
			set_led_flash_mode(DISPLAY_LOADDOWN,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			break;

		case DISPLAY_OVERLOAD:
			set_led_flash_mode(DISPLAY_OVERLOAD,C_LED_FLASH_OFF,0,0,0,C_TIME_5S);
			gu8v_led_buffer[0] = LED_CHAR_OFF;
			gu8v_led_buffer[1] = LED_CHAR_R;
			gu8v_led_buffer[2] = LED_CHAR_R;
			gu8v_led_buffer[3] = LED_CHAR_E;
			fg_led_buffer_point_byte = 0x00;
			/* Until the start of send overweight*/
			if(!gbv_TxSDKWeightStatus){
				while(!fg_time_10s){
					gu8_worktasks = TASK_SLEEP;
					GCC_CLRWDT();
				}
			}
			break;

		case DISPLAY_IMPEDANCEING:
			#if 1
			gu8v_led_buffer[0] = LED_CHAR_OFF;
			gu8v_led_buffer[1] = LED_CHAR__;
			gu8v_led_buffer[2] = LED_CHAR__;
			gu8v_led_buffer[3] = LED_CHAR_OFF;
			fg_led_buffer_point_byte = 0x00;
			#else
			fun_HEX2BCD(gu16_display_weight);
			#endif
			set_led_flash_mode(DISPLAY_IMPEDANCEING,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			set_overtime2poweroff(C_TIME_10S);
			break;

		case DISPLAY_IMPEDANCE_FINISH:
			switch(gu16_impedence_data)
			{
				case IMPEDANCE_ERR_NOTEST:
				case IMPEDANCE_ERR_ABNORMAL:
				case IMPEDANCE_ERR_OUTRANGE:
                    gu16_impedence_data = 0x00;
					break;

				default:
					gbv_TxSDKImpedanceStatus = 1;
					break;
			}
			set_BHSDKState(ENTER_WEIGHT_NORMAL);
			set_led_flash_mode(DISPLAY_IMPEDANCE_FINISH,C_LED_FLASH_OFF,C_LED_FLASH_IMP,C_TIME_05S,0,C_TIME_10S);
			break;

        case DISPLAY_UNLOCK_WEIGHT:
			fun_HEX2BCD(gu16_display_weight);
			set_led_flash_mode(DISPLAY_UNLOCK_WEIGHT,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
            break;

		case DISPLAY_CAL0:
			fun_HEX2BCD(gu16_display_weight);
			set_led_flash_mode(DISPLAY_CAL0,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			set_overtime2poweroff(C_TIME_10S);
			break;

//		case DISPLAY_CAL1:
//			fun_HEX2BCD(gu16_display_weight);
//			set_led_flash_mode(DISPLAY_CAL1,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
//			break;

//		case DISPLAY_CAL2:
//			fun_HEX2BCD(gu16_display_weight);
//			set_led_flash_mode(DISPLAY_CAL2,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
//			break;

//		case DISPLAY_CAL3:
//			fun_HEX2BCD(gu16_display_weight);
//			set_led_flash_mode(DISPLAY_CAL3,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
//			break;

		case DISPLAY_CALPASS:
			fg_led_buffer_point_byte = 0x00;
			while(1){
				gu8v_led_buffer[LED_NUM_QIAN] = LED_CHAR_P;//'P'
				gu8v_led_buffer[LED_NUM_BAI]= LED_CHAR_A;  //'A'
				gu8v_led_buffer[LED_NUM_SHI]= LED_CHAR_5;  //'S'
				gu8v_led_buffer[LED_NUM_GE] = LED_CHAR_5;  //'S'
				GCC_CLRWDT();
			}
			break;

		case DISPLAY_CALFAIL:
			fg_led_buffer_point_byte = 0x00;
			while(1){
				gu8v_led_buffer[LED_NUM_QIAN] = LED_CHAR_F;//'F'
				gu8v_led_buffer[LED_NUM_BAI]= LED_CHAR_I;  //'I'
				gu8v_led_buffer[LED_NUM_SHI]= LED_CHAR_A;  //'A'
				gu8v_led_buffer[LED_NUM_GE] = LED_CHAR_5;  //'S'
				GCC_CLRWDT();
			}
			break;

		default:
		case DISPLAY_ALLOFF:
			set_led_all_buffer(0);
			set_led_flash_mode(DISPLAY_ALLOFF,C_LED_FLASH_OFF,0,0,0,C_TIME_10S);
			break;
	}

	fun_bluetooth_detected();

}


/*******************************************************************************
*Function name:fun_bluetooth_detected
*Description  :Detect APP connection Bluetooth status.
*Parameter    :none
*Return       :none
*******************************************************************************/
void fun_bluetooth_detected(void)
{
	if((DISPLAY_POWERON != gu8_display_mode) && (DISPLAY_ALLOFF != gu8_display_mode)){
		if(fg_time_100ms){
			fg_time_100ms = 0;
			if(!P_BLE_ST && !P_BLE_EN){
				if(C_BLE_COUNT <= gu8_ble_count++){
					gu8_ble_count = 0;
					fg_led_ble = 1;
				}
			}else{
				gu8_ble_count = 0;
				fg_led_ble = 0;
			}
		}
	}
}


/*******************************************************************************
*Function name:set_overtime2poweroff
*Description  :Update shutdown time.
*Parameter    :overtime: time=overtime*100Ms
*Return       :none
*******************************************************************************/
void set_overtime2poweroff(u8 overtime)
{
	gu8v_timed_shutdown = overtime;
}


/*******************************************************************************
*Function name:is_timedshutdown
*Description  :ready to go to sleep.
*Parameter    :none
*Return       :none
*******************************************************************************/
void is_timedshutdown(void)
{
	if(fg_time_10s){
		fg_time_10s = 0;
		gu8_worktasks = TASK_SLEEP;
	}
}


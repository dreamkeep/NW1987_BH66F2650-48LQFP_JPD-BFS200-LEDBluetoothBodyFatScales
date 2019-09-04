
//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : bodyfatscales_task..c
// Description: JPD-BFS200 body fat scale working status
//     Author : ghg
//   Customer : 京柏(JingBai)
//Targer Board: 京柏(JingBai):JPD-BFS200
//     Note   :Initial on 20190821
//*********************************************************************/

#include "common.h"

u8  gu8_worktasks;//体脂称工作模式.
u16 gu16_weigh;    //显示体重前的原始体重,精度为0.1jin的体重数据。
u16 gu16_memory_weigh;//200g记忆体重，精度为0.1jin的体重数据。
u16 gu16_currentweigh;
u16 gu16_impedence_data;//原始阻抗数据.
u16 gu16_BodyFatRate;//来自蓝牙的体脂率.

/**************************************************************
*Function name:set_BHSDKState
*Description  :user set BHSDKState, the scale status.
*Parameter    :none
*Return       :none
***************************************************************/
void set_BHSDKState(u8 state)
{
	BHSDKState = state;
}

u8 is_BHSDKState_change(void)
{
	static u8 BHSDKState_old = ENTER_SDK_NONE;
	if(BHSDKState_old != BHSDKState){
		BHSDKState_old = BHSDKState;
		return 1;
	}
	return 0;
}


//void fun_DisplayMode_LoadFix(void)
//{
//	if(is_BHSDKState_change()){
//		fun_weight_unit_change(SDKWeight.DataStable);
//		set_display_mode(DISPLAY_LOADFIX);
//	}
//}


//void fun_DisplayMode_LoadDown(void)
//{
//	fun_weight_unit_change(SDKWeight.DataStable);
//	set_display_mode(DISPLAY_LOADDOWN);
//}

//void fun_DisplayMode_OverLoad(void)
//{
//	set_display_mode(DISPLAY_OVERLOAD);
//}

//void fun_DisplayMode_ImpedanceFinish(void)
//{
//	set_display_mode(DISPLAY_IMPEDANCE_FINISH);
//	gu16_impedence_data = SDKImpedance.Data;
//}

/*******************************************************************************
*Function name:task_bodyfatscales
*Description  :1.Complete UI or other actions base on 'BHSDKState' status.
*             :2.All working states of the scale.
*Parameter    :none
*Return       :none
*******************************************************************************/
void task_bodyfatscales(void)
{
	//依據BHSDKState完成UI或者其他動作
	switch (BHSDKState)
	{
		case STATE_WEIGHT_PREPARE:	// 稱重準備中
			// 切換為ENTER_WEIGHT_NORMAL后,通常有300ms左右稱重準備時間
			break;

		case STATE_WEIGHT_NOLOAD:// 空載/當前重量小於最小稱重重量
			// fun_DisplayMode_NoLoad();此處寫User UI,比如顯示臨時重量SDKWeight.DataCurrent
            if(is_BHSDKState_change()){
                fun_weight_unit_change(SDKWeight.DataCurrent);
                set_display_mode(DISPLAY_NOLOAD);

				if(fg_manual_readycal){
					fg_manual_readycal = 0;
					set_BHSDKState(ENTER_WEIGHT_CAL);
				}
            }
			break;

		case STATE_WEIGHT_LOADUP:	// 有上稱動作/鎖定狀態下加載解鎖重量,重量由0點變成>最小稱重重量
		    // fun_DisplayMode_LoadUp();此處寫User UI,比如顯示臨時重量SDKWeight.DataCurrent
		    fun_weight_unit_change(SDKWeight.DataCurrent);
		    set_display_mode(DISPLAY_LOADUP);
		    gbv_TxSDKWeightStatus = 1;
		    gu8_data_type = DATA_TYPE_ING;
		    fg_loadok = 1;
		break;

		case STATE_WEIGHT_LOADOK:	// 完成一次稱重測量
            // fun_DisplayMode_LoadOk();此處寫User UI,比如開始閃爍穩定重量SDKWeight.DataState等
			if(C_UNLOCK_WEIGHT >= SDKWeight.DataStable){
				fun_weight_unit_change(SDKWeight.DataCurrent);
				set_display_mode(DISPLAY_UNLOCK_WEIGHT);
			}else{
				if(is_BHSDKState_change()){
					fun_weight_unit_change(SDKWeight.DataStable);
					set_display_mode(DISPLAY_LOADFIX);
				}
			}
			break;
		case STATE_WEIGHT_LOADFIX:	// 完成一次稱重測量后重量穩定沒有解鎖
			// fun_DisplayMode_LoadFix();此處寫User UI,,比如開始閃爍穩定重量SDKWeight.DataState等
			gu8v_time_30s = C_TIME_30S;
			if(!fg_memory_200g){
				fg_memory_200g = 1;
				gu16_memory_weigh = SDKWeight.DataStable;
			}else{
				if(fun_unsigned32BitABS(gu16_memory_weigh,SDKWeight.DataStable) <= C_REMEMBER_200G){
					GCC_NOP();
				}else{
					gu16_memory_weigh = SDKWeight.DataStable;
				}
			}
			if(C_UNLOCK_WEIGHT >= SDKWeight.DataStable){
				if(fun_unsigned32BitABS(SDKWeight.DataCurrent,gu16_currentweigh) > C_REMEMBER_200G){
					gu16_currentweigh = SDKWeight.DataCurrent;
					fun_weight_unit_change(SDKWeight.DataCurrent);
					set_overtime2poweroff(C_TIME_10S);//如果重量有变化更新时间不去睡眠.
				}else{
					fun_weight_unit_change(gu16_memory_weigh);
				}
				set_display_mode(DISPLAY_UNLOCK_WEIGHT);
			}else{
				if(is_BHSDKState_change()){
					gbv_TxSDKWeightStatus = 1;
					gu8_data_type = DATA_TYPE_LOCK;
				}
				fun_weight_unit_change(gu16_memory_weigh);
				set_display_mode(DISPLAY_LOADFIX);

				//Ready to manual cal
				if(fg_manual_cal){
					if(C_WEIGHT_MANUALCAL < gu16_memory_weigh){
						fg_manual_cal = 0;
						fg_manual_readycal = 1;
					}
				}
			}

			break;
		case STATE_WEIGHT_LOADDOWN:	// 下秤動作
            // fun_DisplayMode_LoadDown();此處寫User UI,,比如顯示鎖定SDKWeight.DataState等
			if(C_UNLOCK_WEIGHT >= SDKWeight.DataStable){
				fun_weight_unit_change(SDKWeight.DataCurrent);
				set_display_mode(DISPLAY_UNLOCK_WEIGHT);
				if(is_BHSDKState_change()){
					gbv_TxSDKWeightStatus = 1;
				}
			}else{
				if(is_BHSDKState_change()){
					fun_weight_unit_change(gu16_memory_weigh);
					set_display_mode(DISPLAY_LOADDOWN);
				}
			}

			if(fg_manual_readycal){
				fg_manual_readycal = 0;
				set_BHSDKState(ENTER_WEIGHT_CAL);
			}
			break;
		case STATE_WEIGHT_OVERLOAD:	// 超重,當前重量大於最大稱重重量
			// fun_DisplayMode_OverLoad();此處寫User UI,,比如顯示-OL-等
			fun_weight_unit_change(SDKWeight.DataCurrent);
			set_display_mode(DISPLAY_OVERLOAD);
			if(is_BHSDKState_change()){
				gbv_TxSDKWeightStatus = 1;
				gu8v_UartTxCycle = C_TIMEING_CYCLE100MS;
			}
			gu8_data_type = DATA_TYPE_OVERLOAD;
			break;
		case STATE_IMPEDANCE_REFERENCE1:// 正在量測參考電阻1
		case STATE_IMPEDANCE_REFERENCE2:// 正在量測參考電阻2
		case STATE_IMPEDANCE_CHECKBODY: // 判斷是否有人體
		case STATE_IMPEDANCE_RX:		// 正在量測待測阻抗
			// fun_DisplayMode_Impedanceing();此處寫User UI,,比如跑----/oooo提示阻抗測量中
			set_display_mode(DISPLAY_IMPEDANCEING);
            gu16_impedence_data= SDKImpedance.Data;
			break;
		case STATE_IMPEDANCE_FINISH:	// 阻抗量測結束,此時可以讀取gu16v_CurrentImpedance_ohm
			// fun_DisplayMode_ImpedanceFinish();
			//BHSDKState = ENTER_IMPEDANCE;

			gu8_data_type = DATA_TYPE_LOCK;
			gu16_impedence_data = SDKImpedance.Data;
			set_display_mode(DISPLAY_IMPEDANCE_FINISH);
		    break;
		case STATE_AUTOON_FASTMODE:		// 快速ADC自動上稱判斷
		case STATE_AUTOON_SLOWMODE:		// 慢速ADC自動上稱判斷
			// 通常這個時候無任何UI
			break;
		case STATE_AUTOON_PASS: 		// 自動上稱OK
			// 此時可以點亮顯示,并切換到普通稱重模式進行MCU的正常工作
			gu8_worktasks = TASK_WEIGHT_AUTOON;
			break;
		case STATE_AUTOON_FAIL: 		// 自動上秤失敗,此時請繼續讓 MCU 進入HALT狀態
			//fun_BodyFatScalesSDK_PowerDown();
			//GCC_HALT();
			gu8_worktasks = TASK_SLEEP;
			break;
		case STATE_WEIGHT_CAL0: // 正在標定零點
			// fun_DisplayMode_CAL0();此處寫User UI,,比如提示CAL 0kg
			fun_weight_unit_change(0);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL1:	// 正在標定第1點
			// fun_DisplayMode_CAL1();此處寫User UI,,比如提示CAL 50kg
			fun_weight_unit_change(C_WEIGHT_CAL1);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL2:	// 正在標定第2點
			// fun_DisplayMode_CAL2();此處寫User UI,,比如提示CAL 100kg
			fun_weight_unit_change(C_WEIGHT_CAL2);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL3:	// 正在標定第3點
			// fun_DisplayMode_CAL3();此處寫User UI,,比如提示CAL 150kg
			fun_weight_unit_change(C_WEIGHT_CAL3);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CALPASS:	// 標定成功
			// fun_DisplayMode_CALPASS();此處寫User UI,,比如提示PASS
			set_display_mode(DISPLAY_CALPASS);
			break;
		case STATE_WEIGHT_CALFAIL:	// 標定失敗
			// fun_DisplayMode_CALFAIL();此處寫User UI,,比如提示FIAS
			set_display_mode(DISPLAY_CALFAIL);
			break;
		default:
			break;
	}

	is_BHSDKState_change();
}

/********************************************************************
Function: 上电开机才进入启动模式.
INPUT	:
OUTPUT	:
NOTE	:LED全显3S,3S后直到上电后秤归零完成才切换到正常称重模式.
********************************************************************/
void task_scalesstartup(void)
{
	set_display_mode(DISPLAY_POWERON);
	if(fg_time_3s){
		if(!SDKWeight.flag.b.IsNeedTare){
			set_led_all_buffer(0);
			gu8_worktasks = TASK_SCALES;
			BHSDKState = ENTER_WEIGHT_NORMAL;
		}
	}
}

/*******************************************************************************
*Function name:task_scaleslowbattry
*Description  :Low power mode,LED show "LO" and ready to go to sleep.
*Parameter    :none
*Return       :none
*******************************************************************************/
void task_scaleslowbattry(void)
{
	set_display_mode(DISPLAY_LOWBATTERY);
}


/*******************************************************************************
Function: 睡眠模式.
INPUT	:
OUTPUT	:
NOTE	:睡眠初始化，并打开看门狗每1S唤醒检测是否上称成功，上称失败则继续睡眠.
*******************************************************************************/
void task_scales2sleep(void)
{
	SET_EMI_DISABEL();

	/*STM off */
	SETSTM_OFF();
	poweron_gpio_init();

    /* led all off */
	set_display_mode(DISPLAY_ALLOFF);
	led_init();

	/* Watchdog wakes up for a second */
	SETWDTTIME_1000MS();

	/* UART disable */
	SET_UART_DISABLE();
	SET_UART_PIN_DISABLE();

	/* Bluetooth Disable */
    P_BLE_EN = HIGH;

	fg_time_byte = 0x00;
    fg_led_flag_byte = 0x00;
    fg_flag3_byte = 0x00;
	fg_led_buffer_point_byte = 0x00;

	set_overtime2poweroff(C_TIME_10S);

	/* 200g memory function,timming 30s*/
	if(gu8v_time_30s){
		gu8v_time_30s--;
	}else{
		fg_memory_200g = 0;
	}

	fun_BodyFatScalesSDK_PowerDown();

	/* sleep0 mode */
	_fhiden = 0;
	_fsiden = 0;/* if wdt enable,fLIRC = on. */
	GCC_NOP();
	GCC_NOP();
	GCC_HALT();
}

/*******************************************************************************
*Function name:task_scaleswakeup
*Description  :Wakeup mode,init some variables, set the scale to normal weight.
*Parameter    :none
*Return       :none
*******************************************************************************/
void task_scaleswakeup(void)
{
    /* normal weight */
	gu8_worktasks = TASK_SCALES;
	BHSDKState = ENTER_WEIGHT_NORMAL;

	/* Enable bluetooth */
	P_BLE_EN = LOW;
	gu8_ble_count = 0;

	/* UART Enable */
	SET_UART_PIN_PA5PA6();
	SET_UART_ENABLE();
	gbv_UartRxSuccess = 0;
	gbv_IsBusyUartTx = 0;

    /* 200g memory function */
	gu8v_time_30s = C_TIME_30S;

	/* STM Enable */
	SETSTM_TIMER2MS();
	SETSTM_ISRENABLE();
	SETSTM_ON();
	SET_EMI_ENABLE();
}


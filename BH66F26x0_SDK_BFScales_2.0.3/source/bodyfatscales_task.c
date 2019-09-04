
//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : bodyfatscales_task..c
// Description: JPD-BFS200 body fat scale working status
//     Author : ghg
//   Customer : ����(JingBai)
//Targer Board: ����(JingBai):JPD-BFS200
//     Note   :Initial on 20190821
//*********************************************************************/

#include "common.h"

u8  gu8_worktasks;//��֬�ƹ���ģʽ.
u16 gu16_weigh;    //��ʾ����ǰ��ԭʼ����,����Ϊ0.1jin���������ݡ�
u16 gu16_memory_weigh;//200g�������أ�����Ϊ0.1jin���������ݡ�
u16 gu16_currentweigh;
u16 gu16_impedence_data;//ԭʼ�迹����.
u16 gu16_BodyFatRate;//������������֬��.

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
	//����BHSDKState���UI������������
	switch (BHSDKState)
	{
		case STATE_WEIGHT_PREPARE:	// �Q�؜ʂ���
			// �ГQ��ENTER_WEIGHT_NORMAL��,ͨ����300ms���ҷQ�؜ʂ�r�g
			break;

		case STATE_WEIGHT_NOLOAD:// ���d/��ǰ����С���С�Q������
			// fun_DisplayMode_NoLoad();��̎��User UI,�����@ʾ�R�r����SDKWeight.DataCurrent
            if(is_BHSDKState_change()){
                fun_weight_unit_change(SDKWeight.DataCurrent);
                set_display_mode(DISPLAY_NOLOAD);

				if(fg_manual_readycal){
					fg_manual_readycal = 0;
					set_BHSDKState(ENTER_WEIGHT_CAL);
				}
            }
			break;

		case STATE_WEIGHT_LOADUP:	// ���ϷQ����/�i����B�¼��d���i����,������0�c׃��>��С�Q������
		    // fun_DisplayMode_LoadUp();��̎��User UI,�����@ʾ�R�r����SDKWeight.DataCurrent
		    fun_weight_unit_change(SDKWeight.DataCurrent);
		    set_display_mode(DISPLAY_LOADUP);
		    gbv_TxSDKWeightStatus = 1;
		    gu8_data_type = DATA_TYPE_ING;
		    fg_loadok = 1;
		break;

		case STATE_WEIGHT_LOADOK:	// ���һ�ηQ�؜y��
            // fun_DisplayMode_LoadOk();��̎��User UI,�����_ʼ�W�q��������SDKWeight.DataState��
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
		case STATE_WEIGHT_LOADFIX:	// ���һ�ηQ�؜y�������������]�н��i
			// fun_DisplayMode_LoadFix();��̎��User UI,,�����_ʼ�W�q��������SDKWeight.DataState��
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
					set_overtime2poweroff(C_TIME_10S);//��������б仯����ʱ�䲻ȥ˯��.
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
		case STATE_WEIGHT_LOADDOWN:	// �³ӄ���
            // fun_DisplayMode_LoadDown();��̎��User UI,,�����@ʾ�i��SDKWeight.DataState��
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
		case STATE_WEIGHT_OVERLOAD:	// ����,��ǰ����������Q������
			// fun_DisplayMode_OverLoad();��̎��User UI,,�����@ʾ-OL-��
			fun_weight_unit_change(SDKWeight.DataCurrent);
			set_display_mode(DISPLAY_OVERLOAD);
			if(is_BHSDKState_change()){
				gbv_TxSDKWeightStatus = 1;
				gu8v_UartTxCycle = C_TIMEING_CYCLE100MS;
			}
			gu8_data_type = DATA_TYPE_OVERLOAD;
			break;
		case STATE_IMPEDANCE_REFERENCE1:// �������y�������1
		case STATE_IMPEDANCE_REFERENCE2:// �������y�������2
		case STATE_IMPEDANCE_CHECKBODY: // �Д��Ƿ������w
		case STATE_IMPEDANCE_RX:		// �������y���y�迹
			// fun_DisplayMode_Impedanceing();��̎��User UI,,������----/oooo��ʾ�迹�y����
			set_display_mode(DISPLAY_IMPEDANCEING);
            gu16_impedence_data= SDKImpedance.Data;
			break;
		case STATE_IMPEDANCE_FINISH:	// �迹���y�Y��,�˕r�����xȡgu16v_CurrentImpedance_ohm
			// fun_DisplayMode_ImpedanceFinish();
			//BHSDKState = ENTER_IMPEDANCE;

			gu8_data_type = DATA_TYPE_LOCK;
			gu16_impedence_data = SDKImpedance.Data;
			set_display_mode(DISPLAY_IMPEDANCE_FINISH);
		    break;
		case STATE_AUTOON_FASTMODE:		// ����ADC�Ԅ��ϷQ�Д�
		case STATE_AUTOON_SLOWMODE:		// ����ADC�Ԅ��ϷQ�Д�
			// ͨ���@���r��o�κ�UI
			break;
		case STATE_AUTOON_PASS: 		// �Ԅ��ϷQOK
			// �˕r�����c���@ʾ,���ГQ����ͨ�Q��ģʽ�M��MCU����������
			gu8_worktasks = TASK_WEIGHT_AUTOON;
			break;
		case STATE_AUTOON_FAIL: 		// �Ԅ��ϳ�ʧ��,�˕rՈ�^�m׌ MCU �M��HALT��B
			//fun_BodyFatScalesSDK_PowerDown();
			//GCC_HALT();
			gu8_worktasks = TASK_SLEEP;
			break;
		case STATE_WEIGHT_CAL0: // ���ژ˶����c
			// fun_DisplayMode_CAL0();��̎��User UI,,������ʾCAL 0kg
			fun_weight_unit_change(0);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL1:	// ���ژ˶���1�c
			// fun_DisplayMode_CAL1();��̎��User UI,,������ʾCAL 50kg
			fun_weight_unit_change(C_WEIGHT_CAL1);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL2:	// ���ژ˶���2�c
			// fun_DisplayMode_CAL2();��̎��User UI,,������ʾCAL 100kg
			fun_weight_unit_change(C_WEIGHT_CAL2);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CAL3:	// ���ژ˶���3�c
			// fun_DisplayMode_CAL3();��̎��User UI,,������ʾCAL 150kg
			fun_weight_unit_change(C_WEIGHT_CAL3);
			set_display_mode(DISPLAY_CAL0);
			break;
		case STATE_WEIGHT_CALPASS:	// �˶��ɹ�
			// fun_DisplayMode_CALPASS();��̎��User UI,,������ʾPASS
			set_display_mode(DISPLAY_CALPASS);
			break;
		case STATE_WEIGHT_CALFAIL:	// �˶�ʧ��
			// fun_DisplayMode_CALFAIL();��̎��User UI,,������ʾFIAS
			set_display_mode(DISPLAY_CALFAIL);
			break;
		default:
			break;
	}

	is_BHSDKState_change();
}

/********************************************************************
Function: �ϵ翪���Ž�������ģʽ.
INPUT	:
OUTPUT	:
NOTE	:LEDȫ��3S,3S��ֱ���ϵ��ӹ�����ɲ��л�����������ģʽ.
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
Function: ˯��ģʽ.
INPUT	:
OUTPUT	:
NOTE	:˯�߳�ʼ�������򿪿��Ź�ÿ1S���Ѽ���Ƿ��ϳƳɹ����ϳ�ʧ�������˯��.
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


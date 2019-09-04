#include "common.h"

#define EEPROM_ADDR_START 0x01		// EEPROM 存儲開始位置
#define EEPROM_DATA_CALID_CODE 0xAA // 校準成功標誌數據,偵測到此數據,認為校準成功
/**************************************************************
*Function name:user_initial
*Description  :user config init
*Parameter    :none
*Return       :none
***************************************************************/
void user_initial(void)
{
	set_overtime2poweroff(C_TIME_10S);
	fg_time_byte = 0x00;
	fg_led_flag_byte = 0x00;
	fg_flag3_byte = 0x00;
	fg_memory_byte = 0x00;

	set_led_all_buffer(0);
	set_display_mode(DISPLAY_ALLOFF);
	gu8_weigh_targeunit = UNIT_DEFAULT;
    gbv_IsBusyUartTx = 0;
    gbv_UartRxSuccess = 0;
    gu8v_led_delay3S = 0;

    /* Calibration method */
	if (Read_EEPROMByte(EEPROM_ADDR_START) == EEPROM_DATA_CALID_CODE){
		fg_manual_cal = 0;
		SDKWeightSetting.flag.b.IsAutoCalOn = WEIGHT_AUTOCAL;/* Enable auto cal*/
	}else{
		fg_manual_cal = 1;
		SDKWeightSetting.flag.b.IsAutoCalOn = 0;
	}

    gu8_worktasks = TASK_STARTUP;/* Power on */
	// 切換為稱重模式
	BHSDKState = ENTER_WEIGHT_NORMAL;
	SDKWeight.flag.b.IsNeedTare = 1;//*上電重量默認為0kg*/
	// 切換為阻抗模式
	 //BHSDKState = ENTER_IMPEDANCE;
	 //SDKImpedance.Channel = IMPEDANCE_CHANNEL_TWOLEGS;
	 //SDKImpedance.flag.b.IsUseTwoArms=0;
	// 切換為稱重模式
	/*BHSDKState = ENTER_WEIGHT_NORMAL;*/
	/*SDKWeight.flag.b.IsNeedTare = 1;			// 上電重量默認為0kg*/
	// 切換為標定模式
	// BHSDKState = ENTER_WEIGHT_CAL;

	SETSTM_TIMER2MS();
	SETSTM_ISRENABLE();
	SET_EMI_ENABLE();
}





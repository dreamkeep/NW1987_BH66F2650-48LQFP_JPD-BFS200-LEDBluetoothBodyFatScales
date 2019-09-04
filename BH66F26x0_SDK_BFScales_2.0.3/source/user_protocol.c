
#include "common.h"
volatile bit gbv_TxSDKWeightStatus;		// 發送SDK狀態的標誌,在需要發送的地方置位falg即可
volatile bit gbv_TxSDKImpedanceStatus;
volatile bit gbv_TxFinishStatus;

/*******************************************************************************
*function   : 异或校验和(OXR checksum).
*input      : *psurce：数据指针；     length:数据指针中的数据个数.
*output     : 异或校验和:
*description: 异或校验和:
           eg: FD 34 00 00.  则:XOR_checksum= 0xFD ^ 0x34 ^ 0x00 ^ 0x00 = 0xC9
*******************************************************************************/
u8 get_XOR_Checksum(volatile u8 * psurce, u8 length)
{

	u8 XOR_checksum = 0;
	while(length--){
		XOR_checksum ^= *psurce;
		psurce++;
	}

	return XOR_checksum;
}

#if _UART_DEBUG == ENABLE
void UART_SendData(u8* pdata, u8 len)
{
	volatile u8 i = 0;
	while(i < len){
		GCC_CLRWDT();
		if((_txif == 1)&&(_tidle == 1)){
			_acc = _usr;
			_txr_rxr = *pdata;
			i++;
			pdata++;
		}
	}
}
#endif

/*******************************************************************************
*Function name:fun_TxSDKImpedanceWeightStatus
*Description  :send weight & impedence.
*Parameter    :none.
*Return       :none
*******************************************************************************/
void fun_TxSDKImpedanceWeightStatus()
{
	gu8v_UartTxBuf[0] = SEND_HEAD_CODE;
	gu8v_UartTxBuf[1] = (gu16_impedence_data*10) & 0x00FF;
	gu8v_UartTxBuf[2] = ((gu16_impedence_data*10) & 0xFF00 )>>8;//;
 	gu8v_UartTxBuf[3] = (gu16_display_weight*10) & 0x00FF;
 	gu8v_UartTxBuf[4] = ((gu16_display_weight*10)& 0xFF00 )>>8;
	gu8v_UartTxBuf[5] = 0x00;//0x00;
	gu8v_UartTxBuf[6] = 0x00;//0x00;
	gu8v_UartTxBuf[7] = 0x00;//0x00;
	gu8v_UartTxBuf[8] = gu8_weigh_targeunit;
	gu8v_UartTxBuf[9] = gu8_data_type;//锁定数据.
	gu8v_UartTxBuf[10] = get_XOR_Checksum(gu8v_UartTxBuf,10);
	fun_UartStartTx(11);
}


/*******************************************************************************
*Function name:fun_UserProtocol
*Description  :User sends data and processes received data.
*Parameter    :none.
*Return       :none
*******************************************************************************/
void fun_UserProtocol()
{
	//	UART TX
	if((gu8v_UartTxCycle >= C_TIMEING_CYCLE100MS) && (!gbv_IsBusyUartTx))	// 建議加入定時發送，防止數據發送太快
	{
		 gu8v_UartTxCycle = 0;
		if (gbv_TxSDKWeightStatus)
		{
			gbv_TxSDKWeightStatus = 0;
			fun_TxSDKImpedanceWeightStatus();
		}
		else if (gbv_TxSDKImpedanceStatus)
		{
			gbv_TxSDKImpedanceStatus = 0;
			fun_TxSDKImpedanceWeightStatus();
            gu16_impedence_data = 0;
		}
	}

	// UART RX
	if (gbv_UartRxSuccess)	// UART RX
	{
		gbv_UartRxSuccess = 0;

		if(REC_HEAD_CODE == gu8v_UartRxBuf[POS_HEARD]){
			u8 XOR_checksum = get_XOR_Checksum(&gu8v_UartRxBuf[0],POS_CHECKSUM-1);
			if(XOR_checksum == gu8v_UartRxBuf[POS_CHECKSUM]){

				switch(gu8v_UartRxBuf[POS_CMDTYPE])
				{
					case CMDTYPE_LO:
						gu8_worktasks = TASK_LOWBATTERY;//test
						break;

					default:
						break;
				}

				//Unit conversion.
				if( UNIT_KG == gu8v_UartRxBuf[POS_UNIT])
					gu8_weigh_targeunit = UNIT_KG;
				else if( UNIT_LB == gu8v_UartRxBuf[POS_UNIT])
					gu8_weigh_targeunit = UNIT_LB;

				fun_weight_unit_change(gu16_weigh);

			}
		}

        u8 i = 0;
        for(i = 0; i < UART_LENGTH_RX; i++){
            gu8v_UartRxBuf[i] = 0;
        }
	}
}




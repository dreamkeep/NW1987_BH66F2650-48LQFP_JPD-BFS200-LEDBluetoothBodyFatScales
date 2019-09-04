#include "common.h"

volatile unsigned char 	gu8v_UartTxBuf[UART_LENGTH_TX];
volatile unsigned char 	gu8v_UartRxBuf[UART_LENGTH_RX];
volatile unsigned char  lu8v_TxBufoffset;   // TX 偏移�?
volatile unsigned char  lu8v_TxBufLength;   // TX 幀長度
volatile unsigned char  gu8v_UartTxCycle;   // TX 發送週期
volatile bit gbv_IsBusyUartTx;              // TX is busy

volatile unsigned char  lu8v_RxBufoffset;   // RX 偏移�?
volatile unsigned char  lu8v_RxBufLength;   // RX 幀長度
volatile unsigned char  gu8v_TBRxTimeOutCnt;// RX 幀timeout
volatile bit gbv_UartRxSuccess;             // Rx is ok,user can process the rx buf data

volatile unsigned char gu8_UartData;
volatile bit fg_uart_rec_start; /* =1 start recieving */

/********************************************************************
Function: Uart初始�?
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_UARTPowerOnInit()
{
    // 鏁告摎鍌宠几鏍煎紡瑷畾
	SET_UART_Format_D8_P0_S1();
    // 娉㈢壒鐜囪ō�?
	SET_UART_BAUTRATE_9600();
	SET_UART_ADDRESS_DISABLE();
	SET_UART_RECEIVER_IE_ENABLE();
	SET_UART_TRANSMITTER_IE_ENABLE();
	SET_UART_TRANSMITTER_EMPTY_ENABLE();
	_mf1e = 1;
	SET_UART_ENABLE();
	// UART0 IO

}

/********************************************************************
Function: Uart开始发�?
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void  fun_UartStartTx( unsigned char TxLength)
{
	lu8v_TxBufLength = TxLength;
	// Start TX
	gbv_IsBusyUartTx = 1; // uart 蹇欑�?
	lu8v_TxBufoffset = 1; // 鍥犵�?宸茬稉鐩存帴鐧奸€佷�?
	_acc = _usr;
	_txr_rxr = gu8v_UartTxBuf[0];
}


///********************************************************************
//Function: Uart Receive & Send
//INPUT	:
//OUTPUT:
//NOTE	:
//********************************************************************/
DEFINE_ISR(UART_ISR, UART_VECTOR)
{

	// 噪声干扰错误
	if (_nf)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}
	// 帧错�?
	if (_ferr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}
	// 溢出错误
	if (_oerr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
		lu8v_RxBufoffset = 0;
	}

	/* Receive*/
	if (_txif && gbv_IsBusyUartTx)
	{
		if (lu8v_TxBufoffset < lu8v_TxBufLength)
		{
			_txr_rxr = gu8v_UartTxBuf[lu8v_TxBufoffset];
		}
		else
		{
			if (_tidle)
			{
				gbv_IsBusyUartTx = 0;
			}
		}
		lu8v_TxBufoffset++;
	}

	_urf = 0;
	/* send */
	if (_rxif)
	{
		_rxif = 0;

		_acc = _usr;
		gu8_UartData = _txr_rxr;

        /* Waiting for the last data processing to complete */
		if(gbv_UartRxSuccess) {
			fg_uart_rec_start = 0;
			return;
		}

		gu8v_TBRxTimeOutCnt = C_TIMEING_TIMEOUT;

		if(!fg_uart_rec_start){
			switch(gu8_UartData)
			{
				case REC_HEAD_CODE:
					fg_uart_rec_start = 1;
					lu8v_RxBufLength = REC_BUF_DATA_LEN;
					break;
				default:
					lu8v_RxBufLength = REC_BUF_DATA_LEN;
					break;
			}
			lu8v_RxBufoffset = 0;
		}

		//start recive
		if(fg_uart_rec_start){

            /* Range check */
			if(fg_uart_rec_start && (lu8v_RxBufLength <= lu8v_RxBufoffset)){
				fg_uart_rec_start = 0;
				lu8v_RxBufoffset = 0;
			}

			gu8v_UartRxBuf[lu8v_RxBufoffset++] = gu8_UartData;

			if(lu8v_RxBufLength <= lu8v_RxBufoffset){
				lu8v_RxBufoffset = 0;
				gbv_UartRxSuccess = 1;
				fg_uart_rec_start = 0;
			}
		}
	}
}


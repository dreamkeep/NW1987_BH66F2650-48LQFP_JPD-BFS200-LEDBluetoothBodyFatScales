#ifndef BH66F26X0_UART_H__
#define BH66F26X0_UART_H__

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ����׃�� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define  UART_LENGTH_TX	11//20	// �f�h�������L��
#define  UART_LENGTH_RX	11//20	// �f�h�������L��
extern volatile unsigned char 	gu8v_UartTxBuf[UART_LENGTH_TX];
extern volatile unsigned char 	gu8v_UartRxBuf[UART_LENGTH_RX];
extern volatile unsigned char  lu8v_TxBufoffset;   // TX ƫ����
extern volatile unsigned char  lu8v_TxBufLength;   // TX ���L��
extern volatile unsigned char  gu8v_UartTxCycle;   // TX �l���L��
extern volatile bit gbv_IsBusyUartTx;              // TX is busy

extern volatile unsigned char  lu8v_RxBufoffset;   // RX ƫ����
extern volatile unsigned char  lu8v_RxBufLength;   // RX ���L��
extern volatile unsigned char  gu8v_TBRxTimeOutCnt;// RX ��timeout
extern volatile bit gbv_UartRxSuccess;             // Rx is ok,user can process the rx buf data

extern volatile bit fg_uart_rec_start;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ���ú��� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_UARTPowerOnInit();     // ��ʼ��
void fun_UartStartTx( unsigned char TxLength);  // �_ʼ�l��
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ �A���x@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_UART_ENABLE()	{ _uarten = 1;_rxen = 1;_txen = 1;_urf = 0;_txif = 0; _ure = 1; _emi = 1; _ure = 1;}
#define SET_UART_DISABLE()	{ _uarten = 0;_rxen = 0;_txen = 0;_ure = 0;}

/* UART IO-->PA5-Uart-Tx; PA6-Uart-Rx */
#define SET_UART_PIN_PA5PA6()  { _pas12 = 1; _pas13 = 1; _pas14 = 1; _pas15 = 1; _rxps1 = 0; _rxps0 = 0;}
#define SET_UART_PIN_DISABLE() { _pas12 = 0; _pas13 = 0; _pas14 = 0; _pas15 = 0; _rxps1 = 0; _rxps0 = 0;}

#define SET_UART_Format_D8_P0_S1()			{ _ucr1 = 0x00; }// ��ݔ8bit = (8bit-Data  None-Parity  None-Add)1bit-Stop
//#define SET_UART_Format_D7_PEVEN_S1()		{ _ucr1 = 0x20; }// ��ݔ8bit = (7bit-Data  Enen-Parity  None-Add)1bit-Stop
//#define SET_UART_Format_D7_PODD_S1()		{ _ucr1 = 0x30; }// ��ݔ8bit = (7bit-Data  Odd -Parity  None-Add)1bit-Stop
//#define SET_UART_Format_D9_P0_S1()			{ _ucr1 = 0x40; }// ��ݔ9bit = (9bit-Data  None-Parity  None-Add)1bit-Stop
//#define SET_UART_Format_D8_PEVEN_S1()		{ _ucr1 = 0x60; }// ��ݔ9bit = (8bit-Data  Even-Parity  None-Add)1bit-Stop
//#define SET_UART_Format_D8_PODD_S1()		{ _ucr1 = 0x70; }// ��ݔ9bit = (8bit-Data  Odd-Parity   None-Add)1bit-Stop

#define SET_UART_Format_D8_P0_S2()			{ _ucr1 = 0x00; }// ��ݔ8bit = (8bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_PEVEN_S2()		{ _ucr1 = 0x20; }// ��ݔ8bit = (7bit-Data  Enen-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_PODD_S2()		{ _ucr1 = 0x30; }// ��ݔ8bit = (7bit-Data  Odd -Parity  None-Add)2bit-Stop
#define SET_UART_Format_D9_P0_S2()			{ _ucr1 = 0x40; }// ��ݔ9bit = (9bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_PEVEN_S2()		{ _ucr1 = 0x60; }// ��ݔ9bit = (8bit-Data  Even-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_PODD_S2()		{ _ucr1 = 0x70; }// ��ݔ9bit = (8bit-Data  Odd-Parity   None-Add)2bit-Stop

#define SET_UART_WAKEUP_ENABLE()			    { _wake  = 1;}
#define SET_UART_WAKEUP_DISABLE()				{ _wake  = 0;}
#define SET_UART_ADDRESS_ENABLE()				{ _adden = 1;}
#define SET_UART_ADDRESS_DISABLE()				{ _adden = 0;}
#define SET_UART_RECEIVER_IE_ENABLE()			{ _rie   = 1;} // OERR(���)/RXIF(����Ч����)��λ�r�����Д����Iλ
#define SET_UART_RECEIVER_IE_DISABLE()			{ _rie   = 0;}
#define SET_UART_TRANSMITTER_IE_ENABLE()		{ _tiie = 1;} // TIDLE(�o������ݔ)��λ�������Д����Iλ
#define SET_UART_TRANSMITTER_IE_DISABLE()		{ _tiie = 0;}
#define SET_UART_TRANSMITTER_EMPTY_ENABLE()		{ _teie = 1;} // TXIF(�����Ѽ��d����λ��������TXR���)��λ�r�������Д����Iλ
#define SET_UART_TRANSMITTER_EMPTY_DISABLE()	{ _teie = 0;}

//#define _HIRC_4_8M_
#define _HIRC_4_0M_
#ifdef _HIRC_4_0M_
    #define SET_UART_BAUTRATE_300()			{ _brgh = 0; _brg = 207;}
    #define SET_UART_BAUTRATE_1200()		{ _brgh = 0; _brg = 51;}
    #define SET_UART_BAUTRATE_2400()		{ _brgh = 0; _brg = 25;}
    #define SET_UART_BAUTRATE_4800()		{ _brgh = 0; _brg =  12;}
    #define SET_UART_BAUTRATE_9600()		{ _brgh = 1; _brg =  25;}
    #define SET_UART_BAUTRATE_19200()		{ _brgh = 1; _brg =  12;}
    #define SET_UART_BAUTRATE_250000()		{ _brgh = 1; _brg =   0;}
#endif

#ifdef _HIRC_4_8M_
    #define SET_UART_BAUTRATE_300()			{ _brgh = 0; _brg = 207;}
    #define SET_UART_BAUTRATE_1200()		{ _brgh = 1; _brg = 207;}
    #define SET_UART_BAUTRATE_2400()		{ _brgh = 1; _brg = 103;}
    #define SET_UART_BAUTRATE_4800()		{ _brgh = 1; _brg =  51;}
    #define SET_UART_BAUTRATE_9600()		{ _brgh = 1; _brg =  25;}
    #define SET_UART_BAUTRATE_19200()		{ _brgh = 1; _brg =  12;}
    #define SET_UART_BAUTRATE_250000()		{ _brgh = 1; _brg =   0;}
#endif
#ifdef _HIRC_9_6M_
    #define SET_UART_BAUTRATE_1200()			{ _brgh = 0; _brg = 103;}
    #define SET_UART_BAUTRATE_2400()			{ _brgh = 1; _brg = 207;}
    #define SET_UART_BAUTRATE_4800()			{ _brgh = 1; _brg = 103;}
    #define SET_UART_BAUTRATE_9600()			{ _brgh = 1; _brg =  51;}
    #define SET_UART_BAUTRATE_19200()		{ _brgh = 1; _brg =  25;}
    #define SET_UART_BAUTRATE_38400()		{ _brgh = 1; _brg =  12;}
    #define SET_UART_BAUTRATE_250000()		{ _brgh = 1; _brg =   1;}
#endif
#ifdef _HIRC_14_4M_
    #define SET_UART_BAUTRATE_1200()			{ _brgh = 0; _brg = 155;}
    #define SET_UART_BAUTRATE_2400()			{ _brgh = 0; _brg =  77;}
    #define SET_UART_BAUTRATE_4800()			{ _brgh = 1; _brg = 155;}
    #define SET_UART_BAUTRATE_9600()			{ _brgh = 1; _brg =  77;}
    #define SET_UART_BAUTRATE_19200()		{ _brgh = 1; _brg =  38;}
    #define SET_UART_BAUTRATE_57600()		{ _brgh = 1; _brg =  12;}
    #define SET_UART_BAUTRATE_250000()		{ _brgh = 1; _brg =   2;}
#endif


#endif //BH66F26X0_UART_H__

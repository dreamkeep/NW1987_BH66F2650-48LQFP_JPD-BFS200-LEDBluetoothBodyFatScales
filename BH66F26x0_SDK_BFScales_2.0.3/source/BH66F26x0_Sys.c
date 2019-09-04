//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : BH66F26x0_Sys.h
// Description: BH66F26x0 system init
//     Author : ghg
//   Customer : 京柏
//Targer Board: 京柏:JPD-BFS200
//     Note   :Initial on 20190820
//*********************************************************************/

#include "common.h"

static void ram_init(void);

/**************************************************************
*Function name:poweron_system_init
*Description  :System init
*Parameter    :none
*Return       :none
***************************************************************/
void poweron_system_init(void)
{
    poweron_gpio_init();
    system_clock_init();
	ram_init();
	SETWDTTIME_500MS();
	SETLVR_2_1V();
	SETLVD_DISABLE();

	/*TM Set*/
	SETSTM_TIMER2MS();
	SETSTM_ISRENABLE();
	// PTM0 unused
	// PTM1 unused
	// PTM2 unused
	// Timebase0 unused
	// Timebase1 unused

    /* UART init */
	uart_init();
}

/**************************************************************
*Function name:system_clock_init
*Description  :system clock init
*Parameter    :none
*Return       :none
***************************************************************/
void system_clock_init(void)
{
    #ifdef _HIRC_4M_
        _scc = 0x00;
        _fhs   = 0;
        _hircc = 0x03;
        while (!_hircf);	// Wait HIRC Oscillator Stable
    #endif // _HIRC_4M_

    #ifdef _HIRC_8M_
        _fhs   = 0;
        _hircc = 0x05;
        while (!_hircf);	// Wait HIRC Oscillator Stable
    #endif // _HIRC_8M_

    #ifdef _HIRC_12M_
        _fhs   = 0;
        _hircc = 0x09;
        while (!_hircf);	// Wait HIRC Oscillator Stable
    #endif // _HIRC_12M_

    #ifdef _HXT_10M_BELOW_
        _pas11 = 1; 		// SET PA4 TO OSC1
        _pas10 = 1;
        _pas07 = 1; 		// SET PA3 TO OSC2
        _pas06 = 1;
        _fhs  = 1;
        _hxtc = 0x01;		// HXTM = 1锛孒XT Frequency<10MHz,HXT Oscillator Enable
        while (!_hxtf); 	// Wait HXT Oscillator Stable
    #endif // _HXT_10M_BELOW_

    #ifdef _HXT_10M_OVER_
        _pas11 = 1; 		// SET PA4 TO OSC1
        _pas10 = 1;
        _pas07 = 1; 		// SET PA3 TO OSC2
        _pas06 = 1;
        _fhs  = 1;
        _hxtc = 0x05;		// HXTM = 1锛孒XT Frequency>10MHz,HXT Oscillator Enable
        while (!_hxtf); 	// Wait HXT Oscillator Stable
    #endif // _HXT_10M_OVER_

    #ifdef _LXT_
        _pas01 = 1; 		// SET PA0 TO LXT1
        _pas00 = 1;
        _pas05 = 1; 		// SET PA2 TO LXT2
        _pas04 = 1;
        _fss   = 1;
        _lxten = 1;
        while (!_lxtf); 	// Wait LXT Oscillator Stable
    #endif // _LXT_

    #ifdef _LIRC_
        _fss   = 0;
        _lxten = 0;
    #endif // _LIRC_
}


/**************************************************************
*Function name:poweron_gpio_init
*Description  :power on to initialize  gpio.
*Parameter    :none
*Return       :none
***************************************************************/
void poweron_gpio_init(void)
{
	// PA0-Unused	   PA1-LVDIN:Unused
	// PA2-Unused	   PA3-Unused
	// PA4-Unused      PA5-Uart-Tx,default IO
	// PA6-Uart-Rx,default IO	   PA7-BLE_State
    _pa   = PA_DEFAULT;
    _pac  = PAC_DEFAULT;
    _papu = PAPU_DEFAULT;
    _pawu = PAWU_DEFAULT;
    _pas0 = 0B00000000;
    _pas1 = 0B00000000;

	// PB0-BLE prower  PB1-Unused
	// PB2-LEDCOM3	   PB3-LEDCOM2
	// PB4-Unused	   PB5-Unused
	// PB6-Unused	   PB7-Unused
    _pb   = PB_DEFAULT;
    _pbc  = PBC_DEFAULT;
    _pbpu = PBPU_DEFAULT;
    _pbs0 = 0B00000000;

	// PC0-LED_SEG1		PC1-LED_SEG2
	// PC2-LED_SEG3		PC3-LED_SEG4
	// PC4-LED_SEG5		PC5-LED_SEG6
	// PC6-LED_SEG7		PC7-LED_SEG8
    _pc   = PC_DEFAULT;
    _pcc  = PCC_DEFAULT;
    _pcpu = PCPU_DEFAULT;
    _pcs0 = 0B00000000;
    _pcs1 = 0B00000000;

	// PD0-LEDCOM4	   PD1-LEDCOM1
	// PD2-Unused      PD3-Unused
	// PD4-Unused	   PD5-Unused
	// PD6-Unused	   PD7-Unused
    _pd   = PD_DEFAULT;
    _pdc  = PDC_DEFAULT;
    _pdpu = PDPU_DEFAULT;
    _pds0 = 0B00000000;

	// PTP2I-Unused 	 PTP1I-Unused
	// PTCK2PS-Unused	 STCKPS-Unused
    _ifs0 = 0B00000000;
	// SCSA-Unused		SDIA-Unused
	// SCKA-Unused		RUnused
    _ifs1 = 0B00000000;

    _sledc0 = 0xff;/* 源电流选择位 */
    _sledc1 = 0xff;/* 源电流选择位 */

	P_BLE_ST_C = INPUT;
	P_BLE_EN_C = OUTPUT;
	P_BLE_EN = LOW; /* Enable bluetooth */
}

/**************************************************************
*Function name:poweron_gpio_init
*Description  :gpio init, note:To completely cleared RAM.
*Parameter    :none
*Return       :none
***************************************************************/
static void ram_init(void)
{
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h < RAMBANK)
	{
		for(_tblp = 0x00;_tblp < RAMBANK_SIZE;_tblp++)
		{
			 _iar1 = 0;
			  _mp1l++;
		}
		_mp1l = 0x80;
		_mp1h++;
	}
}

/**************************************************************
*Function name:uart_init
*Description  :uart init:9600 baud rate,PA5-Tx,PA6-Rx
*Parameter    :none
*Return       :none
***************************************************************/
void uart_init(void)
{
    /* UART IO */
	/* PA5-Uart-Tx; PA6-Uart-Rx */
	SET_UART_PIN_PA5PA6();

    /* 8bit, no parity, a stop bit*/
    SET_UART_Format_D8_P0_S1();

    /* Baut rate */
    SET_UART_BAUTRATE_9600();

	SET_UART_WAKEUP_DISABLE();
    SET_UART_ADDRESS_DISABLE();
    SET_UART_RECEIVER_IE_ENABLE();
    SET_UART_TRANSMITTER_IE_ENABLE();
    SET_UART_TRANSMITTER_EMPTY_ENABLE();
    SET_UART_ENABLE();
}

/* Interrupt: move to interrupt.c */
#if 0

DEFINE_ISR(isr_int0,INT0_VECTOR)
{

}

DEFINE_ISR(isr_int1,INT1_VECTOR)
{

}

DEFINE_ISR(isr_adc,ADC_VECTOR)
{

}

/* Multi function0 STM0 & PTM0 */
DEFINE_ISR(isr_mf0,MuFunction0_VECTOR)
{

}


/*  Multi function1 PTM1 & PTM2 */
DEFINE_ISR(isr_mf1,MuFunction1_VECTOR)
{

}

/*  Multi function2 LVD & EEPROM W */
DEFINE_ISR(isr_mf2,MuFunction2_VECTOR)
{

}

DEFINE_ISR(isr_timebase0,Timebase0_VECTOR)
{

}

DEFINE_ISR(isr_timebase1,Timebase1_VECTOR)
{

}

DEFINE_ISR(isr_uart,UART_VECTOR)
{

}

DEFINE_ISR(isr_sim,SIM_VECTOR)
{

}

DEFINE_ISR(isr_spi,SPI_VECTOR)
{

}
#endif



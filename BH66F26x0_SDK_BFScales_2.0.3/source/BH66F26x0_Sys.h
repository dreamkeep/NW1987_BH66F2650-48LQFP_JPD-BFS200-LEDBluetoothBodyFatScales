//*********************************************************************
//  Copyright : 2019 New Wave Eelectronics (ShenZhen) LTD.
//  File Name : BH66F26x0_Sys.h
// Description: 系统初始化相关程序.
//     Author : ghg
//   Customer : 京柏
//Targer Board: 京柏:JPD-BFS200
//     Note   :Initial on 20190820
//*********************************************************************/

#ifndef BH66F26x0_SYS_H__
#define BH66F26x0_SYS_H__

/* SYSTEM CLOCK SETTING */
/* A: HIRC_HXT_select */
#define _HIRC_4M_
//#define _HIRC_8M_
//#define _HIRC_12M_
//#define _HXT_10M_OVER_
//#define _HXT_10M_BELOW_

/* B: LIRC_LXT_select */
#define _LIRC_
//#define _LXT_

/* RAM BANK */
#define RAMBANK         2
#define RAMBANK_SIZE    ((0xFF-0x80)+1)/*+1: clear bank_addr:0xff,不加1则最后的0xff地址清除不到0 */

/* Extern function */
extern void poweron_system_init(void);
extern void system_clock_init(void);
extern void poweron_gpio_init(void);
extern void uart_init(void);

/* WDT SET */
// WDT clock Source fs =fsub
// WDT time计算方式: WDT time =  2^18/fsub
// example:(max time 周期最长2^18，Source fs = 32000)
// WDT time = 2^18/32000= 8s
#define SETWDT_DISABLE()		{ _wdtc = 0xA8;}
#define SETWDTTIME_8MS()		{ _wdtc = 0x50;}
#define SETWDTTIME_32MS()		{ _wdtc = 0x51;}
#define SETWDTTIME_125MS()		{ _wdtc = 0x52;}
#define SETWDTTIME_500MS()		{ _wdtc = 0x53;}
#define SETWDTTIME_1000MS()		{ _wdtc = 0x54;}
#define SETWDTTIME_2000MS()		{ _wdtc = 0x55;}
#define SETWDTTIME_4000MS()		{ _wdtc = 0x56;}
#define SETWDTTIME_8000MS()		{ _wdtc = 0x57;}

/* LVR */
//					@-------------LVR config--------------@
#define  SETLVR_2_1V()			{ _lvrc = 0x55;}
#define  SETLVR_2_55V()			{ _lvrc = 0x33;}
#define  SETLVR_3_15V()			{ _lvrc = 0x88;}
#define  SETLVR_3_8V()			{ _lvrc = 0xAA;}

/* LVD */
//					@-------------LVD config--------------@
#define SETLVD_LVDIN()			{ _lvdc = 0x10; }
#define SETLVD_2V2()			{ _lvdc = 0x11; }
#define SETLVD_2V4()			{ _lvdc = 0x12; }
#define SETLVD_2V7()			{ _lvdc = 0x13; }
#define SETLVD_3V0()			{ _lvdc = 0x14; }
#define SETLVD_3V3()			{ _lvdc = 0x15; }
#define SETLVD_3V6()			{ _lvdc = 0x16; }
#define SETLVD_4V0()			{ _lvdc = 0x17; }
#define SETLVD_ENABLE()			{ _lvden = 1;}
#define SETLVD_DISABLE()		{ _lvden = 0;}
#define SET_DAC_DSIABLE()		{ _dsdacen = 0;}
/* STM */
#ifdef _HIRC_4M_
#define SETSTM_TIMER2MS()       {_stmc0 = 0B00100000; _stmc1 = 0B11000001; _stmal = 500%256; _stmah = 500>>8;}/* fH/16,off, timing,cmp A,timming:2ms*/
#endif
#ifdef _HIRC_8M_
#define SETSTM_TIMER2MS()       {_stmc0 = 0B00110000; _stmc1 = 0B11000001; _stmal = 250; _stmah = 0;}/* fH/64,off, timing,cmp A,timming:2ms*/
#endif
#ifdef _HIRC_12M_
#define SETSTM_TIMER2MS()       {_stmc0 = 0B00110000; _stmc1 = 0B11000001; _stmal = 375%256; _stmah = 375>>8;}/* fH/64,off, timing,cmp A,timming:2ms*/
#endif
#define SETSTM_ISRENABLE()      {_stmaf = 0; _stmae = 1; _mf0f = 0; _mf0e = 1; _ston = 1;}
#define SETSTM_ON()             {_ston = 1;}
#define SETSTM_OFF()            {_ston = 0;}

#define SET_MF0E_DISABLE()		{ _mf0e = 0;}
#define SET_MF0E_ENABLE()		{ _mf0e = 1;}
#define SET_MF1E_DISABLE()		{ _mf1e = 0;}
#define SET_MF1E_ENABLE()		{ _mf1e = 1;}
#define SET_MF2E_DISABLE()		{ _mf2e = 0;}
#define SET_MF2E_ENABLE()		{ _mf2e = 1;}
#define SET_EMI_ENABLE()        {  _emi  = 1;}
#define SET_EMI_DISABEL()       {  _emi  = 0;}
#define SET_INT1EDISABLE()		{ _int1e =0 ;}
#define SET_ADC_IN_DISABLE()	{ _ade = 0;}

/* GPIO DEFAULT SETTING */
#define PA_DEFAULT              0B00000000
#define PAC_DEFAULT             0B11111111 /* pa3:unused */
#define PAPU_DEFAULT            0B00011101
#define PAWU_DEFAULT            0B00000000

#define PB_DEFAULT              0B00000000
#define PBC_DEFAULT             0B11110010 /* Pb1,pb4~pb7: unused */
#define PBPU_DEFAULT            0B11110010

#define PC_DEFAULT              0B00000000
#define PCC_DEFAULT             0B00000000 /* pc0~pc7: LED SEG1~SEG8 */
#define PCPU_DEFAULT            0B00000000

#define PD_DEFAULT              0B00000000
#define PDC_DEFAULT             0B11111100 /*pd4_pd7:null;  pd2,pd3:unused; pd0:COM4; pd1:COM1*/
#define PDPU_DEFAULT            0B00000000

/* bluetooth */
#define P_BLE_ST		        _pa7  /* Bluetooth status: =0 connection; =1 disconnect*/
#define P_BLE_ST_C		        _pac7
#define P_BLE_EN		        _pb0  /* Bluetooth enable or disable control : =0 Enable; =1 Disable*/
#define P_BLE_EN_C		        _pbc0

/* LED */
#define	 LEDCOM1 				_pd1
#define	 LEDCOM2 				_pb3
#define  LEDCOM3 				_pb2
#define  LEDCOM4 				_pd0

#define	 LEDSEG	     			_pc
#define	 LEDSEGC     			_pcc

#define  LEDSEG8                _pc7/* POINT */

#define	 LEDCOMC1   			_pdc1
#define	 LEDCOMC2   			_pbc3
#define	 LEDCOMC3   			_pbc2
#define	 LEDCOMC4   			_pdc0



#define OUTPUT                  0
#define INPUT                   1
#define LOW                     0
#define HIGH                    1

/* BH66F2650 INTERRUPT */
//					-----ISR VECTOR Definations------;
//中断入口地址
#define	START_VECTOR			0x000		// 主程序
#define INT0_VECTOR				0x004		// Interrupt 0
#define INT1_VECTOR				0x008		// Interrupt 1
#define ADC_VECTOR				0x00C		// ADC
#define MuFunction0_VECTOR		0x010		// Multi function0 STM0 & PTM0
#define STM0_VECTOR				0x010		// STM0
#define PTM0_VECTOR				0x010		// PTM0
#define MuFunction1_VECTOR		0x014		// Multi function1 PTM1 & PTM2
#define PTM1_VECTOR				0x014		// PTM1
#define PTM2_VECTOR				0x014		// PTM2
#define MuFunction2_VECTOR		0x018		// Multi function2 LVD & EEPROM W
#define Timebase0_VECTOR		0x020		// timebase0
#define Timebase1_VECTOR		0x024		// timebase1
#define UART_VECTOR		    	0x028		// UART
#define SIM_VECTOR				0x02C		// SIM SPI & IIC
#define SPI_VECTOR				0x030		// SPI
#endif //BH66F26x0_SYS_H__

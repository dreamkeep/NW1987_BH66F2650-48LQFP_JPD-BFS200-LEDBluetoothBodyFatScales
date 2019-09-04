asm (" message' **************************************************** ' ");
asm (" message' *       2018 BY BEST HEALTH ELECTRONIC INC         * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *        SDK  NAME  :      BFScales.c   	       * ' ");
asm (" message' *   Compiler   Ver. :      V3.52                   * ' ");
asm (" message' *   IDE3000    Ver. :      V7.96                   * ' ");
asm (" message' *   RELEASE    Ver. :      2.0.3                   * ' ");
asm (" message' *   RELEASE   DATA  :     2018/06/22               * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *    MCU / CFG Ver. :   BH66F2650 / 1.8            * ' ");
asm (" message' *                       BH66F2660 / 1.2            * ' ");
asm (" message' **************************************************** ' ");
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              此文件不能修改!!!                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "SDK_UserSetting.h"
#include "SDK_Interface.h"
#include "BH66F2650.h"

#define SINWAVE_DATA_ADDRESS	    0x300   //  SIN WAVE
#define SINGAIN 					0.8 	//  玄波增益  range: 0.5~0.9
// ADC DATA RARE 計算方式:
// FMCLK = Fsys = 4000000,CHOP = 2, N = 12,OSR = 16384
// FADCK = FMCLK/(CHOP/N) =166667=167K
// DataRate = FADCK/OSR = 10.2HZ
#define CHOP2_FLMS30()              { _flms2=0; _flms1=0; _flms0=0;}
#define CHOP2_FLMS12()              { _flms2=0; _flms1=1; _flms0=0;}
#define CHOP1_FLMS30()              { _flms2=1; _flms1=0; _flms0=0;}
#define CHOP1_FLMS12()              { _flms2=1; _flms1=1; _flms0=0;}
#define OSR_16384()                 { _ador2=0; _ador1=0; _ador0=0;}
#define OSR_8192()                  { _ador2=0; _ador1=0; _ador0=1;}
#define OSR_4096()                  { _ador2=0; _ador1=1; _ador0=0;}
#define OSR_2048()                  { _ador2=0; _ador1=1; _ador0=1;}
#define OSR_1024()                  { _ador2=1; _ador1=0; _ador0=0;}
#define OSR_512()                   { _ador2=1; _ador1=0; _ador0=1;}
#define OSR_256()                   { _ador2=1; _ador1=1; _ador0=0;}
#define OSR_128()                   { _ador2=1; _ador1=1; _ador0=1;}
static  volatile  unsigned int SinDataRam[32] __attribute__ ((at(SINWAVE_DATA_ADDRESS)));
#ifdef SYS_HIGH_FREQUENCY_OSC_4MHZ
#define SET_SINFREQ_50KHz()			{ _sgn = 2-1; _sgdnr = 20 -1;}
#define SETSINFREQ_5KHz()			{ _sgn =16-1; _sgdnr = 25 -1;}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x1F; CHOP2_FLMS30(); OSR_1024(); }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x1F; CHOP2_FLMS12(); OSR_128();  }
const unsigned int SinData_50KHz[32] = {
	SINGAIN * 0, SINGAIN * 80, SINGAIN * 158, SINGAIN * 232, SINGAIN * 300, SINGAIN * 361,
	SINGAIN * 413, SINGAIN * 455, SINGAIN * 486, SINGAIN * 505, SINGAIN * 511, SINGAIN * 505,
	SINGAIN * 486, SINGAIN * 455, SINGAIN * 413, SINGAIN * 361, SINGAIN * 300, SINGAIN * 232,
	SINGAIN * 158, SINGAIN * 80, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0,
	SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, SINGAIN * 0, // 20~31
};
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_8MHZ
#define SET_SINFREQ_50KHz()			{ _sgn = 4-1; _sgdnr = 20 -1;}
#define SETSINFREQ_5KHz()			{ _sgn =32-1; _sgdnr = 25 -1;}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_16384() }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x00; CHOP2_FLMS30(); OSR_1024(); }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x00; CHOP2_FLMS12(); OSR_128();  }
const unsigned int SinData_50KHz[32] = {
	SINGAIN*0, SINGAIN*80, SINGAIN*158, SINGAIN*232, SINGAIN*300,SINGAIN* 361,
	SINGAIN* 413, SINGAIN*455, SINGAIN*486, SINGAIN*505, SINGAIN*511, SINGAIN*505,
	SINGAIN* 486, SINGAIN*455, SINGAIN*413, SINGAIN*361, SINGAIN*300,SINGAIN*232,
	SINGAIN*158, SINGAIN*80, SINGAIN*0, SINGAIN*0, SINGAIN*0, SINGAIN*0,SINGAIN*0,
	SINGAIN*0, SINGAIN*0, SINGAIN*0, SINGAIN*0, SINGAIN*0, SINGAIN*0, SINGAIN*0,// 20~31
};
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_12MHZ
#define SET_SINFREQ_50KHz()			{ _sgn = 4-1; _sgdnr = 30 -1;}
#define SETSINFREQ_5KHz()			{ _sgn =40-1; _sgdnr = 30 -1;}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x02; CHOP2_FLMS30(); OSR_512();  }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x1F; CHOP2_FLMS30(); OSR_128();  }
const unsigned int SinData_50KHz[32] = {
	SINGAIN*0, SINGAIN*53, SINGAIN*106, SINGAIN*158, SINGAIN*208, SINGAIN*256, SINGAIN*300,
	SINGAIN*342, SINGAIN*380, SINGAIN*413, SINGAIN*443, SINGAIN*467, SINGAIN*486, SINGAIN*500,
	SINGAIN*508, SINGAIN*511, SINGAIN*508, SINGAIN*500, SINGAIN*486, SINGAIN*467, // 0~19
	SINGAIN*443, SINGAIN*413, SINGAIN*380, SINGAIN*342, SINGAIN*300, SINGAIN*256, SINGAIN*208,
	SINGAIN*158, SINGAIN*106, SINGAIN*53, SINGAIN*0,SINGAIN* 0,					// 20~31
};
#endif
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//                用戶設置  重量接口                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_LoadUserSetting()
{
	SDKWeightSetting.WeightMax             = WEIGHT_MAX;
	SDKWeightSetting.WeightMin             = WEIGHT_MIN;
	SDKWeightSetting.WeightUnLockTemp      = WEIGHT_UNLOCK_TEMP;
	SDKWeightSetting.WeightUnLockStable    = WEIGHT_UNLOCK_STATE;
	SDKWeightSetting.WeightAutoOn          = WEIGHT_AUTOON;
	SDKWeightSetting.flag.b.IsAutoCalOn    = WEIGHT_AUTOCAL;
	SDKWeightSetting.flag.b.IsAutoUnlockOn = WEIGHT_AUTOUNLOCK;
}
void fun_LoadWeightSetting()
{
	SET_ADC_DATARATE_10HZ();
	SDKADCFilterData.StableCntTag = ADCSTABLE_WEIGHT_CNT;
	SDKADCFilterData.StableThreshold   = ADCSTABLE_WEIGHT_THRESHOLD;
}
void fun_LoadAutoOnSetting()
{
	SET_ADC_DATARATE_1300HZ();
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//                用戶設置  阻抗接口                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_LoadImpedanceSetting()
{
	// Sin 波頻率設置
	unsigned char i;
	for (i = 0; i < 32; i++)
	{
		SinDataRam[i] =  SinData_50KHz[i];
	}
	SET_SINFREQ_50KHz();
	// 採樣率設置
	SET_ADC_DATARATE_64HZ();
	// 濾波參數設置
	SDKADCFilterData.StableCntTag  = ADCSTABLE_IMPEDANCE_CNT;
	SDKADCFilterData.StableThreshold   = ADCSTABLE_IMPEDANCE_THRESHOLD;
}
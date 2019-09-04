//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              ���ļ������޸�!!!                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef _SDK_INTERFACE_H_
#define _SDK_INTERFACE_H_

#include "SDK_typedef.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  �����ӿ�                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_BodyFatScalesSDK();            // ������,������ѭ�h�{��
void fun_BodyFatScalesSDK_PowerOn();    // ��늳�ʼ��,MCU��늺��{��һ��
void fun_BodyFatScalesSDK_PowerDown();  // ���߳�ʼ��,MCU����ǰ�{��һ��
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  ׃���ӿ�                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  RW ���x�Ɍ�, Rֻ���x,���܌�!!!
extern unsigned char const SDKVersion[3];    // R SDK �汾̖ SDKVersion[0]���汾̖  SDKVersion[1]�ΰ汾̖ SDKVersion[2]��ӆ̖
extern unsigned char BHSDKState;             // RW   ������B�xȡ�c�ГQ,���� BodyfatSDKState ö�e
extern ADCSource_t SDKADCSourceData;         // ԭʼADC����,Ԕ������SDK_typedef.h ADCSource_t
extern ADCFilter_t SDKADCFilterData;         // �V��ADC����,Ԕ������SDK_typedef.h ADCFilter_t
extern volatile Weight_t SDKWeight;                   // �������P����,Ԕ������SDK_typedef.h Weight_t
extern BodyScalesSetting_t SDKWeightSetting; // �����Ñ��O������,Ԕ������SDK_typedef.h BodyScalesSetting_t
extern Impedance_t SDKImpedance;             // �迹���P����,Ԕ������SDK_typedef.h Impedance_t
extern HeartRate_t SDKHeartRate;             // �������P����,Ԕ������SDK_typedef.h HeartRate_t
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  �����ӿ�                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void Write_EEPROMByte(unsigned char addr, unsigned char WriteData);   // ��һ��Byte����
unsigned char Read_EEPROMByte(unsigned char addr);                    // �xһ��Byte����
unsigned long fun_unsigned32BitABS(unsigned long a, unsigned long b); // ȡ32λ�o��̖��ֵ




#endif

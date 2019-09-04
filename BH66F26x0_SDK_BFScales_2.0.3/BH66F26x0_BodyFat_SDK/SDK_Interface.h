//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              此文件不能修改!!!                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef _SDK_INTERFACE_H_
#define _SDK_INTERFACE_H_

#include "SDK_typedef.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK接口  函數接口                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_BodyFatScalesSDK();            // 主函數,主程序循環調用
void fun_BodyFatScalesSDK_PowerOn();    // 上電初始化,MCU上電后調用一次
void fun_BodyFatScalesSDK_PowerDown();  // 休眠初始化,MCU休眠前調用一次
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK接口  變量接口                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  RW 可讀可寫, R只能讀,不能寫!!!
extern unsigned char const SDKVersion[3];    // R SDK 版本號 SDKVersion[0]主版本號  SDKVersion[1]次版本號 SDKVersion[2]修訂號
extern unsigned char BHSDKState;             // RW   工作狀態讀取與切換,參考 BodyfatSDKState 枚舉
extern ADCSource_t SDKADCSourceData;         // 原始ADC數據,詳細參考SDK_typedef.h ADCSource_t
extern ADCFilter_t SDKADCFilterData;         // 濾波ADC數據,詳細參考SDK_typedef.h ADCFilter_t
extern volatile Weight_t SDKWeight;                   // 重量相關數據,詳細參考SDK_typedef.h Weight_t
extern BodyScalesSetting_t SDKWeightSetting; // 重量用戶設定數據,詳細參考SDK_typedef.h BodyScalesSetting_t
extern Impedance_t SDKImpedance;             // 阻抗相關數據,詳細參考SDK_typedef.h Impedance_t
extern HeartRate_t SDKHeartRate;             // 心率相關數據,詳細參考SDK_typedef.h HeartRate_t
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK接口  其他接口                         @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void Write_EEPROMByte(unsigned char addr, unsigned char WriteData);   // 寫一個Byte數據
unsigned char Read_EEPROMByte(unsigned char addr);                    // 讀一個Byte數據
unsigned long fun_unsigned32BitABS(unsigned long a, unsigned long b); // 取32位無符號差值




#endif

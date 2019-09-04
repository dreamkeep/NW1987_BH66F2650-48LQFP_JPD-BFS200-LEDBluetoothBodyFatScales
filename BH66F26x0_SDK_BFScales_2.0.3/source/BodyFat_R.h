//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : BodyFat.h
// Description: 體脂計算
//   Customer : Holtek Demo Code
//Targer Board: None
//___________________________________________________________________
//___________________________________________________________________
#ifndef _BODYFAT_H_
#define _BODYFAT_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 變量說明 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern volatile unsigned long Body_Rx;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 輸入的Impedance必須小於1530

// 輸入的Impedance=0xffff,Body_Rx=0xFFFFFFFF;
//表示阻抗量測錯誤，穿鞋等情況,APP此時顯示阻抗錯誤
void FUN_GETBODYRX(unsigned int Impedance);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Application notes @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  Important
//  en
//  1.Options → project settings
//  2.project Options  → linker Options → Libraies Browse → select the BodyFat_R.lib file

//  zh-tw
//  彙編調用C請在IDE3000菜單欄執行
//  1.選項 → 專案設定
//  2.專案設定 → 連接選型,瀏覽選擇Bodyfat_R.lib文件

#endif
//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : BodyFat.h
// Description: �w֬Ӌ��
//   Customer : Holtek Demo Code
//Targer Board: None
//___________________________________________________________________
//___________________________________________________________________
#ifndef _BODYFAT_H_
#define _BODYFAT_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ׃���f�� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern volatile unsigned long Body_Rx;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ���ú��� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ݔ���Impedance���С�1530

// ݔ���Impedance=0xffff,Body_Rx=0xFFFFFFFF;
//��ʾ�迹���y�e�`����Ь����r,APP�˕r�@ʾ�迹�e�`
void FUN_GETBODYRX(unsigned int Impedance);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Application notes @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  Important
//  en
//  1.Options �� project settings
//  2.project Options  �� linker Options �� Libraies Browse �� select the BodyFat_R.lib file

//  zh-tw
//  �����{��CՈ��IDE3000�ˆΙڈ���
//  1.�x� �� �����O��
//  2.�����O�� �� �B���x��,�g�[�x��Bodyfat_R.lib�ļ�

#endif
#ifndef __BODYFATSCALES_TASK_H__
#define __BODYFATSCALES_TASK_H__

extern u8  gu8_worktasks;//体脂称工作模式.
extern u16 gu16_weigh;    //显示体重前的原始体重,精度为10的体重数据。
extern u16 gu16_memory_weigh;//200g记忆体重，精度为10g的体重数据。
extern u16 gu16_currentweigh;//Precision:10g
extern u16 gu16_impedence_data;//原始阻抗数据
extern u16 gu16_BodyFatRate;//来自蓝牙的体脂率.

//extern void fun_DisplayMode_NoLoad(void);
//extern void fun_DisplayMode_LoadFix(void);
//extern void fun_DisplayMode_LoadDown(void);
//extern void fun_DisplayMode_OverLoad(void);
//extern void fun_DisplayMode_ImpedanceFinish(void);
//extern void task_bodyfatscales(void);
extern void set_BHSDKState(u8 state);
extern u8 is_BHSDKState_change(void);
extern void task_bodyfatscales(void);
extern void task_scalesstartup(void);
extern void task_scaleslowbattry(void);
extern void task_scales2sleep(void);
extern void task_scaleswakeup(void);

#endif //__BODYFATSCALES_TASK_H__

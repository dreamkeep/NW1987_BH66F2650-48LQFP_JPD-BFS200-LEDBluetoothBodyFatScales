#ifndef FUNCTION_H__
#define FUNCTION_H__

extern u8  gu8_display_mode;//LED��ʾģʽ.
extern u16 gu16_display_weight;//�Ѿ�ת����λ�����ʾ��������.
extern u8 gu8_weigh_targeunit;//Ŀ�����ص�λ.

/* LED ��˸����ʾ����ʱ�ȱ���*/
extern volatile u8  gu8v_time_dalay; //
extern volatile u8  gu8v_howtimes;  //
extern volatile u8  gu8v_led_speed; //��˸�Ŀ���
extern volatile u8  gu8v_led_delay; //��ʱdelayʱ����ִ����˸.
extern volatile u8  gu8v_led_delay3S;//����LEDȫ��3s��ʱ.
extern volatile u8  gu8v_timed_shutdown;//��ʱ�ػ���ʱ.

extern void fun_weight_unit_change(u16 weigh);
extern void fun_DisplayLEDADCData();
extern void set_led_flash_mode(u8 mode, u8 ledflash, u8 count, u8 speed, u8 delay, u8 overtime);
extern u8 get_led_flash_status(void);

extern void set_display_mode(u8 dismode);
//extern u8 Get_DisplayMode(void);
extern void fun_diaplay_mode(void);
extern void fun_bluetooth_detected(void);
extern void set_overtime2poweroff(u8 overtime);
extern void is_timedshutdown(void);

#endif //FUNCTION_H__

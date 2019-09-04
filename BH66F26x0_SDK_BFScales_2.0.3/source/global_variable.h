#ifndef GLOBAL_VARIABLE_H__
#define GLOBAL_VARIABLE_H__

#include "typedef.h"


extern volatile __byte_type gu8v_time_flag;
#define fg_time_byte        gu8v_time_flag.u8
#define fg_time_2ms         gu8v_time_flag.bits.b0
#define fg_time_100ms       gu8v_time_flag.bits.b1
#define fg_time_3s          gu8v_time_flag.bits.b2
#define fg_time_10s         gu8v_time_flag.bits.b3
#define fg_time_200ms_t       gu8v_time_flag.bits.b4

extern volatile __byte_type gu8v_led_flag;
#define fg_led_flag_byte    gu8v_led_flag.u8
#define fg_led_delay        gu8v_led_flag.bits.b0
#define fg_led_timing       gu8v_led_flag.bits.b1
#define fg_led_change       gu8v_led_flag.bits.b2
#define fg_led_flash        gu8v_led_flag.bits.b3
#define fg_led_ble          gu8v_led_flag.bits.b4

extern volatile __byte_type gu8v_flag3;
#define fg_flag3_byte       gu8v_flag3.u8
#define fg_loadok           gu8v_flag3.bits.b0
#define fg_manual_readycal  gu8v_flag3.bits.b1
#define fg_manual_cal       gu8v_flag3.bits.b2
#define fg_adc_inside_code  gu8v_flag3.bits.b3

extern volatile __byte_type gu8v_memory_flag4;
#define fg_memory_byte      gu8v_memory_flag4.u8
#define fg_memory_200g      gu8v_memory_flag4.bits.b0

extern volatile u8 gu8v_time_100ms;
extern volatile u8 gu8v_led_delay3s;
extern volatile u8 gu8v_time_30s;

extern u8 gu8_data_type;/* data type:=0/1/2. */
extern u8 gu8_ble_count;

#endif //GLOBAL_VARIABLE_H__

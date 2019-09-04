#ifndef LED_DISPLAY_H__
#define LED_DISPLAY_H__

/* define: LED dispaly char index */
#define LED_CHAR_0					0 /* '0' */
#define LED_CHAR_1					1 /* '1' */
#define LED_CHAR_2					2 /* '2' */
#define LED_CHAR_3					3 /* '3' */
#define LED_CHAR_4					4 /* '4' */
#define LED_CHAR_5					5 /* '5' */
#define LED_CHAR_6					6 /* '6' */
#define LED_CHAR_7					7 /* '7' */
#define LED_CHAR_8					8 /* '8' */
#define LED_CHAR_9					9 /* '9' */
#define LED_CHAR_A					10 /* 'A' */
#define LED_CHAR_B					11 /* 'B' */
#define LED_CHAR_C					12 /* 'C' */
#define LED_CHAR_D					13 /* 'D' */
#define LED_CHAR_E					14 /* 'E' */
#define LED_CHAR_F					15 /* 'F' */
#define LED_CHAR_OFF				16 /* ALL OFF */
#define LED_CHAR_H 					17 /* 'H' */
#define LED_CHAR_I					18 /* 'I' */
#define LED_CHAR_L					19 /* 'L' */
#define LED_CHAR_O					20 /* 'O' */
#define LED_CHAR_P					21 /* 'P' */
#define LED_CHAR_R					22 /* 'r' */
#define LED_CHAR__					23 /* '-' */
#define LED_CHAR_ALL				24 /* ALL ON */
#define C_LED_CHAR_NUM				25


#define C_LED_BUFF_MAX				4
#define LED_NUM_GE                  0
#define LED_NUM_SHI                 1
#define LED_NUM_BAI                 2
#define LED_NUM_QIAN                3

/* variable */
extern volatile unsigned char       gu8v_weight_unit;
extern volatile unsigned char       gu8v_led_buffer[C_LED_BUFF_MAX];

/* flag */
extern volatile __byte_type         gu8v_led_buffer_point;
#define fg_led_buffer_point_byte    gu8v_led_buffer_point.u8
#define fg_led_point1               gu8v_led_buffer_point.bits.b0
#define fg_led_point2               gu8v_led_buffer_point.bits.b1

/* function */
extern void led_display_scan(void);
extern void led_init(void);
extern void set_led_all_buffer(u8 OnOff);
extern void fun_HEX2BCD(u16 DisplayNum);

#endif //LED_DISPLAY_H__

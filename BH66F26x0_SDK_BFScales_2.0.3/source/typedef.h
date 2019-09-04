//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : typedef.h
// Description: �����A̎���x
//Targer Board: None
//   MCU      : None
//   Author   : ChenTing
//   Date     : 2015/05/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _TYPEDEF_H__
#define _TYPEDEF_H__


/************************Type Defination*****************/
typedef char			s8;
typedef int				s16;
typedef long			s32;
typedef unsigned char 	u8;
typedef unsigned int    u16;
typedef unsigned long   u32;

#define BOOL			u8
#define ENABLE			1
#define Enable			1
#define Disable			0
#define DISABLE			0
#define TRUE			1
#define FALSE			0
#define NULL			0



	typedef unsigned char __1_byte;
	typedef struct {
	    unsigned char b0:1;
	    unsigned char b1:1;
	    unsigned char b2:1;
	    unsigned char b3:1;
	    unsigned char b4:1;
	    unsigned char b5:1;
	    unsigned char b6:1;
	    unsigned char b7:1;
	} __8_bits;
	typedef union {
	    __8_bits bits;
	    __1_byte u8;
	    __1_byte s8;
	} __byte_type;


	typedef long	__S16_bit;
	typedef struct {
	    unsigned char b0:1;
	    unsigned char b1:1;
	    unsigned char b2:1;
	    unsigned char b3:1;
	    unsigned char b4:1;
	    unsigned char b5:1;
	    unsigned char b6:1;
	    unsigned char b7:1;
	    unsigned char b8:1;
	    unsigned char b9:1;
	    unsigned char b10:1;
	    unsigned char b11:1;
	    unsigned char b12:1;
	    unsigned char b13:1;
	    unsigned char b14:1;
	    unsigned char b15:1;

	} __16_bits;
	typedef union {
		struct
		{
			unsigned char byte0;
			unsigned char byte1;
		}byte;
	    __16_bits bits;
		int		 		 s16;
	    unsigned int	 u16;
	} __16_type;



	typedef long	__S32_bit;
	typedef struct {
	    unsigned char b0:1;
	    unsigned char b1:1;
	    unsigned char b2:1;
	    unsigned char b3:1;
	    unsigned char b4:1;
	    unsigned char b5:1;
	    unsigned char b6:1;
	    unsigned char b7:1;
	    unsigned char b8:1;
	    unsigned char b9:1;
	    unsigned char b10:1;
	    unsigned char b11:1;
	    unsigned char b12:1;
	    unsigned char b13:1;
	    unsigned char b14:1;
	    unsigned char b15:1;
	    unsigned char b16:1;
	    unsigned char b17:1;
	    unsigned char b18:1;
	    unsigned char b19:1;
	    unsigned char b20:1;
	    unsigned char b21:1;
	    unsigned char b22:1;
	    unsigned char b23:1;
	    unsigned char b24:1;
	    unsigned char b25:1;
	    unsigned char b26:1;
	    unsigned char b27:1;
	    unsigned char b28:1;
	    unsigned char b29:1;
	    unsigned char b30:1;
	    unsigned char b31:1;

	} __32_bits;
	typedef union {
		struct
		{
			unsigned char byte0;
			unsigned char byte1;
			unsigned char byte2;
			unsigned char byte3;

		}byte;
	    __32_bits 		bits;
	    unsigned long 	u32;
	    long			s32;
	} __32_type;

#endif


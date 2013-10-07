/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Changelog:
*******************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)

/*Bit Operation macro*/ 
#define SETBIT(var,bitnum) ((var) |= (0x1<<(bitnum)))
#define CLRBIT(var,bitnum) ((var) &= ~(0x1<<(bitnum)))
#define REDBIT(var,bitnum) (((var)>>(bitnum))&0x01)

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned int u32;
typedef signed int s32;

#endif
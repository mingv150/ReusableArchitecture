/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Common.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Common_H_
#define _Common_H_

/*Macro Definition*/

#define TRUE 1
#define FALSE 0
#define NULL (void *)0
/*Bit Operation macro*/ 
#define SETBIT(var,bitnum) ((var) |= (0x1<<(bitnum)))
#define CLRBIT(var,bitnum) ((var) &= ~(0x1<<(bitnum)))
#define REDBIT(var,bitnum) (((var)>>(bitnum))&0x00000001)

#define OFFSETOF(type,member) ((unsigned int)&((type *)0)->member)
#define	MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define ARR_SIZE(a) (sizeof((a))/sizeof((a[0])))

/*Data Type Specification*/
/*base data type of this compiler*/
typedef bit bool;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned short long int u24;
typedef signed short long int s24;
typedef unsigned long int u32;
typedef signed long int s32;

#ifndef _Common_C_
/*Interface Declarations*/

#endif

#endif
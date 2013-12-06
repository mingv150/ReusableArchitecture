/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: ///Common.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Common_H_
#define _Common_H_

/*For common use*/
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

#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

#if !defined(__PACKED)
    #define __PACKED
#endif

/*Data Type Specification*/
//C basic date type 
typedef bool u8;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned short long int u24;
typedef signed short long int s24;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long int u32;
typedef signed long int s32;
typedef unsigned long long u64;
typedef signed long long s64
typedef float f32;
typedef double float f64;
typedef long double float f64;


typedef union
{
    u8 Val;
    struct
    {
        __EXTENSION u8 b0:1;
        __EXTENSION u8 b1:1;
        __EXTENSION u8 b2:1;
        __EXTENSION u8 b3:1;
        __EXTENSION u8 b4:1;
        __EXTENSION u8 b5:1;
        __EXTENSION u8 b6:1;
        __EXTENSION u8 b7:1;
    } bits;
} u8_VAL, u8_BITS;

typedef union 
{
    u16 Val;
    u8 v[2] __PACKED;
    struct __PACKED
    {
        u8 LB;
        u8 HB;
    } byte;
    struct __PACKED
    {
        __EXTENSION u8 b0:1;
        __EXTENSION u8 b1:1;
        __EXTENSION u8 b2:1;
        __EXTENSION u8 b3:1;
        __EXTENSION u8 b4:1;
        __EXTENSION u8 b5:1;
        __EXTENSION u8 b6:1;
        __EXTENSION u8 b7:1;
        __EXTENSION u8 b8:1;
        __EXTENSION u8 b9:1;
        __EXTENSION u8 b10:1;
        __EXTENSION u8 b11:1;
        __EXTENSION u8 b12:1;
        __EXTENSION u8 b13:1;
        __EXTENSION u8 b14:1;
        __EXTENSION u8 b15:1;
    } bits;
} u16_VAL, u16_BITS;

typedef union
{
    u32 Val;
    u16 w[2] __PACKED;
    u8  v[4] __PACKED;
    struct __PACKED
    {
        u16 LW;
        u16 HW;
    } word;
    struct __PACKED
    {
        u8 LB;
        u8 HB;
        u8 UB;
        u8 MB;
    } byte;
    struct __PACKED
    {
        u16_VAL low;
        u16_VAL high;
    }wordUnion;
    struct __PACKED
    {
        __EXTENSION u8 b0:1;
        __EXTENSION u8 b1:1;
        __EXTENSION u8 b2:1;
        __EXTENSION u8 b3:1;
        __EXTENSION u8 b4:1;
        __EXTENSION u8 b5:1;
        __EXTENSION u8 b6:1;
        __EXTENSION u8 b7:1;
        __EXTENSION u8 b8:1;
        __EXTENSION u8 b9:1;
        __EXTENSION u8 b10:1;
        __EXTENSION u8 b11:1;
        __EXTENSION u8 b12:1;
        __EXTENSION u8 b13:1;
        __EXTENSION u8 b14:1;
        __EXTENSION u8 b15:1;
        __EXTENSION u8 b16:1;
        __EXTENSION u8 b17:1;
        __EXTENSION u8 b18:1;
        __EXTENSION u8 b19:1;
        __EXTENSION u8 b20:1;
        __EXTENSION u8 b21:1;
        __EXTENSION u8 b22:1;
        __EXTENSION u8 b23:1;
        __EXTENSION u8 b24:1;
        __EXTENSION u8 b25:1;
        __EXTENSION u8 b26:1;
        __EXTENSION u8 b27:1;
        __EXTENSION u8 b28:1;
        __EXTENSION u8 b29:1;
        __EXTENSION u8 b30:1;
        __EXTENSION u8 b31:1;
    } bits;
} u32_VAL;

#ifdef _Common_C_
/*For local users*/
/*Macro Definition*/
/*Data Type Specification*/
#else
/*For external users*/
/*Macro Definition*/
/*Data Type Specification*/
/*Interface Declarations*/
#endif

#endif
/****************************************************************************
Copyright (C), 2014, Mingv150, All rights reserved
FileName: /Driver/Key/Key.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Key_H_
#define _Key_H_

/*For common use*/
/*Macro Definition*/
#define KEY_0 0
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_ARRAYSIZE 4
#define KEY_UP 1
#define KEY_DOWN 0
#define KEY_HIGH KEY_UP
#define KEY_LOW KEY_DOWN

/*Data Type Specification*/
typedef u32 t_Key_Arraytype; 
typedef s8 (*t_Key_Send)(u8 KeyType,u8 UpDown);
typedef struct
{
    t_Key_Arraytype IOState[KEY_ARRAYSIZE];
    t_Key_Arraytype IOStateBuf[KEY_ARRAYSIZE];
    t_Key_Arraytype IOStatePre[KEY_ARRAYSIZE];
    t_Key_Arraytype IODebounce[KEY_ARRAYSIZE];
    t_Key_Arraytype KeyEvent;
    t_Key_Arraytype KeyState;
    t_Key_Send SendEventCb;
}t_Key;

#ifdef _Key_C_
/*For local users*/
/*Macro Definition*/
/*Data Type Specification*/
#else
/*For external users*/
/*Macro Definition*/
/*Data Type Specification*/
/*Interface Declarations*/
void Key_Process(t_Key_Send CbFun);
#endif

#endif
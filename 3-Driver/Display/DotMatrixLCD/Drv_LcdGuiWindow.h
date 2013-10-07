/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdGuiWindow.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Drv_LcdGuiWindow_H_
#define _Drv_LcdGuiWindow_H_

/*Macro Definition*/


/*Data Type Specification*/
CLASS(Window)
{
    // 窗口位置左上角X坐标
    u16 x;        
    // 窗口位置左上角Y坐标
    u16 y;
    // 窗口宽度 
    u16 width;
    // 窗口高度 
    u16 hight;
    // 定义标题栏指针 (标题字符为ASCII字符串，最大个数受窗口限制)     
    u8 *title;   
    // 定义状态栏指针 (若为空时则不显示状态栏)   
    u8 *state;
    // 窗口操作函数
    u8 (* Draw)(Window *pthis);
    u8 (* Hide)(Window *pthis);
    void (* Clear)(Window *pthis);
};

#ifndef _Drv_LcdGuiWindow_C_
/*Interface Declarations*/

#endif

#endif
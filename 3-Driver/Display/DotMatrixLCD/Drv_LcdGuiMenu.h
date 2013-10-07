/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdGuiMenu.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Drv_LcdGuiMenu_H_
#define _Drv_LcdGuiMenu_H_

/*Macro Definition*/
/* 定义主菜单宽度，及最大菜单个数 */
#define  MMENU_WIDTH                34
#define  MMENU_NO                   6

/*Data Type Specification*/
CLASS(Menu)
{  
    Window *win;          
    u8 no; 
    u8 *str[MMENU_NO];   

    u8 (* MMenuDraw)(Menu *pthis);
    void (* ButtonOK)(Menu *pthis, u16 x, u16 y);
};

#ifndef _Drv_LcdGuiMenu_C_
/*Interface Declarations*/

#endif

#endif
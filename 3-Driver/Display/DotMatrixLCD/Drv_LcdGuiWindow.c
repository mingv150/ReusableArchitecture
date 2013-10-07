/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdGuiWindow.c
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#define _Drv_LcdGuiWindow_C_
/*common header file*/
#include "Common.h"
#include "lw_oopc.h"
#include "Drv_LcdModel.h"
/*my header file*/
#include "Drv_LcdGuiBasic.h"
#include "Drv_LcdGuiWindow.h"


/*Global Data Structure*/


/****************************************************************************
Function: static u8 Drv_LcdGuiWindow_Draw(Window *pthis)
Description: 
Input: 
Output: 
*****************************************************************************/
static u8 Drv_LcdGuiWindow_Draw(Window *pthis)
{
    u8  *str;
    u32  bak, bak1, bak2;

    /* 参数过滤，若窗口起出范围，则返回0 */
    // 宽度、高度检查，限制最小窗口
    if ((pthis->width < 20) || (pthis->hight < 20)) 
        return FALSE; 

    // 窗口宽度是否溢出
    if ((pthis->x + pthis->width) > Drv_LcdGuiBasic_GetXMax()) 
        return FALSE;        

    // 窗口高度是否溢出
    if ((pthis->y + pthis->hight) > Drv_LcdGuiBasic_GetYMax())
        return FALSE;         

    /* 开始画窗口 */
    Drv_LcdGuiBasic_RectangleFill(pthis->x, pthis->y, pthis->x + pthis->width - 1, pthis->y + pthis->hight - 1, 0);
    Drv_LcdGuiBasic_RectangleFill(pthis->x, pthis->y, pthis->x + pthis->width - 1, pthis->y + pthis->hight - 1, 0);  
    Drv_LcdGuiBasic_Line(pthis->x, pthis->y + 12, pthis->x + pthis->width - 1,pthis->y + 12);                          
    Drv_LcdGuiBasic_Line(pthis->x + 12, pthis->y, pthis->x + 12, pthis->y + 12);             
    Drv_LcdGuiBasic_Line(pthis->x, pthis->y, pthis->x + 12, pthis->y + 12);
    Drv_LcdGuiBasic_Line(pthis->x + 12, pthis->y, pthis->x, pthis->y + 12);

    
    /* 写标题 */
    if (pthis->title != NULL)
    {
        str = pthis->title;
        bak = pthis->x + 15;
        bak1 = pthis->y + 3;
        bak2 = pthis->x + pthis->width - 1;

        while (1)
        {
            if ((bak + 8) > bak2) break;                            
            if (*str == '\0') break;                                   
            Drv_LcdGuiBasic_Drawfont(GUIBASIC_ASCII, bak, bak1, *str++);
            bak += 6;
        }
    }

    
    /* 写状态栏 */
    if ( pthis->state != NULL )
    {
        // 判断是否可以画状态栏
        if ( pthis->hight < 60) return (0);                             
        // 画状态栏 
        Drv_LcdGuiBasic_Line(pthis->x, pthis->y + pthis->hight - 11, pthis->x + pthis->width - 1, pthis->y + pthis->hight - 11);

        str = pthis->state;
        bak = pthis->x + 3;
        bak1 = pthis->y + pthis->hight - 9;
        bak2 = pthis->x + pthis->width - 1;

        while (1)
        {
            if ( (bak + 8) > bak2 ) break;                        
            if (*str == '\0') break;                                   
            Drv_LcdGuiBasic_Drawfont(GUIBASIC_ASCII, bak, bak1, *str++);
            bak += 6;
        }
    }


    return TRUE;
}


/****************************************************************************
Function: static u8 Drv_LcdGuiWindow_Hide(Window *pthis)
Description:
Input:
Output:
*****************************************************************************/
static u8 Drv_LcdGuiWindow_Hide(Window *pthis)
{
    return TRUE;
}


/****************************************************************************
Function: static void Drv_LcdGuiWindow_Clear(Window *pthis)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdGuiWindow_Clear(Window *pthis)
{

}


/****************************************************************************
Function: Constructor
Description:
Input:
Output:
*****************************************************************************/
CTOR(Window)
FUNCTION_SETTING(Draw,Drv_LcdGuiWindow_Draw);
FUNCTION_SETTING(Hide,Drv_LcdGuiWindow_Hide);
FUNCTION_SETTING(Clear,Drv_LcdGuiWindow_Clear);
END_CTOR
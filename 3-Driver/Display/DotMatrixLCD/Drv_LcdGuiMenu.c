/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdGuiMenu.c
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#define _Drv_LcdGuiMenu_C_
/*common header file*/
# include "Common.h"
# include "lw_oopc.h"
# include "Drv_LcdModel.h"
/*my header file*/
#include "Drv_LcdGuiBasic.h"
#include "Drv_LcdGuiWindow.h"
#include "Drv_LcdGuiMenu.h"


/*Global Data Structure*/

const u8 DCB2HEX_TAB[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

const u8 button_ok[] = 
{
0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x20,0x00,
0x00,0x00,0x00,0x02,0x00,0x40,0x00,0x0E,0x76,0x00,0x01,0x00,0x80,0x00,0x11,0x24,
0x00,0x00,0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,0x00,0x11,0x30,0x00,0x00,
0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,0x00,0x11,0x28,0x00,0x00,0x80,0x80,
0x00,0x11,0x24,0x00,0x00,0x80,0x40,0x00,0x0E,0x76,0x00,0x01,0x00,0x20,0x00,0x00,
0x00,0x00,0x02,0x00,0x18,0x00,0x00,0x00,0x00,0x0C,0x00,0x07,0xFF,0xFF,0xFF,0xFF,
0xF0,0x00
};


u8  GUI_LoadLine(u16 x, u16 y, u8 *dat, u16 no)
{  
    u8   bit_dat;
    u8   i;
    u8  bakc;

   /* 参数过滤 */
   if(x>=Drv_LcdGuiBasic_GetXMax()) return(0);
   if(y>=Drv_LcdGuiBasic_GetYMax()) return(0);
   
   for(i=0; i<no; i++)
   {  /* 判断是否要读取点阵数据 */
      if( (i%8)==0 ) bit_dat = *dat++;
     
      /* 设置相应的点为color或为back_color */
      if( (bit_dat&DCB2HEX_TAB[i&0x07])==0 ) 

        bakc = 0;
         else  bakc = 1;
         Drv_LcdGuiBasic_PutPixel(x,y,bakc);   
     
      if( (++x)>=Drv_LcdGuiBasic_GetXMax() ) return(0);
   }
   
   return(1);
}




void  GUI_LoadPic(u16 x, u16 y, u8 *dat, u16 hno, u16 lno)
{  u32  i;

    for (i = 0; i < lno; i++)
    {

        GUI_LoadLine(x, y, dat, hno);             // 输出一行数据
        y++;                                      // 显示下一行
        dat += (hno >> 3);                        // 计算下一行的数据
        if ( (hno & 0x07) != 0 ) dat++;
    }
}


void  Drv_LcdGuiMenu_ButtonOK(Menu *pthis, u16 x, u16 y)
{  
    GUI_LoadPic(x, y, (u8 *) button_ok, 49, 14);
}



/****************************************************************************
Function: u8 Drv_LcdGuiMenu_MMenuDraw(Menu *pthis)
Description: 
Input: 
Output: 
*****************************************************************************/
u8 Drv_LcdGuiMenu_MMenuDraw(Menu *pthis)
{
    Window *mwin;
    u8 i;
    u8 xx;

    /* 参数过滤 */
    if ((pthis->no) == 0) return (0);

    mwin = pthis->win;                     // 取得窗口句柄
    /* 判断是否可以显示主菜单 */
    if ((mwin->hight) < 50) return (0);
    if ((mwin->width) < 50) return (0);

    /* 画菜单条，并显示菜主单 */
    Drv_LcdGuiBasic_Line(mwin->x, mwin->y + 22, mwin->x + mwin->width - 1, mwin->y + 22);

    xx = mwin->x;
    for (i = 0; i < (pthis->no); i++)
    {
        if ( (xx + MMENU_WIDTH) > (mwin->x + mwin->width) ) return (0);

        Drv_LcdGuiBasic_Drawfont(GUIBASIC_ASCII, xx + 2, mwin->y + 14, *(pthis->str[i]));
        xx += MMENU_WIDTH;
        Drv_LcdGuiBasic_Line(xx, mwin->y + 12, xx, mwin->y + 22);    // 显示主菜单分界线
    }

    return (1);
}


/****************************************************************************
Function:
Description:
Input:
Output:
*****************************************************************************/
CTOR(Menu)
FUNCTION_SETTING(MMenuDraw,Drv_LcdGuiMenu_MMenuDraw);
FUNCTION_SETTING(ButtonOK,Drv_LcdGuiMenu_ButtonOK);
END_CTOR
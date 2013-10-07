/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdGuiBasic.h
Description:
Author:
Version:
Changelog:
*****************************************************************************/

#ifndef _Drv_LcdGuiBasic_H_
#define _Drv_LcdGuiBasic_H_

/*Macro Definition*/
#define GUIBASIC_ASCII 1
#define GUIBASIC_GB1716 2

/*Data Type Specification*/

#ifndef _Drv_LcdGuiBasic_C_
/*Interface Declarations*/
void Drv_LcdGuiBasic_InitGui();
u16 Drv_LcdGuiBasic_GetXMax(void);
u16 Drv_LcdGuiBasic_GetYMax(void);
void Drv_LcdGuiBasic_PutPixel(u16 x, u16 y, u8 color);
void Drv_LcdGuiBasic_Drawfont(u8 Fonttype, u16 x, u16 y, u8 Font);
void Drv_LcdGuiBasic_DrawString(u8 Fonttype, u16 x, u16 y, u8 *str);
void Drv_LcdGuiBasic_Line(u16 x_start, u16 y_start, u16 x_end, u16 y_end);
void Drv_LcdGuiBasic_RectangleFill(u16 x1, u16 y1, u16 x2, u16 y2, u8 Mode);
#endif

#endif
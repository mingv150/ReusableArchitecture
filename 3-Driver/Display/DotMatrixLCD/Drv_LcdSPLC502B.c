/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdSPLC502B.c
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#define _Drv_LcdSPLC502B_C_
/*common header file*/
#include "Common.h"
#include "lw_oopc.h"
#include "Drv_LcdModel.h"
/*my header file*/
#include "Drv_LcdHardware.h"
#include "Drv_LcdSPLC502B.h"


/*Global Data Structure*/


/****************************************************************************
Function: static void delay(__IO uint32_t nCount)
Description:
Input:
Output:
*****************************************************************************/
static void delay(u32 nCount)
{
    u32 index = 0;
    for (index = (10 * nCount); index != 0; index--)
    {
    }
}


/****************************************************************************
Function: static void Drv_LcdSPLC502B_Init(Splc502b *pthis)
Description: 
Input: 
Output: 
*****************************************************************************/
static void Drv_LcdSPLC502B_Init(LCDInterface *pthis)
{
    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev,LCDBus);

    Dev->XMax = SPLC502B_XMAX;
    Dev->YMax = SPLC502B_YMAX;

    Bus->SetBusType(Bus,DRV_LCDHARDWARE_6800);

    Bus->ResetLcd(Bus,0);
	delay(100000);
    Bus->ResetLcd(Bus,1);
    delay(100000);

    Bus->WriteCommand(Bus,0xAF); 
    Bus->WriteCommand(Bus,0x2F); 
    Bus->WriteCommand(Bus,0x81); 
    Bus->WriteCommand(Bus,0x10); 
    Bus->WriteCommand(Bus,0x27); 
    Bus->WriteCommand(Bus,0xA2); 
    Bus->WriteCommand(Bus,0xC0); 
    Bus->WriteCommand(Bus,0xA1); 
    Bus->WriteCommand(Bus,0xA4); 
    Bus->WriteCommand(Bus,0xA6);
    Bus->WriteCommand(Bus,0xAC);
    Bus->WriteCommand(Bus,0x00);
    Bus->WriteCommand(Bus,0x40); 
}


/****************************************************************************
Function: static void Drv_LcdSPLC502B_ReadDot(LCDInterface *pthis,u16 x,u16 y,u32 *color)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdSPLC502B_ReadDot(LCDInterface *pthis,u16 x,u16 y,u32 *color)
{
    u8 x_lsb,x_hsb;
    u8 y_page;

    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev, LCDBus);

    if(x > Dev->XMax)
    {
        x = Dev->XMax;
    }

    if(y > Dev->YMax)
    {
        y = Dev->YMax;
    }      
    
    x_lsb = (x&0x000f);                             
    x_hsb = ((x>>4)&0x000f)+0x10;                             
    
    y_page = (y>>3)+0xb0;                               
    Bus->WriteCommand(Bus,(u32)y_page);

    Bus->WriteCommand(Bus,(u32)x_lsb);
    Bus->WriteCommand(Bus,(u32)x_hsb);
    
    Bus->WriteCommand(Bus,0xe0);                                
    y_page = (u8)Bus->ReadData(Bus);

    *color = (u32)(y_page >> (y&0x07))&0x00000001;   
}


/****************************************************************************
Function: static void Drv_LcdSPLC502B_WriteDot(LCDInterface *pthis,u16 x,u16 y,u8 color)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdSPLC502B_WriteDot(LCDInterface *pthis,u16 x,u16 y,u32 color)
{
    u8 x_lsb,x_hsb;
    u8 y_page;
    u8 dot_mask=0x01;

    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev, LCDBus);

    if(x > Dev->XMax)
    {
        x = Dev->XMax;
    }

    if(y > Dev->YMax)
    {
        y = Dev->YMax;
    }      
	
	x_lsb = (x&0x000f);								
	x_hsb = ((x>>4)&0x000f)+0x10;						      

	switch(y&0x07)
	{
		case 0: dot_mask = 0x01;break;
		case 1: dot_mask = 0x02;break;
		case 2: dot_mask = 0x04;break;
		case 3: dot_mask = 0x08;break;
		case 4: dot_mask = 0x10;break;
		case 5: dot_mask = 0x20;break;
		case 6: dot_mask = 0x40;break;
		case 7: dot_mask = 0x80;break;
	}
	
	y_page = (y>>3)+0xb0;								
	Bus->WriteCommand(Bus,(u32)y_page);

	Bus->WriteCommand(Bus,(u32)x_lsb);
	Bus->WriteCommand(Bus,(u32)x_hsb);
	
	Bus->WriteCommand(Bus,0xe0);								
    y_page = (u8)Bus->ReadData(Bus);

	if(color) 
        y_page |= dot_mask;
	else 
        y_page &= ~dot_mask;

	Bus->WriteData(Bus,(u32)y_page);							
	Bus->WriteCommand(Bus,0xee);								
}


/****************************************************************************
Function: static void Drv_LcdSPLC502B_FillScreen(LCDInterface *pthis,u32 Color)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdSPLC502B_FillScreen(LCDInterface *pthis,u32 Color)
{
    unsigned char i,j,k;
    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev, LCDBus);

    k = Dev->YMax;
    k = k >> 3;

    for (i=0; i<k; i++)
    {
        Bus->WriteCommand(Bus,(u32)(0xb0+i));
        Bus->WriteCommand(Bus,0x10);
        Bus->WriteCommand(Bus,0x00);
        
        for(j=0; j<Dev->XMax; j++)
        {
            Bus->WriteData(Bus,Color);
        }
    }
}


/****************************************************************************
Function: static u16 Drv_LcdSPLC502B_GetXMax(LCDInterface *pthis)
Description:
Input:
Output:
*****************************************************************************/
static u16 Drv_LcdSPLC502B_GetXMax(LCDInterface *pthis)
{
    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev, LCDBus);

    return (u16)Dev->XMax;
}


/****************************************************************************
Function: static u16 Drv_LcdSPLC502B_GetYMax(LCDInterface *pthis)
Description:
Input:
Output:
*****************************************************************************/
static u16 Drv_LcdSPLC502B_GetYMax(LCDInterface *pthis)
{
    Splc502b *Dev = NULL; 
    LCDBus *Bus = NULL;

    Dev = SUB_PTR(pthis,LCDInterface,Splc502b);
    Bus = SUPER_PTR(Dev, LCDBus);

    return (u16)Dev->YMax;
}


/****************************************************************************
Function: Constructor
Description:
Input:
Output:
*****************************************************************************/
CTOR(Splc502b)
SUPER_CTOR(LCDBus);
FUNCTION_SETTING(LCDInterface.Init, Drv_LcdSPLC502B_Init);
FUNCTION_SETTING(LCDInterface.ReadDot,Drv_LcdSPLC502B_ReadDot);
FUNCTION_SETTING(LCDInterface.WriteDot, Drv_LcdSPLC502B_WriteDot);
FUNCTION_SETTING(LCDInterface.FillScreen,Drv_LcdSPLC502B_FillScreen);
FUNCTION_SETTING(LCDInterface.GetXMax,Drv_LcdSPLC502B_GetXMax);
FUNCTION_SETTING(LCDInterface.GetYMax,Drv_LcdSPLC502B_GetYMax);
END_CTOR

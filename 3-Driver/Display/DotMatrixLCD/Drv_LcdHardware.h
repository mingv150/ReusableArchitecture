/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdHardware.h
Description:  
Author:  
Version:  	
Changelog: 
*****************************************************************************/

#ifndef _Drv_LcdHardware_H_
#define _Drv_LcdHardware_H_


/*Macro Definition*/
#define LCDHARDWARE_8080 0
#define LCDHARDWARE_6800 1
#define LCDHARDWARE_SERI 2

#define DRV_LCDHARDWARE_SETCS() GPIO_SetBits(LCD_PORT_CS, LCD_Pin_CS)
#define DRV_LCDHARDWARE_CLRCS() GPIO_ResetBits(LCD_PORT_CS, LCD_Pin_CS)

#define DRV_LCDHARDWARE_SETRS() GPIO_SetBits(LCD_PORT_RS, LCD_Pin_RS)
#define DRV_LCDHARDWARE_CLRRS() GPIO_ResetBits(LCD_PORT_RS, LCD_Pin_RS)

#define DRV_LCDHARDWARE_SETRE() GPIO_SetBits(LCD_PORT_RE, LCD_Pin_RE)
#define DRV_LCDHARDWARE_CLRRE() GPIO_ResetBits(LCD_PORT_RE, LCD_Pin_RE)

#define DRV_LCDHARDWARE_SETWE() GPIO_SetBits(LCD_PORT_WE, LCD_Pin_WE)
#define DRV_LCDHARDWARE_CLRWE() GPIO_ResetBits(LCD_PORT_WE, LCD_Pin_WE)

#define DRV_LCDHARDWARE_SETWR() GPIO_SetBits(LCD_PORT_WR, LCD_Pin_WR)
#define DRV_LCDHARDWARE_CLRWR() GPIO_ResetBits(LCD_PORT_WR, LCD_Pin_WR)

#define DRV_LCDHARDWARE_SETEN() GPIO_SetBits(LCD_PORT_EN, LCD_Pin_EN)
#define DRV_LCDHARDWARE_CLREN() GPIO_ResetBits(LCD_PORT_EN, LCD_Pin_EN)

#define DRV_LCDHARDWARE_SETRESET() GPIO_SetBits(LCD_PORT_RESET, LCD_Pin_RESET) 
#define DRV_LCDHARDWARE_CLRRESET() GPIO_ResetBits(LCD_PORT_RESET, LCD_Pin_RESET)

#define DRV_LCDHARDWARE_WRITEDAT(DAT) GPIO_Write(GPIOE, (u16)DAT<<8)
#define DRV_LCDHARDWARE_READDAT(DAT) DAT = (u32)(GPIO_ReadInputData(GPIOE)>>8)

#define DRV_LCDHARDWARE_DBIN() LCD_DBPins_INOUT(0)
#define DRV_LCDHARDWARE_DBOUT() LCD_DBPins_INOUT(1) 

/*Data Type Specification*/
// LCD总线类
ABS_CLASS(LCDBus)
{
	u8 bustype;
	void (* SetBusType)(LCDBus *pthis, u8 bustype);
	void (* WriteCommand)(LCDBus *pthis, u32 Com);
	u32 (* ReadStatus)(LCDBus *pthis);
	void (* WriteData)(LCDBus *pthis, u32 Dat);
	u32 (* ReadData)(LCDBus *pthis);
    void (* ResetLcd)(LCDBus *pthis, u8 reset);
    void (* BackLight)(LCDBus *pthis, u8 brightness);
};

// 多态：通过接口来实现对不同的类型的LCD对象的操作
INTERFACE(LCDInterface)
{
	void (* Init)(LCDInterface *pthis);
	void (* FillScreen)(LCDInterface *pthis, u32 color);
	void (* WriteDot)(LCDInterface *pthis, u16 x, u16 y, u32 color);
	void (* ReadDot)(LCDInterface *pthis, u16 x, u16 y, u32 *color);
	u16 (* GetXMax)(LCDInterface *pthis);
	u16 (* GetYMax)(LCDInterface *pthis);
};

#ifndef _Drv_LcdHardware_C_
/*Interface Declarations*/

#endif

#endif		
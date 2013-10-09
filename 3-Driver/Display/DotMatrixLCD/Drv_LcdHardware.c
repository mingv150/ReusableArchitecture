/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdHardware.c
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/


#define _Drv_LcdHardware_C_
/*common header file*/
#include "Common.h"
#include "lw_oopc.h"
#include "Drv_LcdModel.h"
/*my header file*/
#include "Device.h"
#include "Drv_LcdHardware.h"


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
Function: static void Drv_LcdHardware_SetBusType(LCDBus *pthis,u8 bustype)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdHardware_SetBusType(LCDBus *pthis,u8 bustype)
{
	pthis->bustype = bustype;
}


/****************************************************************************
Function: static void Drv_LcdHardware_WriteCommand(LCDBus *pthis,u16 Command)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdHardware_WriteCommand(LCDBus *pthis,u32 Command)
{
	switch(pthis->bustype)
	{
	case LCDHARDWARE_8080:
		DRV_LCDHARDWARE_CLRCS();
  		DRV_LCDHARDWARE_CLRRS();
  		DRV_LCDHARDWARE_SETRE();
  		DRV_LCDHARDWARE_CLRWE();
  		DRV_LCDHARDWARE_WRITEDAT(Command);
  		DRV_LCDHARDWARE_SETWE();
  		DRV_LCDHARDWARE_SETRE();
  		DRV_LCDHARDWARE_SETRS();
  		DRV_LCDHARDWARE_SETCS();
		break;
	case LCDHARDWARE_6800:
		DRV_LCDHARDWARE_CLRRS();
		delay(1);
		DRV_LCDHARDWARE_CLRWR();
		delay(1);
		DRV_LCDHARDWARE_WRITEDAT(Command);
		delay(1);
		DRV_LCDHARDWARE_CLRCS();
		delay(1);
		DRV_LCDHARDWARE_SETEN();
		delay(2);
		DRV_LCDHARDWARE_CLREN();
		delay(1);
		DRV_LCDHARDWARE_SETCS();
		delay(1);
		break;
	case DRV_LCDHARDWARE_SERI:
		break;
	default:
		break;	
	}
}


/****************************************************************************
Function: static u8 Drv_LcdHardware_ReadStatus(LCDBus *pthis)
Description:
Input:
Output:
*****************************************************************************/
static u32 Drv_LcdHardware_ReadStatus(LCDBus *pthis)
{
    return 0;
}


/****************************************************************************
Function: static void Drv_LcdHardware_WriteData(LCDBus *pthis,u16 Data)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdHardware_WriteData(LCDBus *pthis,u32 Data)
{
	switch(pthis->bustype)
	{
	case LCDHARDWARE_8080:
		DRV_LCDHARDWARE_CLRCS();
  		DRV_LCDHARDWARE_SETRS();
  		DRV_LCDHARDWARE_SETRE();
  		DRV_LCDHARDWARE_CLRWE();
  		DRV_LCDHARDWARE_WRITEDAT(Data);
  		DRV_LCDHARDWARE_SETWE();
  		DRV_LCDHARDWARE_SETRE();
  		DRV_LCDHARDWARE_SETRS();
  		DRV_LCDHARDWARE_SETCS(); 
		break;
	case LCDHARDWARE_6800:
		DRV_LCDHARDWARE_SETRS();
		delay(1);
		DRV_LCDHARDWARE_CLRWR();
		delay(1);
		DRV_LCDHARDWARE_WRITEDAT(Data);
		delay(1);
		DRV_LCDHARDWARE_CLRCS();
		delay(1);
		DRV_LCDHARDWARE_SETEN();
		delay(2);
		DRV_LCDHARDWARE_CLREN();
		delay(1);
		DRV_LCDHARDWARE_SETCS();
		delay(1);
		break;
	case DRV_LCDHARDWARE_SERI:
		break;
	default:
		break;	
	}
}


/****************************************************************************
Function: static u8 Drv_LcdHardware_ReadData(LCDBus *pthis)
Description:
Input:
Output:
*****************************************************************************/
static u32 Drv_LcdHardware_ReadData(LCDBus *pthis)
{
	u32 Data;
	switch(pthis->bustype)
	{
	case LCDHARDWARE_8080:
		DRV_LCDHARDWARE_DBIN();
		DRV_LCDHARDWARE_CLRCS();
  		DRV_LCDHARDWARE_SETRS();
  		DRV_LCDHARDWARE_CLRRE();
  		DRV_LCDHARDWARE_SETWE();
  		DRV_LCDHARDWARE_READDAT(Data);
  		DRV_LCDHARDWARE_SETWE();
  		DRV_LCDHARDWARE_SETRE();
  		DRV_LCDHARDWARE_SETRS();
  		DRV_LCDHARDWARE_SETCS();
  		DRV_LCDHARDWARE_DBOUT(); 
		break;
	case LCDHARDWARE_6800:
		DRV_LCDHARDWARE_SETRS();
		delay(1);
		DRV_LCDHARDWARE_SETWR();
		delay(1);
		DRV_LCDHARDWARE_CLRCS();
		delay(1);
		DRV_LCDHARDWARE_DBIN();
		DRV_LCDHARDWARE_SETEN();
		delay(2);
		DRV_LCDHARDWARE_CLREN();
		delay(1);
		DRV_LCDHARDWARE_SETEN();
		delay(2);
		DRV_LCDHARDWARE_CLREN();
		delay(1);
		DRV_LCDHARDWARE_READDAT(Data);
		delay(1);
		DRV_LCDHARDWARE_SETCS();
		delay(1);
		DRV_LCDHARDWARE_DBOUT();
		break;
	case DRV_LCDHARDWARE_SERI:
		break;
	default:
		break;	
	}

	return Data;
}


/****************************************************************************
Function: static void Drv_LcdHardware_ResetLcd(LCDBus *pthis,u8 reset)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdHardware_ResetLcd(LCDBus *pthis,u8 reset)
{
    if(reset)
    {
        DRV_LCDHARDWARE_SETRESET();
    }
    else
    {
        DRV_LCDHARDWARE_CLRRESET();
    }
}


/****************************************************************************
Function: static void Drv_LcdHardware_BackLight(LCDBus *pthis,u8 brightness)
Description:
Input:
Output:
*****************************************************************************/
static void Drv_LcdHardware_BackLight(LCDBus *pthis,u8 brightness)
{
    return;
}


/****************************************************************************
Function: Constructor
Description:
Input:
Output:
*****************************************************************************/
ABS_CTOR(LCDBus)
FUNCTION_SETTING(SetBusType,Drv_LcdHardware_SetBusType);
FUNCTION_SETTING(WriteCommand,Drv_LcdHardware_WriteCommand);
FUNCTION_SETTING(ReadStatus,Drv_LcdHardware_ReadStatus);
FUNCTION_SETTING(WriteData,Drv_LcdHardware_WriteData);
FUNCTION_SETTING(ReadData,Drv_LcdHardware_ReadData);
FUNCTION_SETTING(ResetLcd,Drv_LcdHardware_ResetLcd);
FUNCTION_SETTING(BackLight,Drv_LcdHardware_BackLight);
END_ABS_CTOR
/****************************************************************************
Copyright (C), Year, Mingv150, All rights reserved
FileName: /Driver/Keypad/Key.c
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#define _Key_C_
/****************************************************************************
Global header file:
*****************************************************************************/
#include "Common.h"
//#include "lw_oopc.h"

#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xhw_nvic.h"
#include "xsysctl.h"
#include "xgpio.h"

/****************************************************************************
Local header file:
*****************************************************************************/
#include "Key.h"

/****************************************************************************
Global Data Structure:
*****************************************************************************/
//static u8 Led_Purpose;


/****************************************************************************
Function: Key_Set
Description:
Input:
Output:
Notes:
*****************************************************************************/
static void Key_Set(t_Key *pKey,u8 Key,u32 Level)
{
    if(Level)
    {
        SETBIT(pKey->IOState[Key/BIT_SIZE(t_Key_Arraytype)],Key%BIT_SIZE(t_Key_Arraytype));
    }
    else
    {
        CLRBIT(pKey->IOState[Key/BIT_SIZE(t_Key_Arraytype)],Key%BIT_SIZE(t_Key_Arraytype));
    }
}


/****************************************************************************
Function: Key_Scan
Description:
Input:
Output:
Notes:
*****************************************************************************/
static void Key_Scan(t_Key *pKey)
{
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOB);
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN );
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_10, xGPIO_DIR_MODE_IN );
    
	Key_Set(pKey,KEY_0,xGPIOPinRead(xGPIO_PORTC_BASE,xGPIO_PIN_4));
    Key_Set(pKey,KEY_1,xGPIOPinRead(xGPIO_PORTB_BASE,xGPIO_PIN_10));
    
}


/****************************************************************************
Function: Key_Debounce
Description:
Input:
Output:
Notes:
*****************************************************************************/
static void Key_Debounce(t_Key *pKey)
{
    u8 i,j;
    
    for(i=0; i<ARR_SIZE(pKey->IOState); i++)
    {
        if(pKey->IOState[i] != pKey->IOStateBuf[i])
        {
            pKey->IOStateBuf[i] = pKey->IOState[i];
            pKey->IODebounce[i] = 0;
        }
        else if(pKey->IODebounce[i] < KEY_DEBOUNCE)
        {
            pKey->IODebounce[i]++;
        }
        else
        {
            pKey->KeyEvent = pKey->IOState[i]^pKey->IOStatePre[i];
            pKey->IOStatePre[i] = pKey->IOState[i];
            pKey->KeyState = pKey->IOState[i];
            
            for(j=0; j<(BIT_SIZE(t_Key_Arraytype)); j++)
            {
                if(REDBIT(pKey->KeyEvent,j))
                {
                    if(REDBIT(pKey->KeyState,j))
                    {
                        pKey->SendEventCb(j+i*(BIT_SIZE(t_Key_Arraytype)),KEY_HIGH);
                    }
                    else
                    {
                        pKey->SendEventCb(j+i*(BIT_SIZE(t_Key_Arraytype)),KEY_LOW);
                    }
                }
            }           
        }
    }
}


/****************************************************************************
Function: Key_Process
Description:
Input:
Output:
Notes:
*****************************************************************************/
void Key_Process(t_Key_Send CbFun)
{
    static t_Key KeyObj;

    KeyObj.SendEventCb = CbFun;
    Key_Scan(&KeyObj);
    Key_Debounce(&KeyObj);
}

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
static void Key_Set(t_Key *pKey,u8 Key,u8 Level)
{
    if(Level)
    {
        SETBIT(pKey->IOState[Key/32],Key%32);
    }
    else
    {
        CLRBIT(pKey->IOState[Key/32],Key%32);
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
    Key_Set(pKey,KEY_0,gpio0);
    Key_Set(pKey,KEY_1,gpio1);
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
            pKey->Debounce[i] = 0;
        }
        else if(pKey->Debounce[i] < SHORTDEBOUNCE)
        {
            pKey->Debounce[i]++;
        }
        else
        {
            pKey->KeyEvent = pKey->IOState[i]^pKey->IOStatePre[i];
            pKey->IOStatePre[i] = pKey->IOState[i];
            pKey->KeyState = pKey->IOState[i];
            
            for(j=0; j<(sizeof(pKey->KeyEvent)<<4); j++)
            {
                if(REDBIT(pKey->KeyEvent,j))
                {
                    if(REDBIT(pKey->KeyState,j))
                    {
                        pKey->SendEventCb(j+i*(sizeof(pKey->KeyEvent)<<4),KEY_HIGH);
                    }
                    else
                    {
                        pKey->SendEventCb(j+i*(sizeof(pKey->KeyEvent)<<4),KEY_LOW);
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

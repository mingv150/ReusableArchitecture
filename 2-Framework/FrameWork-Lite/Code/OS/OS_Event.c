/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Changelog:
*******************************************************************************/
#define _OS_EVENT_C_

#include "../Common.h"
#include "../oopc.h"
#include "../Model.h"

#include "OS_Event.h"

#include "OS_Dispatch.h"


u8 u8_Event_SigBuf1[EVENT_BUF1SIZE];
u8 u8_Event_SigBuf2[EVENT_BUF2SIZE];
u8 u8_Event_SigBuf3[EVENT_BUF3SIZE];
u8 u8_Event_SigBuf4[EVENT_BUF4SIZE];
u8 u8_Event_SigBuf5[EVENT_BUF5SIZE];
u8 u8_Event_SigBuf6[EVENT_BUF6SIZE];
u8 u8_Event_SigBuf7[EVENT_BUF7SIZE];
u8 u8_Event_SigBuf8[EVENT_BUF8SIZE];

u8 u8_Event_ParBuf1[EVENT_BUF1SIZE];
u8 u8_Event_ParBuf2[EVENT_BUF2SIZE];
u8 u8_Event_ParBuf3[EVENT_BUF3SIZE];
u8 u8_Event_ParBuf4[EVENT_BUF4SIZE];
u8 u8_Event_ParBuf5[EVENT_BUF5SIZE];
u8 u8_Event_ParBuf6[EVENT_BUF6SIZE];
u8 u8_Event_ParBuf7[EVENT_BUF7SIZE];
u8 u8_Event_ParBuf8[EVENT_BUF8SIZE];


t_Event st_Event_List[8] =
{
    {0,0,EVENT_BUF1SIZE,u8_Event_SigBuf1,u8_Event_ParBuf1},
    {0,0,EVENT_BUF2SIZE,u8_Event_SigBuf2,u8_Event_ParBuf2},
    {0,0,EVENT_BUF3SIZE,u8_Event_SigBuf3,u8_Event_ParBuf3},
    {0,0,EVENT_BUF4SIZE,u8_Event_SigBuf4,u8_Event_ParBuf4},
    {0,0,EVENT_BUF5SIZE,u8_Event_SigBuf5,u8_Event_ParBuf5},
    {0,0,EVENT_BUF6SIZE,u8_Event_SigBuf6,u8_Event_ParBuf6},
    {0,0,EVENT_BUF7SIZE,u8_Event_SigBuf7,u8_Event_ParBuf7},
    {0,0,EVENT_BUF8SIZE,u8_Event_SigBuf8,u8_Event_ParBuf8}
};

       
/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Event_Init(void)
{


}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
u8 OS_Event_PutEvent(u8 Prio,u8 Signal,u8 Param)
{
    t_Event *pEvent;
    u8 ReValue;
    
    pEvent = &st_Event_List[Prio];

    OS_ENTER_CRITICAL();
    if(pEvent->OutIndex == (pEvent->InIndex+1)%pEvent->QueSize)
    {
        ReValue = FALSE;
    }
    else if(pEvent->OutIndex == pEvent->InIndex)
    {
        OS_Dispatch_SetTaskReady(Prio,Signal,Param);
        ReValue = TRUE;
    }
    else
    {
        if(pEvent->SigQuePtr == NULL || pEvent->ParQuePtr == NULL)
        {
            ReValue = FALSE;
        }
        else
        {
            pEvent->SigQuePtr[pEvent->InIndex] = Signal;
            pEvent->ParQuePtr[pEvent->InIndex] = Param;
            pEvent->InIndex = (++pEvent->InIndex)%pEvent->QueSize;
            ReValue = TRUE;
        }
    }
    OS_EXIT_CRITICAL();
    return ReValue;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
u8 OS_Event_PutEventISR(u8 Prio,u8 Signal,u8 Param)
{
    t_Event *pEvent;
    u8 ReValue;
    
    pEvent = &st_Event_List[Prio];

    if(pEvent->OutIndex == (pEvent->InIndex+1)%pEvent->QueSize)
    {
        ReValue = FALSE;
    }
    else if(pEvent->OutIndex == pEvent->InIndex)
    {
        OS_Dispatch_SetTaskReady(Prio,Signal,Param);
        ReValue = TRUE;
    }
    else
    {
        if(pEvent->SigQuePtr == NULL || pEvent->ParQuePtr == NULL)
        {
            ReValue = FALSE;
        }
        else
        {
            pEvent->SigQuePtr[pEvent->InIndex] = Signal;
            pEvent->ParQuePtr[pEvent->InIndex] = Param;
            pEvent->InIndex = (++pEvent->InIndex)%pEvent->QueSize;
            ReValue = TRUE;
        }
    }
    return ReValue;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Event_GetEvent(u8 Prio,u8 *pSignal,u8 *pParam)
{
    u8 key;
    t_Event *pEvent;

    pEvent = &st_Event_List[Prio];

    if(pEvent->OutIndex == pEvent->InIndex)
    {
        *pSignal = EVENT_EMPTYSIG;
        *pParam = EVENT_EMPTYSIG;
        return;
    }
    
    *pSignal = pEvent->SigQuePtr[pEvent->OutIndex]; 
    *pParam = pEvent->ParQuePtr[pEvent->OutIndex];
    pEvent->OutIndex = (++pEvent->OutIndex)%pEvent->QueSize;
}

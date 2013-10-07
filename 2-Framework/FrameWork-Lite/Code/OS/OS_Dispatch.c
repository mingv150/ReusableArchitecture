/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Changelog:
*******************************************************************************/
#define _OS_DISPATCH_C_

#include "../Common.h"
#include "../oopc.h"
#include "../Model.h"

#include "OS_Dispatch.h"

#include "OS_Event.h"


t_Dispatch st_Dispatch = 
{
    {0}
};

t_Task st_TaskList[16] = 
{
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0},
    {NULL,0,0}
};


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Dispatch_SetTaskReady(u8 Prio,u8 Signal,u8 Param)
{
    SETBIT(st_Dispatch.ReadyList,Prio);
    st_TaskList[Prio].EventSig = Signal;
    st_TaskList[Prio].EventParam = Param;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Dispatch_SetTaskIdle(u8 Prio)
{
    CLRBIT(st_Dispatch.ReadyList,Prio);
    st_TaskList[Prio].EventSig = EVENT_EMPTYSIG;
    st_TaskList[Prio].EventParam = EVENT_EMPTYSIG;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Dispatch_Scheduler(void)
{
    u8 i;
	u8 Prionum;
	u16 ReadyList;
    t_Task *pTask;

    ReadyList = st_Dispatch.ReadyList;
    
    if(ReadyList == 0)
    {
        return;
    }

    for(i=(sizeof(ReadyList)<<4);i>0;i--)
    {
        if(REDBIT(ReadyList,i-1))
        {
            Prionum = i-1;
            break;
        }
    }

    pTask = &st_TaskList[Prionum];

    if(pTask->TaskFun == NULL)
    {
        return;
    }
    pTask->TaskFun(pTask);

    if(pTask->EventSig == EVENT_EMPTYSIG)
    {
        pTask->EventSig = EVENT_EXITSIG;
        pTask->TaskFun(pTask);
        pTask->EventSig = EVENT_ENTRYSIG;
        pTask->TaskFun(pTask);
    }

    OS_ENTER_CRITICAL();

    OS_Event_GetEvent(Prionum,&pTask->EventSig,&pTask->EventParam);

    if(pTask->EventSig == EVENT_EMPTYSIG)
    {
        OS_Dispatch_SetTaskIdle(Prionum);
    }

    OS_EXIT_CRITICAL(); 
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Dispatch_TaskInit(u8 Prio,t_TaskFun Fun)
{
    t_Task *pTask;

    pTask = &st_TaskList[Prio];
    pTask->TaskFun = Fun;
    pTask->EventSig = EVENT_ENTRYSIG;
    pTask->TaskFun(pTask);    
}

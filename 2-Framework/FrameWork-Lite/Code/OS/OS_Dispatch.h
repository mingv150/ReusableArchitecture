/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Changelog:
*******************************************************************************/
#ifndef _OS_DISPATCH_H_
#define _OS_DISPATCH_H_


typedef struct
{
    u16 ReadyList;
}t_Dispatch;

typedef struct Task
{
    void (*TaskFun)(struct Task *);
    u8 EventSig;
    u8 EventParam;
}t_Task;

typedef void (*t_TaskFun)(t_Task *);


#ifndef _OS_DISPATCH_C_
void OS_Dispatch_SetTaskReady(u8 Prio,u8 Signal,u8 Param);
void OS_Dispatch_SetTaskIdle(u8 Prio);
void OS_Dispatch_TaskInit(u8 Prio,t_TaskFun Fun);
void OS_Dispatch_Scheduler(void);
#endif

#endif

/*******************************************************************************
*Copyright(C),2012-2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Date:
*******************************************************************************/
#ifndef _OS_TIMER_H_
#define _OS_TIMER_H_

#define TIMER_TIMERNUM  5
#define TIMER_NOTIMER   0xFF
#define TIMER_INFINITE  0xF


typedef void (*t_Timer_CBFun)(void *pCbParam);

typedef struct
{
    u8 TimerID:6;
    u8 IsActive:1;
    u8 TimeOut:1;
    u8 RepeatTotal:4;
    u8 RepeatCount:4;
    u32 Tick;
    u32 Time;
    void *pCbParam;
    t_Timer_CBFun pCbFun;

}t_TimerAttr;


#ifndef _OS_TIMER_C_
void OS_Timer_Init(void);
u8 OS_Timer_Create(u32 MSecs,u8 Repeat,t_Timer_CBFun FunCb,void *pCbParam);
u8 OS_Timer_Cancel(u8 *pTimerID);
u8 OS_Timer_TimeOutChk(u8 TimerID);
void OS_Timer_Scan(void);
#endif

#endif


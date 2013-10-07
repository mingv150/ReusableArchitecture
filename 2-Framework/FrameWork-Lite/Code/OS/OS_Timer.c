/*******************************************************************************
*Copyright(C),2012-2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Date:
*******************************************************************************/

#define _OS_TIMER_C_
/*Common*/
#include "../Common.h"
#include "../oopc.h"
#include "../Model.h"

/*myself*/
#include "OS_Timer.h"

/*mycall*/


static t_TimerAttr st_Timer_Attr[TIMER_TIMERNUM]=
{
    {0,0,0,0,0,0,0,NULL},
    {1,0,0,0,0,0,0,NULL},
    {2,0,0,0,0,0,0,NULL},
    {3,0,0,0,0,0,0,NULL},
    {4,0,0,0,0,0,0,NULL}
};


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Timer_Init(void)
{
    u8 i;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
		st_Timer_Attr[i].TimerID = i;
		st_Timer_Attr[i].IsActive = 0;
		st_Timer_Attr[i].RepeatTotal = 0;
		st_Timer_Attr[i].RepeatCount = 0;
		st_Timer_Attr[i].Tick = 0;
		st_Timer_Attr[i].Time = 0;
		st_Timer_Attr[i].TimeOut = 0;
		st_Timer_Attr[i].pCbParam = NULL;
		st_Timer_Attr[i].pCbFun = NULL;
    }
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
u8 OS_Timer_Create(u32 MSecs,u8 Repeat,t_Timer_CBFun FunCb,void *pCbParam)
{
    u8 i = 0;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
        if(!st_Timer_Attr[i].IsActive)
        {
            if(Repeat == 0)
            {
                Repeat = 1;
            }
            st_Timer_Attr[i].Tick = 0;
            st_Timer_Attr[i].Time = MSecs;
			st_Timer_Attr[i].RepeatCount = 0;	

            st_Timer_Attr[i].RepeatTotal = Repeat;
            st_Timer_Attr[i].TimeOut = 0;
            st_Timer_Attr[i].pCbFun = FunCb;
            st_Timer_Attr[i].pCbParam = pCbParam;
            st_Timer_Attr[i].IsActive = 1;
            return st_Timer_Attr[i].TimerID;
        }
    }

    return TIMER_NOTIMER;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
u8 OS_Timer_Cancel(u8 *pTimerID)
{
    u8 i;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
        if(st_Timer_Attr[i].TimerID == *pTimerID)
        {
            st_Timer_Attr[i].IsActive = 0;
            st_Timer_Attr[i].RepeatTotal = 0;
            st_Timer_Attr[i].RepeatCount = 0;
            st_Timer_Attr[i].Tick = 0;
            st_Timer_Attr[i].Time = 0;
            st_Timer_Attr[i].TimeOut = 0;
            st_Timer_Attr[i].pCbParam = NULL;
            st_Timer_Attr[i].pCbFun = NULL;
            *pTimerID = TIMER_NOTIMER;
            return TRUE;
        }
    }

    return FALSE;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
u8 OS_Timer_TimeOutChk(u8 TimerID)
{
	u8 i;
	
	for(i=0;i<TIMER_TIMERNUM;i++)
	{
		if(st_Timer_Attr[i].TimerID == TimerID)
		{
			if(st_Timer_Attr[TimerID].TimeOut)
			{
				st_Timer_Attr[TimerID].TimeOut = 0;
				return TRUE;
			}
		}
	}
	return FALSE;
}


/*******************************************************************************
*Function:
*Description:
*Input:
*Output:
*******************************************************************************/
void OS_Timer_Scan(void)
{
    u8 i;
    //u8 IDtemp = 0;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
        if(st_Timer_Attr[i].IsActive)
        {
            if(st_Timer_Attr[i].Tick == st_Timer_Attr[i].Time)
            {
                st_Timer_Attr[i].Tick = 0;

                if(st_Timer_Attr[i].RepeatTotal == TIMER_INFINITE)
                {
                    st_Timer_Attr[i].TimeOut = 1;
                    if(st_Timer_Attr[i].pCbFun != NULL)
                    {
                        st_Timer_Attr[i].pCbFun(st_Timer_Attr[i].pCbParam);
                    }
                }
                else
                {
                    st_Timer_Attr[i].RepeatCount++;

                    if(st_Timer_Attr[i].RepeatCount <= st_Timer_Attr[i].RepeatTotal)
                    {
                        st_Timer_Attr[i].TimeOut = 1;
                        if(st_Timer_Attr[i].pCbFun != NULL)
                        {
                            st_Timer_Attr[i].pCbFun(st_Timer_Attr[i].pCbParam); 
                        }
                    }
                    else
                    {
                        //IDtemp = st_Timer_Attr[i].TimerID;
                        //Drv_Timer_Cancel(&IDtemp);
                        st_Timer_Attr[i].IsActive = 0;
                        st_Timer_Attr[i].RepeatTotal = 0;
                        st_Timer_Attr[i].RepeatCount = 0;
                        st_Timer_Attr[i].Tick = 0;
                        st_Timer_Attr[i].Time = 0;
                        //st_Timer_Attr[i].TimeOut = 0;
                        st_Timer_Attr[i].pCbParam = NULL;
                        st_Timer_Attr[i].pCbFun = NULL;
                    }
                }
            }
            else
            {
                st_Timer_Attr[i].Tick++;
            }
        }
    }
}


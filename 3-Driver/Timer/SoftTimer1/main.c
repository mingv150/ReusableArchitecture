#include <stdio.h>
#include <stdlib.h>

/*
http://www.cnblogs.com/bandynewer/archive/2012/05/29/2523704.html
使用硬件定时器软模拟多个定时器（8.15改进版)
在嵌入式平台中，界面有许多的数据需要定时刷新，而硬件资源不可能提供大量的定时器。

在没有上系统的情况下，使用该方法模拟定时器是不错的方法。如果非裸奔大可不必如此麻烦。

该方法可单独使用也可以结合GUI中的消息循环配套使用，也可以给应用层定时获取底层数据。

基本思路：用结构体表示定时器，用结构体数组存放多个定时器，初始化模拟定时器时设定定时的最大时间。每个定时器固定ID。

定时器的管理人工实现，定时中断扫描整个数组来完成定时过程。

　　　　　通过SetTimer和KillTimer来设置和取消定时器。

在定时器数量较少的情况下，扫描速度对定时影响可满足一般应用需求。

　　　　  整体与windows定时处理机制类似。

与消息循环配合

这种实现方法效果非常好，定时器精度较高。定时器中断中完成以下过程：扫描数组，比较时间，发送消息，退出。

指向函数使用

定时精确度与指向的函数复杂度成反比。一般用于定时扫描键盘，或者扫描其他硬件返回值。定时器中断需要完成以下过程：扫描

　　数组，比较时间，所指向函数完整完成，退出。

以下是相关源代码，在IAR5.5编译通过，芯片STM32F207，LIB版本3.5。

本函数代码是与消息队列配合使用。

如需单独使用，请修改中断函数。

1.定时器的初始化。这个只要看官方例程。

定时器中断函数，能放简单的处理语句，复杂函数，复杂语句建议不要使用
*/

#define TIMER_TIMERNUM 5
#define TIMER_NOTIMER   0xFF
#define TIMER_INFINITE  0xF
#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned int u32;
typedef signed int s32;


typedef void (*t_TimerCB)(void);

typedef struct
{
    u8 TimerID:6;
    u8 IsActive:1;
	u8 TimeOut:1;
    u8 RepeatTotal:4;
    u8 RepeatCount:4;
    u16 Tick;
    u16 Time;
    t_TimerCB CallBack;

}t_TimerAttr;

t_TimerAttr st_Timer_Attr[TIMER_TIMERNUM]=
{
    {0,0,0,0,0,0,0,NULL},
    {1,0,0,0,0,0,0,NULL},
    {2,0,0,0,0,0,0,NULL},
    {3,0,0,0,0,0,0,NULL},
    {4,0,0,0,0,0,0,NULL}
};


void Timer_Init()
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
		st_Timer_Attr[i].CallBack = NULL;
    }
}

u8 Timer_Create(u16 MSecs,u8 Repeat,t_TimerCB FunCb)
{
    u8 i = 0;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
        if(!st_Timer_Attr[i].IsActive)
        {
            if(FunCb==NULL)
                return TIMER_NOTIMER;
            st_Timer_Attr[i].Tick = 0;
            st_Timer_Attr[i].Time = MSecs;
			st_Timer_Attr[i].RepeatCount = 0;
            st_Timer_Attr[i].RepeatTotal = Repeat;
			st_Timer_Attr[i].TimeOut = 0;
			st_Timer_Attr[i].CallBack = FunCb;
            st_Timer_Attr[i].IsActive = 1;
            return st_Timer_Attr[i].TimerID;
        }
    }

    return TIMER_NOTIMER;
}

u8 Timer_Cancel(u8 TimerID)
{
    u8 i;

    for(i=0;i<TIMER_TIMERNUM;i++)
    {
        if(st_Timer_Attr[i].TimerID == TimerID)
        {
            st_Timer_Attr[i].IsActive = 0;
            st_Timer_Attr[i].RepeatTotal = 0;
            st_Timer_Attr[i].RepeatCount = 0;
            st_Timer_Attr[i].Tick = 0;
            st_Timer_Attr[i].Time = 0;
            st_Timer_Attr[i].TimeOut = 0;
            st_Timer_Attr[i].CallBack = NULL;
            return TRUE;
        }
    }

    return FALSE;
}

u8 Timer_TimeOutChk(u8 TimerID)
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

void Timer_Scan(void)
{
    u8 i;

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
                    if(st_Timer_Attr[i].CallBack != NULL)
                        st_Timer_Attr[i].CallBack();
                }
                else
                {
                    st_Timer_Attr[i].RepeatCount++;

                    if(st_Timer_Attr[i].RepeatCount <= st_Timer_Attr[i].RepeatTotal)
                    {
						st_Timer_Attr[i].TimeOut = 1;
                        if(st_Timer_Attr[i].CallBack != NULL)
                            st_Timer_Attr[i].CallBack();
                    }
                    else
                    {
                        Timer_Cancel(st_Timer_Attr[i].TimerID);
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

int main()
{
    while(1)
    {
        Timer_Scan();
    }
    printf("Hello world!\n");
    return 0;
}

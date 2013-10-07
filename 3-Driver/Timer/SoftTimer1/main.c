#include <stdio.h>
#include <stdlib.h>

/*
http://www.cnblogs.com/bandynewer/archive/2012/05/29/2523704.html
ʹ��Ӳ����ʱ����ģ������ʱ����8.15�Ľ���)
��Ƕ��ʽƽ̨�У�����������������Ҫ��ʱˢ�£���Ӳ����Դ�������ṩ�����Ķ�ʱ����

��û����ϵͳ������£�ʹ�ø÷���ģ�ⶨʱ���ǲ���ķ�����������㱼��ɲ�������鷳��

�÷����ɵ���ʹ��Ҳ���Խ��GUI�е���Ϣѭ������ʹ�ã�Ҳ���Ը�Ӧ�ò㶨ʱ��ȡ�ײ����ݡ�

����˼·���ýṹ���ʾ��ʱ�����ýṹ�������Ŷ����ʱ������ʼ��ģ�ⶨʱ��ʱ�趨��ʱ�����ʱ�䡣ÿ����ʱ���̶�ID��

��ʱ���Ĺ����˹�ʵ�֣���ʱ�ж�ɨ��������������ɶ�ʱ���̡�

����������ͨ��SetTimer��KillTimer�����ú�ȡ����ʱ����

�ڶ�ʱ���������ٵ�����£�ɨ���ٶȶԶ�ʱӰ�������һ��Ӧ������

��������  ������windows��ʱ����������ơ�

����Ϣѭ�����

����ʵ�ַ���Ч���ǳ��ã���ʱ�����Ƚϸߡ���ʱ���ж���������¹��̣�ɨ�����飬�Ƚ�ʱ�䣬������Ϣ���˳���

ָ����ʹ��

��ʱ��ȷ����ָ��ĺ������Ӷȳɷ��ȡ�һ�����ڶ�ʱɨ����̣�����ɨ������Ӳ������ֵ����ʱ���ж���Ҫ������¹��̣�ɨ��

�������飬�Ƚ�ʱ�䣬��ָ����������ɣ��˳���

���������Դ���룬��IAR5.5����ͨ����оƬSTM32F207��LIB�汾3.5��

����������������Ϣ�������ʹ�á�

���赥��ʹ�ã����޸��жϺ�����

1.��ʱ���ĳ�ʼ�������ֻҪ���ٷ����̡�

��ʱ���жϺ������ܷż򵥵Ĵ�����䣬���Ӻ�����������佨�鲻Ҫʹ��
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

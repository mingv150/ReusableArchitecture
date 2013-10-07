#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef unsigned short int s16;
typedef unsigned int u32;
typedef unsigned int s32;

typedef void(*t_StateFun)(void);

enum
{
    FSM_STATEA = 0,
    FSM_STATEB,
    FSM_STATEC,
    FSM_STATED,
    FSM_STATEMAX
};

enum
{
    FSM_EVENTA = 0,
    FSM_EVENTB,
    FSM_EVENTC,
    FSM_EVENTD,
    FSM_EVENTMAX
};

typedef struct fsm
{
    u8 StateID;
    u8 StateTabSize;
    const u8 *StateTabPst;
    t_StateFun StateFun;
}t_fsm;

const u8 u8_fsm_ATab[][2] =
{
    {FSM_EVENTA,FSM_STATEA},
    {FSM_EVENTB,FSM_STATEB},
    {FSM_EVENTC,FSM_STATEC},
    {FSM_EVENTD,FSM_STATED},
};

const u8 u8_fsm_BTab[][2] =
{
    {FSM_EVENTA,FSM_STATEA},
    {FSM_EVENTB,FSM_STATEB},
    {FSM_EVENTC,FSM_STATEC},
    {FSM_EVENTD,FSM_STATED}
};

const u8 u8_fsm_CTab[][2] =
{
    {FSM_EVENTA,FSM_STATEA},
    {FSM_EVENTB,FSM_STATEB},
    {FSM_EVENTC,FSM_STATEC},
    {FSM_EVENTD,FSM_STATED}
};

const u8 u8_fsm_DTab[][2] =
{
    {FSM_EVENTA,FSM_STATEA},
    {FSM_EVENTB,FSM_STATEB},
    {FSM_EVENTC,FSM_STATEC},
    {FSM_EVENTD,FSM_STATED}
};

u8 getevent()
{
    static volatile u8 event = 0;

    event = (++event)%FSM_EVENTMAX;

    return event;
}

void FunA()
{
    printf("i am StateA\n");
}

void FunB()
{
    printf("i am StateB\n");
}

void FunC()
{
    printf("i am StateC\n");
}

void FunD()
{
    printf("i am StateD\n");
}

const t_fsm st_fsm_StateSet[] =
{
    {FSM_STATEA,sizeof(u8_fsm_ATab),&u8_fsm_ATab[0][0],FunA},
    {FSM_STATEB,sizeof(u8_fsm_BTab),&u8_fsm_BTab[0][0],FunB},
    {FSM_STATEC,sizeof(u8_fsm_CTab),&u8_fsm_CTab[0][0],FunC},
    {FSM_STATED,sizeof(u8_fsm_DTab),&u8_fsm_DTab[0][0],FunD}
};


void fsm_Process()
{
    u8 i,j;
    u8 Event;
    static u8 SystemState = FSM_STATEA;

    for(i=0;i<sizeof(st_fsm_StateSet)/sizeof(st_fsm_StateSet[0]);i++)
    {
        if(SystemState == st_fsm_StateSet[i].StateID)
        {
            st_fsm_StateSet[i].StateFun();

            Event = getevent();

            for(j=0;j<st_fsm_StateSet[i].StateTabSize/2;j++)
            {
                if(Event == st_fsm_StateSet[i].StateTabPst[j*2+0])
                {
                    SystemState = st_fsm_StateSet[i].StateTabPst[j*2+1];
                }
            }
        }
        else
        {
            SystemState = FSM_STATEA;
        }
    }
}

int main()
{
    while(1)
    {
        fsm_Process();
    }

    return 0;
}

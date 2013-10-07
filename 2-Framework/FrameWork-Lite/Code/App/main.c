/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description: 
*Author:
*Version:
*Changelog:
*******************************************************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include <htc.h>
#include "../Common.h"
#include "../oopc.h"
#include "../Model.h"

#include "../OS/OS_Dispatch.h"
#include "../OS/OS_Event.h"
#include "../OS/OS_Timer.h"

void App_Task1(t_Task *pMySelf)
{

}

void App_Task2(t_Task *pMySelf)
{

}

void App_Task3(t_Task *pMySelf)
{

}

void App_Task4(t_Task *pMySelf)
{

}




int main()
{

    OS_Timer_Init();
    OS_Event_Init();
    OS_Dispatch_TaskInit(1,App_Task1);
    OS_Dispatch_TaskInit(1,App_Task2);
    OS_Dispatch_TaskInit(1,App_Task3);
    OS_Dispatch_TaskInit(1,App_Task4);
    
    //printf("Hello world!\n");
    return 0;
}

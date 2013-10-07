/*******************************************************************************
*Copyright(C),2012-2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Date:
*******************************************************************************/
#define _MAIN_C_
#include <stdio.h>
#include <stdlib.h>
#include "Drv_NTC.h"

int main(void)
{
    u32 ResVal = 0;

    printf("Input a temperature val (0x007f ~ 0x7efe): \n");
    scanf("%x", &ResVal);
    printf("Resistor Value = %x\n", ResVal);
    printf("Return Temperature = %5.2f\n", Drv_NTC_CheckTem(ResVal));
    return 0;
}


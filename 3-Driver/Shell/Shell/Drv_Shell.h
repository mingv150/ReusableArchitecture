/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_Shell.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Drv_Shell_H_
#define _Drv_Shell_H_

/*Macro Definition*/
//used to expand TABs
#define  SHELL_TABSIZE 4
#define  SHELL_TABSEQ ("    ")
//erase sequence
#define  SHELL_ERASE_SEQ ("\b \b") 

/*Data Type Specification*/
typedef struct
{
    //name
    char *name;
    //Usage message     
    char *usage;
    //function   
    void (*CmdFun)(char *para);
}t_Cmd;


#ifndef _Drv_Shell_C_
/*Interface Declarations*/

#endif

#endif
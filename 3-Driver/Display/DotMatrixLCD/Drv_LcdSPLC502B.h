/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdSPLC502B.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Drv_LcdSPLC502B_H_
#define _Drv_LcdSPLC502B_H_

/*Macro Definition*/
#define SPLC502B_XMAX (132)
#define SPLC502B_YMAX (64)  

/*Data Type Specification*/

CLASS(Splc502b)
{
    u16 XMax;
	u16 YMax;
    // 继承LCD总线类
    EXTENDS(LCDBus);
    // 实现通用LCD接口
	IMPLEMENTS(LCDInterface);
};

#ifndef _Drv_LcdSPLC502B_C_
/*Interface Declarations*/

#endif

#endif
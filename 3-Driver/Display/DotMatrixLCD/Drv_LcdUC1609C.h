/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_LcdUC1609C.h
Description:  
Author:  
Version:  
Changelog: 
*****************************************************************************/

#ifndef _Drv_LcdUC1609C_H_
#define _Drv_LcdUC1609C_H_

/*Macro Definition*/
#define UC1609C_XMAX (192)
#define UC1609C_YMAX (64) 

/*Data Type Specification*/
CLASS(Uc1609c)
{
    u16 XMax;
	u16 YMax;
    // 继承LCD总线类
    EXTENDS(LCDBus);
    // 实现通用LCD接口
	IMPLEMENTS(LCDInterface);
};

#ifndef _Drv_LcdUC1609C_C_
/*Interface Declarations*/

#endif

#endif
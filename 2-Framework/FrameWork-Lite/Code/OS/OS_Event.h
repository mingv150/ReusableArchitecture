/*******************************************************************************
*Copyright(C),2013,mingv150,All rights reserved
*FileName:
*Description:
*Author:
*Version:
*Changelog:
*******************************************************************************/
#ifndef _OS_EVENT_H_
#define _OS_EVENT_H_

#define EVENT_EMPTYSIG      0
#define EVENT_ENTRYSIG      1   /**< 进入动作信号 */
#define EVENT_EXITSIG       2   /**< 退出动作信号 */
#define EVENT_INITSIG       3   /**< 初始转换信号 */
#define EVENT_TIMEOUTSIG    4   /**< 时间事件信号 */
#define EVENT_KEYDOWNSIG    5   /**< 按键事件信号 */
#define EVENT_USERSIG       6   /**< 用户应用程序可以使用的第一个信号 */

#define EVENT_BUF1SIZE 5
#define EVENT_BUF2SIZE 5
#define EVENT_BUF3SIZE 5
#define EVENT_BUF4SIZE 5
#define EVENT_BUF5SIZE 5
#define EVENT_BUF6SIZE 5
#define EVENT_BUF7SIZE 5
#define EVENT_BUF8SIZE 5

typedef struct
{
    u8 InIndex;
    u8 OutIndex;
    u8 QueSize;
    u8 *SigQuePtr;
    u8 *ParQuePtr;
}t_Event;

#ifndef _OS_EVENT_C_
void OS_Event_Init(void);
u8 OS_Event_PutEvent(u8 Prio,u8 Signal,u8 Param);
u8 OS_Event_PutEventISR(u8 Prio,u8 Signal,u8 Param);
void OS_Event_GetEvent(u8 Prio,u8 *pSignal,u8 *pParam);
#endif

#endif


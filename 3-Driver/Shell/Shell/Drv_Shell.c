/****************************************************************************
Copyright (C), 2013, Mingv150, All rights reserved
FileName: Drv_Shell.c
Description:
Author:
Version:
Changelog:
*****************************************************************************/

#define _Drv_Shell_C_
/*common header file*/
#include "Common.h"
#include "lw_oopc.h"
#include <stdio.h>
/*my header file*/
#include "Drv_Shell.h"


/*Global Data Structure*/

/*h - help命令，用来输出所有支持的命令以及功能；
f - find命令，用来在yaffs文件系统中查找文件夹或文件；
o - open命令，用来打开目录；
g - get命令， 用来上传文件，通过串口和超级终端实现的zmodem协议，从yaffs中上传指定文件到PC中；
b - back命令，用来返回到yaffs文件系统根目录；
n - next命令，用来显示文件夹接下来的10个目录项（目录项可以是文件夹或文件）；
t - top命令， 用来回到目录顶部；
e - exit命令，用来退出shell界面，串口进入机器正常工作时的方式，接收自己定义的串口协议指令。*/
void Drv_Shell_HelpCmd(char *para);
void StatusCmdExeFun(char *para);
void FindCmdExeFun(char *para);
void OpenCmdExeFun(char *para);
void GetCmdExeFun(char *para);
void BackCmdExeFun(char *para);
void NextCmdExeFun(char *para);
void TopCmdExeFun(char *para);
void DownloadCmdExeFun(char *para);

t_Cmd CmdTbl[] =
{
    {"help", "help - help, list all cmd\n\r",Drv_Shell_HelpCmd},
    {"view", "view - view log status\n\r",StatusCmdExeFun},
    {"find", "find - find in root dir\n\r",FindCmdExeFun},
    {"open", "open - open directory\n\r",OpenCmdExeFun},
    {"get", "get - get specific file\n\r",GetCmdExeFun},
    {"back", "back - back to root directory\n\r",BackCmdExeFun},
    {"next", "next - next 10 dirent\n\r",NextCmdExeFun},
    {"go", "go - go to top of directory\n\r",TopCmdExeFun},
    {"download", "download - download a file from pc\n\r",DownloadCmdExeFun},
    {"exit", "exit - exit shell\n\r",NULL}
};


/****************************************************************************
Function: static char * Drv_Shell_DelChar(char *buffer, char *p, int *colp, int *np, int plen)
Description: Come form u-boot-1.3.4
Input:
Output:
*****************************************************************************/
static char * Drv_Shell_DelChar(char *buffer, char *p, int *colp, int *np, int plen)
{
    char *s;
    u8 n = 0;

    if (*np == 0)
    {
        return (p);
    }

    //will retype the whole line
    if (*(--p) == '\t')
    {
/*        while (*colp > plen)
        {
            printf("%s",SHELL_ERASE_SEQ);
            (*colp)--;
        }

        for (s = buffer; s < p; ++s)
        {
            if (*s == '\t')
            {
                //printf("%s",SHELL_TABSEQ + ((*colp) & 07));
                //*colp += SHELL_TABSIZE - ((*colp) & 07);
                printf("%s",SHELL_TABSEQ);
                *colp -= SHELL_TABSIZE;
            }
            else
            {
                ++(*colp);
                printf("%s",*s);
            }
        }
*/
        for(n=0;n<SHELL_TABSIZE;n++)
        {
            printf("%s",SHELL_ERASE_SEQ);
            (*colp)--;
        }
    }
    else
    {
        printf("%s",SHELL_ERASE_SEQ);
        (*colp)--;
    }

    (*np)--;

    return (p);
}


/****************************************************************************
Function: int Drv_Shell_Readline2Buffer(const char *const prompt, char *buffer)
Description: Come form u-boot-1.3.4
Input:
Output:
*****************************************************************************/
static int Drv_Shell_Readline2Buffer(const char *const prompt, char *buffer,u8 BufLen)
{
    char *p = buffer;
    char *p_buf = p;
    //buffer index
    int n = 0;
    //prompt length
    int plen = 0;
    //output column cnt
    int col;
    char c;

    //print prompt
    if (prompt)
    {
        plen = strlen(prompt);
        printf("%s", prompt);
    }

    col = plen;

    for (;;)
    {
        //read a char from serial port
        c = getch();

        //character handling
        switch (c)
        {
        case '\r':
            //Enter Key
        case '\n':
            //回车表示命令输入结束
            *p = '\0';
            printf("\r\n");
            return (p - p_buf);
        case '\0': /* nul */
            continue;
        case 0x03: /* ^C - break */
            //CTRL+C表示取消命令输入
            p_buf[0] = '\0'; /* discard input */
            printf("\r\n");//luodefu
            return (-1);
        case 0x15: /* ^U - erase line */
            //CTRL+U表示擦除一行命令输入
            while (col > plen)
            {
                printf("%s",SHELL_ERASE_SEQ);
                --col;
            }
            p = p_buf;
            n = 0;
            continue;
        case 0x17: /* ^W - erase word */
            //CTRL+W表示删除一个词
            p = Drv_Shell_DelChar(p_buf, p, &col, &n, plen);
            while ((n > 0) && (*p != ' '))
            {
                p = Drv_Shell_DelChar(p_buf, p, &col, &n, plen);
            }
            continue;
        case 0x08: /* ^H  - backspace */
        case 0x7F: /* DEL - backspace */
            //表示删除一个字符
            p = Drv_Shell_DelChar(p_buf, p, &col, &n, plen);
            continue;

        default:
            /*
             * Must be a normal character then
             */
            if (n < BufLen - 2) //luodefu-命令行缓冲区大小16
            {
                if (c == '\t')   /* expand TABs */
                {
                    //printf("%s",SHELL_TABSEQ + (col & 07));
                    //col += SHELL_TABSIZE - (col & 07);
                    printf("%s",SHELL_TABSEQ);
                    col += SHELL_TABSIZE;
                }
                else
                {
                    ++col;  /* echo input */
                    printf("%c", c);
                }
                *p++ = c;
                ++n;
            }
            else       /* Buffer full */
            {
                printf("%c",'\a');
            }
        }
    }
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void ShowCurDirectory(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void StatusCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void FindCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void OpenCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void GetCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void BackCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void NextCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void TopCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description:
Input:
Output:
*****************************************************************************/
void DownloadCmdExeFun(char *para)
{
    printf("%s\n", para);
    return;
}


/****************************************************************************
Function: Name
Description: print all the help information of command
Input:
Output:
*****************************************************************************/
void Drv_Shell_HelpCmd(char *para)
{
    int n;

    printf("---------------- here is all cmd supported ----------------\n\r");

    for (n = 0; n < sizeof(CmdTbl) / sizeof(t_Cmd); n++)
    {
        printf("%s", CmdTbl[n].usage);
    }
}


/****************************************************************************
Function: void Drv_Shell_Exe(void)
Description:
Input:
Output:
*****************************************************************************/
void Drv_Shell_Exe(void)
{
    int i, n, CmdIndex;
    char CmdBuffer[32];
    char Cmd[16];
    char Param[32];

    Drv_Shell_HelpCmd(NULL);

    while (1)
    {
        Drv_Shell_Readline2Buffer("MCU_Shell>", CmdBuffer ,sizeof(CmdBuffer));

        if (0 == CmdBuffer[0])
        {
            continue;
        }


        for(n = 0; n < sizeof(Cmd); n++)
        {
            if(CmdBuffer[n] != 0 && CmdBuffer[n] != ' ')
            {
                Cmd[n] = CmdBuffer[n];        
            }    
            else
            {
                Cmd[n] = '\0';
                break;  
            }
        }

        if(Cmd[n] != '\0')
        {
            printf("cmd error, you can input h for help\n\r");
            continue;     
        }

        n = n+1;

        for(i=0; n < sizeof(CmdBuffer); n++,i++)
        {
            Param[i] = CmdBuffer[n];     
        }
            
        for (n = 0; n < sizeof(CmdTbl) / sizeof(t_Cmd); n++)
        {
            if(strcmp(CmdTbl[n].name,Cmd) == 0)
            {
                //CmdIndex = n;
                CmdTbl[n].CmdFun(Param);
                printf("\n\r");
                break;
            }
            else 
            {
                if(n == sizeof(CmdTbl) / sizeof(t_Cmd) -1)
                printf("cmd error, you can input h for help\n\r");
            }
        }






/*        //检查命令
        if (('f' == CmdBuffer[0] || 'o' == CmdBuffer[0] || 'g' == CmdBuffer[0]))
        {
            //f、o、g命令和参数之间用1个空格隔开
            if (' ' != CmdBuffer[1])
            {
                printf("cmd error, you can input h for help\n\r");
                continue;
            }
        }
        else
        {
            //其他命令不带参数，第二个字符必须是结束符'/0'
            if (0 != CmdBuffer[1])
            {
                printf("cmd error, you can input h for help\n\r");
                continue;
            }
        }

        //查找命令
        CmdIndex = -1;

        for (n = 0; n < sizeof(CmdTbl) / sizeof(t_Cmd); n++)
        {
            if (CmdTbl[n].name == CmdBuffer[0])
            {
                CmdIndex = n;
                break;
            }
        }

        if (-1 == CmdIndex)
        {
            //查找命令失败
            printf("cmd error, you can input h for help\n\r");
            continue;
        }

        //如果是exit命令，则退出shell界面，机器进入正常工作模式
        if ('e' == CmdTbl[CmdIndex].name)
        {
            //yaffs_closedir(pCurDirectory);
            printf("Exit shell, return to work mode, good bye!^_^\n\r");
            //delay_ms(1000);
            return;
        }

        //检查enter和get命令参数
        if (('o' == CmdTbl[CmdIndex].name || 'g' == CmdTbl[CmdIndex].name)\
            && (CmdBuffer[2] < '0' || '9' < CmdBuffer[2]))
        {
            printf("cmd para error\n\r");
            continue;
        }

        //执行命令
        (CmdTbl[CmdIndex].CmdFun)(&CmdBuffer[2]);
        printf("\n\r");*/

    }
}


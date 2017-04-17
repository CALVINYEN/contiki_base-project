/**************************************************
  * DS18B20函数原型及相关变量
  * 相关文件：DS18B20.H
  * 编写日期：2011.1.4
  * 编写人：  杨帆
  * 修改历史:
  *   2011.1.4 15:05 调整了参数定义
  *   2011.1.5 10:14 增加温度小数部分对应数值表
  *
**************************************************/

#ifndef DS18B20_H_
#define DS18B20_H_

#include "cc253x.h"
#include "sys/clock.h"
/**************************************************
  以下定义为DS18B20支持的所有命令
***************************************************/

#define SEARCH_ROM      0xF0              //搜索ROM
#define READ_ROM        0x33              //读ROM
#define MATCH_ROM       0x55              //匹配ROM(挂多个DS18B20时使用)
#define SKIP_ROM        0xCC              //跳过匹配ROM(单个DS18B20时跳过)
#define ALARM_SEARCH    0xEC              //警报搜索

#define CONVERT_T       0x44              //开始转换温度
#define WR_SCRATCHPAD   0x4E              //写便笺
#define RD_SCRATCHPAD   0xBE              //读便笺
#define CPY_CCTATCHPAD  0x48              //复制便笺
#define RECALL_EE       0xB8              //未启用
#define RD_PWR_SUPPLY   0xB4              //读电源供应

#define DQ            P0_7                //DS18B20数据IO口
#define DQ_DIR_OUT    0x80                //DS18B20 IO方向
#define CL_DQ()     DQ = 0              //清除数据
#define SET_DQ()    DQ = 1             //设置数据
#define SET_OUT()   P0DIR |=  DQ_DIR_OUT  //设置IO方向,out设置IO方向为输出
#define SET_IN()    P0DIR &= ~DQ_DIR_OUT  //设置IO方向,in设备IO方向为输入

extern void DS18B20_Write(unsigned char x); //DS18B20写命令

extern unsigned char DS18B20_Read(void);    //DS18B20读数据

extern void DS18B20_Init(void);             //DS18B20初始化/复位

extern void DS18B20_SendConvert(void);      //发送转换温度命令

extern void DS18B20_GetTem(unsigned char *integer, unsigned char *decimal);           //DS18B20获取温度

#endif
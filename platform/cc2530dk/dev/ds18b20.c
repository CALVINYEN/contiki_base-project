/**************************************************
  * DS18B20相关功能的实现
  * 相关文件：DS18B20.C
  * 编写日期：2011.1.4
  * 编写人：  杨帆
  * 修改历史:
  *   2010.1.4 16:48 调整了变量、对函数进行优化
  *   2010.1.4 10:20 调整了正负温度转换,完善注释

**************************************************/
#include "ds18b20.h"

/*
 *    写命令函数
 *    输入参数：  命令（DS18B20.H中定义）
 *    输出参数：  无
 *    返回参数：  无
 *
 */
void DS18B20_Write(unsigned char cmd)
{
    unsigned char i;
    SET_OUT();                  //设置IO为输出，2530->DS18B20
    
    /*每次一位，循环8次*/
    for(i=0; i<8; i++) {
        CL_DQ();              //IO为低    
        if( cmd & (1<<i) ) {    //写数据从低位开始
          SET_DQ();           //IO输入高电平
        }
        else {
          CL_DQ();            //IO输出低电平
        }
        clock_delay_usec(40);        //保持15~60us
        SET_DQ();             //IO口拉高
    }
    SET_DQ();                 //IO口拉高
}


/*
 *    读数据函数
 *    输入参数：  无
 *    输出参数：  无
 *    返回参数：  读取的数据
 *
 */
unsigned char DS18B20_Read(void)
{
    unsigned char rdData;     //读出的数据
    unsigned char i, dat;     //临时变量
    
    rdData = 0;               //读出的数据初始化为0     
    
    /* 每次读一位，读8次 */
    for(i=0; i<8; i++) {
        CL_DQ();            //IO拉低
        SET_DQ();           //IO拉高
        SET_IN();           //设置IO方向为输入 DS18B20->CC2530
        dat = DQ;           //读数据,从低位开始
        
        if(dat)　{
          rdData |= (1<<i); //如果读出的数据位为正
        }
        else {
          rdData &= ~(1<<i);//如果读出的数据位为负
        }
        
        clock_delay_usec(70);      //保持60~120us
        SET_OUT();          //设置IO方向为输出 CC2530->DS18B20

    }
    return (rdData);        //返回读出的数据
}


/*
 *    DS18B20初始化/复位函数
 *    输入参数：  无
 *    输出参数：  无
 *    返回参数：  无
 *
 */
void DS18B20_Init(void)
{
    SET_OUT();
    SET_DQ();         //IO口拉高
    CL_DQ();          //IO口拉低
    clock_delay_usec(550);   //IO拉低后保持一段时间 480-960us
    SET_DQ();         //释放
    SET_IN();         //IO方向为输入 DS18B20->CC2530
    clock_delay_usec(40);    //释放总线后等待15-60us
    
    /* 等待DQ变低 */
    while(DQ) {
        ; 
    }
    clock_delay_usec(240);   //检测到DQ 变低后，延时60-240us
    SET_OUT();        //设置IO方向为输出 CC2530->DS18B20
    SET_DQ();         //IO拉高
}


/*
 *    DS18B20 转换温度函数
 *    输入参数：  无
 *    输出参数：  无
 *    返回参数：  无
 *
 */
void DS18B20_SendConvert(void)
{
    DS18B20_Init();               //复位18B20
    DS18B20_Write(SKIP_ROM);      //发出跳过ROM匹配操作
    DS18B20_Write(CONVERT_T);     //启动温度转换
}


/*
 *    DS18B20获取温度函数
 *    输入参数：  无
 *    输出参数：  无
 *    返回参数：  无
 *
 */
void DS18B20_GetTem(unsigned char *integer, unsigned char *decimal)
{
    unsigned char tem_h,tem_l;    //温度高位字节及低位字节
    unsigned char a,b;            //临时变量
    unsigned char flag;           //温度正负标记，正为0，负为1
	unsigned char FRACTION_INDEX[16] = {0, 1, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9 };//小数值查询表
    DS18B20_Init();               //DS18B20复位       
    DS18B20_Write(SKIP_ROM);      //跳过ROM匹配
    
    DS18B20_Write(RD_SCRATCHPAD); //写便笺
    tem_l = DS18B20_Read();       //读温度低位
    tem_h = DS18B20_Read();       //读温度高位

    /* 判断温度正负 */
    if(tem_h & 0x80) {
        flag = 1;                 //温度为负
        a = (tem_l>>4);           //取温度低4位原码
        b = (tem_h<<4)& 0xf0;     //取温度高4位原码
        tem_h = ~(a|b) + 1;       //取整数部分数值，不符号位
        
        tem_l = ~(a&0x0f) + 1;    //取小数部分原值，不含符号位
    }
    else {
        flag = 0;                 //为正
        a = tem_h<<4;
        a += (tem_l&0xf0)>>4;     //得到整数部分值 
        b = tem_l&0x0f;           //得出小数部分值
        tem_h = a;                //整数部分
        tem_l = b&0xff;           //小数部分
    }
    
    *decimal = FRACTION_INDEX[tem_l]; //查表得小数值
    *integer = tem_h| (flag<<7);      //整数部分，包括符号位
}
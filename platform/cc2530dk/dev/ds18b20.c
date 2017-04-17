/**************************************************
  * DS18B20��ع��ܵ�ʵ��
  * ����ļ���DS18B20.C
  * ��д���ڣ�2011.1.4
  * ��д�ˣ�  �
  * �޸���ʷ:
  *   2010.1.4 16:48 �����˱������Ժ��������Ż�
  *   2010.1.4 10:20 �����������¶�ת��,����ע��

**************************************************/
#include "ds18b20.h"

/*
 *    д�����
 *    ���������  ���DS18B20.H�ж��壩
 *    ���������  ��
 *    ���ز�����  ��
 *
 */
void DS18B20_Write(unsigned char cmd)
{
    unsigned char i;
    SET_OUT();                  //����IOΪ�����2530->DS18B20
    
    /*ÿ��һλ��ѭ��8��*/
    for(i=0; i<8; i++) {
        CL_DQ();              //IOΪ��    
        if( cmd & (1<<i) ) {    //д���ݴӵ�λ��ʼ
          SET_DQ();           //IO����ߵ�ƽ
        }
        else {
          CL_DQ();            //IO����͵�ƽ
        }
        clock_delay_usec(40);        //����15~60us
        SET_DQ();             //IO������
    }
    SET_DQ();                 //IO������
}


/*
 *    �����ݺ���
 *    ���������  ��
 *    ���������  ��
 *    ���ز�����  ��ȡ������
 *
 */
unsigned char DS18B20_Read(void)
{
    unsigned char rdData;     //����������
    unsigned char i, dat;     //��ʱ����
    
    rdData = 0;               //���������ݳ�ʼ��Ϊ0     
    
    /* ÿ�ζ�һλ����8�� */
    for(i=0; i<8; i++) {
        CL_DQ();            //IO����
        SET_DQ();           //IO����
        SET_IN();           //����IO����Ϊ���� DS18B20->CC2530
        dat = DQ;           //������,�ӵ�λ��ʼ
        
        if(dat)��{
          rdData |= (1<<i); //�������������λΪ��
        }
        else {
          rdData &= ~(1<<i);//�������������λΪ��
        }
        
        clock_delay_usec(70);      //����60~120us
        SET_OUT();          //����IO����Ϊ��� CC2530->DS18B20

    }
    return (rdData);        //���ض���������
}


/*
 *    DS18B20��ʼ��/��λ����
 *    ���������  ��
 *    ���������  ��
 *    ���ز�����  ��
 *
 */
void DS18B20_Init(void)
{
    SET_OUT();
    SET_DQ();         //IO������
    CL_DQ();          //IO������
    clock_delay_usec(550);   //IO���ͺ󱣳�һ��ʱ�� 480-960us
    SET_DQ();         //�ͷ�
    SET_IN();         //IO����Ϊ���� DS18B20->CC2530
    clock_delay_usec(40);    //�ͷ����ߺ�ȴ�15-60us
    
    /* �ȴ�DQ��� */
    while(DQ) {
        ; 
    }
    clock_delay_usec(240);   //��⵽DQ ��ͺ���ʱ60-240us
    SET_OUT();        //����IO����Ϊ��� CC2530->DS18B20
    SET_DQ();         //IO����
}


/*
 *    DS18B20 ת���¶Ⱥ���
 *    ���������  ��
 *    ���������  ��
 *    ���ز�����  ��
 *
 */
void DS18B20_SendConvert(void)
{
    DS18B20_Init();               //��λ18B20
    DS18B20_Write(SKIP_ROM);      //��������ROMƥ�����
    DS18B20_Write(CONVERT_T);     //�����¶�ת��
}


/*
 *    DS18B20��ȡ�¶Ⱥ���
 *    ���������  ��
 *    ���������  ��
 *    ���ز�����  ��
 *
 */
void DS18B20_GetTem(unsigned char *integer, unsigned char *decimal)
{
    unsigned char tem_h,tem_l;    //�¶ȸ�λ�ֽڼ���λ�ֽ�
    unsigned char a,b;            //��ʱ����
    unsigned char flag;           //�¶�������ǣ���Ϊ0����Ϊ1
	unsigned char FRACTION_INDEX[16] = {0, 1, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9 };//С��ֵ��ѯ��
    DS18B20_Init();               //DS18B20��λ       
    DS18B20_Write(SKIP_ROM);      //����ROMƥ��
    
    DS18B20_Write(RD_SCRATCHPAD); //д���
    tem_l = DS18B20_Read();       //���¶ȵ�λ
    tem_h = DS18B20_Read();       //���¶ȸ�λ

    /* �ж��¶����� */
    if(tem_h & 0x80) {
        flag = 1;                 //�¶�Ϊ��
        a = (tem_l>>4);           //ȡ�¶ȵ�4λԭ��
        b = (tem_h<<4)& 0xf0;     //ȡ�¶ȸ�4λԭ��
        tem_h = ~(a|b) + 1;       //ȡ����������ֵ��������λ
        
        tem_l = ~(a&0x0f) + 1;    //ȡС������ԭֵ����������λ
    }
    else {
        flag = 0;                 //Ϊ��
        a = tem_h<<4;
        a += (tem_l&0xf0)>>4;     //�õ���������ֵ 
        b = tem_l&0x0f;           //�ó�С������ֵ
        tem_h = a;                //��������
        tem_l = b&0xff;           //С������
    }
    
    *decimal = FRACTION_INDEX[tem_l]; //����С��ֵ
    *integer = tem_h| (flag<<7);      //�������֣���������λ
}
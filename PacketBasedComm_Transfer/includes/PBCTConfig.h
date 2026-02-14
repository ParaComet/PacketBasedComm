#ifndef __PBCT_CONFIG_H
#define __PBCT_CONFIG_H

//起始字节
#define PBCT_START_BYTE 0xAA
//转义字节
#define PBCT_TM_BYTE 0xAB
//结束字节
#define PBCT_END_BYTE 0xAC

//无符号一位整形
typedef unsigned char PBCT_U1;
//CRC多项式类型,需为无符号
typedef unsigned short PBCT_CRCPOLY;
//数据长度类型
typedef unsigned int PBCT_DTLEN;

#endif
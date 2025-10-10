#ifndef __CRC_H
#define __CRC_H

#include "PBCTConfig.h"

//无符号一位整形
typedef PBCT_U1 CRC_U1;
//CRC多项式类型,需为无符号
typedef PBCT_CRCPOLY CRC_POLY;
//数据长度类型
typedef PBCT_DTLEN CRC_DTLEN;

/**
 * 计算特定多项式下一组数据经过CRC校验除法后的余数
 * 若需要兼容计算已有校验码的数据,校验码需要提前进行左对齐
 * @param dt 要计算的数据
 * @param dtLen 要计算数据的长度
 * @param crcPoly 选取的多项式
 * @param crcBits 选取的多项式的位数
 */
CRC_POLY CRC_calRemainder(
    CRC_U1* dt,
    CRC_DTLEN dtLen,
    CRC_POLY crcPoly,
    CRC_U1 crcBits
);

#endif
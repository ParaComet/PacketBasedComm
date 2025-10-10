#ifndef __PBCT_SEND_H
#define __PBCT_SEND_H

//数据帧装后的格式如下:
//[PBCT_START_BYTE][原始数据长度+CRC校验码长度][数据主体][CRC校验码][PBCT_END_BYTE]
//1. "[原始数据长度+CRC校验码长度][数据主体][CRC校验码]"中如果有任何字节与 PBCT_START_BYTE 或 PBCT_END_BYTE 重合
//   都会在其之前填充一个字节 PBCT_TM_BYTE 以与真正的开始和结束字节作区分
//   此填充发生的时间可以看作是在"[原始数据长度+CRC校验码长度][数据主体][CRC校验码]"之后
//   所以不会影响到原数据的含义
//2. CRC校验码的长度为其比特位数除以8后向上取整,若其比特位数不是8的倍数,则会进行左对齐后再参与传输
//3. "[原始数据长度+CRC校验码长度]"采用低位先行模式,即低位的数据解析后在结果数据索引更靠前的位置
//   "[CRC校验码]"则采用高位先行以方便计算
//4. CRC校验的范围为 "[数据主体]"

#include "PBCTConfig.h"

//抽象出的发送回调函数
typedef void (*PBCT_sendCB)(PBCT_U1* datas,PBCT_DTLEN dtLen);

/**
 * 发送需要包装的数据,缓冲区每填满一次就会发送一次已处理的数据
 * @param callBack 经过处理后的数据由此回调函数发出
 * @param oriData 需要处理的原始数据
 * @param oriDTLen 原始数据的长度
 * @param buffer 缓冲区
 * @param bufferLen 缓冲区大小
 * @param dtlLen 
 * @param crcPoly 此次发送使用的CRC多项式,填0表示不需要
 * @param crcBits 此次发送使用的CRC多项式位数,若不需要CRC校验可以填0
 */
void PBCT_send(
    PBCT_sendCB callBack,
    PBCT_U1* oriData,
    PBCT_DTLEN oriDTLen,
    PBCT_U1* buffer,
    PBCT_DTLEN bufferLen,
    PBCT_U1 dtlLen,
    PBCT_CRCPOLY crcPoly,
    PBCT_U1 crcBits
);

#endif
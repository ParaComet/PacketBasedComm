#ifndef __PBCT_RECEIVE_H
#define __PBCT_RECEIVE_H

//数据帧格式见 PBCTSend.h

#include "PBCTConfig.h"

typedef PBCT_U1 PBCT_ERRCODE;
//转义字节后若不是三个需要转义的字节抛出此错误
#define PBCT_ERR_ILLEGAL_TMBYTE 0x00
//有未经转义的开始字节时抛出此错误
#define PBCT_ERR_ILLEGAL_START_BYTE 0x01
//当数据帧的长度与数据帧开头标定的长度不同时抛出此错误
#define PBCT_ERR_LEN_NOT_CORRECT 0x02
//CRC校验错误时抛出此错误
#define PBCT_ERR_CRC_NOT_CORRECT 0x03

//抽象出的内存申请函数
typedef PBCT_U1* (*PBCT_malloc)(PBCT_DTLEN dtLen);
//抽象出的数据帧解析结束回调函数,dt为数据,dtLen为数据长度
typedef void (*PBCT_overCB)(PBCT_U1* dt,PBCT_DTLEN dtLen);
//抽象出的错误处理函数
typedef void (*PBCT_err)(PBCT_ERRCODE err);
//抽象出的包起始回调函数
typedef void (*PBCT_start)();

struct PBCT_process
{

    PBCT_malloc pbctMalloc;
    PBCT_overCB overCB;
    PBCT_err err;
    PBCT_start start;
    PBCT_U1 dtlLen;
    PBCT_CRCPOLY crcPoly;
    PBCT_U1 crcBits;

    PBCT_U1 isLastTM,isPacketStart;
    PBCT_DTLEN dtLen;
    PBCT_U1* dtBuffer;
    PBCT_DTLEN dtIndex,dtLenByte;

};

/**
 * 初始化一个处理进程
 * @param process 要初始化的进程
 * @param pbctMalloc 内存申请函数
 * @param overCB 数据帧解析结束回调函数,其中传入的dt参数就为 pbctMalloc 返回的地址,dtLen为去掉CRC校验码的原始数据
 * @param err 解析出现错误的回调函数
 * @param crcPoly 此次发送使用的CRC多项式,填0表示不需要
 * @param crcBits 此次发送使用的CRC多项式位数,若不需要CRC校验可以填0
 */
void PBCT_initProcess(
    struct PBCT_process* process,
    PBCT_malloc pbctMalloc,
    PBCT_overCB overCB,
    PBCT_start start,
    PBCT_err err,
    PBCT_U1 dtlLen,
    PBCT_CRCPOLY crcPoly,
    PBCT_U1 crcBits
);

/**
 * 重置进程状态至初始化后
 * @param process 要重置的进程
 */
void PBCT_resetProcess(struct PBCT_process* process);

/**
 * 若某个进程需要接收数据则调用此函数
 * @param process 进程
 * @param rcvDT 接收的数据
 * @param rcvLen 接收数据的长度
 */
void PBCT_receiveData(struct PBCT_process* process,PBCT_U1* rcvDT,PBCT_DTLEN rcvLen);

#endif
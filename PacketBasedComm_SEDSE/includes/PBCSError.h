//错误处理相关
#ifndef __PBCS_ERROR_H
#define __PBCS_ERROR_H

#include "PBCSCFGFile.h"

//无错误
#define PBCS_ERROR_NO 0x00

//不存在的数据包
#define PBCS_ERROR_INFO_UNDEFINED_PACKET 0x03
//不存在的数据包类型
#define PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE 0x04

//简易错误信息构造函数,供内部使用
PBCS_U4 PBCS_errorCont(PBCS_U1 errCode,PBCS_U1 infoB1,PBCS_U1 infoB2,PBCS_U1 infoB3);

/**
 * 获取错误码
 * @param error 错误信息
 * @return 错误信息中的错误码
 */
PBCS_U1 PBCS_getErrCode(PBCS_U4 error);

/**
 * 获取错误信息中的附加信息
 * @param error 错误信息
 * @param infoBit 要获取第几位附加信息,大于2的值都视为2
 * @return 获取结果
 */
PBCS_U1 PBCS_getErrInfo(PBCS_U4 error,PBCS_U1 infoBit);

#endif
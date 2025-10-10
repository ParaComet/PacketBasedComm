#ifndef __BINARY_SEARCH_H
#define __BINARY_SEARCH_H

#include "PBCSConfig.h"

//比较结果类型
typedef PBCS_I1 BNRSCH_COMP;
//数据长度类型
#ifdef PBCS_8BIT_SPT
typedef PBCS_U8 BNRSCH_LEN;
#else
typedef PBCS_U4 BNRSCH_LEN;
#endif
//1字节无符号整数类型
typedef PBCS_U1 BNRSCH_U1;

//抽象出的比较函数,若data1>data2返回值应大于0,若data1==data2返回值应等于0,否则返回值应小于0
typedef BNRSCH_COMP (*BNRSCH_compareTo)(const void* data1,const void* data2,const void* args);
//抽象出的取值函数,datas代表所有数据的集合,index是需要取的元素的索引
typedef const void* (*BNRSCH_access)(const void* datas,BNRSCH_LEN index,const void* args);

/**
 * 使用二分法在有序集合中的某个部分查找指定数据
 * @param datas 有序集合
 * @param data 要查找的数据
 * @param start 需要查找部分的起始索引
 * @param len 需要查找部分的长度
 * @param comp 此次查找使用的比较函数,第二个参数恒传入 data
 * @param access 此次查找使用的取值函数
 * @param result 若查找成功则返回查找到的数据的下标
 * @return 若查找成功则返回1,否则返回0
 */
BNRSCH_U1 BNRSCH_find(
    const void* datas,
    const void* data,
    const void* args,
    BNRSCH_LEN start,
    BNRSCH_LEN len,
    BNRSCH_compareTo comp,
    BNRSCH_access access,
    BNRSCH_LEN* result
);

#endif
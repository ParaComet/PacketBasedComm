//一些供内部使用的回调函数

#ifndef __PBCS_CALLBACKS_H
#define __PBCS_CALLBACKS_H

#include "PBCSConfig.h"
#include "BinarySearch.h"

BNRSCH_COMP PBCS_BNRSCH_compareTo_getPacketCfg(const void* data1,const void* data2,const void* args);

BNRSCH_COMP PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex(const void* data1,const void* data2,const void* args);

const void* PBCS_BNRSCH_access_isBelongTo(const void* datas, BNRSCH_LEN index,const void* args);

const void* PBCS_BNRSCH_access_getPacketCfg(const void* datas, BNRSCH_LEN index,const void* args);

const void* PBCS_BNRSCH_access_cfgPacketNums(const void* datas, BNRSCH_LEN index,const void* args);

#endif
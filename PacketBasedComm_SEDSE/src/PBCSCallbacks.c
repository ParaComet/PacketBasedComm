#include "PBCSCallbacks.h"

BNRSCH_COMP PBCS_BNRSCH_compareTo_getPacketCfg(const void* data1,const void* data2,const void* args){

    const PBCS_U1* d1 = (const PBCS_U1*)data1;
    const PBCS_U1* d2 = (const PBCS_U1*)data2;
    const struct PBCS_config* config = (const struct PBCS_config*)args;
    PBCS_PTID ptid1 = 0,ptid2 = 0;
    PBCS_PID pid1 = 0,pid2 = 0;

    for(PBCS_I2 i = config->ptidLen - 1;i >= 0;i--){
        ptid1 <<= 8;
        ptid1 = d1[i];
        ptid2 <<= 8;
        ptid2 = d2[i];
    }
    for(PBCS_I2 i = config->pidLen - 1;i >= 0;i--){
        pid1 <<= 8;
        pid1 = d1[i + config->ptidLen];
        pid2 <<= 8;
        pid2 = d2[i + config->ptidLen];
    }

    if(ptid1 > ptid2){
        return 1;
    }else if(ptid1 == ptid2){
        if(pid1 > pid2){
            return 1;
        }else if(pid1 == pid2){
            return 0;
        }else{
            return -1;
        }
    }else{
        return -1;
    }

}

BNRSCH_COMP PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex(const void* data1,const void* data2,const void* args){

    PBCS_PTID ptid1 = 0;
    const PBCS_PTID ptid2 = *((const PBCS_PTID*)data2);
    const struct PBCS_config* config = (const struct PBCS_config*)args;

    for(PBCS_I2 i = config->ptidLen - 1;i >= 0;i--){
        ptid1 <<= 8;
        ptid1 = ((const PBCS_U1*)data1)[i];
    }

    if(ptid1 > ptid2){
        return 1;
    }else if(ptid1 == ptid2){
        return 0;
    }else{
        return -1;
    }

}

const void* PBCS_BNRSCH_access_isBelongTo(const void* datas, BNRSCH_LEN index,const void* args){
    return ((const PBCS_U1*)datas) + index * 2 * ((const struct PBCS_config*)args)->ptidLen;
}

const void* PBCS_BNRSCH_access_getPacketCfg(const void* datas, BNRSCH_LEN index,const void* args){
    const struct PBCS_config* config = (const struct PBCS_config*)args;
    return ((const PBCS_U1*)datas) + index * (config->ptidLen + config->pidLen + config->cfgIndexLen);
}

const void* PBCS_BNRSCH_access_cfgPacketNums(const void* datas, BNRSCH_LEN index,const void* args){
    const struct PBCS_config* config = (const struct PBCS_config*)args;
    return ((const PBCS_U1*)datas) + index * (config->ptidLen + config->pidLen);
}
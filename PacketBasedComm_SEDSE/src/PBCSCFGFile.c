#include "PBCSCFGFile.h"
#include "PBCSError.h"
#include "BinarySearch.h"
#include "PBCSCallbacks.h"

PBCS_U4 PBCS_getPacketCfg(PBCS_CFGINDEX* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID,PBCS_PID pkgID){

    PBCS_U1 tmpData[sizeof(PBCS_PTID) + sizeof(PBCS_PID)];
    PBCS_I2 i = 0;
    const PBCS_U1* resultPos;
    BNRSCH_U1 succeed = 0;
    BNRSCH_LEN position = 0;

    for(i = 0;i < config->ptidLen;i++){
        tmpData[i] = pkgTypeID & 0xFF;
        pkgTypeID >>= 8;
    }
    for(i = 0;i < config->pidLen;i++){
        tmpData[i + config->ptidLen] = pkgID & 0xFF;
        pkgID >>= 8;
    }

    succeed = BNRSCH_find(
        config->packetsIndexes,
        tmpData,
        config,
        0,
        config->totalPkts,
        PBCS_BNRSCH_compareTo_getPacketCfg,
        PBCS_BNRSCH_access_getPacketCfg,
        &position
    );

    if(!succeed) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKET,0,0,0);
    resultPos = ((const PBCS_U1*)PBCS_BNRSCH_access_getPacketCfg(config->packetsIndexes,position,config)) + 
        config->ptidLen + config->pidLen;
    *result = 0;
    for(i = config->cfgIndexLen - 1;i >= 0;i--){
        (*result) <<= 8;
        *result += resultPos[i];
    }
    return 0;

}

PBCS_U4 PBCS_isBelongTo(PBCS_BOOL* result,const struct PBCS_config* config,PBCS_PTID child,PBCS_PTID parent){

    BNRSCH_LEN position = 0;
    const PBCS_U1* drParentPos = 0;
    PBCS_I2 i;
    PBCS_PTID drParent = 0;
    
    if(config->ptidLen == 0){
        if(child != 0 || parent != 0) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE,0,0,0);
        *result = 0;
        return 0;
    }

    BNRSCH_U1 succeed = BNRSCH_find(
        config->belonging,
        &child,
        config,
        0,
        config->totalTypes,
        PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex,
        PBCS_BNRSCH_access_isBelongTo,
        &position
    );
    if(!succeed) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE,0,0,0);

    drParentPos = ((const PBCS_U1*)PBCS_BNRSCH_access_isBelongTo(config->belonging,position,config)) + config->ptidLen;
    for(i = config->ptidLen - 1;i >= 0;i--){
        drParent <<= 8;
        drParent += drParentPos[i];
    }

    if(drParent == parent) *result = 1;
    else if(drParent == child) *result = 0;
    else return PBCS_isBelongTo(result,config,drParent,parent);
    return 0;

}

PBCS_U4 PBCS_pktIsBelongTo(PBCS_PTID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig){
    const PBCS_U1* resultPos = (config->packets + pkgConfig);
    PBCS_I2 i;
    *result = 0;
    if(config->ptidLen == 0) return 0;
    for(i = config->ptidLen - 1;i >= 0;i--){
        (*result) <<= 8;
        (*result) += resultPos[i];
    }
    return 0;
}

PBCS_U4 PBCS_getPacketID(PBCS_PID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig){
    const PBCS_U1* resultPos = (config->packets + pkgConfig + config->ptidLen);
    PBCS_I2 i;
    *result = 0;
    for(i = config->pidLen - 1;i >= 0;i--){
        (*result) <<= 8;
        (*result) += resultPos[i];
    }
    return 0;
}

PBCS_U4 PBCS_getAllPacketTypes(PBCS_PTID* result,const struct PBCS_config* config){
    PBCS_PTID i = 0;
    PBCS_I2 j;
    const PBCS_U1* tmpPos;
    if(config->ptidLen == 0) return result[0] = 0;
    for(;i < config->totalTypes;i++){
        result[i] = 0;
        tmpPos = (const PBCS_U1*)PBCS_BNRSCH_access_isBelongTo(config->belonging,i,config);
        for(j = config->ptidLen - 1;j >= 0;j--){
            result[i] <<= 8;
            result[i] += tmpPos[j];
        }
    }
    return 0;
}

PBCS_U4 PBCS_getAllOccupiedPacketTypes(PBCS_PTID* result,const struct PBCS_config* config){
    PBCS_PTID i = 0;
    PBCS_I2 j;
    const PBCS_U1* tmpPos;
    if(config->ptidLen == 0) return result[0] = 0;
    tmpPos = config->packetNums;
    for(;i < config->occupiedTypes;i++){
        result[i] = 0;
        for(j = config->ptidLen - 1;j >= 0;j--){
            result[i] <<= 8;
            result[i] += tmpPos[j];
        }
        tmpPos += config->ptidLen + config->pidLen;
    }
}

//内部函数,获取数据包类型在 packetNums 数组里的位置
PBCS_U4 PBCS_getPacketTypeIndex(BNRSCH_LEN* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID){
    BNRSCH_LEN position = 0;
    PBCS_I2 i;
    const PBCS_U1* resultPos;
    BNRSCH_U1 succeed = BNRSCH_find(
        config->packetNums,
        &pkgTypeID,
        config,
        0,
        config->occupiedTypes,
        PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex,
        PBCS_BNRSCH_access_cfgPacketNums,
        &position
    );
    if(!succeed) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE,0,0,0);
    *result = position;
    return 0;
}

PBCS_U4 PBCS_getPacketsNum(PBCS_PID* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID){
    const PBCS_U1* resultPos;
    BNRSCH_LEN index;
    PBCS_I2 i;
    PBCS_U4 errCode = 0;
    if(config->ptidLen == 0) {
        if(pkgTypeID != 0) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE,0,0,0);
        *result = (PBCS_PID) config->totalPkts;
        return 0;
    }
    if((errCode = PBCS_getPacketTypeIndex(&index,config,pkgTypeID)) != 0) return errCode;
    resultPos = (const PBCS_U1*)(config->packetNums + index * (config->ptidLen + config->pidLen) + config->ptidLen);
    *result = 0;
    for(i = config->pidLen - 1;i >= 0;i--){
        (*result) <<= 8;
        *result += resultPos[i];
    }
    return 0;
}

PBCS_U4 PBCS_getPackets(PBCS_PID* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID){
    PBCS_PID num = 0,i = 0;
    const PBCS_U1* tmpPos;
    BNRSCH_LEN position;
    BNRSCH_COMP comp;
    PBCS_I2 j;
    PBCS_U4 errCode = 0;
    if(config->ptidLen == 0){ 
        if(pkgTypeID != 0) return PBCS_errorCont(PBCS_ERROR_INFO_UNDEFINED_PACKETTYPE,0,0,0);
        num = (PBCS_PID)config->totalPkts;
        tmpPos = config->packetsIndexes;
        for(;i < num;i++){
            result[i] = 0;
            for(j = config->pidLen - 1;j >= 0;j--){
                result[i] <<= 8;
                result[i] += tmpPos[j];
            }
            tmpPos += config->pidLen + config->cfgIndexLen;
        }
    }else{
        if((errCode = PBCS_getPacketsNum(&num,config,pkgTypeID)) != 0) return errCode;
        BNRSCH_find(
            config->packetsIndexes,
            &pkgTypeID,
            config,
            0,
            config->totalPkts,
            PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex,
            PBCS_BNRSCH_access_getPacketCfg,
            &position
        );
        while(1){
            if(position == 0) break;
            position--;
            comp = PBCS_BNRSCH_compareTo_isBelongTo_getPacketTypeIndex(
                PBCS_BNRSCH_access_getPacketCfg(
                    config->packetsIndexes,
                    position,
                    config
                ),
                &pkgTypeID,
                config
            );
            if(comp != 0) {
                position++;
                break;
            }
        }
        tmpPos = config->packetsIndexes + position * (config->ptidLen + config->pidLen + config->cfgIndexLen) + config->ptidLen;
        for(;i < num;i++){
            result[i] = 0;
            for(j = config->pidLen - 1;j >= 0;j--){
                result[i] <<= 8;
                result[i] += tmpPos[j];
            }
            tmpPos += config->ptidLen + config->pidLen + config->cfgIndexLen;
        }
    }
}

PBCS_U4 PBCS_getDataNum(PBCS_DTID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig){
    const PBCS_U1* resultPos;
    PBCS_I2 i;
    resultPos = (const PBCS_U1*)(config->packets + pkgConfig + config->ptidLen + config->pidLen);
    *result = 0;
    for(i = config->dtidLen - 1;i >= 0;i--){
        (*result) <<= 8;
        *result += resultPos[i];
    }
    return 0;
}

PBCS_U4 PBCS_getDataTypemark(PBCS_U1* result,PBCS_DTID dtid,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig){
    PBCS_DTID memoryPos = dtid / 2;
    PBCS_U1 markBit = *(config->packets + 
        pkgConfig + 
        config->ptidLen + 
        config->pidLen + 
        config->dtidLen + 
        memoryPos
    );
    if(dtid % 2 == 0){
        *result = markBit & 0x0F;
    }else{
        *result = markBit >> 4;
    }
    return 0;
}
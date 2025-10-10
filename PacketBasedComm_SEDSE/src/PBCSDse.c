#include "PBCSDse.h"

void PBCS_getDataLowAH(void* result,const PBCS_U1* ori,PBCS_DATAINDEX len){
    PBCS_U1* u1P = 0;
    PBCS_U2* u2P = 0;
    PBCS_U4* u4P = 0;
#ifdef PBCS_8BIT_SPT
    PBCS_U8* u8P = 0;
#endif
    switch(len){
    case 1:
        u1P = (PBCS_U1*)result;
        *u1P = ori[0];
        break;
    case 2:
        u2P = (PBCS_U2*)result;
        *u2P = ori[1];
        *u2P <<= 8;
        *u2P += ori[0];
        break;
    case 4:
        u4P = (PBCS_U4*)result;
        *u4P = ori[3];
        *u4P <<= 8;
        *u4P += ori[2];
        *u4P <<= 8;
        *u4P += ori[1];
        *u4P <<= 8;
        *u4P += ori[0];
        break;
#ifdef PBCS_8BIT_SPT
    case 8:
        u8P = (PBCS_U8*)result;
        *u8P = ori[7];
        *u8P <<= 8;
        *u8P += ori[6];
        *u8P <<= 8;
        *u8P += ori[5];
        *u8P <<= 8;
        *u8P += ori[4];
        *u8P <<= 8;
        *u8P += ori[3];
        *u8P <<= 8;
        *u8P += ori[2];
        *u8P <<= 8;
        *u8P += ori[1];
        *u8P <<= 8;
        *u8P += ori[0];
        break;
#endif
    }
}

PBCS_U4 PBCS_getPacketCfgFromStream(PBCS_CFGINDEX* result,const struct PBCS_config* config,const PBCS_U1* pkgData){
    PBCS_PTID ptid = 0;
    PBCS_PID pid = 0;
    PBCS_I2 i = 0;
    for(i = config->ptidLen - 1;i >= 0;i--){
        ptid <<= 8;
        ptid += pkgData[i];
    }
    pkgData += config->ptidLen;
    for(i = config->pidLen - 1;i >= 0;i--){
        pid <<= 8;
        pid += pkgData[i];
    }
    return PBCS_getPacketCfg(result,config,ptid,pid);
}

PBCS_U4 PBCS_getPacketDataOffsets(
    PBCS_DATAINDEX* result,
    PBCS_VDLEN* vdLens,
    PBCS_DTID* vdNum,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_U1* pkgData
){

    PBCS_VDLEN vdLen = 0;
    PBCS_DTID dtNum = 0,dtid = 0,vdIndex = 0;
    PBCS_U1 dtMark = 0;
    PBCS_I2 i = 0;
    PBCS_U4 errCode = 0;
    PBCS_DATAINDEX current = 0,vdCurrent = config->ptidLen + config->pidLen;
    if((errCode = PBCS_getDataNum(&dtNum,config,pkgConfig)) != 0){
        return errCode;
    }
    (*vdNum) = 0;
    for(;dtid < dtNum;dtid++){
        if((errCode = PBCS_getDataTypemark(&dtMark,dtid,config,pkgConfig)) != 0){
            return errCode;
        }
        if(dtMark == PBCS_DTMARK_VL){
            (*vdNum)++;
        }
    }

    current = config->ptidLen + config->pidLen + (*vdNum) * config->vdlLen;
    for(dtid = 0;dtid < dtNum;dtid++){
        result[dtid] = current;
        if((errCode = PBCS_getDataTypemark(&dtMark,dtid,config,pkgConfig)) != 0){
            return errCode;
        }
        switch(dtMark){
        case PBCS_DTMARK_U1:
        case PBCS_DTMARK_I1:
            current += 1;
            break;
        case PBCS_DTMARK_U2:
        case PBCS_DTMARK_I2:
            current += 2;
            break;
        case PBCS_DTMARK_U4:
        case PBCS_DTMARK_I4:
            current += 4;
            break;
        case PBCS_DTMARK_VL:
            vdLen = 0;
            for(i = config->vdlLen - 1;i >= 0;i--){
                vdLen <<= 8;
                vdLen += (pkgData + vdCurrent)[i];
            }
            vdLens[vdIndex++] = vdLen;
            current += vdLen;
            vdCurrent += config->vdlLen;
            break;
#ifdef PBCS_8BIT_SPT
        case PBCS_DTMARK_U8:
        case PBCS_DTMARK_I8:
        case PBCS_DTMARK_F8:
            current += 8;
            break;
#endif
        }
    }
    result[dtNum] = current;
    return 0;

}

PBCS_U4 PBCS_getDataByU1(PBCS_U1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],1);
}

PBCS_U4 PBCS_getDataByU2(PBCS_U2* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],2);
}

PBCS_U4 PBCS_getDataByU4(PBCS_U4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],4);
}

PBCS_U4 PBCS_getDataByI1(PBCS_I1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],1);
}

PBCS_U4 PBCS_getDataByI2(PBCS_I2* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],2);
}

PBCS_U4 PBCS_getDataByI4(PBCS_I4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],4);
}

PBCS_U4 PBCS_getDataByF4(PBCS_F4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],4);
}

PBCS_U4 PBCS_getDataByV(PBCS_U1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_DATAINDEX i = 0,len = offsets[dataID + 1] - offsets[dataID];
    pkgData += offsets[dataID];
    for(;i < len;i++){
        result[i] = pkgData[i];
    }
    return 0;
}

#ifdef PBCS_8BIT_SPT
PBCS_U4 PBCS_getDataByU8(PBCS_U8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],8);
    return 0;
}

PBCS_U4 PBCS_getDataByI8(PBCS_I8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],8);
    return 0;
}

PBCS_U4 PBCS_getDataByF8(PBCS_F8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData){
    PBCS_getDataLowAH(result,pkgData + offsets[dataID],8);
    return 0;
}
#endif
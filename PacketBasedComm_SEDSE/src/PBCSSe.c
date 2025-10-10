#include "PBCSSe.h"

void PBCS_fillDataLowAH(PBCS_U1* dest,void* ori,PBCS_DATAINDEX len){

    PBCS_U1 u1 = 0;
    PBCS_U2 u2 = 0;
    PBCS_U4 u4 = 0;
#ifdef PBCS_8BIT_SPT
    PBCS_U8 u8 = 0;
#endif

    switch(len){
    case 1:
        u1 = *((PBCS_U1*)ori);
        dest[0] = u1;
        break;
    case 2:
        u2 = *((PBCS_U2*)ori);
        dest[0] = u2 & 0xFF;
        dest[1] = (u2 >>= 8) & 0xFF;
        break;
    case 4:
        u4 = *((PBCS_U4*)ori);
        dest[0] = u4 & 0xFF;
        dest[1] = (u4 >>= 8) & 0xFF;
        dest[2] = (u4 >>= 8) & 0xFF;
        dest[3] = (u4 >>= 8) & 0xFF;
        break;
#ifdef PBCS_8BIT_SPT
    case 8:
        u8 = *((PBCS_U8*)ori);
        dest[0] = u8 & 0xFF;
        dest[1] = (u8 >>= 8) & 0xFF;
        dest[2] = (u8 >>= 8) & 0xFF;
        dest[3] = (u8 >>= 8) & 0xFF;
        dest[4] = (u8 >>= 8) & 0xFF;
        dest[5] = (u8 >>= 8) & 0xFF;
        dest[6] = (u8 >>= 8) & 0xFF;
        dest[7] = (u8 >>= 8) & 0xFF;
        break;
#endif
    }

}

PBCS_U4 PBCS_initPacket(
    PBCS_U1* result,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_VDLEN* lens,
    PBCS_DTID vdNum
){
    PBCS_VDLEN vdLenTmp = 0;
    PBCS_DTID vdIndex = 0;
    PBCS_PTID ptid = 0;
    PBCS_PID pid = 0;
    PBCS_U4 errCode = 0;
    PBCS_U1 j = 0;
    if(
        (errCode = PBCS_pktIsBelongTo(&ptid,config,pkgConfig)) != 0 ||
        (errCode = PBCS_getPacketID(&pid,config,pkgConfig)) != 0
    ){
        return errCode;
    }
    for(j = 0;j < config->ptidLen;j++){
        result[j] = ptid & 0xFF;
        ptid >>= 8;
    }
    for(j = 0;j < config->pidLen;j++){
        result[j + config->ptidLen] = pid & 0xFF;
        pid >>= 8;
    }
    result += config->ptidLen + config->pidLen;
    for(;vdIndex < vdNum;vdIndex++,result += config->vdlLen){
        vdLenTmp = lens[vdIndex];
        for(j = 0;j < config->vdlLen;j++){
            result[j] = vdLenTmp & 0xFF;
            vdLenTmp >>= 8;
        }
    }
}

PBCS_U4 PBCS_genPacketDataOffsets(
    PBCS_DATAINDEX* result,
    PBCS_DATAINDEX* sedLen,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_VDLEN* lens,
    PBCS_DTID vdNum
){
    PBCS_DTID vdIndex = 0,dtid = 0,dtNum = 0;
    PBCS_U4 errCode = 0;
    PBCS_U1 dtMark = 0;
    PBCS_DATAINDEX current = config->ptidLen + config->pidLen + vdNum * config->vdlLen;
    if((errCode = PBCS_getDataNum(&dtNum,config,pkgConfig)) != 0){
        return errCode;
    }
    for(;dtid < dtNum;dtid++){
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
            current += lens[vdIndex++];
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
    *sedLen = result[dtNum] = current;
    return 0;
}

PBCS_U4 PBCS_writeDataU1(PBCS_U1* result,PBCS_U1 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,1);
    return 0;
}

PBCS_U4 PBCS_writeDataU2(PBCS_U1* result,PBCS_U2 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,2);
    return 0;
}

PBCS_U4 PBCS_writeDataU4(PBCS_U1* result,PBCS_U4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,4);
    return 0;
}

PBCS_U4 PBCS_writeDataI1(PBCS_U1* result,PBCS_I1 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,1);
    return 0;
}

PBCS_U4 PBCS_writeDataI2(PBCS_U1* result,PBCS_I2 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,2);
    return 0;
}

PBCS_U4 PBCS_writeDataI4(PBCS_U1* result,PBCS_I4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,4);
    return 0;
}

PBCS_U4 PBCS_writeDataF4(PBCS_U1* result,PBCS_F4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,4);
    return 0;
}

PBCS_U4 PBCS_writeDataV(PBCS_U1* result,PBCS_U1* val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_DATAINDEX i = 0,len = offsets[dataID + 1] - offsets[dataID];
    result += offsets[dataID];
    for(;i < len;i++){
        result[i] = val[i];
    }
    return 0;
}

#ifdef PBCS_8BIT_SPT
PBCS_U4 PBCS_writeDataU8(PBCS_U1* result,PBCS_U8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,8);
    return 0;
}

PBCS_U4 PBCS_writeDataI8(PBCS_U1* result,PBCS_I8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,8);
    return 0;
}

PBCS_U4 PBCS_writeDataF8(PBCS_U1* result,PBCS_F8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets){
    PBCS_fillDataLowAH(result + offsets[dataID],&val,8);
    return 0;
}
#endif
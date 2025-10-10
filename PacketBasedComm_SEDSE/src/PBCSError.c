#include "PBCSError.h"

PBCS_U4 PBCS_errorCont(PBCS_U1 errCode,PBCS_U1 infoB1,PBCS_U1 infoB2,PBCS_U1 infoB3){
    PBCS_U4 result = 0;
    result += errCode;
    result <<= 8;
    result += infoB1;
    result <<= 8;
    result += infoB2;
    result <<= 8;
    result += infoB3;
    return result;
}

PBCS_U1 PBCS_getErrCode(PBCS_U4 error){
    return error >> 24;
}

PBCS_U1 PBCS_getErrInfo(PBCS_U4 error,PBCS_U1 infoBit){
    if(infoBit > 2) infoBit = 2;
    error <<= (infoBit + 1) * 8;
    return error >> 24;
}
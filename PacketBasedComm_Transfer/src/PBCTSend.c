#include "PBCTSend.h"
#include "CRC.h"

void PBCT_writeByteToBuf(
    PBCT_sendCB callBack,
    PBCT_U1* buffer,
    PBCT_DTLEN bufferLen,
    PBCT_DTLEN* nowIndex,
    PBCT_U1 waitToWrite
){
    if((*nowIndex) >= bufferLen){
        callBack(buffer,bufferLen);
        *nowIndex = 0;
    }
    buffer[(*nowIndex)++] = waitToWrite;
}

void PBCT_writeByteCheck(
    PBCT_sendCB callBack,
    PBCT_U1* buffer,
    PBCT_DTLEN bufferLen,
    PBCT_DTLEN* nowIndex,
    PBCT_U1 waitToWrite
){
    if(waitToWrite == PBCT_START_BYTE || waitToWrite == PBCT_TM_BYTE || waitToWrite == PBCT_END_BYTE){
        PBCT_writeByteToBuf(callBack,buffer,bufferLen,nowIndex,PBCT_TM_BYTE);
    }
    PBCT_writeByteToBuf(callBack,buffer,bufferLen,nowIndex,waitToWrite);
}

void PBCT_send(
    PBCT_sendCB callBack,
    PBCT_U1* oriData,
    PBCT_DTLEN oriDTLen,
    PBCT_U1* buffer,
    PBCT_DTLEN bufferLen,
    PBCT_U1 dtlLen,
    PBCT_CRCPOLY crcPoly,
    PBCT_U1 crcBits
){
    
    PBCT_CRCPOLY errCode = 0;
    PBCT_DTLEN dtIndex = 0,bufIndex = 1,lenInDT = oriDTLen;
    PBCT_DTLEN i = 0;

    if(crcPoly != 0) {
        lenInDT += (--crcBits) / 8;
        if(crcBits % 8 != 0) lenInDT++;
        errCode = CRC_calRemainder(oriData,oriDTLen,crcPoly,crcBits + 1);
        if(crcBits % 8 != 0) errCode <<= (crcBits / 8 + 1) * 8 - crcBits;
    }
    buffer[0] = PBCT_START_BYTE;

    for(;i < dtlLen;i++){
        PBCT_writeByteCheck(callBack,buffer,bufferLen,&bufIndex,(lenInDT >> (i * 8)) & 0xFF);
    }

    for(;dtIndex < oriDTLen;dtIndex++){
        PBCT_writeByteCheck(callBack,buffer,bufferLen,&bufIndex,oriData[dtIndex]);
    }

    if(crcPoly != 0){
        i = lenInDT - oriDTLen - 1;
        while(1){
            PBCT_writeByteCheck(callBack,buffer,bufferLen,&bufIndex,errCode >> (i * 8));
            if(i == 0) break;
            else i--;
        }
    }

    PBCT_writeByteToBuf(callBack,buffer,bufferLen,&bufIndex,PBCT_END_BYTE);
    if(bufIndex > 0) callBack(buffer,bufIndex);

}
#include "PBCTReceive.h"
#include "CRC.h"

void PBCT_initProcess(
    struct PBCT_process* process,
    PBCT_malloc pbctMalloc,
    PBCT_overCB overCB,
    PBCT_start start,
    PBCT_err err,
    PBCT_U1 dtlLen,
    PBCT_CRCPOLY crcPoly,
    PBCT_U1 crcBits
){
    process->pbctMalloc = pbctMalloc;
    process->overCB = overCB;
    process->start = start;
    process->err = err;
    process->dtlLen = dtlLen;
    process->crcPoly = crcPoly;
    process->crcBits = crcBits;
    PBCT_resetProcess(process);
}

void PBCT_resetProcess(struct PBCT_process* process){
    process->isLastTM = 0;
    process->isPacketStart = 0;
    process->dtLen = 0;
    process->dtBuffer = 0;
    process->dtIndex = 0;
    process->dtLenByte = 0;
}

void PBCT_receiveData(struct PBCT_process* process,PBCT_U1* rcvDT,PBCT_DTLEN rcvLen){

    PBCT_DTLEN i = 0,antiOverflow = 0,crc = 0;
    for(;i < rcvLen;i++){
        if(!process->isPacketStart && rcvDT[i] == PBCT_START_BYTE){
            process->isPacketStart = 1;
            process->start();
        }else if(process->isPacketStart){

            if(process->isLastTM){
                if(
                    rcvDT[i] != PBCT_START_BYTE && 
                    rcvDT[i] != PBCT_TM_BYTE && 
                    rcvDT[i] != PBCT_END_BYTE
                ) {
                    process->err(PBCT_ERR_ILLEGAL_TMBYTE);
                    PBCT_resetProcess(process);
                    break;
                }
            }else if(rcvDT[i] == PBCT_TM_BYTE){
                process->isLastTM = 1;
                continue;
            }

            if(!process->isLastTM){
                if(rcvDT[i] == PBCT_START_BYTE){
                    process->err(PBCT_ERR_ILLEGAL_START_BYTE);
                    PBCT_resetProcess(process);
                    break;
                }else if(rcvDT[i] == PBCT_END_BYTE && process->dtIndex != process->dtLen){
                    process->err(PBCT_ERR_LEN_NOT_CORRECT);
                    PBCT_resetProcess(process);
                    break;
                }
            }

            if(process->dtLenByte < process->dtlLen){

                antiOverflow = rcvDT[i];
                process->dtLen += antiOverflow << ((process->dtLenByte)++);
                if(process->dtLenByte >= process->dtlLen){
                    process->dtBuffer = process->pbctMalloc(process->dtLen);
                }

            }else{

                if(rcvDT[i] != PBCT_END_BYTE && process->dtIndex >= process->dtLen){
                    process->err(PBCT_ERR_LEN_NOT_CORRECT);
                    PBCT_resetProcess(process);
                    break;
                }else if(!process->isLastTM && rcvDT[i] == PBCT_END_BYTE){
                    if(process->crcPoly != 0){
                        crc = CRC_calRemainder(
                            process->dtBuffer,
                            process->dtLen,
                            process->crcPoly,
                            process->crcBits
                        );
                        if(crc != 0){
                            process->err(PBCT_ERR_CRC_NOT_CORRECT);
                            PBCT_resetProcess(process);
                            break;
                        }
                        process->crcBits--;
                        if(process->crcBits % 8 == 0){
                            process->overCB(process->dtBuffer,process->dtLen - process->crcBits / 8);
                        }else{
                            process->overCB(process->dtBuffer,process->dtLen - process->crcBits / 8 - 1);
                        }
                    }else{
                        process->overCB(process->dtBuffer,process->dtLen);
                    }
                    PBCT_resetProcess(process);
                    break;
                }
                process->dtBuffer[(process->dtIndex++)] = rcvDT[i];

            }

            if(process->isLastTM){
                process->isLastTM = 0;
            }

        }
    }

}
#include "CRC.h"

CRC_POLY CRC_calRemainder(
    CRC_U1* dt,
    CRC_DTLEN dtLen,
    CRC_POLY crcPoly,
    CRC_U1 crcBits
){

    CRC_POLY result = 0,highestBit = 1 << (crcBits - 1),crtDT = dt[0],crtBit = 0x80;
    CRC_DTLEN index = 0;

    while(1){

        if(index > dtLen) break;

        result <<= 1;
        if(crtDT & crtBit) result++;
        if(result & highestBit) result ^= crcPoly;

        if(crtBit == 1) {
            index++;
            if(index == dtLen){
                crtBit = 1 << (crcBits - 2);
                crtDT = 0;
            }else{
                crtBit = 0x80;
                crtDT = dt[index];
            }
        }else crtBit >>= 1;

    }

    return result;

}
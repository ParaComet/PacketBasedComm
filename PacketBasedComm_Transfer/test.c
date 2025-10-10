#include "PBCTReceive.h"
#include "PBCTSend.h"
#include "stdio.h"
#include "stdlib.h"

struct PBCT_process process;

PBCT_U1* mallocCB(PBCT_DTLEN dtLen){
    return malloc(dtLen);
}

void startCB(){
    printf("receive start!\n");
}

void overCB(PBCT_U1* dt,PBCT_DTLEN dtLen){
    printf("\nreceive over: ");
    for(int i = 0;i < dtLen;i++){
        printf("%X ",dt[i]);
    }
    printf("\n");
}

void errCB(PBCT_ERRCODE err){
    printf("\n");
    printf("err:%X",err);
    printf("\n");
}

void sendCB(PBCT_U1* dt,PBCT_DTLEN dtLen){
    PBCT_receiveData(&process,dt,dtLen);
    for(int i = 0;i < dtLen;i++){
        printf("%X ",dt[i]);
    }
}

int main(){

    unsigned char dt[8] = {0x00,0xAA,0x01,0xC8,0xAB,0x02,0xAC,0x03};
    PBCT_initProcess(&process,mallocCB,overCB,startCB,errCB,sizeof(PBCT_DTLEN),0x189,9);
    PBCT_send(sendCB,dt,8,malloc(3),3,sizeof(PBCT_DTLEN),0x189,9);

}
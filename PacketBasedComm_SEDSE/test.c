#include "stdio.h"
#include "stdlib.h"
#include "PBCSSe.h"
#include "PBCSDse.h"
#include "output.h"

const PBCS_U1 data_belonging[12] = {0x00,0x00, 0x01,0x00, 0x02,0x01, 0x03,0x01, 0x04,0x00, 0x05,0x05};
const PBCS_U1 data_packetNums[6] = {
    0x00, 0x02,0x00,
    0x03, 0x03,0x00
};
const PBCS_U1 data_packets[43] = {
    0x00, 0x00,0x00, 0x02,0x00,0x00,0x00, 0x40,
    0x00, 0x01,0x00, 0x01,0x00,0x00,0x00, 0x07,
    0x03, 0x00,0x00, 0x01,0x00,0x00,0x00, 0x06,
    0x03, 0x01,0x00, 0x05,0x00,0x00,0x00, 0x10,0x82,0x07,
    0x03, 0x02,0x00, 0x03,0x00,0x00,0x00, 0xAA,0x08
};
const PBCS_U1 data_packetsIndexes[30] = {
    0x00, 0x00,0x00, 0x00,0x00,0x00,
    0x00, 0x01,0x00, 0x08,0x00,0x00,
    0x03, 0x00,0x00, 0x10,0x00,0x00,
    0x03, 0x01,0x00, 0x18,0x00,0x00,
    0x03, 0x02,0x00, 0x22,0x00,0x00
};

const PBCS_U1 data_nonT_packets[36] = {
    0x00,0x00, 0x02,0x00,0x00,0x00, 0x40,
    0x01,0x00, 0x01,0x00,0x00,0x00, 0x07,
    0x02,0x00, 0x01,0x00,0x00,0x00, 0x06,
    0x03,0x00, 0x05,0x00,0x00,0x00, 0x10,0x82,0x07,
    0x04,0x00, 0x00,0x00,0x00,0x00
};
const PBCS_U1 data_nonT_packetsIndexes[25] = {
    0x00,0x00, 0x00,0x00,0x00,
    0x01,0x00, 0x07,0x00,0x00,
    0x02,0x00, 0x0E,0x00,0x00,
    0x03,0x00, 0x15,0x00,0x00,
    0x04,0x00, 0x1E,0x00,0x00
};

const struct PBCS_config config = {data_belonging,data_packetNums,data_packets,data_packetsIndexes,6,2,5,1,2,3,4,3};
const struct PBCS_config config_nonT = {0,0,data_nonT_packets,data_nonT_packetsIndexes,1,1,5,0,2,3,4,3};

int main(){
    
    // PBCS_CFGINDEX result_getPacketCfg;
    // PBCS_BOOL result_isBelongTo;
    // PBCS_PTID result_pktIsBelongTo;
    // PBCS_PTID result_pktTypes[5];
    // PBCS_PID result_pkt;
    // PBCS_PID result_pkts[5];
    // PBCS_DTID result_dtid;
    // PBCS_U1 result_dtTypemark;

    // PBCS_getPacketCfg(&result_getPacketCfg,&config,0,0);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,0,1);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,3,0);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,3,1);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,3,2);

    // PBCS_isBelongTo(&result_isBelongTo,&config,3,1);
    // PBCS_isBelongTo(&result_isBelongTo,&config,1,2);

    // PBCS_pktIsBelongTo(&result_pktIsBelongTo,&config,result_getPacketCfg);
    // PBCS_getPacketID(&result_pkt,&config,result_getPacketCfg);
    // PBCS_getDataNum(&result_dtid,&config,result_getPacketCfg);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,0,1);
    // PBCS_pktIsBelongTo(&result_pktIsBelongTo,&config,result_getPacketCfg);
    // PBCS_getPacketID(&result_pkt,&config,result_getPacketCfg);
    // PBCS_getDataNum(&result_dtid,&config,result_getPacketCfg);

    // PBCS_getAllPacketTypes(result_pktTypes,&config);
    // PBCS_getAllOccupiedPacketTypes(result_pktTypes,&config);

    // PBCS_getPacketsNum(&result_pkt,&config,0);
    // PBCS_getPacketsNum(&result_pkt,&config,3);

    // PBCS_getPackets(result_pkts,&config,0);
    // PBCS_getPackets(result_pkts,&config,3);

    // PBCS_getPacketCfg(&result_getPacketCfg,&config,3,1);
    // PBCS_getDataTypemark(&result_dtTypemark,0,&config,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,1,&config,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,2,&config,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,3,&config,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,4,&config,result_getPacketCfg);

    // PBCS_DATAINDEX result_offsetArr[6];
    // PBCS_VDLEN lens[1] = {7};
    // PBCS_DATAINDEX sedLen;
    // PBCS_U1 vd[7] = {0,5,6,7,8,9,10};
    // PBCS_DTID vdNum;
    // PBCS_U1 result_readU1 = 0;
    // PBCS_U2 result_readU2 = 0;
    // PBCS_U4 result_readU4 = 0;
    // PBCS_U8 result_readU8 = 0;
    // PBCS_I2 result_readI2 = 0;

    // PBCS_getPacketCfg(&result_getPacketCfg,&config,3,1);
    // PBCS_genPacketDataOffsets(result_offsetArr,&sedLen,&config,result_getPacketCfg,lens,1);
    // PBCS_U1* sendDT = (PBCS_U1*)malloc(sedLen);
    // PBCS_initPacket(sendDT,&config,result_getPacketCfg,lens,1);
    // PBCS_writeDataU1(sendDT,4,0,result_offsetArr);
    // PBCS_writeDataU2(sendDT,3,1,result_offsetArr);
    // PBCS_writeDataU4(sendDT,2,2,result_offsetArr);
    // PBCS_writeDataU8(sendDT,1,3,result_offsetArr);
    // PBCS_writeDataV(sendDT,vd,4,result_offsetArr);

    // PBCS_getPacketCfgFromStream(&result_getPacketCfg,&config,sendDT);
    // PBCS_getPacketDataOffsets(result_offsetArr,lens,&vdNum,&config,result_getPacketCfg,sendDT);
    // PBCS_getDataByU1(&result_readU1,result_offsetArr,0,sendDT);
    // PBCS_getDataByU2(&result_readU2,result_offsetArr,1,sendDT);
    // PBCS_getDataByU4(&result_readU4,result_offsetArr,2,sendDT);
    // PBCS_getDataByU8(&result_readU8,result_offsetArr,3,sendDT);
    // PBCS_getDataByV(vd,result_offsetArr,4,sendDT);

    // free(sendDT);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config,0,0);
    // PBCS_genPacketDataOffsets(result_offsetArr,&sedLen,&config,result_getPacketCfg,0,0);
    // sendDT = (PBCS_U1*)malloc(sedLen);
    // PBCS_initPacket(sendDT,&config,result_getPacketCfg,0,0);
    // PBCS_writeDataU1(sendDT,4,0,result_offsetArr);
    // PBCS_writeDataI2(sendDT,-3,1,result_offsetArr);

    // PBCS_getPacketCfgFromStream(&result_getPacketCfg,&config,sendDT);
    // PBCS_getPacketDataOffsets(result_offsetArr,lens,&vdNum,&config,result_getPacketCfg,sendDT);
    // PBCS_getDataByU1(&result_readU1,result_offsetArr,0,sendDT);
    // PBCS_getDataByI2(&result_readI2,result_offsetArr,1,sendDT);

    // //------------------------------------------------------

    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,3);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,4);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,0);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,1);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,2);

    // PBCS_pktIsBelongTo(&result_pktIsBelongTo,&config_nonT,result_getPacketCfg);
    // PBCS_getPacketID(&result_pkt,&config_nonT,result_getPacketCfg);
    // PBCS_getDataNum(&result_dtid,&config_nonT,result_getPacketCfg);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,3);
    // PBCS_pktIsBelongTo(&result_pktIsBelongTo,&config_nonT,result_getPacketCfg);
    // PBCS_getPacketID(&result_pkt,&config_nonT,result_getPacketCfg);
    // PBCS_getDataNum(&result_dtid,&config_nonT,result_getPacketCfg);

    // PBCS_getAllPacketTypes(result_pktTypes,&config_nonT);
    // PBCS_getAllOccupiedPacketTypes(result_pktTypes,&config_nonT);
    // PBCS_getPackets(result_pkts,&config_nonT,0);

    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,3);
    // PBCS_getDataTypemark(&result_dtTypemark,0,&config_nonT,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,1,&config_nonT,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,2,&config_nonT,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,3,&config_nonT,result_getPacketCfg);
    // PBCS_getDataTypemark(&result_dtTypemark,4,&config_nonT,result_getPacketCfg);

    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,3);
    // PBCS_genPacketDataOffsets(result_offsetArr,&sedLen,&config_nonT,result_getPacketCfg,lens,1);
    // sendDT = (PBCS_U1*)malloc(sedLen);
    // PBCS_initPacket(sendDT,&config_nonT,result_getPacketCfg,lens,1);
    // PBCS_writeDataU1(sendDT,4,0,result_offsetArr);
    // PBCS_writeDataU2(sendDT,3,1,result_offsetArr);
    // PBCS_writeDataU4(sendDT,2,2,result_offsetArr);
    // PBCS_writeDataU8(sendDT,1,3,result_offsetArr);
    // PBCS_writeDataV(sendDT,vd,4,result_offsetArr);

    // PBCS_getPacketCfgFromStream(&result_getPacketCfg,&config_nonT,sendDT);
    // PBCS_getPacketDataOffsets(result_offsetArr,lens,&vdNum,&config_nonT,result_getPacketCfg,sendDT);
    // PBCS_getDataByU1(&result_readU1,result_offsetArr,0,sendDT);
    // PBCS_getDataByU2(&result_readU2,result_offsetArr,1,sendDT);
    // PBCS_getDataByU4(&result_readU4,result_offsetArr,2,sendDT);
    // PBCS_getDataByU8(&result_readU8,result_offsetArr,3,sendDT);
    // PBCS_getDataByV(vd,result_offsetArr,4,sendDT);

    // free(sendDT);
    // PBCS_getPacketCfg(&result_getPacketCfg,&config_nonT,0,0);
    // PBCS_genPacketDataOffsets(result_offsetArr,&sedLen,&config_nonT,result_getPacketCfg,0,0);
    // sendDT = (PBCS_U1*)malloc(sedLen);
    // PBCS_initPacket(sendDT,&config_nonT,result_getPacketCfg,0,0);
    // PBCS_writeDataU1(sendDT,4,0,result_offsetArr);
    // PBCS_writeDataI2(sendDT,-3,1,result_offsetArr);

    // PBCS_getPacketCfgFromStream(&result_getPacketCfg,&config_nonT,sendDT);
    // PBCS_getPacketDataOffsets(result_offsetArr,lens,&vdNum,&config_nonT,result_getPacketCfg,sendDT);
    // PBCS_getDataByU1(&result_readU1,result_offsetArr,0,sendDT);
    // PBCS_getDataByI2(&result_readI2,result_offsetArr,1,sendDT);

    PBCS_CFGINDEX packet;
    PBCS_U4 err = PBCS_getPacketCfg(&packet,&Aconfig,1,0);
    printf("%d",packet);

    return 0;

}
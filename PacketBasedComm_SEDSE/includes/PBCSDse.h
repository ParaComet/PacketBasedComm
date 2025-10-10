//提供反序列化数据包所需的函数
#ifndef __PBCS_DSE_H
#define __PBCS_DSE_H

//数据包格式见 PBCSSe.h

#include "PBCSCFGFile.h"

/**
 * 从传入的配置为待解析的数据包找到所需的数据包配置
 * @param result 寻找结果
 * @param config 此次解析使用的配置
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPacketCfgFromStream(PBCS_CFGINDEX* result,const struct PBCS_config* config,const PBCS_U1* pkgData);

/**
 * 根据传入的配置和具体的待解析的数据包建立位移数组,并返回其中所有可变长度数据的长度
 * 传入的 result 数组长度不应少于此数据包中的数据个数+1
 * 传入的 vdLens 数组长度不应少于此数据包中的可变长度数据个数
 * @param result 建立结果
 * @param vdLens 所有可变长度数据的长度,按数据ID号从小到大排列
 * @param vdNum 返回可变数据的个数
 * @param config 此次解析使用的配置
 * @param pkgConfig PBCS_getPacketCfg 解析到的数据包配置
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPacketDataOffsets(
    PBCS_DATAINDEX* result,
    PBCS_VDLEN* vdLens,
    PBCS_DTID* vdNum,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_U1* pkgData
);

/**
 * 获取数据包中的指定数据,结果以 PBCS_U1 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByU1(PBCS_U1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_U2 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByU2(PBCS_U2* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_U4 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByU4(PBCS_U4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_I1 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByI1(PBCS_I1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_I2 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByI2(PBCS_I2* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_I4 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByI4(PBCS_I4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_I1 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByF4(PBCS_F4* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_U1* 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByV(PBCS_U1* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

#ifdef PBCS_8BIT_SPT
/**
 * 获取数据包中的指定数据,结果以 PBCS_U8 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByU8(PBCS_U8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_I8 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByI8(PBCS_I8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);

/**
 * 获取数据包中的指定数据,结果以 PBCS_F8 类型返回
 * @param result 获取结果
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @param dataID 数据ID
 * @param pkgData 需要解析的数据包
 * @return 解析时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataByF8(PBCS_F8* result,const PBCS_DATAINDEX* offsets,PBCS_DTID dataID,const PBCS_U1* pkgData);
#endif

#endif
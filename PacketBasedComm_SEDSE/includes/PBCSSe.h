//提供序列化数据包所需的函数
#ifndef __PBCS_SE_H
#define __PBCS_SE_H

//数据包序列化格式如下:
//[数据包类型ID]       [数据包ID]         <可变参数长度>        <数据1,2,3.....>
//sizeof(PBCS_PTID)   sizeof(PBCS_PID)   sizeof(PBCS_VDLEN)   各数据类型的长度
//"<>"代表重复单元
//所有数据都采用低位先行模式,即低位的数据解析后在结果数据索引更靠前的位置,u1数组则不改变原来的顺序
//对于 f4 和 f8 ,采用先将其指针类型强制转型成 u4* 和 u8* 后再继续低位先行存放的方法

#include "PBCSCFGFile.h"

/**
 * 初始化序列数组
 * @param result 初始化结果
 * @param config 指定的配置
 * @param pkgConfig 数据包配置
 * @param lens 若数据包中有可变长度数据,按次序填入可变长度数据的长度,若没有可以填空指针
 * @param vdNum lens的长度
 * @return 初始化时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_initPacket(
    PBCS_U1* result,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_VDLEN* lens,
    PBCS_DTID vdNum
);

/**
 * 根据传入的配置和具体的可变数据长度数组建立位移数组,并返回基于此位移数组序列化后数据包的长度
 * 传入的 result 数组长度不应少于此数据包中的数据个数+1
 * @param result 建立结果
 * @param sedLen 序列化后数据包的长度
 * @param config 此次解析使用的配置
 * @param pkgConfig PBCS_getPacketCfg 解析到的数据包配置
 * @param lens 若数据包中有可变长度数据,按次序填入可变长度数据的长度,若没有可以填空指针
 * @param vdNum lens的长度
 * @return 建立时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_genPacketDataOffsets(
    PBCS_DATAINDEX* result,
    PBCS_DATAINDEX* sedLen,
    const struct PBCS_config* config,
    PBCS_CFGINDEX pkgConfig,
    const PBCS_VDLEN* lens,
    PBCS_DTID vdNum
);

/**
 * 向序列数组中写入 PBCS_U1 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_genPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataU1(PBCS_U1* result,PBCS_U1 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_U2 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataU2(PBCS_U1* result,PBCS_U2 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_U4 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataU4(PBCS_U1* result,PBCS_U4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_I1 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataI1(PBCS_U1* result,PBCS_I1 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_I2 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataI2(PBCS_U1* result,PBCS_I2 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_I4 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataI4(PBCS_U1* result,PBCS_I4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_F4 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataF4(PBCS_U1* result,PBCS_F4 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

/**
 * 向序列数组中写入 PBCS_U1* 类型可变长度数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataV(PBCS_U1* result,PBCS_U1* val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);

#ifdef PBCS_8BIT_SPT
/**
 * 向序列数组中写入 PBCS_U8 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataU8(PBCS_U1* result,PBCS_U8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);
#endif

#ifdef PBCS_DATATYPESP_I8
/**
 * 向序列数组中写入 PBCS_I8 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataI8(PBCS_U1* result,PBCS_I8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);
#endif

#ifdef PBCS_8BIT_SPT
/**
 * 向序列数组中写入 PBCS_F8 类型数据
 * @param result 写入结果
 * @param val 需要写入的数据
 * @param dataID 数据ID
 * @param offsets PBCS_getPacketDataOffsets 获取的偏移数组
 * @return 写入时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_writeDataF8(PBCS_U1* result,PBCS_F8 val,PBCS_DTID dataID,const PBCS_DATAINDEX* offsets);
#endif

#endif
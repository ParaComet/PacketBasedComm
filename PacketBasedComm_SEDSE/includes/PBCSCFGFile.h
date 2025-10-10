//提供加载配置和获取关于配置本身的一些信息的函数
#ifndef __PBCS_CONFIGURATION_FILE_H
#define __PBCS_CONFIGURATION_FILE_H

#include "PBCSConfig.h"

//数据类型标识
#define PBCS_DTMARK_U1 0x00 //u1
#define PBCS_DTMARK_U2 0x01 //u2
#define PBCS_DTMARK_U4 0x02 //u4
#define PBCS_DTMARK_I1 0x03 //i1
#define PBCS_DTMARK_I2 0x04 //i2
#define PBCS_DTMARK_I4 0x05 //i4
#define PBCS_DTMARK_F4 0x06 //f4
#define PBCS_DTMARK_VL 0x07 //v
#ifdef PBCS_8BIT_SPT
#define PBCS_DTMARK_U8 0x08 //u8
#define PBCS_DTMARK_I8 0x09 //i8
#define PBCS_DTMARK_F8 0x0A //f8
#endif

/**
 * 按数据包类型ID和数据包ID在指定配置中获取数据包配置
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgTypeID 数据包类型ID,若为无类型模式可任意填
 * @param pkgID 数据包ID
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPacketCfg(PBCS_CFGINDEX* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID,PBCS_PID pkgID);

/**
 * 根据指定配置判断两数据包类型是否有从属关系
 * @param result 判断结果
 * @param config 指定的配置
 * @param child 将要被判定为属于 parent 的数据包类型ID
 * @param parent 将要被判定为包含 child 的数据包类型ID
 * @result 判断时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_isBelongTo(PBCS_BOOL* result,const struct PBCS_config* config,PBCS_PTID child,PBCS_PTID parent);

/**
 * 根据指定配置获取数据包所属的数据包类型ID
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgConfig 数据包配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_pktIsBelongTo(PBCS_PTID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig);

/**
 * 根据指定配置获取数据包ID
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgConfig 数据包配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPacketID(PBCS_PID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig);

/**
 * 根据指定配置获取所有已注册的数据包类型的ID,顺序存放
 * result 的长度不应小于 config->totalTypes
 * @param result 获取结果
 * @param config 指定的配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getAllPacketTypes(PBCS_PTID* result,const struct PBCS_config* config);

/**
 * 根据指定配置获取所有已注册的有数据包的数据包类型的ID,顺序存放
 * result 的长度不应小于 config->occupiedTypes
 * @param result 获取结果
 * @param config 指定的配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getAllOccupiedPacketTypes(PBCS_PTID* result,const struct PBCS_config* config);

/**
 * 根据传入的配置获取某个指定数据包类型下的数据包个数
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgTypeID 数据包类型ID
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPacketsNum(PBCS_PID* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID);

/**
 * 根据传入的配置获取某个指定数据包类型下所有的数据包ID,顺序存放
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgTypeID 数据包类型ID
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getPackets(PBCS_PID* result,const struct PBCS_config* config,PBCS_PTID pkgTypeID);

/**
 * 根据指定配置获取数据包的数据个数
 * @param result 获取结果
 * @param config 指定的配置
 * @param pkgConfig 数据包配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataNum(PBCS_DTID* result,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig);

/**
 * 根据指定配置获取数据包指定数据ID的数据类型标识
 * @param result 获取结果
 * @param dtid 需要获取的数据ID
 * @param config 指定的配置
 * @param pkgConfig 数据包配置
 * @return 获取时若有错误则返回具体的错误信息
 */
PBCS_U4 PBCS_getDataTypemark(PBCS_U1* result,PBCS_DTID dtid,const struct PBCS_config* config,PBCS_CFGINDEX pkgConfig);

#endif
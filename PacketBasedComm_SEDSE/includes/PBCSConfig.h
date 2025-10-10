//此配置文件可修改解析器的一些参数以及控制一些功能的开关
//注:整个API的数据存放和数据包生成如无特殊声明都遵循低位先行原则
#ifndef __PBCS_CONFIG_H
#define __PBCS_CONFIG_H

//一些基本数据类型                     类型标识
typedef unsigned char PBCS_U1;      //u1
typedef unsigned short PBCS_U2;     //u2
typedef unsigned int PBCS_U4;       //u4
typedef char PBCS_I1;               //i1
typedef short PBCS_I2;              //i2
typedef int PBCS_I4;                //i4
typedef float PBCS_F4;              //f4

//提供八位数据类型支持
#define PBCS_8BIT_SPT
#ifdef PBCS_8BIT_SPT
typedef unsigned long long PBCS_U8; //u8
typedef long long PBCS_I8;          //i8
typedef double PBCS_F8;             //f8
#endif

//bool类型
typedef PBCS_U1 PBCS_BOOL;

//序列化后数据包的形式:
//有类型模式: [数据包类型ID][数据包ID][可变数据1长度][可变数据2长度]...[数据1][数据2]...
//无类型模式: [数据包ID][可变数据1长度][可变数据2长度]...[数据1][数据2]...
//下列选项用来选择程序中承载这些数据的变量的类型,所选类型长度必须要大于等于所有所用的 PBCS_config 中对应各项的长度的最大值
//数据包类型ID的长度(字节)
typedef PBCS_U4 PBCS_PTID;
//数据包ID的长度(字节)
typedef PBCS_U4 PBCS_PID;
//数据包中可变长度数据的长度的标识长度(字节)
typedef PBCS_U4 PBCS_VDLEN;
//数据包中数据的ID长度(字节)
typedef PBCS_U4 PBCS_DTID;
//PBCS_config 中的数组使用的索引类型,最小限制可见下方 PBCS_config 的注释
typedef PBCS_U4 PBCS_CFGINDEX;

//待解析数据包数组使用的索引类型
typedef PBCS_U4 PBCS_DATAINDEX;

//代表一个可用的配置
//ptidLen == 0 时视为启用无类型模式,此时可视为整个配置中只有一个ID为0的数据包类型,并且所有的数据包都属于它
struct PBCS_config
{

    //注释为内部数据存放格式,"<>"包含的为重复单元
    //<[数据包类型ID][父数据包类型ID]>
    //顺序存储
    const PBCS_U1* belonging;
    //<[数据包类型ID][此类型下的数据包个数]>
    //顺序存储
    const PBCS_U1* packetNums;
    //有类型模式: <[数据包类型ID][数据包ID][此数据包下的数据个数]<高四位数据类型标识|低四位数据类型标识>>
    //无类型模式: <[数据包ID][此数据包下的数据个数]<高四位数据类型标识|低四位数据类型标识>>
    //数据ID低四位在前
    const PBCS_U1* packets;
    //有类型模式: <[数据包类型ID][数据包ID][在packets中的起始索引]>
    //无类型模式: <[数据包ID][在packets中的起始索引]>
    //顺序存储
    const PBCS_U1* packetsIndexes;

    const PBCS_PTID totalTypes;
    const PBCS_PTID occupiedTypes;
#ifdef PBCS_8BIT_SPT
    const PBCS_U8 totalPkts;
#else
    const PBCS_U4 totalPkts;
#endif

    //此配置使用的数据包类型ID的长度(字节)
    const PBCS_U1 ptidLen;
    //此配置使用的数据包ID的长度(字节)
    const PBCS_U1 pidLen;
    //此配置使用的数据包中可变长度数据的长度(字节)
    const PBCS_U1 vdlLen;
    //此配置使用的数据包中数据的ID长度(字节)
    const PBCS_U1 dtidLen;
    //此配置使用的程序中数据的ID长度(字节)
    const PBCS_U1 cfgIndexLen;

};

#endif
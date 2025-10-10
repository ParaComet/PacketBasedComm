//
// Created by QingG on 2025/9/13.
//

#ifndef PBCSCONFIGGENERATOR_PBCSTYPEDEF_H
#define PBCSCONFIGGENERATOR_PBCSTYPEDEF_H

#include "cstdint"

namespace PBCS{
    //数据包类型ID
    typedef uint64_t PBCS_PTID;
    //数据包ID
    typedef uint64_t PBCS_PID;
    //数据包中数据的ID长度(字节)
    typedef uint64_t PBCS_DTID;
    //PBCS_config 中的数组使用的索引类型,最小限制可见下方 PBCS_config 的注释
    typedef uint64_t PBCS_CFGINDEX;
}

#endif //PBCSCONFIGGENERATOR_PBCSTYPEDEF_H
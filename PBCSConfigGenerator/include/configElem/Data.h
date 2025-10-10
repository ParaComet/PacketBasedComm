//
// Created by QingG on 2025/9/14.
//

#ifndef PBCSCONFIGGENERATOR_DATA_H
#define PBCSCONFIGGENERATOR_DATA_H
#include <string>

namespace PBCS{
    enum class DataType{
        UINT8,
        UINT16,
        UINT32,
        INT8,
        INT16,
        INT32,
        FLOAT32,
        VARIABLE,
        UINT64,
        INT64,
        FLOAT64
    };
    class Data {
        DataType dataType;
        std::string name;
        friend class Packet;
    public:
        explicit Data(DataType dataType, std::string name);
        DataType getDataType();
        std::string getName();
        void setDataType(DataType dataType);
    };
}

#endif //PBCSCONFIGGENERATOR_DATA_H
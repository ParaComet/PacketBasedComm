//
// Created by QingG on 2025/9/14.
//

#include "configElem/Data.h"

namespace PBCS {

    Data::Data(DataType dataType, std::string name) {
        this->dataType = dataType;
        this->name = std::move(name);
    }

    DataType Data::getDataType() {
        return dataType;
    }

    std::string Data::getName() {
        return name;
    }

    void Data::setDataType(DataType dataType) {
        this->dataType = dataType;
    }

}
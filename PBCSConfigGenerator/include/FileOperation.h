//
// Created by QingG on 2025/9/15.
//

#ifndef PBCSCONFIGGENERATOR_CONFIGFILE_H
#define PBCSCONFIGGENERATOR_CONFIGFILE_H

#include "configElem/Classes.h"
#include <string>

namespace PBCS {
    Config* loadConfigFile(const std::string& filePath);
    int saveConfigFile(Config* config,const std::string& filePath,const std::string& encoding);
}

#endif //PBCSCONFIGGENERATOR_CONFIGFILE_H
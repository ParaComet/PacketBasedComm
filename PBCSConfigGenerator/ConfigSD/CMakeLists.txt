cmake_minimum_required(VERSION 3.10)
project(ConfigSD)

aux_source_directory(./ SRC)

include_directories(${INCLUDE})

set(LIBRARY_OUTPUT_PATH ${OUTPUT_PATH})

add_library(${CONFIG_SD_LIBFILE} SHARED ${SRC})

target_link_libraries(${CONFIG_SD_LIBFILE}
        Qt5::Core
        Qt5::Xml
)
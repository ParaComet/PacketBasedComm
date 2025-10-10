cmake_minimum_required(VERSION 4.0)
project(CodeGen)

aux_source_directory(./ SRC)

include_directories(${INCLUDE})

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH})

add_executable(${GENERATOR_EXECFILE} ${SRC})

link_directories(${OUTPUT_PATH})
target_link_libraries(${GENERATOR_EXECFILE}
        Qt5::Core
        Qt5::Xml
        ${CONFIG_SD_LIBFILE}
)
cmake_minimum_required(VERSION 3.10)
project(Editor)

file(GLOB_RECURSE SRC_UI ./ui/*.cpp)
file(GLOB_RECURSE SRC ./*.cpp)

include_directories(${INCLUDE} ./ui)

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH})

if(WIN32)
    add_executable(${EDITOR_EXECFILE} WIN32 ${SRC} ${SRC_UI} ${RES_PATH}/title.rc)
else()
    add_executable(${EDITOR_EXECFILE} ${SRC} ${SRC_UI} ${RES_PATH}/title.rc)
endif()

link_directories(${OUTPUT_PATH})
target_link_libraries(${EDITOR_EXECFILE}
        Qt5::Core
        Qt5::Xml
        Qt5::Gui
        Qt5::Widgets
        ${CONFIG_SD_LIBFILE}
)
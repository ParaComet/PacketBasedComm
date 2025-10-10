cmake_minimum_required(VERSION 4.0)
project(PBCSConfigGenerator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "E:/Qt/Qt5.8.0/5.8/mingw53_32")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        REQUIRED)

set(OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set(INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(RES_PATH ${PROJECT_SOURCE_DIR}/res)

set(CONFIG_SD_LIBFILE configSD)
set(EDITOR_EXECFILE editor)
set(GENERATOR_EXECFILE gen)

add_compile_definitions(-DGEN_EXECNAME=\"${GENERATOR_EXECFILE}\")

file(REMOVE_RECURSE ${OUTPUT_PATH})

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${OUTPUT_PATH}/res)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/qtLib/debug ${OUTPUT_PATH})
else ()
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/qtLib/release ${OUTPUT_PATH})
endif ()

add_subdirectory(CodeGen)
add_subdirectory(ConfigSD)
add_subdirectory(Editor)
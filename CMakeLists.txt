# <CMakeLists.txt> -*- coding: utf-8 -*-
#
# Project owlnext-sample-listviewctrl-header
# Copyright (C) 2023 neige68
#

cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)
# スタティックリンク
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(NAME "sample")
message(STATUS "NAME: ${NAME}")
project(${NAME} CXX)

#------------------------------------------------------------
#
# boost
#

# BOOST を探す
# C: ドライブ以外の場合は 環境変数 CMAKE_PREFIX_PATH 等をセットしてください
find_package(Boost 1.75 REQUIRED COMPONENTS date_time system)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#------------------------------------------------------------
#
# OWL
#

# Include/Link Dir # add_executable より前じゃないとだめらしい
message(STATUS "LGS: $ENV{LGS}")
include_directories($ENV{OWLROOT}/include)
link_directories($ENV{OWLROOT}/lib)

#------------------------------------------------------------

# コンパイルオプション
set(CMAKE_CXX_FLAGS "/EHsc /MP /W4 /Yu\"pch.h\"")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D__TRACE /D__WARN /D__DEBUG=2")

if (${UNICODE})
    add_compile_definitions(UNICODE;_UNICODE)
    add_link_options(/ENTRY:wWinMainCRTStartup)
endif()

# マニフェストは無しにする
add_link_options(/MANIFEST:NO /SUBSYSTEM:WINDOWS)

# ソース
set(SOURCE
    sampldlg.cpp
    )

add_executable(${NAME} WIN32 main.cpp ${SOURCE} res.rc resource.rc pch.cpp)

# プリコンパイルヘッダを生成
set_source_files_properties(pch.cpp PROPERTIES COMPILE_FLAGS "/Yc\"pch.h\"")

# ライブラリ
set(LIBS
    )
target_link_libraries(${NAME} ${LIBS}) # add_executable より後じゃないとだめらしい

# end of <CMakeLists.txt>

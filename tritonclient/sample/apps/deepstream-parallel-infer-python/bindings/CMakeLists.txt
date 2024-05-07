# SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
cmake_policy(VERSION 3.12)

project(pyds_common DESCRIPTION "Python bindings for Deepstream Apps Common")

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Setting values not set by user
function(check_variable_set variable_name default_value)
  if (NOT DEFINED ${variable_name})
    set(${variable_name} ${default_value} PARENT_SCOPE)
  endif()
endfunction()

check_variable_set(PYTHON_MAJOR_VERSION 3)
check_variable_set(PYTHON_MINOR_VERSION 10)
check_variable_set(PIP_PLATFORM linux_x86_64)
check_variable_set(DS_PATH "/opt/nvidia/deepstream/deepstream")

# Checking values are allowed
macro(check_variable_allowed var_name var_list)
  if(NOT ${var_name} IN_LIST ${var_list})
    message(FATAL_ERROR "${var_name} must be one of ${${var_list}}")
  endif()
endmacro()
set(PYTHON_MAJVERS_ALLOWED 3)
check_variable_allowed(PYTHON_MAJOR_VERSION PYTHON_MAJVERS_ALLOWED)
set(PYTHON_MINVERS_ALLOWED 10)
check_variable_allowed(PYTHON_MINOR_VERSION PYTHON_MINVERS_ALLOWED)
set(PIP_PLATFORM_ALLOWED linux_x86_64 linux_aarch64)
check_variable_allowed(PIP_PLATFORM PIP_PLATFORM_ALLOWED)

# Setting C++ values
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting python build versions
set(PYTHON_VERSION ${PYTHON_MAJOR_VERSION}.${PYTHON_MINOR_VERSION})
set(DS_COMMON_PATH "/opt/nvidia/deepstream/deepstream/sources/apps/apps-common/")
set(DS_PARALLEL_PATH "../../deepstream-parallel-infer/")

find_package(PkgConfig REQUIRED)
find_package(PythonLibs REQUIRED)
pkg_search_module(GSTREAMER REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(GSTREAMER_RTSP_SERVER REQUIRED IMPORTED_TARGET gstreamer-rtsp-server-1.0>=1.4)
pkg_search_module(JSONGLIB REQUIRED IMPORTED_TARGET json-glib-1.0)

include(FetchContent) 
FetchContent_Declare(pybind11
  URL
    https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz
  CMAKE_CACHE_ARGS
    -DPYBIND11_TEST:BOOL=OFF
)
FetchContent_MakeAvailable(pybind11)

add_library(${PROJECT_NAME}
  SHARED
    src/bindings.cpp
    ${DS_PARALLEL_PATH}/deepstream_parallel_infer_config_parser.cpp
    ${DS_COMMON_PATH}/src/deepstream_audio_classifier_bin.c
    ${DS_COMMON_PATH}/src/deepstream_common.c
    ${DS_COMMON_PATH}/src/deepstream_dsanalytics.c
    ${DS_COMMON_PATH}/src/deepstream_perf.c
    ${DS_COMMON_PATH}/src/deepstream_secondary_gie_bin.c
    ${DS_COMMON_PATH}/src/deepstream_sink_bin.c
    ${DS_COMMON_PATH}/src/deepstream_tiled_display_bin.c
    ${DS_COMMON_PATH}/src/deepstream_c2d_msg.c
    ${DS_COMMON_PATH}/src/deepstream_config_file_parser.c
    ${DS_COMMON_PATH}/src/deepstream_dsexample.c
    ${DS_COMMON_PATH}/src/deepstream_preprocess.c
    ${DS_COMMON_PATH}/src/deepstream_secondary_preprocess.c
    ${DS_COMMON_PATH}/src/deepstream_source_bin.c
    ${DS_COMMON_PATH}/src/deepstream_tracker_bin.c
    ${DS_COMMON_PATH}/src/deepstream_c2d_msg_util.c
    ${DS_COMMON_PATH}/src/deepstream_dewarper_bin.c
    ${DS_COMMON_PATH}/src/deepstream_osd_bin.c
    ${DS_COMMON_PATH}/src/deepstream_primary_gie_bin.c
    ${DS_COMMON_PATH}/src/deepstream_segvisual_bin.c
    ${DS_COMMON_PATH}/src/deepstream_streammux.c
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_config_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_dsexample_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_msgconsumer_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_preprocess_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_source_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_tracker_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_dewarper_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_gie_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_msgconv_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_segvisual_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_streammux_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_dsanalytics_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_image_save_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_osd_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_sink_yaml.cpp
    ${DS_COMMON_PATH}/src/deepstream-yaml/deepstream_tiled_display_yaml.cpp
)

# $<TARGET_PROPERTY:PkgConfig::GSTREAMER,INTERFACE_INCLUDE_DIRECTORIES>
# $<TARGET_PROPERTY:PkgConfig::JSONGLIB,INTERFACE_INCLUDE_DIRECTORIES>
target_include_directories(${PROJECT_NAME}
  PRIVATE
    /usr/local/cuda/include
    ${DS_PATH}/sources/includes
    ${DS_COMMON_PATH}/includes
    ${DS_PARALLEL_PATH}
    ${PYTHON_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    "-Wall"
    "-Wextra"
    "-pedantic"
    "-O3"
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    pthread
    dl
    yaml-cpp
    cudart
    nvds_osd
    nvds_meta
    nvds_infer
    nvds_msgbroker
    nvdsgst_meta
    nvdsgst_helper
    nvdsgst_smartrecord
    nvbufsurface
    nvbufsurftransform
    ${PYTHON_LIBRARIES}
    pybind11::pybind11
    PkgConfig::GSTREAMER
    PkgConfig::GSTREAMER_RTSP_SERVER
    PkgConfig::JSONGLIB
)

target_link_directories(${PROJECT_NAME}
  PUBLIC
    /usr/local/cuda/lib64
    ${DS_PATH}/lib
)

target_link_options(${PROJECT_NAME}
  PUBLIC
    "-Wl,--no-undefined"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pyds_common")

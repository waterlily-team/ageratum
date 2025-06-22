################################################################################
## The configuration files for the Waterlily assets project. This requires CMake 
## version 3.10 or higher.
##
## Copyright (c) 2025 - the Waterlily Team
## This source code is under the GPLv3. For information on what that entails,
## please see <https://www.gnu.org/licenses/gpl-3.0.txt>.
################################################################################

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project("WLAssets" LANGUAGES C VERSION 0.0.0.8)

include(Helpers)
run_checks(ON)
create_target(OFF RAW_SOURCES "WLAssets")

add_dependencies(${PROJECT_NAME} WLLogging)
target_include_directories(${PROJECT_NAME} PRIVATE "$<TARGET_PROPERTY:WLLogging,INTERFACE_INCLUDE_DIRECTORIES>")

cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.general)

# 依存するライブラリ
set(DEPENDS_LIB)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} BitReference.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} FractionalDec.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} InvalidOperationException.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} NullReferenceException.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} QuantumBit.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Rotation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} TristateBoolean.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Vector2d.cpp)

# ビルド
add_library(${AssemblyName} SHARED ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/General)

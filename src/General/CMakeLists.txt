cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.general)

# 依存するライブラリ
set(DEPENDS_LIB)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} Rotation.cpp)

# ビルド
add_library(${AssemblyName} SHARED ${BUILD_SOURCES})
target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/Graphics)

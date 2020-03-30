cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.test.graphics)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.graphics-core)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.graphics-dib)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} core.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} graphics-test.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} dib.cpp)

# ビルドおよびリンク
add_executable(${AssemblyName} ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})

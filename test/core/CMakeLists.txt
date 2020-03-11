cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.test.core)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.core)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} fractionaldec.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} property.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} range.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} rotation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} test-general.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} vector2d.cpp)

# ビルドおよびリンク
add_executable(${AssemblyName} ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})

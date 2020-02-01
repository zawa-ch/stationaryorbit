cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.test.analysis)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.core)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.analysis)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} compensatedfloat.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} differencial.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} newtoncoef.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} polynomialfunction.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} taylorseries.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} test-analysis.cpp)

# ビルドおよびリンク
add_executable(${AssemblyName} ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})

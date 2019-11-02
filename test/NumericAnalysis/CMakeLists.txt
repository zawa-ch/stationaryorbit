cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName numericanalysis-test)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.general)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.numericanalysis)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} CompensatedFloat.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} PolynomialFunction.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} test-numericanalysis.cpp)

# ビルドおよびリンク
add_executable(${AssemblyName} ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})

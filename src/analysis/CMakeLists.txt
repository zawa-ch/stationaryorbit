cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.numericanalysis)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.general)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} CompensatedFloat.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Differencial.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} MidpointIntegral.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} NewtonCoef.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} PolynomialFunction.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} SimpsonIntegral.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} TaylorSeries.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} TrapeziumIntegral.cpp)

# ビルド
add_library(${AssemblyName} SHARED ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})
target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/NumericAnalysis)

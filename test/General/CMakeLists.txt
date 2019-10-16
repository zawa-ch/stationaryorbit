cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.general)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} test-general.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Byte.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Rotation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Vector2d.cpp)

# ビルドおよびリンク
add_executable(general-test ${BUILD_SOURCES})
target_link_libraries(general-test ${DEPENDS_LIB})

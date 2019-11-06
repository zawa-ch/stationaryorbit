cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

#アセンブリ名
set(AssemblyName stationaryorbit.graphics)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.general)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} Bitmap.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BitmapBuffer.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BitmapByteBuffer.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BitmapFrame.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Color.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Graphics.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} ImageInfomation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Point.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} PointF.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} Rectangle.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} RectangleF.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} RGBColor.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/BMPImage.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/BMPImageBitmap.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/BMPImageInfomation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/CoreHeader.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/FileHeader.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/InfoHeader.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/InvalidFormatException.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} BMP/RGB24BMP.cpp)

# ビルド
add_library(${AssemblyName} SHARED ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})
target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/Graphics)

cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE string "clang++ compiler" FORCE)

# インクルードディレクトリ
include_directories(include)

# ライブラリ本体のビルド用ソース
add_subdirectory(src)

# ライブラリテスト用ソース
add_subdirectory(test)

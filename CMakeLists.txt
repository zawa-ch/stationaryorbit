cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

# ライブラリ本体のビルド用ソース
add_subdirectory(src)

# ライブラリテスト用ソース
add_subdirectory(test)

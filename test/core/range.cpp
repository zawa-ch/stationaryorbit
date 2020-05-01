#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core.numeral.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Range()
{
	// 範囲forを用いて0..9の数値を列挙する
	for(auto i : Range(0, 10))
	{
		std::cout << i << std::endl;
	}
	// 逆イテレータを使用して5..11の数値を逆に列挙する
	auto range = Range(5, 12);
	auto rit = range.rbegin();
	do
	{
		auto i = *rit;
		std::cout << i << std::endl;
	} while((++rit)!=range.rend());
	// 0.5fが0.0f以上1.0f未満であることを検査する
	auto frange = Range(0.0f, 1.0f);
	if (frange.isIncluded(0.5f))
	{
		std::cout << "0.0 <= " << 0.5f << " < 1.0f" << std::endl;
	}
	else
	{
		throw std::exception();
	}
}

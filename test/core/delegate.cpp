//	stationaryorbit.test.core:/delegate
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>
#include "stationaryorbit/core.delegate.hpp"
#include "stationaryorbit/core.event.hpp"
using namespace zawa_ch::StationaryOrbit;

class Default_EventArgs : EventArgs {};

class Has_Event
{
public:
	typedef Delegate<const Has_Event&, Default_EventArgs&> Default_EventHandler;
	Default_EventHandler Default_Event;
	void InvokeEvent() const
	{
		auto args = Default_EventArgs();
		Default_Event.Invoke(*this, args);
	}
};

void Test_Delegate()
{
	std::cout << "<--- Delegate/Event --->" << std::endl;
	// Delegate型を使用したイベントを持つ型を用意する
	auto inst = Has_Event();
	bool handled = false;
	// イベントハンドラでhandledをtrueにする
	inst.Default_Event += [&](const auto& sender, Default_EventArgs& args)
	{
		std::cout << "Event handled." << std::endl;
		handled = true;
	};
	inst.InvokeEvent();
	// Default_Eventに登録されたイベントは
	// DelegateをInvokeしたスレッド(ここではメインスレッド)で実行されるため
	// ハンドラを正しく呼び出せている場合はこの段階で必ずhandled==trueになる
	if (!handled) { throw std::exception(); }
}

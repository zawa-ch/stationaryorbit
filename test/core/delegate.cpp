#include <iostream>
#include "stationaryorbit/core.delegate.hpp"
using namespace zawa_ch::StationaryOrbit;

class Default_EventArgs {};

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
	std::cout << "<--- Delegate --->" << std::endl;
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

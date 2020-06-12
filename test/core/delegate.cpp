#include <iostream>
#include "stationaryorbit/core.delegate.hpp"
using namespace zawa_ch::StationaryOrbit;

class Default_EventArgs {};

class Has_Event
{
public:
	typedef  Delegate<const Has_Event&, const Default_EventArgs&> Default_EventHandler;

	Default_EventHandler Default_Event;

	void InvokeEvent() const { Default_Event.Invoke(*this, Default_EventArgs()); }
};

void Test_Delegate()
{
	std::cout << "<--- Delegate --->" << std::endl;
	auto inst = Has_Event();
	inst.Default_Event += [](const auto& sender, const Default_EventArgs& args)
	{
		std::cout << "Event handled." << std::endl;
	};
	inst.InvokeEvent();
}

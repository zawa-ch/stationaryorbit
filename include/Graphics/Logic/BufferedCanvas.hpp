#ifndef __StationaryOrbit_Graphics_BufferedCanvas__
#define __StationaryOrbit_Graphics_BufferedCanvas__
#include "../Logic/Canvas.hpp"
#include "../Logic/CanvasBuffer.hpp"
namespace StationaryOrbit::Graphics
{

	class BufferedCanvas : public Canvas
	{
	private:

		CanvasBuffer buffer;
	
	public:

		BufferedCanvas() : Canvas(buffer) {}
	};

}
#endif // __StationaryOrbit_Graphics_BufferedCanvas__
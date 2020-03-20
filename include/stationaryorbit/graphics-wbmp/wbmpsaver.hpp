#ifndef __stationaryorbit_graphics_wbmp_wbmpsaver__
#define __stationaryorbit_graphics_wbmp_wbmpsaver__
#include <ostream>
#include "fileheader.hpp"
#include "wbmpheaders.hpp"
#include "wbmpbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{
	class WbmpSaverBase
	{
	public:
		virtual uint32_t& HorizonalResolution() noexcept = 0;
		virtual const uint32_t& HorizonalResolution() const noexcept = 0;
		virtual uint32_t& VerticalResolution() noexcept = 0;
		virtual const uint32_t& VerticalResolution() const noexcept = 0;
		virtual void WriteTo(std::ostream& stream) const = 0;
	public:
		static void WriteFileHeader(std::ostream& stream, const FileHeader& data);
		static void WriteCoreHeader(std::ostream& stream, const CoreHeader& data);
		static void WriteInfoHeader(std::ostream& stream, const InfoHeader& data);
		static void WriteV4Header(std::ostream& stream, const V4Header& data);
		static void WriteV5Header(std::ostream& stream, const V5Header& data);
	};
	class WbmpRGBSaver
		: virtual public WbmpSaverBase
	{
	private:
		const WbmpBufferBase& _data;
		uint32_t _resx;
		uint32_t _resy;
	public:
		WbmpRGBSaver(const WbmpBufferBase& data) noexcept;
	public:
		uint32_t& HorizonalResolution() noexcept;
		const uint32_t& HorizonalResolution() const noexcept;
		uint32_t& VerticalResolution() noexcept;
		const uint32_t& VerticalResolution() const noexcept;
		void WriteTo(std::ostream& stream) const;
	private:
		static uint32_t CreatePxData(const WbmpBufferBase& data, const size_t& x, const size_t& y);
		static void WriteLine(std::ostream& stream, const WbmpBufferBase& data, const size_t& y);
	};
}
#endif // __stationaryorbit_graphics_wbmp_wbmpsaver__
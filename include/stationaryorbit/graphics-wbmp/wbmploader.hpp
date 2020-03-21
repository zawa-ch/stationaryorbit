#ifndef __stationaryorbit_graphics_wbmp_wbmploader__
#define __stationaryorbit_graphics_wbmp_wbmploader__
#include "stationaryorbit/exception/soexcept"
#include <array>
#include <vector>
#include <memory>
#include <istream>
#include "fileheader.hpp"
#include "wbmpheaders.hpp"
#include "wbmpbuffer.hpp"
#include "invalidwbmpformatexception.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{
	class WbmpLoaderBase
	{
	public: // interface
		virtual uint32_t HorizonalResolution() const noexcept = 0;
		virtual uint32_t VerticalResolution() const noexcept = 0;
	protected: // internal
		static FileHeader ReadFileHead(std::istream& stream);
		static uint32_t ReadHeaderSize(std::istream& stream);
		static CoreHeader ReadCoreHeader(std::istream& stream);
		static InfoHeader ReadInfoHeader(std::istream& stream);
		static V4Header ReadV4Header(std::istream& stream);
		static V5Header ReadV5Header(std::istream& stream);
	};
	class WbmpLoader
		: virtual public WbmpLoaderBase
	{
	private: // contains
		std::unique_ptr<WbmpBufferBase> _buffer;
		uint32_t _resx;
		uint32_t _resy;
	public: // constructor
		WbmpLoader() = default;
		WbmpLoader(std::istream& stream);
	public: // member
		const WbmpBufferBase& Buffer() const;
	public: // implement WbmpLoaderBase
		uint32_t HorizonalResolution() const noexcept;
		uint32_t VerticalResolution() const noexcept;
	private: // internal
		void ReadBody(std::istream& stream, const FileHeader& filehead, const CoreHeader& header);
		void ReadBody(std::istream& stream, const FileHeader& filehead, const InfoHeader& header);
		void ReadBody(std::istream& stream, const FileHeader& filehead, const V4Header& header);
		void ReadBody(std::istream& stream, const FileHeader& filehead, const V5Header& header);
		std::unique_ptr<WbmpRGBBuffer> ReadRGB(std::istream& stream, const size_t &width, const size_t &height, const zawa_ch::StationaryOrbit::Graphics::WBMP::BitDepth &depth);
	};
}
#endif // __stationaryorbit_graphics_wbmp_wbmploader__
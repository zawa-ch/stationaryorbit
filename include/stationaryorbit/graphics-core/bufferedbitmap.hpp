#ifndef __stationaryorbit_graphics_core_bufferedbitmap__
#define __stationaryorbit_graphics_core_bufferedbitmap__
#include "bitmapbuffer.hpp"
#include "bufferbindbitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T>
	class BufferedBitmap
		: virtual public BufferBindBitmapBase<T>
	{
	public: // type
		typedef BitmapBuffer<T> BufferType;
		typedef ChannelValue<T> ChannelValueType;
	private: // contains
		BufferType _buffer;
	public: // constructor
		BufferedBitmap() = default;
		BufferedBitmap(const BufferType& buffer) : _buffer(buffer) {}
		explicit BufferedBitmap(const BufferBindBitmap<T>& bitmap) : _buffer(bitmap.Buffer()) {}
		template<class fromT>
		explicit BufferedBitmap(const BufferedBitmap<fromT>& bitmap) : _buffer(bitmap.Buffer()) {}
		template<class fromT>
		explicit BufferedBitmap(const BufferBindBitmapBase<fromT>& bitmap) : _buffer(bitmap.Buffer()) {}
		virtual ~BufferedBitmap() = default;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		BufferType& Buffer() noexcept { return _buffer; }
		///	オブジェクトに紐付けられているバッファを取得します。
		const BufferType& Buffer() const noexcept { return _buffer; }
	};

}
#endif // __stationaryorbit_graphics_core_bufferedbitmap__
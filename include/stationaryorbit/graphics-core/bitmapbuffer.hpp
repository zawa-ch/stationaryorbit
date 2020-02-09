#ifndef __StationaryOrbit_Graphics_BitmapBuffer__
#define __StationaryOrbit_Graphics_BitmapBuffer__
#include <cstddef>
#include <memory>
#include "point.hpp"
#include "imageinfomation.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	画像情報を保持するための記憶領域を提供し、アクセスを行うためのメソッドを実装します。
    class IBitmapBuffer
    {
    public:
		
		///	このバッファの画像サイズを取得します。
		virtual Point getSize() const = 0;

		///	このバッファのチャネル数を取得します。
		virtual size_t getChannel() const = 0;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual float getPixel(const Point& pos, size_t ch) const = 0;

		///	指定された1ピクセル・1チャネルにおける値を設定します。
		virtual void setPixel(const Point& pos, size_t ch, const float& value) = 0;

    };

	///	画像情報を各チャネル8ビット整数で保持するためのメモリ空間を提供します。
	class BitmapBuffer
		: public IBitmapBuffer
	{
	private:

		Point _size;
		size_t _ch;
		float* _data;

		///	オブジェクトが使用するオブジェクト数を算出します。
		///	params:
		///	size	Bitmapの画像サイズ。
		///	ch	Bitmapの色チャネル数。
		///	returns:
		///	算出されたオブジェクト数が返ります。
		static size_t CalcLength(const Point& size, const size_t& ch);

		///	このオブジェクトのための記憶域空間を確保します。
		///	params:
		///	size	Bitmapの画像サイズ。
		///	ch	Bitmapの色チャネル数。
		///	returns:
		///	確保された記憶域への参照が返ります。
		///	exception:
		///	std::bad_alloc	メモリの確保に失敗しました。
		///	attribute:
		///	nodiscard	取得したリソースへの参照を返すため、返り値を破棄するとメモリリークが発生する可能性があります。
		[[nodiscard]]
		static float* Allocate(const Point& size, const size_t& ch);

		///	確保していた記憶域空間を開放します。
		void Deallocate() noexcept;

	public:

		BitmapBuffer() = default;

		BitmapBuffer(const Point& size, const size_t& ch);

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	params:
		///	info	キャンバスの生成時に用いるキャンバス情報。
		///	exception:
		///	std::out_of_range	infoで指定している画像サイズが負の値です。
		///	std::bad_alloc	メモリの確保に失敗しました。
		explicit BitmapBuffer(const IImageInfomation& info);

		///	指定されたキャンバスの内容を複製します。
		///	<コピーコンストラクタの特殊化>
		///	exception:
		///	std::bad_alloc	メモリの確保に失敗しました。
		BitmapBuffer(const BitmapBuffer& value);

		///	指定されたキャンバスの内容を複製します。
		///	exception:
		///	std::bad_alloc	メモリの確保に失敗しました。
		explicit BitmapBuffer(const IBitmapBuffer& value);

		///	キャンバスの内容をすべて破棄し、使用しているメモリを開放します。
		///	<デストラクタの特殊化>
		virtual ~BitmapBuffer();
		
		///	このバッファの画像サイズを取得します。
		Point getSize() const { return _size; }

		///	このバッファのチャネル数を取得します。
		size_t getChannel() const { return _ch; }

		float* getData() { return _data; }

		///	このオブジェクトが実体をアロケートできているかを取得します。
		bool IsAllocated() const;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		float getPixel(const Point& pos, size_t ch) const;

		///	指定された1ピクセル・1チャネルにおける値を設定します。
		void setPixel(const Point& pos, size_t ch, const float& value);

		///	キャンバスを複製します。
		///	<コピー代入の特殊化>
		BitmapBuffer& operator=(const BitmapBuffer& value);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapBuffer__
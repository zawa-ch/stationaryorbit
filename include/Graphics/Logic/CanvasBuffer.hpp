#ifndef __StationaryOrbit_Graphics_CanvasBuffer__
#define __StationaryOrbit_Graphics_CanvasBuffer__
#include <cstddef>
#include <memory>
#include "General/General"
#include "../Interface/ICanvasBuffer.hpp"
#include "../Logic/ImageInfomation.hpp"
namespace StationaryOrbit::Graphics
{

	class CanvasBuffer : public ICanvasBuffer
	{
	private:

		std::byte* _data;
		ImageInfomation _info;

		static size_t CalcLength(const ImageInfomation& info);
		static std::byte* Allocate(const ImageInfomation& info);
		static void Deallocate(std::byte* location);
		static void Copy(std::byte* dest, std::byte* src, ImageInfomation& info);

	public:

		CanvasBuffer();

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	params:
		///	info	キャンバスの生成時に用いるキャンバス情報。
		///	exception:
		///	std::out_of_range	infoで指定している画像サイズが負の値です。
		///	std::bad_alloc	メモリの確保に失敗しました。
		CanvasBuffer(const ImageInfomation& info);

		///	指定されたキャンバスの内容を複製します。
		///	<コピーコンストラクタの特殊化>
		///	exception:
		///	std::bad_alloc	メモリの確保に失敗しました。
		CanvasBuffer(const CanvasBuffer& value);

		///	キャンバスの内容をすべて破棄し、使用しているメモリを開放します。
		///	<デストラクタの特殊化>
		virtual ~CanvasBuffer();

		///	このオブジェクトが実体をアロケートできているかを取得します。
		bool IsAllocated() const;

		ImageInfomation getInfomation() const;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		///	取得された値は dest に書き込まれます。
		///	書き込まれるサイズはこのオブジェクトを初期化する際に指定したフォーマットに依存します。
		void getPixel(void* dest, const Point& pos, size_t ch) const;

		///	指定された1ピクセル・1チャネルにおける値を設定します。
		///	読み込まれるサイズはこのオブジェクトを初期化する際に指定したフォーマットに依存します。
		void setPixel(const void* value, const Point& pos, size_t ch);

		///	キャンバスを複製します。
		///	<コピー代入の特殊化>
		CanvasBuffer& operator=(const CanvasBuffer& value);

	};

}
#endif // __StationaryOrbit_Graphics_CanvasBuffer__
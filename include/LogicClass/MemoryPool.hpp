#include <cstdint>
#include <new>
#ifndef __MEMORYPOOL_HPP__
#define __MEMORYPOOL_HPP__
namespace StationaryOrbit
{

	///	伸縮可能なメモリの動的な確保および開放の管理を行います。
	class MemoryPool
	{
	private:

		uint8_t* _data;
		size_t _length;

	public:

		///	空のオブジェクトを初期化します。
		MemoryPool();

		///	新しいオブジェクトを初期化し、内容を複製します。
		///	<コピーコンストラクタの特殊化>
		MemoryPool(const MemoryPool& value);

		///	指定された大きさでメモリを確保し、新しいオブジェクトを初期化します。
		MemoryPool(size_t size);

		///	確保したメモリをすべて開放し、このオブジェクトを破棄します。
		///	<デストラクタの特殊化>
		~MemoryPool();

	private:

		static void* Allocate(size_t size);

		static void Deallocate(void* location);

	public:

		///	メモリを指定された大きさで再確保します。
		///	拡張された部分は0x00で初期化され、収縮された部分は削除されます。
		void Reallocate(size_t size);

		///	メモリを指定された大きさになるまで拡張します。
		///	拡張された部分は0x00で初期化されます。
		///	既に指定されているものより大きなメモリが確保されている場合は何もしません。
		void Expand(size_t size);

		///	メモリを指定された大きさになるまで収縮します。
		///	確保された部分の最後から収縮を行い、収縮された部分は削除されます。
		///	既に指定されているものより確保されているメモリが小さい場合は何もしません。
		void Shrink(size_t size);

		///	オブジェクトの内容を複製し、代入します。
		///	<コピー代入の特殊化>
		MemoryPool& operator=(const MemoryPool& value);

	};

}
#endif // __MEMORYPOOL_HPP__
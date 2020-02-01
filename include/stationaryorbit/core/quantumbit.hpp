#ifndef __StationaryOrbit_QuantumBit__
#define __StationaryOrbit_QuantumBit__
#include <random>
#include "../Structure/Rotation.hpp"
#include "../Structure/TristateBoolean.hpp"
#include "../Logic/InvalidOperationException.hpp"
namespace StationaryOrbit
{

	struct QuantumBit final
	{
	private:

		TristateBoolean val;
		Rotation rot;

		QuantumBit(const QuantumBit&) = delete;	// [削除]コピーコンストラクタ
		QuantumBit operator=(const QuantumBit&) = delete;	// [削除]コピー代入

	public:

		QuantumBit();

		QuantumBit(const Rotation& rotation);

		///	このオブジェクトがtrueまたはfalseのどちらであるかを観測します。
		QuantumBit& Observe();

		///	このオブジェクトが観測済みである、trueまたはfalseのいずれかに収束しているかどうかを取得します。
		bool IsObserved() const;

		///	このオブジェクトの内容をTristateBooleanで取得します。
		TristateBoolean getValue() const { return val; }

		///	このオブジェクトが観測済みである場合、その値をboolで取得します。
		bool getBool() const;

		QuantumBit operator~() const;

		QuantumBit operator|(QuantumBit& value) const;

		QuantumBit operator&(QuantumBit& value) const;

		QuantumBit operator^(QuantumBit& value) const;

	};

}
#endif // __StationaryOrbit_QuantumBit__
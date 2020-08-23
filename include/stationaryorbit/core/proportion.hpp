#ifndef __stationaryorbit_core_proportion__
#define __stationaryorbit_core_proportion__
#include <cstdint>
#include <type_traits>
#include <ratio>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	0.0から1.0の値を整数または浮動小数点数を用いて保持します。
	///	@param	T
	///	値の格納に用いる型。
	///	@note
	///	@a Proportion 型は0.0以上1.0以下の数値をテンプレート型 @a T に格納できるようにします。
	template <class T>
	struct Proportion
	{
		static_assert((std::is_floating_point_v<T>)||(std::is_unsigned_v<T>), "テンプレート型 T は符号なし算術型または浮動小数点数型のいずれかである必要があります。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef T ValueType;
	private:
		ValueType _value;
		constexpr explicit Proportion(const ValueType& init) : _value(init) {}
	public:
		constexpr Proportion() : _value() {}
		constexpr explicit Proportion(const float& value) : Proportion(Proportion<float>(value)) {}
		constexpr explicit Proportion(const double& value) : Proportion(Proportion<double>(value)) {}
		template<class fromT>
		constexpr explicit Proportion(const Proportion<fromT>& from) : Proportion(from.template ConvertTo<T>()) {}
		constexpr Proportion(const Proportion<T>&) = default;
		constexpr Proportion(Proportion<T>&&) = default;
		~Proportion() = default;
	public:
		///	このオブジェクトが正規化されているかどうかを取得します。
		///	@note
		///	@a T が符号なし算術型の場合、常に @a true か返ります。
		constexpr bool IsNormalized() const { return (Min()._value < _value)&&(_value < Max()._value); }
		constexpr Proportion<T> Normalize() const { return Proportion((Min()._value <= _value)?((_value <= Max()._value)?(_value):(Max()._value)):(Min()._value)); }
		constexpr Proportion<T> Abs() const { return this->operator+(); }
		constexpr Proportion<T> Negative() const { return this->operator-(); }
	public:
		///	この型で表すことのできる最大の値を取得します。
		///	@note
		///
		constexpr static Proportion<T> Max()
		{
			static_assert((std::is_floating_point_v<T>)||(std::is_unsigned_v<T>), "テンプレートの特殊化に失敗しました(テンプレート型 T は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<T>) { return Proportion(ValueType(1.0)); }
			if constexpr (std::is_unsigned_v<T>) { return Proportion(std::numeric_limits<T>::max()); }
		}
		///	この型で表すことのできる最小の値を取得します。
		constexpr static Proportion<T> Min()
		{
			static_assert((std::is_floating_point_v<T>)||(std::is_unsigned_v<T>), "テンプレートの特殊化に失敗しました(テンプレート型 T は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<T>) { return Proportion(ValueType(0.0)); }
			if constexpr (std::is_unsigned_v<T>) { return Proportion(0); }
		}
		///	この型で表すことのできる零値を取得します。
		constexpr static Proportion<T> Zero()
		{
			static_assert((std::is_floating_point_v<T>)||(std::is_signed_v<T>), "テンプレートの特殊化に失敗しました(テンプレート型 T は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<T>) { return Proportion(ValueType(0.0)); }
			if constexpr (std::is_signed_v<T>) { return Proportion(0); }
		}
	public:
		constexpr Proportion<T> operator+() const { return Proportion(+_value); }
		constexpr Proportion<T> operator-() const { return Proportion(-_value); }
		constexpr Proportion<T> operator+(const Proportion<T>& other) const { return Proportion(_value + other._value); }
		constexpr Proportion<T> operator-(const Proportion<T>& other) const { return Proportion(_value - other._value); }
		//	TODO: 整数が与えられている場合の乗算・除算の特殊化
		constexpr Proportion<T> operator*(const Proportion<T>& other) const { return Proportion(_value * other._value); }
		constexpr Proportion<T> operator/(const Proportion<T>& other) const { return Proportion(_value / other._value); }
		constexpr Proportion<T>& operator+=(const Proportion<T>& other) const { return *this = Proportion(_value + other._value); }
		constexpr Proportion<T>& operator-=(const Proportion<T>& other) const { return *this = Proportion(_value - other._value); }
		constexpr Proportion<T>& operator*=(const Proportion<T>& other) const { return *this = Proportion(_value * other._value); }
		constexpr Proportion<T>& operator/=(const Proportion<T>& other) const { return *this = Proportion(_value / other._value); }
	public:
		constexpr bool Equals(const Proportion<T>& other) const { return _value == other._value; }
		constexpr bool operator==(const Proportion<T>& other) const { return Equals(other); }
		constexpr bool operator!=(const Proportion<T>& other) const { return !Equals(other); }
	public:
		constexpr int Compare(const Proportion<T>& other) const
		{
			if (_value > other._value) { return 1; }
			else if (_value < other._value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const Proportion<T>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const Proportion<T>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const Proportion<T>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const Proportion<T>& other) const { return Compare(other) >= 0; }
	public: // convert
		constexpr explicit operator ValueType() const { return _value; }
		///	内部に使用する型のキャストを行います。
		///	@param	castT
		///	変換先の型。返ってくる値の型は @a Proportion<castT> となります。
		template<class castT>
		constexpr Proportion<castT> ConvertTo() const
		{
			static_assert((std::is_floating_point_v<T>)||(std::is_unsigned_v<T>), "テンプレートの特殊化に失敗しました(テンプレート型 T は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			static_assert((std::is_floating_point_v<castT>)||(std::is_unsigned_v<castT>), "テンプレートの特殊化に失敗しました(テンプレート型 castT は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<T>)
			{
				if ((_value == std::numeric_limits<T>::quiet_NaN()) || (_value == std::numeric_limits<T>::signaling_NaN()))
				{ throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
				// float -> float
				if constexpr (std::is_floating_point_v<castT>) { return Proportion<castT>(castT(_value)); }
				// float -> integer
				if constexpr (std::is_unsigned_v<castT>)
				{
					if ((_value < 0.0) || (1.0 < _value)) { throw std::invalid_argument("指定する値は0.0以上1.0以下である必要があります。"); }
					return Proportion<castT>(castT(_value * Proportion<castT>::Max()._value));
				}
			}
			if constexpr (std::is_unsigned_v<T>)
			{
				// integer -> float
				if constexpr (std::is_floating_point_v<castT>) { return Proportion<castT>(castT(_value) / Max()._value); }
				// integer -> integer
				if constexpr (std::is_unsigned_v<castT>)
				{
					if constexpr (sizeof(T) < sizeof(castT)) { return Proportion<castT>(castT(_value) * (Proportion<castT>::Max()._value / Max()._value)); }
					else { return Proportion<castT>(castT(_value / (Max()._value / Proportion<castT>::Max()._value))); }
				}
			}
		}
	public:
		Proportion<T>& operator=(const Proportion<T>& value) = default;
		Proportion<T>& operator=(Proportion<T>&& value) = default;
	};
}
#endif // __stationaryorbit_core_proportion__

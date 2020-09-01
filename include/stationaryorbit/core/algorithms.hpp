#ifndef __stationaryorbit__core_algorithms__
#define __stationaryorbit__core_algorithms__
namespace zawa_ch::StationaryOrbit
{
	///	ライブラリで使用される基本的なアルゴリズムを実装します。
	///	このクラスは継承できません。
	class Algorithms final
	{
	public:
		///	整数の除算と乗算を行います。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@param	scale
		///	乗算時の乗数。
		///	@exception
		///	std::invalid_argument
		///	0で除算することはできません。
		template<class Tp>
		static constexpr Tp IntegralFraction(const Tp& numerator, const Tp& denominator, const Tp& scale)
		{
			static_assert(std::is_unsigned_v<Tp>, "テンプレート型 Tp は符号なし算術型である必要があります。");
			if constexpr (std::is_same_v<Tp, bool>)
			{
				if (denominator == false) { throw std::invalid_argument("分母に0を指定することはできません。"); }
				return numerator;
			}
			if constexpr ((std::is_integral_v<Tp>)&&(std::is_unsigned_v<Tp>))
			{
				if (denominator == 0U) { throw std::invalid_argument("分母に0を指定することはできません。"); }
				Tp unit = scale / denominator;
				Tp result = unit * numerator;
				Tp surplus = scale % denominator;
				if (surplus != 0U)
				{
					Tp dv = 0U;
					Tp md = 0U;
					for(size_t i = (sizeof(Tp) * 8U); 0 < i; i--)
					{
						dv *= 2U;
						md *= 2U;
						if (numerator & (Tp(1U) << (i - 1)))
						{
							md += surplus;
						}
						dv += md / denominator;
						md %= denominator;
					}
					result += dv;
				}
				return result;
			}
		}
	};
}
#endif // __stationaryorbit__core_algorithms__
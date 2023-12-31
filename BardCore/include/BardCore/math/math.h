#ifndef BARDCORE_MATH_H
#define BARDCORE_MATH_H

#include "BardCore/bardcore.h"

namespace bardcore
{
    class math
    {
    private:
        /**
         * \brief helper function for calculating the square root via Newton-Raphson 
         * \note credit: Alex Shtoff - https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
         * \param value value to calculate the square root from
         * \param curr current value
         * \param prev previous value
         * \return square root of value
         */
        NODISCARD constexpr static double helper_sqrt_newton_raphson(
            const double value, const double curr,
            const double prev)
        {
            return curr == prev
                       ? curr
                       : helper_sqrt_newton_raphson(value, 0.5 * (curr + value / curr), curr);
        }

    public:
        /**
         * \brief epsilon value for double comparison
         */
        INLINE static constexpr double epsilon = 0.00001;

        /**
         * \brief 180 / pi constant, used for converting radians to degrees
         */
        INLINE static constexpr double _180_div_pi = 57.295779513082323;

        /**
         * \brief pi / 180 constant, used for converting degrees to radians
         */
        INLINE static constexpr double pi_div_180 = 0.017453292519943295;

        /**
         * \brief 2 * pi constant
         */
        INLINE static constexpr double _2pi = 6.28318530717958647692;

        /**
         * \brief pi constant
         */
        INLINE static constexpr double pi = 3.14159265358979323846;

        /**
         * \brief pi / 2 constant
         */
        INLINE static constexpr double pi_2 = 1.57079632679489661923;

        /**
         * \brief pi / 4 constant
         */
        INLINE static constexpr double pi_4 = 0.785398163397448309616;

        /**
         * \brief pi / 4 constant
         */
        INLINE static constexpr double inf = std::numeric_limits<double>::infinity();

        /**
         * \brief calculates the degrees from radians
         * \param radians radians
         * \return degrees
         */
        NODISCARD constexpr static double radians_to_degrees(const double radians) noexcept
        {
            return radians * math::_180_div_pi;
        }

        /**
         * \brief calculates the radians from degrees
         * \param degrees degrees
         * \return radians
         */
        NODISCARD constexpr static double degrees_to_radians(const double degrees) noexcept
        {
            return degrees * math::pi_div_180;
        }

    public:
        /**
         * \brief calculates sqrt at compile time if possible, otherwise it uses std::sqrt
         * \note calculates the square root via Newton-Raphson, during compile time
         * \note sqrt(0) = 0, e.g : 0^(1/2) = 0
         * \param value value to calculate the square root from
         * \throws negative_exception if value is negative
         * \return square root of value
         */
        NODISCARD constexpr static double sqrt(const double value)
        {
            if (value < 0)
                throw exception::negative_exception("value can not be negative");

            if (!std::_Is_constant_evaluated())
                return std::sqrt(value);

            // use std at runtime
            // use constexpr at compile time
            return helper_sqrt_newton_raphson(value, value, 0);
        }

        /**
         * \brief calculates the factorial of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Factorial
         * \param value value to calculate the factorial from
         * \return factorial of value, e.g: value!
         */
        NODISCARD constexpr static double factorial(const unsigned int value) noexcept
        {
            if (value == 0)
                return 1;

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tgamma(static_cast<double>(value) + 1);

            return static_cast<double>(value) * factorial(value - 1);
        }

        /**
         * \brief calculates the power of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Exponentiation
         * \param base base, the value to calculate the power from
         * \param exponent exponent
         * \return double(base)^exponent
         */
        NODISCARD constexpr static double pow(const double base, const int exponent) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::pow(base, static_cast<double>(exponent));

            if (std::_Is_nan(base) || base == inf || base == -inf) // base is inf
                return NAN;

            if (exponent == 0 || equals(base, 1.)) // base is 1 or exponent is 0
                return 1;

            return exponent > 0
                       ? base * pow(base, exponent - 1)
                       : 1 / (base * pow(base, -exponent - 1));
        }

        /**
         * \brief calculates the cosine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/the-maclaurin-expansion-of-cosx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the cosine from in radians
         * \return cosine of value
         */
        NODISCARD constexpr static double cos(const double value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::cos(value);

            if (std::_Is_nan(value) || value == inf || value == -inf) // value is inf
                return NAN;

            return sin(value + pi_2);
        }

        /**
         * \brief calculates the sine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/maclaurin-expansion-of-sinx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the sine from in radians
         * \return sine of value
         */
        NODISCARD constexpr static double sin(double value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::sin(value);

            if (std::_Is_nan(value) || value == inf || value == -inf) // value is inf
                return NAN;

            value = mod(value, 2 * pi); // make value between 0 and 2pi

            double result = 0;
            for (int index = 0; index < 1'000; ++index) // 1 thousand iterations as hard limit
            {
                //formula: Σ (-1)^n * x^(2n) / (2n)!
                const double r = pow(-1, index) * pow(value, 2 * index + 1) / factorial(2 * index + 1);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or inf, stop calculating
                if (equals(r, 0) || (std::_Is_nan(r) || r == inf || r == -inf))
                    break;

                result += r;
            }

            return result;
        }

        /**
         * \brief calculates the tangent of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Trigonometric_functions
         * \note using the Maclaurin Expansion
         * \note compile time might be slightly inaccurate when close to the limit, e.g: somewhere close to pi
         * \param value value to calculate the tangent from in radians
         * \return tangent of value
         */
        NODISCARD constexpr static double tan(const double value) noexcept
        {
            if (std::_Is_nan(value) || value == inf || value == -inf) // value is inf
                return NAN;

            if (equals(mod(value, pi), 0)) // value is a multiple of pi
                return 0;

            if (!equals(value, 0) && equals(mod(value, pi_2), 0)) // value is a multiple of pi/2
                return NAN;

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tan(value);

            return sin(value) / cos(value);
        }

        /**
         * \brief calculates the mod of a number, with a divisor
         * \note read more at: https://en.wikipedia.org/wiki/Modulo_operation
         * \note reference: https://cplusplus.com/reference/cmath/fmod/
         * \note example: mod(5.3, 2) = 1.3
         * \throws zero_exception if divisor is zero
         * \param value number to calculate the modulo from
         * \param divisor divisor, can not be zero
         * \return 
         */
        NODISCARD constexpr static double mod(const double value, const double divisor)
        {
            if (equals(divisor, 0))
                throw exception::zero_exception("divisor can not be zero");

            if (!std::_Is_constant_evaluated()) // use std if runtime
            {
                const auto mod = std::fmod(value, divisor);
                return equals(abs(mod), abs(divisor))
                           ? 0
                           : mod;
            }

            if (equals(value, 0))
                return 0;

            const int multiplier = static_cast<int>(value / divisor + epsilon * sign(value / divisor)); // floor
            return value - static_cast<double>(multiplier) * divisor + DBL_EPSILON * sign(value);
        }

        /**
         * \brief calculates the sign value of a double value
         * \note read more at: https://en.wikipedia.org/wiki/Sign_(mathematics)
         * \param value double value
         * \return sign int value (-1, 0, 1), special case: 0
         */
        NODISCARD constexpr static int sign(const double value) noexcept
        {
            return equals(value, 0)
                       ? 0
                       : (less_than(value, 0)
                              ? -1
                              : 1);
        }

        /**
         * \brief calculates the absolute value of a double value
         * \note read more at: https://en.wikipedia.org/wiki/Absolute_value
         * \param value double value
         * \return absolute double value
         */
        NODISCARD constexpr static double abs(const double value) noexcept
        {
            return less_than(value, 0)
                       ? -value
                       : value;
        }

        /**
         * \brief checks if two double values are equal, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is inf or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a == b with epsilon
         */
        NODISCARD constexpr bool static equals(const double number1,
                                                const double number2) noexcept
        {
            return abs(number1 - number2) <= epsilon;
        }

        /**
         * \brief checks if left double value is greater than right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is inf or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a > b with epsilon
         */
        NODISCARD constexpr bool static greater_than(const double number1,
                                                      const double number2) noexcept
        {
            return number1 - number2 > epsilon;
        }

        /**
         * \brief checks if left double value is less than right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is inf or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a < b with epsilon
         */
        NODISCARD constexpr bool static less_than(const double number1,
                                                   const double number2) noexcept
        {
            return number2 - number1 > epsilon;
        }

        /**
         * \brief calculates the greatest common divisor of two numbers, using the euclidean algorithm
         * \note read more at: https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
         * \note this algorithm is not fast but it was fun to make, it's quite fast for small numbers
         * \throws negative_exception if a or b is negative
         * \throws negative_exception if a or b is negative
         * \param number1 number 1
         * \param number2 number 2
         * \return greatest common divisor of a and b
         */
        NODISCARD constexpr static unsigned int euclidean_gcd(const unsigned int number1, const unsigned int number2)
        {
            if (number1 == 0 || number2 == 0)
                throw exception::zero_exception("a and b must not be zero");
            if (number1 < number2)
                //TODO: make different exception
                throw exception::negative_exception("a must be greater than b");

            const unsigned int mod = number1 % number2;

            if (mod == 0) //stop condition
                return number2;

            return euclidean_gcd(number2, mod);
        }
    };
} // namespace bardcore
#endif //BARDCORE_MATH_H

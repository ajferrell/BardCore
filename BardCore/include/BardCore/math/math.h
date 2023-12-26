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
        NODISCARD constexpr static float sqrt_newton_raphson(const float value, const float curr, const float prev)
        {
            return curr == prev
                       ? curr
                       : sqrt_newton_raphson(value, 0.5f * (curr + value / curr), curr);
        }

    public:
        /**
         * \brief pi constant
         */
        INLINE static constexpr float pi = 3.14159265358979323846f;

        /**
         * \brief calculates the degrees from radians
         * \param radians radians
         * \return degrees
         */
        NODISCARD constexpr static float radians_to_degrees(const float radians)
        {
            return radians * 180.0f / math::pi;
        }

        /**
         * \brief calculates the radians from degrees
         * \param degrees degrees
         * \return radians
         */
        NODISCARD constexpr static float degrees_to_radians(const float degrees)
        {
            return degrees * math::pi / 180.0f;
        }

    public:        
        /**
         * \brief calculates the square root via Newton-Raphson
         * \note sqrt(0) = 0, e.g : 0^(1/2) = 0
         * \param value value to calculate the square root from
         * \throws negative_exception if value is negative
         * \return square root of value
         */
        NODISCARD constexpr static float sqrt(const float value)
        {
            if (value < 0)
                throw exception::negative_exception("value can not be negative");

            return sqrt_newton_raphson(value, value, 0);
        }

        /**
         * \brief calculates the greatest common divisor of two numbers, using the euclidean algorithm
         * \note this algorithm is not fast but it was fun to make, it's quite fast for small numbers
         * \throws negative_exception if a or b is negative
         * \throws negative_exception if a or b is negative
         * \param number1 number 1
         * \param number2 number 2
         * \return greatest common divisor of a and b
         */
        NODISCARD constexpr static int euclidean_gcd(const int number1, const int number2)
        {
            if (number1 <= 0 || number2 <= 0)
                throw exception::negative_exception("a and b must not be negative");
            if (number1 < number2)
                //TODO: make different exception
                throw exception::negative_exception("a must be greater than b");

            const auto mod = number1 % number2;

            if (mod == 0) //stop condition
                return number2;

            return euclidean_gcd(number2, mod);
        }
    };
} // namespace bardcore
#endif //BARDCORE_MATH_H

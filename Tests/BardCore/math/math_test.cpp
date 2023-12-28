#include "pch.h"
#include "BardCore/math/math.h"

namespace testing
{
    //test 90 degrees
    TEST(math_test, radians_to_degrees_test)
    {
        constexpr float degrees = math::radians_to_degrees(1.570f);

        ASSERT_NEAR(90.f, degrees, ROUND_ONE_DECIMALS);
    }

    //test zero
    TEST(math_test, radians_to_degrees_zero_test)
    {
        constexpr float radians = math::degrees_to_radians(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, radians_to_degrees_negative_test)
    {
        constexpr float degrees = math::radians_to_degrees(-1.570f);

        ASSERT_NEAR(-90.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, radians_to_degrees_450_test)
    {
        constexpr float degrees = math::radians_to_degrees(7.854f);

        ASSERT_NEAR(450.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 90 degrees
    TEST(math_test, degrees_to_radians_test)
    {
        constexpr float radians = math::degrees_to_radians(90.f);

        ASSERT_NEAR(1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test zero
    TEST(math_test, degrees_to_radians_zero_test)
    {
        constexpr float radians = math::degrees_to_radians(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, degrees_to_radians_negative_test)
    {
        constexpr float radians = math::degrees_to_radians(-90.f);

        ASSERT_NEAR(-1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, degrees_to_radians_450_test)
    {
        constexpr float radians = math::degrees_to_radians(450.f);

        ASSERT_NEAR(7.85f, radians, ROUND_TWO_DECIMALS);
    }

    //test sqrt constexpr
    TEST(math_test, sqrt_test)
    {
        constexpr float result = math::sqrt(100);
        constexpr float result2 = math::sqrt(52);
        constexpr float result3 = math::sqrt(10000000);

        ASSERT_NEAR(10, result, ROUND_ZERO);
        ASSERT_NEAR(7.21, result2, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(3162, result3, ROUND_ONE);
    }

    //test euclidean_gcd constexpr
    TEST(math_test, euclidean_gcd_test)
    {
        constexpr int result = math::euclidean_gcd(1071, 462);
        
        ASSERT_EQ(21, result);
    }

    //test euclidean_gcd exception
    TEST(math_test, euclidean_gcd_exception_test)
    {
        ASSERT_THROW(math::euclidean_gcd(-1, 1), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(1, -1), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(-1, -1), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(1, 0), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(0, 1), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(0, 0), exception::negative_exception);
        ASSERT_THROW(math::euclidean_gcd(1, 2), exception::negative_exception);
    }

    TEST(math_test, fequals_test)
    {
        constexpr float a = 1.0f;
        constexpr float b = 1.0f;
        constexpr float c = 1.001f;
        constexpr float d = 1.0001f;
        constexpr float e = 1.00001f;

        constexpr float a1 = 42'467'500'000;
        constexpr float b1 = 42'467'500'006;
        constexpr float c1 = 42'467'400'000;
        constexpr float d1 = 42'466'000'000;

        ASSERT_TRUE(math::fequals(a, b));
        ASSERT_FALSE(math::fequals(a, c));
        ASSERT_TRUE(math::fequals(a, d));
        ASSERT_TRUE(math::fequals(a, e));

        ASSERT_TRUE(math::fequals(a1, b1)); // true since float has 6 digits of precision
        ASSERT_FALSE(math::fequals(a1, c1));
        ASSERT_FALSE(math::fequals(a1, d1));
    }

    TEST(math_test, fgreater_than_test)
    {
        constexpr float a = 1.0f;
        constexpr float b = 1.0f;
        constexpr float c = 1.001f;
        constexpr float d = 1.0001f;
        constexpr float e = 1.00001f;

        constexpr float a1 = 0.5f;
        constexpr float b1 = 0.999f;
        constexpr float c1 = 0.9999f;
        constexpr float d1 = 0.99999f;

        ASSERT_FALSE(math::fgreater_than(a, b));
        ASSERT_FALSE(math::fgreater_than(a, c));
        ASSERT_FALSE(math::fgreater_than(a, d));
        ASSERT_FALSE(math::fgreater_than(a, e));

        ASSERT_TRUE(math::fgreater_than(a, a1));
        ASSERT_TRUE(math::fgreater_than(a, b1));
        ASSERT_FALSE(math::fgreater_than(a, c1));
        ASSERT_FALSE(math::fgreater_than(a, d1));
    }

    TEST( test_math, fless_than_test)
    {
        constexpr float a = 1.0f;
        constexpr float b = 1.0f;
        constexpr float c = 1.001f;
        constexpr float d = 1.0001f;
        constexpr float e = 1.00001f;

        constexpr float a1 = 0.5f;
        constexpr float b1 = 0.999f;
        constexpr float c1 = 0.9999f;
        constexpr float d1 = 0.99999f;

        ASSERT_FALSE(math::fless_than(a, b));
        ASSERT_TRUE(math::fless_than(a, c));
        ASSERT_FALSE(math::fless_than(a, d));
        ASSERT_FALSE(math::fless_than(a, e));

        ASSERT_FALSE(math::fless_than(a, a1));
        ASSERT_FALSE(math::fless_than(a, b1));
        ASSERT_FALSE(math::fless_than(a, c1));
        ASSERT_FALSE(math::fless_than(a, d1));
    }
} // namespace testing

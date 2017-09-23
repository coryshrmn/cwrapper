/*
   Copyright 2017 Cory Sherman

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "gtest/gtest.h"

#include "cwrapper/enum.hpp"

enum class TestBitsUInt : std::uint32_t
{
    NONE = 0,
    BIT0 = 1 << 0,
    BIT1 = 1 << 1,
    BIT2 = 1 << 2,
    BIT3 = 1 << 3,
    BIT4 = 1 << 4,
    BIT5 = 1 << 5,
    BIT6 = 1 << 6,
    BIT7 = 1 << 7,
    BIT8 = 1 << 8,
    BIT9 = 1 << 9,
    BIT10 = 1 << 10,
    BIT11 = 1 << 11,
    BIT12 = 1 << 12,
    BIT13 = 1 << 13,
    BIT14 = 1 << 14,
    BIT15 = 1 << 15,
    BIT16 = 1 << 16,
    BIT17 = 1 << 17,
    BIT18 = 1 << 18,
    BIT19 = 1 << 19,
    BIT20 = 1 << 20,
    BIT21 = 1 << 21,
    BIT22 = 1 << 22,
    BIT23 = 1 << 23,
    BIT24 = 1 << 24,
    BIT25 = 1 << 25,
    BIT26 = 1 << 26,
    BIT27 = 1 << 27,
    BIT28 = 1 << 28,
    BIT29 = 1 << 29,
    BIT30 = 1 << 30,
    ALL = 0xffffffff
};

enum class TestBitsUByte : std::uint8_t
{
    NONE = 0,
    BIT0 = 1 << 0,
    BIT1 = 1 << 1,
    BIT2 = 1 << 2,
    BIT3 = 1 << 3,
    BIT4 = 1 << 4,
    BIT5 = 1 << 5,
    BIT6 = 1 << 6,
    ALL = 0xff
};

namespace cwrapper
{
template <>
struct EnumTraits<TestBitsUInt>
{
    static constexpr bool isBitFlag = true;
};
template <>
struct EnumTraits<TestBitsUByte>
{
    static constexpr bool isBitFlag = true;
};
} // namespace cwrapper

TEST(CwrapperEnum, Or)
{
    EXPECT_EQ(TestBitsUInt::BIT0 | TestBitsUInt::BIT1, static_cast<TestBitsUInt>(3));
    EXPECT_EQ(TestBitsUInt::BIT0 | TestBitsUInt::BIT2, static_cast<TestBitsUInt>(5));
    EXPECT_EQ(TestBitsUInt::BIT0 | TestBitsUInt::BIT1 | TestBitsUInt::BIT2, static_cast<TestBitsUInt>(7));

    TestBitsUInt a = TestBitsUInt::BIT0;
    EXPECT_EQ(&(a |= TestBitsUInt::BIT1), &a);
    EXPECT_EQ(a, static_cast<TestBitsUInt>(3));
}

TEST(CwrapperEnum, And)
{
    EXPECT_EQ(TestBitsUInt::BIT0 & TestBitsUInt::BIT1, TestBitsUInt::NONE);
    EXPECT_EQ((TestBitsUInt::BIT0 | TestBitsUInt::BIT1) & TestBitsUInt::BIT1, TestBitsUInt::BIT1);
    EXPECT_EQ((TestBitsUInt::BIT0 | TestBitsUInt::BIT1 | TestBitsUInt::BIT2) & (TestBitsUInt::BIT1 | TestBitsUInt::BIT2) & TestBitsUInt::BIT1, TestBitsUInt::BIT1);
    EXPECT_EQ((TestBitsUInt::BIT0 | TestBitsUInt::BIT1 | TestBitsUInt::BIT2) & (TestBitsUInt::BIT1 | TestBitsUInt::BIT2) & TestBitsUInt::BIT0, TestBitsUInt::NONE);

    TestBitsUInt a = TestBitsUInt::ALL;
    EXPECT_EQ(&(a &= TestBitsUInt::BIT1), &a);
    EXPECT_EQ(a, TestBitsUInt::BIT1);
}

TEST(CwrapperEnum, Xor)
{
    EXPECT_EQ(TestBitsUInt::BIT0 ^ TestBitsUInt::BIT1, static_cast<TestBitsUInt>(3));
    EXPECT_EQ(TestBitsUInt::BIT0 ^ TestBitsUInt::BIT2, static_cast<TestBitsUInt>(5));
    EXPECT_EQ(TestBitsUInt::BIT0 ^ TestBitsUInt::BIT1 ^ TestBitsUInt::BIT2, static_cast<TestBitsUInt>(7));
    EXPECT_EQ(TestBitsUInt::BIT0 ^ (TestBitsUInt::BIT0 | TestBitsUInt::BIT1), TestBitsUInt::BIT1);

    TestBitsUInt a = TestBitsUInt::ALL;
    EXPECT_EQ(&(a ^= TestBitsUInt::BIT1), &a);
    EXPECT_EQ(a, static_cast<TestBitsUInt>(~2));
}

TEST(CwrapperEnum, Not)
{
    EXPECT_EQ(~TestBitsUInt::NONE, TestBitsUInt::ALL);
    EXPECT_EQ(~TestBitsUInt::ALL, TestBitsUInt::NONE);
    EXPECT_EQ(~TestBitsUInt::BIT0, static_cast<TestBitsUInt>(~1));
}

TEST(CwrapperEnum, LShift)
{
    EXPECT_EQ(TestBitsUInt::BIT0 << 1, TestBitsUInt::BIT1);
    EXPECT_EQ(TestBitsUInt::BIT1 << 1, TestBitsUInt::BIT2);
    EXPECT_EQ(TestBitsUInt::BIT1 << 5, TestBitsUInt::BIT6);
    EXPECT_EQ(TestBitsUInt::BIT25 << 10, TestBitsUInt::NONE);
    EXPECT_EQ((TestBitsUInt::BIT0 | TestBitsUInt::BIT2) << 3, TestBitsUInt::BIT3 | TestBitsUInt::BIT5);

    EXPECT_EQ(TestBitsUByte::BIT6 << 3, TestBitsUByte::NONE);

    TestBitsUInt a = TestBitsUInt::BIT0;
    EXPECT_EQ(&(a <<= 2), &a);
    EXPECT_EQ(a, TestBitsUInt::BIT2);
}

TEST(CwrapperEnum, RShift)
{
    EXPECT_EQ(TestBitsUInt::BIT2 >> 1, TestBitsUInt::BIT1);
    EXPECT_EQ(TestBitsUInt::BIT8 >> 3, TestBitsUInt::BIT5);
    EXPECT_EQ(TestBitsUInt::BIT2 >> 5, TestBitsUInt::NONE);
    EXPECT_EQ((TestBitsUInt::BIT5 | TestBitsUInt::BIT9) >> 3, TestBitsUInt::BIT2 | TestBitsUInt::BIT6);

    TestBitsUInt a = TestBitsUInt::BIT5;
    EXPECT_EQ(&(a >>= 3), &a);
    EXPECT_EQ(a, TestBitsUInt::BIT2);
}

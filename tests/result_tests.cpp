#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/result.h"

namespace
{
enum TestEnum
{
    WorseError = -2,
    Error = -1,
    Ok = 0,
    StillOk,
    EvenMoreOk
};

class TestClass
{
    public:
        TestClass() = default;

        bool TestFunction()
        {
            return true;
        }
};

TEST(Result, EnumTest)
{
    Result::Result<TestEnum, int> worseError = Result::Result(TestEnum::WorseError, 0);
    Result::Result<TestEnum, int> error = Result::Result(TestEnum::Error, 0);
    Result::Result<TestEnum, int> ok = Result::Result(TestEnum::Ok, 2);
    Result::Result<TestEnum, int> stillOk = Result::Result(TestEnum::StillOk, 3);
    Result::Result<TestEnum, int> evenMoreOk = Result::Result(TestEnum::EvenMoreOk, 4);

    ASSERT_FALSE(worseError.HasValue());

    ASSERT_FALSE(error.HasValue());

    ASSERT_TRUE(ok.HasValue());
    ASSERT_EQ(*ok, 2);
    ASSERT_EQ(ok.Value(), 2);

    ASSERT_TRUE(stillOk.HasValue());
    ASSERT_EQ(*stillOk, 3);
    ASSERT_EQ(stillOk.Value(), 3);

    ASSERT_TRUE(evenMoreOk.HasValue());
    ASSERT_EQ(*evenMoreOk, 4);
    ASSERT_EQ(evenMoreOk.Value(), 4);
}

TEST(Result, IntTest)
{
    Result::Result<int, int> worseError = Result::Result(-2, 0);
    Result::Result<int, int> error = Result::Result(-1, 0);
    Result::Result<int, int> ok = Result::Result(0, 2);
    Result::Result<int, int> stillOk = Result::Result(1, 3);
    Result::Result<int, int> evenMoreOk = Result::Result(2, 4);

    ASSERT_FALSE(worseError.HasValue());

    ASSERT_FALSE(error.HasValue());

    ASSERT_TRUE(ok.HasValue());
    ASSERT_EQ(*ok, 2);
    ASSERT_EQ(ok.Value(), 2);

    ASSERT_TRUE(stillOk.HasValue());
    ASSERT_EQ(*stillOk, 3);
    ASSERT_EQ(stillOk.Value(), 3);

    ASSERT_TRUE(evenMoreOk.HasValue());
    ASSERT_EQ(*evenMoreOk, 4);
    ASSERT_EQ(evenMoreOk.Value(), 4);
}

TEST(Result, BoolTest)
{
    Result::Result<bool, int> error = Result::Result(false, 0);
    Result::Result<bool, int> ok = Result::Result(true, 1);

    ASSERT_FALSE(error.HasValue());

    ASSERT_TRUE(ok.HasValue());
    ASSERT_EQ(*ok, 1);
    ASSERT_EQ(ok.Value(), 1);
}

TEST(Result, ObjectAccess)
{
    Result::Result<TestEnum, TestClass> testObjectError = Result::Result<TestEnum, TestClass>(TestEnum::Error, Result::nullresult);
    Result::Result<TestEnum, TestClass> testObjectOk = Result::Result<TestEnum, TestClass>(TestEnum::Ok, TestClass());

    ASSERT_FALSE(testObjectError.HasValue());

    ASSERT_TRUE(testObjectOk.HasValue());
    ASSERT_TRUE(testObjectOk->TestFunction());
    ASSERT_TRUE(testObjectOk.Value().TestFunction());
}
}
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

#include "cwrapper/resource.hpp"

struct TestDeleter
{
    void operator()(bool* foo) {
        *foo = true;
    }
};

using TestResource = cwrapper::Resource<bool*, TestDeleter>;

TEST(Resource, Deletion)
{
    bool del = false;
    {
        EXPECT_FALSE(del);
        TestResource resource {&del};
        EXPECT_TRUE(resource.hasHandle());
        EXPECT_FALSE(del);
    }
    EXPECT_TRUE(del);
}

TEST(Resource, MoveConstruct)
{
    bool del = false;
    {
        TestResource outer {&del};
        EXPECT_FALSE(del);
        EXPECT_TRUE(outer.hasHandle());

        {
            TestResource inner {std::move(outer)};

            EXPECT_FALSE(del);
            EXPECT_FALSE(outer.hasHandle());
            EXPECT_TRUE(inner.hasHandle());
        }
        EXPECT_FALSE(outer.hasHandle());
        EXPECT_TRUE(del);

        // let's make sure it doesn't get deleted again
        del = false;
    }
    EXPECT_FALSE(del);
}

TEST(Resource, MoveAssign)
{
    bool del = false;
    {
        TestResource outer;
        EXPECT_FALSE(del);
        EXPECT_FALSE(outer.hasHandle());

        {
            TestResource inner {&del};

            EXPECT_FALSE(del);
            EXPECT_FALSE(outer.hasHandle());
            EXPECT_TRUE(inner.hasHandle());

            EXPECT_EQ(&(outer = std::move(inner)), &outer);

            EXPECT_FALSE(del);
            EXPECT_TRUE(outer.hasHandle());
            EXPECT_FALSE(inner.hasHandle());
        }
        EXPECT_FALSE(del);
        EXPECT_TRUE(outer.hasHandle());
    }
    EXPECT_TRUE(del);
}

TEST(Resource, GetSetHandle)
{
    bool del1 = false;
    bool del2 = false;

    TestResource r1 {&del1};
    EXPECT_FALSE(del1);
    EXPECT_FALSE(del2);
    EXPECT_EQ(r1.getHandle(), &del1);

    r1.setHandle(&del2);
    EXPECT_TRUE(del1);
    EXPECT_FALSE(del2);
    EXPECT_EQ(r1.getHandle(), &del2);
}

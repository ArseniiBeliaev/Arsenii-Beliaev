#include <gtest/gtest.h>
#include "PrintLengthMaxPrefix.h"

TEST(Examples, FirstExample)
{
	ASSERT_EQ(PrintLengthMaxPrefixX("ab+c.aba.*.bac.+.+*","abacb"), 4);
}

TEST(Examples, SecondExample)
{
	ASSERT_EQ(PrintLengthMaxPrefixX("acb..bab.c.*.ab.ba.+.+*a.", "cb"), 0);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

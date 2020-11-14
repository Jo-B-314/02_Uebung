#include <gtest/gtest.h>
#include "../RNA.h"
#include "../InvalidCharacter.h"

using namespace Alphabet;

TEST(RNA, simpleToChar)
{
        RNA rns;
	RNA::Characters c = rns.toCharacter('A');
        EXPECT_EQ(c, RNA::Characters::A);
        c = rns.toCharacter('G');
        EXPECT_EQ(c, RNA::Characters::G);
}

TEST(RNA, invalidChar)
{
	RNA rns;
	ASSERT_THROW(rns.toCharacter('T'), InvalidCharacter);
	ASSERT_THROW(rns.toCharacter('q'), InvalidCharacter);
}

TEST(RNA, insensitive)
{
	RNA rns;
	RNA::Characters c = rns.toCharacter('c');
	RNA::Characters u = rns.toCharacter('u');
	ASSERT_EQ(c, RNA::Characters::C);
	ASSERT_EQ(u, rns.toCharacter('U'));
	ASSERT_EQ(u, RNA::Characters::U);
}

TEST(RNA, toChar)
{
	RNA rns;
	ASSERT_EQ('A', rns.toChar(RNA::Characters::A));
	ASSERT_EQ('G', rns.toChar(RNA::Characters::G));
	ASSERT_EQ('C', rns.toChar(RNA::Characters::C));
	ASSERT_EQ('U', rns.toChar(RNA::Characters::U));
}

#include <gtest/gtest.h>
#include "../DNA.h"
#include "../InvalidCharacter.h"

using namespace Alphabet;

TEST(DNA, simpleToChar)
{
	DNA dns;
	DNA::Characters c = dns.toCharacter('a');
	EXPECT_EQ(c, DNA::Characters::a);
	c = dns.toCharacter('A');
	EXPECT_EQ(c, DNA::Characters::A);
	c = dns.toCharacter('g');
	EXPECT_EQ(c, DNA::Characters::g);
	c = dns.toCharacter('G');
	EXPECT_EQ(c, DNA::Characters::G);
}

TEST(DNA, invalidChar)
{
	DNA dns;
	ASSERT_THROW(dns.toCharacter('u'), InvalidCharacter);
	ASSERT_THROW(dns.toCharacter('p'), InvalidCharacter);
}

TEST(DNA, insensitiveN)
{
	DNA dns;
	DNA::Characters c1 = dns.toCharacter('n');
	DNA::Characters c2 = dns.toCharacter('N');
	EXPECT_EQ(c1, c2);
	EXPECT_EQ(c1, DNA::Characters::N);
}

TEST(DNA, toCharSimple) 
{
	DNA dns;
	char c = dns.toChar(DNA::Characters::N);
	EXPECT_EQ(c, 'N');
	c = dns.toChar(DNA::Characters::T);
	EXPECT_EQ(c, 'T');
	char c2 = dns.toChar(DNA::Characters::T);
	EXPECT_EQ(c, c2);
}

TEST(DNA, canoncalize)
{
	DNA dns;
	DNA::Characters c = DNA::Characters::c;
	DNA::Characters C = DNA::Characters::C;
	EXPECT_EQ(dns.canonicalize(c), C);
	EXPECT_EQ(dns.canonicalize(C), C);
	EXPECT_EQ(dns.canonicalize(c), dns.canonicalize(C));	
}

TEST(DNA, to2Bit)
{
	DNA dns;
	DNA::Characters c = DNA::Characters::c;
	auto b = dns.to2Bit(c);
	ASSERT_EQ(0, b.compare("11"));
}

TEST(DNA, to2BitMask)
{
	DNA dns;
	DNA::Characters c = DNA::Characters::C;
	auto b = dns.to2BitMask(c);
	ASSERT_EQ(0, b.compare("00"));
}

TEST(DNA, to2BitMaskfail)
{
	DNA dns;
	DNA::Characters c = DNA::Characters::a;
	auto b = dns.to2BitMask(c);
	ASSERT_EQ(0, b.compare("01"));
}

TEST(DNA, from2Bit)
{
	DNA dns;
	DNA::Characters c = dns.from2Bit("00");
	char str = 'G';
	char cc = dns.toChar(c);
	bool b = !(str == cc);
	ASSERT_EQ(0, b);
}

TEST(DNA, intron)
{
	DNA dns;
	DNA::Characters c = DNA::Characters::A;
	DNA::Characters l = dns.intron(c);
	char str = 'a';
	char cc = dns.toChar(l);
	bool b = !(str == cc);
	ASSERT_EQ(0, b);
}

TEST(DNA, from2BitMask)
{
	DNA dns;
	DNA::Characters x = DNA::Characters::a;
	DNA::Characters c = dns.from2BitMask("00", x);
	char str = 'A';
	char cc = dns.toChar(c);
	bool b = !(str == cc);
	ASSERT_EQ(0, b);
}
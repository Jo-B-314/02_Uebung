#include <gtest/gtest.h>
#include "../Peptide.h"
#include "../InvalidCharacter.h"

using namespace Alphabet;

TEST(Peptide, toCharacterSimple) 
{
	Peptide p;
	Peptide::Characters c = p.toCharacter('A');
	EXPECT_EQ(c, Peptide::Characters::Ala);
	c = p.toCharacter('C');
	EXPECT_EQ(c, Peptide::Characters::Cys);
	c = p.toCharacter('D');
	EXPECT_EQ(c, Peptide::Characters::Asp);
	c = p.toCharacter('E');
	EXPECT_EQ(c, Peptide::Characters::Glu);
	c = p.toCharacter('F');
	EXPECT_EQ(c, Peptide::Characters::Phe);
	c = p.toCharacter('G');
	EXPECT_EQ(c, Peptide::Characters::Gly);
	c = p.toCharacter('H');
	EXPECT_EQ(c, Peptide::Characters::His);       
       	c = p.toCharacter('I');
        EXPECT_EQ(c, Peptide::Characters::Ile);
	c = p.toCharacter('K');
        EXPECT_EQ(c, Peptide::Characters::Lys);
	c = p.toCharacter('L');
        EXPECT_EQ(c, Peptide::Characters::Leu);
	c = p.toCharacter('M');
        EXPECT_EQ(c, Peptide::Characters::Met);
	c = p.toCharacter('N');
        EXPECT_EQ(c, Peptide::Characters::Asn);
        c = p.toCharacter('P');
        EXPECT_EQ(c, Peptide::Characters::Pro);
        c = p.toCharacter('Q');
        EXPECT_EQ(c, Peptide::Characters::Gln);
        c = p.toCharacter('R');
        EXPECT_EQ(c, Peptide::Characters::Arg);
        c = p.toCharacter('S');
        EXPECT_EQ(c, Peptide::Characters::Ser);
        c = p.toCharacter('T');
        EXPECT_EQ(c, Peptide::Characters::Thr);
        c = p.toCharacter('V');
        EXPECT_EQ(c, Peptide::Characters::Val);
        c = p.toCharacter('W');
        EXPECT_EQ(c, Peptide::Characters::Trp);
        c = p.toCharacter('Y');
        EXPECT_EQ(c, Peptide::Characters::Tyr);
}

TEST(Peptide, insensitive) 
{
	Peptide p;
	Peptide::Characters c = p.toCharacter('a');
	EXPECT_EQ(c, p.toCharacter('A'));
	EXPECT_EQ(c, Peptide::Characters::Ala);
}


TEST(Peptide, InvalidCharacter)
{
	Peptide p;
	ASSERT_THROW(p.toCharacter('x'), InvalidCharacter);
}

TEST(Peptide, toChar)
{
	Peptide p;
	EXPECT_EQ('A', p.toChar(Peptide::Characters::Ala));
	EXPECT_EQ('C', p.toChar(Peptide::Characters::Cys));
        EXPECT_EQ('D', p.toChar(Peptide::Characters::Asp));
        EXPECT_EQ('E', p.toChar(Peptide::Characters::Glu));
        EXPECT_EQ('F', p.toChar(Peptide::Characters::Phe));
        EXPECT_EQ('G', p.toChar(Peptide::Characters::Gly));
        EXPECT_EQ('H', p.toChar(Peptide::Characters::His));
        EXPECT_EQ('I', p.toChar(Peptide::Characters::Ile));
        EXPECT_EQ('K', p.toChar(Peptide::Characters::Lys));
        EXPECT_EQ('L', p.toChar(Peptide::Characters::Leu));
        EXPECT_EQ('M', p.toChar(Peptide::Characters::Met));
        EXPECT_EQ('N', p.toChar(Peptide::Characters::Asn));
        EXPECT_EQ('P', p.toChar(Peptide::Characters::Pro));
        EXPECT_EQ('Q', p.toChar(Peptide::Characters::Gln));
        EXPECT_EQ('R', p.toChar(Peptide::Characters::Arg));
        EXPECT_EQ('S', p.toChar(Peptide::Characters::Ser));
        EXPECT_EQ('T', p.toChar(Peptide::Characters::Thr));
        EXPECT_EQ('V', p.toChar(Peptide::Characters::Val));
        EXPECT_EQ('W', p.toChar(Peptide::Characters::Trp));
        EXPECT_EQ('Y', p.toChar(Peptide::Characters::Tyr));
}


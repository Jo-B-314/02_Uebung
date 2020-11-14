#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <map>
#include "../Peptide.h"
#include "../RNA.h"
#include "../DNA.h"
#include "../Sequence.h"

using namespace Alphabet;

TEST(Sequence, toStringSimple) 
{
	Sequence<DNA> seqDNA;
	seqDNA.push_back(DNA::Characters::G);
	seqDNA.push_back(DNA::Characters::A);
	std::string str = seqDNA.toString();
	unsigned int comp = 2;
	EXPECT_EQ(seqDNA.size(), comp); 
	ASSERT_EQ(0, str.compare("GA"));
}

TEST(Sequence, mapSimple)
{
	Sequence<RNA> seqRNA;
	seqRNA.push_back(RNA::Characters::U);
	std::map<RNA::Characters, size_t> map = seqRNA.statistics();
	EXPECT_NE(map.find(RNA::Characters::U), map.end());
	EXPECT_EQ(map.find(RNA::Characters::A), map.end());
	unsigned int comp = 1;
	EXPECT_EQ(map[RNA::Characters::U], comp);
}

TEST(Sequence, mapIntronExon) 
{
	Sequence<DNA> seqDNA;
	seqDNA.push_back(DNA::Characters::a);
	seqDNA.push_back(DNA::Characters::A);
	std::map<DNA::Characters, size_t> map = seqDNA.statistics();
	EXPECT_NE(map.find(DNA::Characters::A), map.end());
	unsigned int comp = 2;
	EXPECT_EQ(map.find(DNA::Characters::a), map.end());
	EXPECT_EQ(map[DNA::Characters::A], comp);
}

TEST(Sequence, mapMoreChars)
{
	Sequence<Peptide> seqPep;
	seqPep.push_back(Peptide::Characters::Ala);
	seqPep.push_back(Peptide::Characters::Thr);
	seqPep.push_back(Peptide::Characters::Met);
	seqPep.push_back(Peptide::Characters::Ala);
	std::map<Peptide::Characters, size_t> map = seqPep.statistics();
	EXPECT_NE(map.find(Peptide::Characters::Ala), map.end());
	unsigned int comp2 = 2;
	EXPECT_EQ(map[Peptide::Characters::Ala], comp2);
	EXPECT_NE(map.find(Peptide::Characters::Thr), map.end());
	EXPECT_NE(map.find(Peptide::Characters::Met), map.end());
	unsigned int comp1 = 1;
	EXPECT_EQ(map[Peptide::Characters::Met], comp1);
	EXPECT_EQ(map[Peptide::Characters::Thr], comp1);
}

TEST(Sequence, no_overlap)
{
	Sequence<DNA> seqDNA1;
	seqDNA1.push_back(DNA::Characters::G);
	seqDNA1.push_back(DNA::Characters::A);
	Sequence<DNA> seqDNA2;
	seqDNA2.push_back(DNA::Characters::T);
	size_t overlap = seqDNA1.overlap(seqDNA2);
	size_t comp = 0;
	EXPECT_EQ(comp, overlap);
}

TEST(Sequence, simpleOverlap)
{
	Sequence<DNA> seqDNA1;
	seqDNA1.push_back(DNA::Characters::C);
	Sequence<DNA> seqDNA2;
	seqDNA2.push_back(DNA::Characters::C);
	size_t overlap = seqDNA1.overlap(seqDNA2);
	size_t comp = 1;
	EXPECT_EQ(comp, overlap);
}

TEST(Sequence, Overlap) 
{
	Sequence<RNA> seq1 = Sequence<RNA>::fromString("GAUUACAGGACCCU");
	Sequence<RNA> seq2 = Sequence<RNA>::fromString("GACCCUGAUGGC");
	size_t  overlap = seq1.overlap(seq2);
	size_t comp = 6;
	EXPECT_EQ(comp, overlap);
}

TEST(Sequence, overlap_repeat)
{
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("GAGAGAGAGAGAGA");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("GAGAGAGAGAGAGA");
	size_t overlap = seq1.overlap(seq2);
	size_t comp = 14;
	EXPECT_EQ(comp, overlap);
}

TEST(Sequence, fromStringTest) 
{
	Sequence<DNA> seqDNA = Sequence<DNA>::fromString("GATTACA");
	std::string str = seqDNA.toString();
	EXPECT_EQ(0, str.compare("GATTACA"));
}

TEST(Sequence, equalOp) 
{
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("GATTACA");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("GATTACA");
	EXPECT_EQ(seq1, seq2);
}

TEST(Sequence, ineqalOp) 
{
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("GATTACA");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("GAAGAGAGAGAGAG");
	EXPECT_NE(seq1, seq2);
}

TEST(Sequence, ostreamOp) 
{
	Sequence<DNA> seq = Sequence<DNA>::fromString("GATTACA");
	std::stringstream ss;
	ss << seq;
	std::string str = ss.str();
	ASSERT_EQ(0, str.compare(seq.toString()));
}

TEST(Sequence, istreamOp)
{
	Sequence<DNA> seq =  Sequence<DNA>::fromString("G");
	std::stringstream ss (seq.toString());
	std::string str;
	ss >> str;
	ASSERT_EQ(0, str.compare(seq.toString()));
}

TEST(Sequence, compare_equal) {
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("ATGCGGGAGAAATAG");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("GAGAAATAG");
	ASSERT_TRUE(seq1.compare(seq2, 6));
}

TEST(sequence, compare_not_equal) {
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("ATGCGGGAGAAATAG");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("GAGATATAG");
	ASSERT_FALSE(seq1.compare(seq2, 6));
}

TEST(Sequence, compare_index_fail) {
	Sequence<DNA> seq1 = Sequence<DNA>::fromString("ATGCGGGAGAAATAG");
	Sequence<DNA> seq2 = Sequence<DNA>::fromString("AGAAATAG");
	ASSERT_FALSE(seq1.compare(seq2, 6));
}

TEST(Sequence, to2Bit)
{
	Sequence<DNA> seq = Sequence<DNA>::fromString("AGANATAG");
	std::string bit = seq.to2Bit();
	std::string str = "01000100011001000000001000000000";
	std::cout << bit << std::endl;
	std::cout << str << std::endl;
	ASSERT_EQ(0, str.compare(bit));
}

TEST(Sequence, to2Bitplus)
{
	Sequence<DNA> seq = Sequence<DNA>::fromString("AGA");
	std::string bit = seq.to2Bit();
	std::string str = "0100010000000000";
	std::cout << bit << std::endl;
	std::cout << str << std::endl;
	ASSERT_EQ(0, str.compare(bit));
}
#include <gtest/gtest.h>
#include <string>

#include "../2Bit.h"
#include "../Sequence.h"
#include "../DNA.h"
#include "../ParsingException.h"

using namespace Alphabet;


TEST(Bit2, ostreamExon) 
{
	Sequence<DNA> seq = Sequence<DNA>::fromString("AGGAT");
	seq.setComment("Sequence 1");
	const Sequence2BitWriter writer(seq);
	std::stringstream ss;
	ss << writer;
	std::string str = ss.str();
	std::stringstream comp;
	comp << ">Sequence 1:0-4\nP01000001100000000000000000000000\n";
	std::string compstr = comp.str();
	ASSERT_EQ(0, compstr.compare(str));
}

TEST(Bit2, ostreamIntron)
{
	Sequence<DNA> seq = Sequence<DNA>::fromString("GattAN");
	seq.setComment("ChrY");
	const Sequence2BitWriter writer(seq);
	std::stringstream ss;
	ss << writer;
	std::string str = ss.str();
	std::stringstream comp;
	comp << ">ChrY:0-5\nP00011010010000000001010100100000\n";
	std::string compstr = comp.str();
	ASSERT_EQ(0, compstr.compare(str));
}


TEST(Bit2, istreamSimple)
{
	Sequence<DNA> seq_;
	Sequence<DNA>& seq = seq_;
	std::stringstream ss;
	ss << ">ChrY:0-5\nP00011010010000000001010100100000\n";
	ss >> from2Bit(seq);
	std::string comment = "ChrY";
	ASSERT_EQ(0, comment.compare(seq.getComment()));
	std::string sequence = "GattAN";
	ASSERT_EQ(0, sequence.compare(seq.toString()));
}

TEST(Bit2, istreamError)
{
	Sequence<DNA> seq_;
	Sequence<DNA>& seq = seq_;
	std::stringstream ss;
        ss << ">ChrY:0-5\n00011010010000000001010100100000\n";
	ASSERT_THROW(ss >> from2Bit(seq), ParsingException);
	std::stringstream ss2;
	ss2 << "<jkj:0-2\n0101010100000000\n";
	ASSERT_THROW(ss2 >> from2Bit(seq), ParsingException);
	std::stringstream ss3;
	ss3 << ">ChrY:0-5\n00011010010000000000\n";
	ASSERT_THROW(ss3 >> from2Bit(seq), ParsingException);
}

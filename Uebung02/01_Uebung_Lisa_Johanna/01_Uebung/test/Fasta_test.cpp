#include <gtest/gtest.h>
#include <string>

#include "../Fasta.h"
#include "../Sequence.h"
#include "../DNA.h"
#include "../Peptide.h"

using namespace Alphabet;

TEST(Fasta, writerSimpleComment)
{
	Sequence<DNA> Dnaseq;
	Dnaseq.push_back(DNA::Characters::G);
	Dnaseq.push_back(DNA::Characters::C);
	Dnaseq.setComment("i'm a comment");
	const Sequence<DNA>& seq = Dnaseq;
	SequenceFastaWriter<DNA> writer(seq);
	std::string str = writer.getSequence().getComment();
	ASSERT_EQ(0, str.compare("i'm a comment"));
}

TEST(Fasta, writerDnaSequence)
{
	Sequence<DNA> Dnaseq;
	Dnaseq.push_back(DNA::Characters::G);
	Dnaseq.push_back(DNA::Characters::C);
	Dnaseq.setComment("test");
	const Sequence<DNA>& seq = Dnaseq;
	SequenceFastaWriter<DNA> writer (seq);
	std::string str = writer.getSequence().toString();
	ASSERT_EQ(0, str.compare("GC"));
}

TEST(Fasta, ostreamPeptide)
{
	Sequence<Peptide> pepseq;
	pepseq.push_back(Peptide::Characters::Ala);
	pepseq.push_back(Peptide::Characters::Lys);
	const Sequence<Peptide>& seq = pepseq;
	SequenceFastaWriter<Peptide> writer (seq);
	std::stringstream ss;
	ss << writer;
	std::string str = ss.str();
	ASSERT_EQ(0, str.compare(seq.toString()));
}

TEST(Fasta, ostreamDNA)
{
	Sequence<DNA> dnaseq;
	dnaseq.push_back(DNA::Characters::A);
	dnaseq.push_back(DNA::Characters::T);
	const Sequence<DNA>& seq = dnaseq;
	SequenceFastaWriter<DNA> writer (seq);
	std::stringstream ss;
	ss << writer;
	std::string str = ss.str();
	ASSERT_EQ(0, str.compare(seq.toString()));
}

TEST(Fasta, ostreamComment)
{
	Sequence<DNA> dnaseq;
	dnaseq.push_back(DNA::Characters::A);
	dnaseq.push_back(DNA::Characters::C);
	dnaseq.setComment("comment1");
	const Sequence<DNA>& seq = dnaseq;
	std::string seq_str = ">" + seq.getComment() + "\n" + seq.toString() + "\n";
	SequenceFastaWriter<DNA> writer (seq);
	std::stringstream ss;
	ss << writer;
	std::string ss_str = ss.str();
	ASSERT_EQ(0, seq_str.compare(ss_str));
}

TEST(Fasta, istreamDNA)
{
	Sequence<DNA> dnaseq;
	dnaseq.push_back(DNA::Characters::A);
	dnaseq.push_back(DNA::Characters::G);
	dnaseq.push_back(DNA::Characters::T);
	dnaseq.setComment("comment");
	Sequence<DNA>& seq = dnaseq;
	std::string seq_str = ">" + seq.getComment() + "\n" + seq.toString() + "\n";
	Sequence<DNA> emptyseq;
	SequenceFastaReader<DNA> reader (emptyseq);
	std::stringstream ss (seq_str);
	ss >> fromFasta(emptyseq);
	ASSERT_EQ(0, seq.toString().compare(reader.getSequence().toString()));
}

TEST(Fasta, toFasta)
{
	Sequence<DNA> dnaseq;
	dnaseq.push_back(DNA::Characters::G);
	dnaseq.push_back(DNA::Characters::T);
	Sequence<DNA>& seq = dnaseq;
	SequenceFastaWriter<DNA> writer (seq);
	std::stringstream ss;
	ss << toFasta(seq);
	ASSERT_EQ(0, seq.toString().compare(ss.str()));
}
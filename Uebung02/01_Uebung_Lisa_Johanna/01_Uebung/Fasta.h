
#ifndef BIOINFOI_FASTA_H
#define BIOINFOI_FASTA_H

#include "Sequence.h"
#include "ParsingException.h"

#include <istream>
#include <ostream>
#include <iterator>

/**
 * A simple helper class used to signal
 * that we want to write a DNA sequence in 2Bit format.
 */
template<typename Alpha>
class SequenceFastaWriter
{
  public:
	SequenceFastaWriter(const Sequence<Alpha>& seq);
	
	Sequence<Alpha> getSequence() const{
		return seq_;
	}

	/// Global input operator
	template<typename A>
	friend std::ostream& operator<<(std::ostream& strm,
	                                const SequenceFastaWriter<A>&);


  private:
	/// Stores a reference to the sequence to write.
	const Sequence<Alpha>& seq_;
};

/**
 * A simple helper class used to signal
 * that we want to read a DNA sequence in 2Bit format.
 */
template<typename Alpha>
class SequenceFastaReader
{
  public:
	SequenceFastaReader(Sequence<Alpha>& seq);

	Sequence<Alpha>& getSequence() {
		return seq_;
	}

	/// Global input operator (Needs an rvalue reference to work with from2Bit...)
	template<typename A>
	friend std::istream& operator>>(std::istream& strm, SequenceFastaReader<A>&&);

  private:
	/// Stores a reference to the sequence to read.
	Sequence<Alpha>& seq_;
};

template<typename Alpha>
SequenceFastaWriter<Alpha> toFasta(const Sequence<Alpha>& seq) {
	SequenceFastaWriter<Alpha> writer(seq);
	return writer;
}

template<typename Alpha>
SequenceFastaReader<Alpha> fromFasta(Sequence<Alpha>& seq) {
	SequenceFastaReader<Alpha> reader(seq);
	return reader;
}

template <typename Alpha>
SequenceFastaReader<Alpha>::SequenceFastaReader(Sequence<Alpha>& seq)
    : seq_(seq)
{
}

template <typename Alpha>
std::ostream& operator<<(std::ostream& strm,
                         const SequenceFastaWriter<Alpha>& writer)
{
	Sequence<Alpha> seq_ = writer.getSequence();
	std::string comment = seq_.getComment();
        	if (comment.compare("") != 0) {
                	strm << ">" << seq_.getComment() << std::endl << seq_ << std::endl;
        	} else {
                	strm << seq_;
        	}
        	return strm;
}

template <typename Alpha>
std::istream& operator>>(std::istream& strm,
                         SequenceFastaReader<Alpha>&& reader)
{
	std::istream_iterator<char> eos; //end of stream iterator
	std::string comment;
	char c;
	strm >> c;
	if (c == '>') {
		//there is a comment -> we read the header line
		getline(strm, comment);
		reader.getSequence().setComment(comment);
	} else {
		throw ParsingException("no Header");
	}
	std::istream_iterator<char> iter(strm);
	if (iter == eos) {
		throw ParsingException("Header but no Sequence");
	}
	Sequence<Alpha>& seq = reader.getSequence();
	for (; (iter != eos); iter++) {
		seq.push_back(Alpha::toCharacter(*iter));
		while ((char) strm.peek() == '\n') {
			strm.get();
		}
		if ((char) strm.peek() == '>') break;
	}
	while ((char) strm.peek() == '\n') strm.get();
	return strm;
}

template <typename Alpha>
SequenceFastaWriter<Alpha>::SequenceFastaWriter(const Sequence<Alpha>& seq)
    : seq_(seq)
{
}

#endif // BIOINFOI_FASTA_H


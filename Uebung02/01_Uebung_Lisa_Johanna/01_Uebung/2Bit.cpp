#include "2Bit.h"
#include "ParsingException.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <istream>
#include <sstream>

using Seq = Sequence<Alphabet::DNA>;


Sequence2BitReader::Sequence2BitReader(Seq& seq) : seq_(seq) {}

std::istream& operator>>(std::istream& strm, Sequence2BitReader&& reader)
{
   	std::string comment;
    char c;
	strm >> c;
	std::cout << c;
    std::istream_iterator<char> eos;
    if (c == '>') {
    	//comment inbetween > and :
    	getline(strm, comment, ':');
		const std::string comment_ = comment;
   		Seq& seq = reader.getSequence();
		assert(comment.compare("") != 0);
		seq.setComment(comment);
    } else {
	std::cout << c;
        throw ParsingException("no header");
    }
	//write from : to P in full_string
    std::string full_string = "";
	std::istream_iterator<char> comm_iter(strm);

	/**
	 * we store all information about the number of bases in one string
	 */
	for(; (*comm_iter != 'P') && (comm_iter != eos); comm_iter++) {
		full_string.push_back(*comm_iter);
	}

	if (comm_iter == eos) {
        throw ParsingException("header but no sequence or no P");
    	}

	//write rest in seq_with_mask
	Seq& seq = reader.getSequence();
    std::string seq_with_mask;
	/**
	 * we read the sequence of bits until we reach the eof or the next seq
	 */
    for (++comm_iter; (comm_iter != eos); comm_iter++) {
        	seq_with_mask.push_back(*comm_iter);
		while ((char) strm.peek() == '\n') strm.get();
		if ((char) strm.peek() == '>') break;
    }
	//we remove all the whitespace 
	while ((char) strm.peek() == '\n') strm.get();

	//split string at -
	std::string endstr = "";
	std::string beginstr = "";
	std::stringstream split (full_string);
	std::getline(split, beginstr, '-');
	std::getline(split, endstr);

	int begin = std::stoi(beginstr); 
	if ((begin != 1) && (begin != 0)) {
		throw ParsingException("no valid begin");
	}
		
	//we need zero based values to get the elements in our seq string
    int end = std::stoi(endstr);
	if (begin == 1) {
		begin = 0;
		end--;
	}

	int num_of_null = 0;
	while ((end + 1) % 4 != 0) {
		num_of_null++;
		end ++;
		//we have to increase end because otherwise we'd never end
	}

	unsigned int compare = (end + 1) * 4;
	if (seq_with_mask.size() != compare) {
		throw ParsingException("not correct number of bit");
	}

	/**
	 * now we read our sequence and the mask simlutaneously
	 * we ignore all the 00 which don't code for a base
	 */
    for (int i = begin; i <= ((end - num_of_null)); i++) {
        std::string from2bit;
		std::string mask;
		from2bit.push_back(seq_with_mask[2 * i]);
		mask.push_back(seq_with_mask[((1 + end) * 2) + 2 * i]);
		from2bit = from2bit + seq_with_mask[2 * i + 1];
		mask = mask + seq_with_mask[((1 + end) * 2) + 2 * i + 1];
		Alphabet::DNA::Characters character = Alphabet::DNA::from2Bit(from2bit);
		character = Alphabet::DNA::from2BitMask(mask, character);
		seq.push_back(character);
    }
        return strm;
}

Sequence2BitWriter::Sequence2BitWriter(const Seq& seq) : seq_(seq) {}

std::ostream& operator<<(std::ostream& strm, const Sequence2BitWriter& writer)
{
	Sequence<Alphabet::DNA> seq_ = writer.getSequence();
        std::string comment = seq_.getComment();
        if (comment.compare("") != 0) {
		strm << ">" << seq_.getComment() << ":0-" << seq_.size()-1 << std::endl << "P" << seq_.to2Bit() << std::endl;
        } else {
            strm << seq_;
        }
        return strm;
		
}

Sequence2BitWriter to2Bit(const Seq& sequence)
{
	Sequence2BitWriter writer(sequence);
	return writer;
}

Sequence2BitReader from2Bit(Seq& sequence)
{
	Sequence2BitReader reader(sequence);
	return reader;
}


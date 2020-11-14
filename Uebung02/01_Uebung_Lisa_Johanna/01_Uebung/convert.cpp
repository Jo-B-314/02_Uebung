#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cassert>
#include "Fasta.h"
#include "Sequence.h"
#include "DNA.h"
#include "2Bit.h"

using namespace Alphabet;

int main(int argc, char* argv[])
{
	if (argc != 3) {
		//Illegal number of Commandline arguments
		std::cerr << "Illeagl number of arguments" << argc << std::endl;
		return 1;
	}
	std::string argv1(argv[1]);
	std::string argv2(argv[2]);
	if (argv1.find(".fa") != std::string::npos && argv2.find(".fa.2bit") != std::string::npos) {
		//in argv[1] steht .fa, aber .fa.fa möglich
		//from fasta to 2bit
		std::ifstream in_file(argv[1]);
		std::ofstream out_file(argv[2]);
		if (!in_file || !out_file) {
			std::cerr << "Could not open file" << std::endl;
			return 1;
		} else {
			while(in_file.good()) {
				Sequence<DNA> seq_;
				Sequence<DNA>& seq = seq_;
				in_file >> fromFasta(seq);
				out_file << to2Bit(seq);
			}
			in_file.close();
			out_file.close();
		}
	} else {
		if (argv1.find(".fa.2bit") != std::string::npos && argv2.find(".fa") != std::string::npos) {
		//from 2bit to fasta
		std::ifstream in_file(argv[1]);
		std::ofstream out_file(argv[2]);
		if (!in_file || !out_file) {
			std::cerr << "Could not open file" << std::endl;
			return 1;
		}
		while (in_file.good()) {
			Sequence<DNA> seq_;
			Sequence<DNA>& seq = seq_;
			in_file >> from2Bit(seq);
			out_file << toFasta(seq);
		}
		in_file.close();
		out_file.close();
		} else {
		std::cerr << "Illegal fileformat to read from " << argv[1] << std::endl;
		return 1;
		}
	}
	return 0;
}


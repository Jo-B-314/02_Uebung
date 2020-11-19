#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cassert>
#include "Fasta.h"
#include "Sequence.h"
#include "DNA.h"
#include "Assembler.h"

using namespace Alphabet;

/**
 * our main can be called ./graph fasta.fa file.dot # we read DNA Sequences with fromFasta
 * out of fasta.fa and store our overlap-graph in file.dot
 */
int main(int argc, char* argv[])
{
	if (argc != 3) {
		//Illegal number of Commandline arguments
		std::cerr << "Illeagl number of arguments" << argc << std::endl;
		return 1;
	}
	std::string argv1(argv[1]);
	std::string argv2(argv[2]);
	if (argv1.find(".fa") != std::string::npos && argv2.find(".dot") != std::string::npos) {
		//wir lesen aus einer fasta Datei und speichern das graphviz Format in einer .dot Datei
		std::ifstream in_file(argv[1]);
		std::ofstream out_file(argv[2]);
		if (!in_file || !out_file) {
			std::cerr << "Could not open file" << std::endl;
			return 1;
		} else {
            std::vector<Sequence<DNA>> vector; 
			while(in_file.good()) {
				Sequence<DNA> seq_;
				Sequence<DNA>& seq = seq_;
				in_file >> fromFasta(seq);
                vector.push_back(seq);
			}
            Assembler assembler(vector);
            Graph<Sequence<DNA>> graph = assembler.getGraph();
            out_file << graph;
			in_file.close();
			out_file.close();
        }
    } else {
        std::cerr << "Wrong format type" << std::endl;
        return 1;
    }
    return 0;
} 

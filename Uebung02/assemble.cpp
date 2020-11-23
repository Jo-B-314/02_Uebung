#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cassert>
#include<sstream>

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
    std::string h = "-h";
    std::string help = "--help";
	//if one of our arguments is --help or -h we print a text on the command line
    for (int i = 0; i < argc; i++) {
        if (h.compare(argv[i]) == 0 || help.compare(argv[i]) == 0){
            std::cout << "Help window:\n";
            std::cout << "-h / --help: opens this help window\n";
            std::cout << "-f / --fasta [FILE]: we read the given FASTA-file\n";
            std::cout << "-s / --save [DIRECTORY]: saves all our steps in the given directory (optional)\n";
            return 0;
        }
    }
    std::string file_path;
    std::string directory_path;
    std::string f = "-f";
    std::string file = "--file";
    std::string s = "-s";
    std::string save = "--save";
    if (argc != 3 && argc != 5) {
        std::cerr << "wrong number of arguments\n";
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        if (f.compare(argv[i]) == 0 || file.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no file \n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (file_path.size() == comp0) {
                file_path = argv[i+1];
            } else {
                std::cerr << "more than one file given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
        if (s.compare(argv[i]) == 0 || save.compare(argv[i]) == 0) {
            if (i+1 >= argc) {
                std::cerr << "flag but no directory\n use -h or --help to open the help window\n";
                return 1;
            }
            size_t comp0 = 0;
            if (directory_path.size() == comp0) {
                directory_path = argv[i+1];
            } else {
                std::cerr << "more than one directory given\n use -h or --help to open the help window\n";
                return 1;
            }
        }
    }
    
    if (argc == 5 && !directory_path.size()) {
        std::cerr << "wrong arguments\n";
        return 1;
    }

    if (!file_path.size()) {
        std::cerr << "no file given\n use -h or --help to open the help window\n";
        return 1;
    }
	
	if (file_path.find(".fa") != std::string::npos) {
		//wir read a .fa file
		std::ifstream in_file(file_path);
		if (!in_file) {
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
            if (!directory_path.size()) {
                Sequence<DNA> sequence = assembler.assemble();
                std::cout << "\nAssembled sequence:\n" << sequence << std::endl;
            } else {
                //there was a directory given
                Graph<Sequence<DNA>>& graph = assembler.getGraph();
                std::string path;
                if (directory_path.back() == '/') {
                    path = directory_path + "step0.dot";
                } else {
                    path = directory_path + "/step0.dot";
                }
                std::ofstream out(path);
                if (!out) {
                    std::cerr << "could not open out file\n";
                    return 1;
                }
                out << graph;
                out.close();
                size_t comp1 = 1;
                int count = 1;
                while (graph.numNodes() > comp1) {
                    assembler.joinLargestEdge();
                    graph = assembler.getGraph();
                    std::string step_path;
                    std::stringstream helper;
                    helper << "step" << count << ".dot";
                    if (directory_path.back() == '/') {
                        step_path = directory_path + helper.str();
                    } else {
                        step_path = directory_path + "/" + helper.str();
                    }
                    std::ofstream out_file(step_path);
                    if (!out_file) {
                        std::cerr << "could not open out_file\n";
                        return 1;
                    }
                    out_file << graph;
                    out_file.close();
                    count++;
                }
                auto nodeptr = graph.beginNodes();
                Sequence<DNA> sequence = nodeptr->label;
                std::cout << "\nAssembled sequence:\n" << sequence << std::endl;
            }
			in_file.close();
        }
    } else {
        std::cerr << "Wrong format type" << std::endl;
        return 1;
    }
    return 0;
} 

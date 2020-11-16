#include "Assembler.h"
#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

#include <memory>
#include <vector>
#include <iostream>

using Seq = Sequence<Alphabet::DNA>;
using OGraph = Graph<Seq>;

Assembler::Assembler(const std::vector<Seq>& sequences){
    OGraph graph(sequences);
    graph_ = graph;
    auto iter1 = graph_.beginNodes();
    while (iter1 != graph_.endNodes()) {
        auto iter2 = graph_.beginNodes();
        while (iter2 != graph_.endNodes()) {
            if (iter1 == iter2) {
                iter2++; 
                continue;
            }
            size_t overlap = iter1->label.overlap(iter2->label);
            size_t val0 = 0; //otherwise we get a warning
            if (overlap > val0) {
                graph_.addEdge(&(*iter1), &(*iter2), overlap);
            }
            iter2++;
        }
        iter1++;
    }
}

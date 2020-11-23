#include "Assembler.h"
#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

#include <memory>
#include <vector>
#include <iostream>
#include <cassert>

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

bool Assembler::isValid(const OGraph::Edge& e) {
    bool b = false;
    for (auto iter = graph_.beginNodes(); iter != graph_.endNodes(); iter++) {
        if (&*iter == e.source || &*iter == e.target) {
            if (b) {
                //we found both
                return true;
            }
            //we found one
            b = true;
        }
    }
    //we found just one or no one at all
    return false;
}

void Assembler::joinLargestEdge() {
    size_t max = 0;
    OGraph::Edge e(nullptr, nullptr, 0);
    for (auto node_iter = graph_.beginNodes(); node_iter != graph_.endNodes(); node_iter++) {
        for (auto edge_iter = node_iter->out_edges.begin(); 
             edge_iter != node_iter->out_edges.end(); edge_iter++) {
            if (edge_iter->second > max) {
                max = edge_iter->second;
                e.source = &*node_iter;
                e.target = edge_iter->first;
                e.weight = edge_iter->second;
            }
        }
    }
    size_t comp0 = 0;
    if (max != comp0) {
        assert(e.source != nullptr);
        assert(e.target != nullptr);
        assert(isValid(e));
        graph_.contractEdge(e);
    }
}

Seq Assembler::assemble() {
    size_t comp1 = 1;
    while (graph_.numNodes() > comp1) {
        joinLargestEdge();
    }
    assert(graph_.numNodes() == comp1);
    auto nodeptr = graph_.beginNodes();
    return nodeptr->label;
}

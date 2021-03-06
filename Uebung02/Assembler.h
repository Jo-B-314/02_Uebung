#ifndef BIOINFO1_ASSEMBLER_H
#define BIOINFO1_ASSEMBLER_H

#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

class Assembler
{
  public:
  	
	using Seq = Sequence<Alphabet::DNA>;
	using OGraph = Graph<Seq>;

	/**
	 * Creates an overlap-graph that contains the passed sequences as nodes.
	 */
	Assembler(const std::vector<Assembler::Seq>& sequences);
    
    /**
     * computes whether source and target of the edge are still nodes of graph_
     */
    bool isValid(const OGraph::Edge& e);
    
    /**
     * contracts edge with highest weight
     */
    void joinLargestEdge();
    
    /**
     * uses Greedy Alg an returns computed Sequence
     */
    Seq assemble();
    
    Assembler(): graph_() {}
    /**
     * returns the overlap-graph so the user can call every function
     */
    OGraph& getGraph(){
        return graph_;
    }
    
    private:
        OGraph graph_;
};

#endif // BIOINFO1_ASSEMBLER_H


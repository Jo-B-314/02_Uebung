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
};

#endif // BIOINFO1_ASSEMBLER_H


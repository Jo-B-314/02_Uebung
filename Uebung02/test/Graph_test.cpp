#include <gtest/gtest.h>

#include <memory>
#include <initializer_list>
#include <set>
#include <vector>
#include <deque>
#include <string>

#include "../Sequence.h"
#include "../DNA.h"

#include "../Graph.h"

using namespace Alphabet;

TEST(Graph, oneEdge)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GATTAcN");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("ATTNcc");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Edge e = graph.addEdge(n1, n2, 2);
    size_t val2 = 2;
    ASSERT_EQ(val2, graph.numNodes());
    ASSERT_EQ(val2, e.weight);
    ASSERT_EQ(n1, e.source);
    ASSERT_EQ(n2, e.target);
    ASSERT_TRUE(seq1 == n1->label);
    size_t val1 = 1;
    ASSERT_EQ(val1, n1->out_edges.size());
}

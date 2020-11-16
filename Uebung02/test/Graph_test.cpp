#include <gtest/gtest.h>

#include <memory>
#include <initializer_list>
#include <iostream>
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


TEST(Graph, contractEdge) 
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GGATTG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("GATTGG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("CACGGA");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Node *n3 = graph.addNode(seq3);
    Graph<Sequence<DNA>>::Edge e = graph.addEdge(n1, n2, 5);
    graph.addEdge(n3, n1, 3);
    graph.addEdge(n3, n2, 2);
    graph.addEdge(n2, n3);
    Graph<Sequence<DNA>>::Node *n12 = graph.contractEdge(e);
    Sequence<DNA> compare_seq = Sequence<DNA>::fromString("GGATTGG");
    ASSERT_EQ(compare_seq, n12->label);
    size_t val1 = 1;
    ASSERT_EQ(val1, n12->out_edges.size());
    ASSERT_EQ(val1, n3->out_edges.size());
    ASSERT_EQ(n12, n3->out_edges[0].first);
    size_t val3 = 3;
    ASSERT_EQ(val3, n3->out_edges[0].second);
}

TEST(Graph, addNode) 
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("CGATTG");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    ASSERT_EQ(seq1, n1->label);
}

TEST(Graph, addEdge)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("TACTTT");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Node *n3 = graph.addNode(seq3);
    graph.addEdge(n1, n2, 2);
    graph.addEdge(n1, n3, 3);
    graph.addEdge(n3, n2, 4);
    size_t val1 = 2;
    size_t val2 = 1;
    size_t val3 = 0;
    ASSERT_EQ(val1, n1->out_edges.size());
    ASSERT_EQ(val2, n3->out_edges.size());
    ASSERT_EQ(val3, n2->out_edges.size());
}

TEST(Graph, removeEdge1)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("TACTTT");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Node *n3 = graph.addNode(seq3);
    auto ed = graph.addEdge(n2, n1, 1);
    graph.addEdge(n2, n3);
    size_t val1 = 2;
    ASSERT_EQ(val1, n2->out_edges.size());
    graph.removeEdge(ed);
    size_t val2 = 1;
    ASSERT_EQ(val2, n2->out_edges.size());
}

TEST(Graph, removeEdges2) 
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("TACTTT");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Node *n3 = graph.addNode(seq3);
    graph.addEdge(n1, n2, 2);
    graph.addEdge(n1, n3, 3);
    graph.addEdge(n3, n2, 4);
    graph.addEdge(n2, n1);
    size_t val0 = 0;
    size_t val1 = 1;
    size_t val2 = 2;
    ASSERT_EQ(val2, n1->out_edges.size());
    ASSERT_EQ(val1, n2->out_edges.size());
    graph.removeEdge(n2, n1);
    ASSERT_EQ(val0, n2->out_edges.size());
    ASSERT_EQ(val2, n1->out_edges.size());
}

TEST(graph, removeEdgesFail)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("TACTTT");
    Graph<Sequence<DNA>> graph;
    Graph<Sequence<DNA>>::Node *n1 = graph.addNode(seq1);
    Graph<Sequence<DNA>>::Node *n2 = graph.addNode(seq2);
    Graph<Sequence<DNA>>::Node *n3 = graph.addNode(seq3);
    Graph<Sequence<DNA>>::Edge ed (n3, n1, 5);
    graph.addEdge(n1, n2, 2);
    graph.addEdge(n1, n3, 3);
    graph.addEdge(n3, n2, 4);
    graph.addEdge(n2, n1);
    size_t val2 = 2;
    graph.removeEdge(ed);
    ASSERT_EQ(val2, n1->out_edges.size());
    graph.removeEdge(n3, n1);
    ASSERT_EQ(val2, n1->out_edges.size());
}
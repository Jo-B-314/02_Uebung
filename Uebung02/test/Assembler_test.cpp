#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "../Sequence.h"
#include "../DNA.h"
#include "../Graph.h"
#include "../Assembler.h"

using namespace Alphabet;

TEST(Assembler, isValid)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Graph<Sequence<DNA>> graph;
    auto n1 = graph.addNode(seq1);
    auto n2 = graph.addNode(seq2);
    auto e = graph.addEdge(n1, n2);
    std::vector<Assembler::Seq> vec;
    vec.push_back(seq1);
    vec.push_back(seq2);
    Assembler::Assembler ass (vec);
    ASSERT_EQ(0, ass.isValid(e));
}

TEST(Assembler, isValid2)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("GCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("CATGAG");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("AATTCC");
    Graph<Sequence<DNA>> graph;
    auto n1 = graph.addNode(seq1);
    auto n2 = graph.addNode(seq2);
    auto n3 = graph.addNode(seq3);
    auto e = graph.addEdge(n1, n2);
    std::vector<Assembler::Seq> vec;
    vec.push_back(seq1);
    vec.push_back(seq2);
    Assembler::Assembler ass (vec);
    ass.getGraph().removeEdge(n1, n2);
    ASSERT_EQ(0, ass.isValid(e));
    ass.getGraph().removeEdge(n1, n3);
    ASSERT_EQ(0, ass.isValid(e));
}

TEST(Assembler, joinEdges)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("TCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("ATGAGC");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("AATCCT");
    Graph<Sequence<DNA>> graph;
    auto n1 = graph.addNode(seq1);
    auto n2 = graph.addNode(seq2);
    auto n3 = graph.addNode(seq3);
    graph.addEdge(n1, n2, 3);
    auto e2 = graph.addEdge(n3, n1, 1);
    std::vector<Assembler::Seq> vec;
    vec.push_back(seq1);
    vec.push_back(seq2);
    Assembler::Assembler ass (vec);
    ass.joinLargestEdge();
    ASSERT_EQ(0, ass.isValid(e2));
}

TEST(Assembler, assembleSeq)
{
    Sequence<DNA> seq1 = Sequence<DNA>::fromString("TCAATG");
    Sequence<DNA> seq2 = Sequence<DNA>::fromString("ATGAGC");
    Sequence<DNA> seq3 = Sequence<DNA>::fromString("AATCTC");
    Graph<Sequence<DNA>> graph;
    auto n1 = graph.addNode(seq1);
    auto n2 = graph.addNode(seq2);
    auto n3 = graph.addNode(seq3);
    graph.addEdge(n1, n2, 3);
    graph.addEdge(n3, n1, 2);
    std::vector<Assembler::Seq> vec;
    vec.push_back(seq1);
    vec.push_back(seq2);
    vec.push_back(seq3);
    Assembler::Assembler avengers (vec);
    auto str1 = avengers.assemble();
    std::string str = "AATCTCAATGAGC";
    ASSERT_EQ(0, str.compare(str1.toString()));
}
#ifndef BIOINFOI_GRAPH_H
#define BIOINFOI_GRAPH_H

#include <algorithm>
#include <list>
#include <memory>
#include <vector>
#include <iostream>

#include "Sequence.h"
/**
 * Generic implementation of a graph class.
 */
template <typename NodeLabel> class Graph
{
  public:

  	/**
  	 * Node class that contains a label 
  	 * and all outgoing edges. Ingoing
  	 * edges are not needed.
  	 */
	struct Node
	{
		explicit Node(const NodeLabel& l) : label(l), out_edges() {}
		NodeLabel label;
		std::vector<std::pair<Node*, size_t>> out_edges;
	};

	/**
  	 * Edge class that contains the 
  	 * source and target nodes as well as
  	 * a edge weight.
  	 */
	struct Edge
	{
		Edge(Node* a, Node* b, size_t w) : source(a), target(b), weight(w) {}
		Node* source;
		Node* target;
		size_t weight;
	};

	/**
	 * Defines how the data is stored internally.
	 *
	 * Can be changed if desired.
	 */
	using NodeContainer = std::list<Node>;
	using node_iterator = typename NodeContainer::iterator;
	using const_node_iterator = typename NodeContainer::const_iterator;

	/**
	 * Default constructor
	 */
	Graph() = default;

	/**
	 * Detailed constructor that also creates the nodes 
	 * of the Graph.
	 */
	explicit Graph(const std::vector<NodeLabel>& new_nodes){
        auto iter = new_nodes.begin();
        while (iter != new_nodes.end()) {
            addNode(*iter);
            iter++;
        }
    }

	/**
	 * Node iterators.
	 */
	node_iterator beginNodes() { return nodes_.begin(); }
	node_iterator endNodes() { return nodes_.end(); }

	const_node_iterator beginNodes() const { return nodes_.cbegin(); }
	const_node_iterator endNodes() const { return nodes_.cend(); }

	/**
	 * Creates a Node with a distict label and return a pointer to the new Node.
	 */
	Node* addNode(const NodeLabel& label) {
        Node node(label);
        nodes_.push_back(node);
        Node* nodep = &nodes_.back();
        return nodep;
    }

	/**
	 * Creates an edge and returns a copy of it.
	 */
	Edge addEdge(Node* n1, Node* n2, size_t weight = 0) {
        Edge edge(n1, n2, weight);
        auto pair = std::make_pair(n2, weight);
        auto iter = n1->out_edges.begin();
        while (iter != n1->out_edges.end()) {
            if (*iter == pair) { std::cout << "if"; return edge; }
            iter++;
        }
        n1->out_edges.push_back(pair);
        return edge;
    }

	/**
	 * Removes the given edge.
	 */
	void removeEdge(const Edge& e) {
        Node* node = e.source;
        //removes all pairs which are equal to (e.target, e.weight)
        remove(node->out_edges.begin(), node->out_edges.end(), std::make_pair(e.target, e.weight));
    }

	/**
	 * If the graph contains an edge betwenn n1 and n2,
	 * it is removed.
	 */
	void removeEdge(Node* n1, const Node* n2) {
        auto iter1 = n1->out_edges.begin();
        while (iter1 != n1->out_edges.end()) {
            auto pair = *iter1;
            if (pair.first == n2) { 
                n1->out_edges.erase(iter1);
                return;
            }
            iter1++;
        }
        auto iter2 = n2->out_edges.begin();
        while (iter2 != n2->out_edges.end()) {
            auto pair = *iter2;
            if (pair.first == n1) {
                n2->out_edges.erase(iter2);
                return;
            }
            iter2++;
        }
    }

	/**
	 * Performs an edge contraction. (see: Wikipedia)
	 */
	Node* contractEdge(const Edge& rem) {
        Node* n1 = rem.source;
        Node* n2 = rem.target;
    }

	/**
	 * Return the number of nodes in the graph.
	 */
	size_t numNodes() const {
        return nodes_.size();
    }

  private:
	NodeContainer nodes_;
};

#endif // BIOINFOI_GRAPH_H


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
            if (*iter == pair) { return edge; }
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
    }

	/**
	 * Performs an edge contraction. (see: Wikipedia)
	 */
	Node* contractEdge(const Edge& rem) {
        Node* n1 = rem.source;
        Node* n2 = rem.target;
        size_t overlap = n1->label.overlap(n2->label);
        NodeLabel new_label;
        for (size_t i = 0; i < n1->label.size() - overlap; i++) {
            new_label.push_back(n1->label[i]);
        }
        for (size_t i = 0; i < n2->label.size(); i++) {
            new_label.push_back(n2->label[i]);
        }
        Node* n12 = addNode(new_label);
        n12->out_edges = n1->out_edges;
        /*
         * all outgoing edges of n1 are also outgoing edges of n12
         * but we have to use addEdge for all the edges of n2 to make sure that we have no
         * edge twice in our storage
         */
        auto out_iter = n2->out_edges.begin();
        while (out_iter != n2->out_edges.end()) {
            addEdge(n12, out_iter->first, out_iter->second);
            out_iter++;
        }
        
        node_iterator node_iter = beginNodes();
        while (node_iter != endNodes()) {
            auto edge_iter = node_iter->out_edges.begin();
            while (edge_iter != node_iter->out_edges.end()) {
                Node* first = edge_iter->first;
                if (first == n1) {
                    /*
                     * looks a little bit strange but it was the fastest way to solve 
                     * the problem with the compiler
                     */
                    addEdge(&(*node_iter), n12, edge_iter->second);
                    removeEdge(&(*node_iter), first);
                    edge_iter = node_iter->out_edges.begin();
                    continue;
                }
                if (first == n2) {
                    removeEdge(&(*node_iter), first);
                    /*
                     * it's not very efficent but otherwise we get a segmentation fault
                     * but we should think again about this again
                     */
                    edge_iter = node_iter->out_edges.begin();
                    continue;
                }
                edge_iter++;
            }
            node_iter++;
        }
        node_iterator iterator = beginNodes();
        while (iterator != endNodes()) {
            if (&(*iterator) == n1 || &(*iterator) == n2) {
                node_iterator rem = iterator;
                iterator = nodes_.erase(rem);
                continue;
            }
            iterator++;
        }
        return n12;
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


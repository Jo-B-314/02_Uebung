#ifndef BIOINFOI_GRAPH_H
#define BIOINFOI_GRAPH_H

#include <algorithm>
#include <list>
#include <memory>
#include <vector>

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
		explicit Node(const NodeLabel& l) : label(l) {}
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
	 * od the Graph.
	 */
	explicit Graph(const std::vector<NodeLabel>& new_nodes);

	/**
	 * Node iterators.
	 */
	node_iterator beginNodes();
	node_iterator endNodes();

	const_node_iterator beginNodes() const;
	const_node_iterator endNodes() const;

	/**
	 * Creates a Node with a distict label and return a pointer to the new Node.
	 */
	Node* addNode(const NodeLabel& label);

	/**
	 * Creates an edge and returns a copy of it.
	 */
	Edge addEdge(Node* n1, Node* n2, size_t weight = 0);

	/**
	 * Removes the given edge.
	 */
	void removeEdge(const Edge& e);

	/**
	 * If the graph contains an edge betwenn n1 and n2,
	 * it is removed.
	 */
	void removeEdge(Node* n1, const Node* n2);

	/**
	 * Performs an edge contraction. (see: Wikipedia)
	 */
	Node* contractEdge(const Edge& rem);

	/**
	 * Return the number of nodes in the graph.
	 */
	size_t numNodes() const;

  private:
	NodeContainer nodes_;
};

#endif // BIOINFOI_GRAPH_H


#pragma once
#include<list>
#include<iostream>
using std::ostream;

template<typename T>class Graph;

template<typename T>
class GraphNode
{
	friend class Graph<T>;

public:
	GraphNode(T val);

	~GraphNode();
	//the adjacency list of current vertex 'u' contains pairs 
	//of adjacency vertex 'v' and weight of edge (u, v)
	std::list<std::pair<GraphNode<T>*, int>> adjacency;
	void addToList(std::pair<GraphNode<T>*, int>);
	
private:
	GraphNode<T> *parent;
	T key;
	int weight;
	T getKey() { return key; }
	bool isInHeap;
};

template<typename T>
GraphNode<T>::GraphNode(T val)
	:parent(nullptr), key(val), weight(INT32_MAX), isInHeap(false)
{}

template<typename T>
GraphNode<T>::~GraphNode()
{}

template<typename T>
void GraphNode<T>::addToList(std::pair<GraphNode<T>*, int> p)
{
	adjacency.push_back(p);
}



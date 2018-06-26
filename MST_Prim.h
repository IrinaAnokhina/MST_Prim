//This implementation of Prim`s algorithm uses a heap
#pragma once
#include<iostream>
using std::ostream;
using std::cout;
using std::cin;
#include<iterator>
#include<vector>
#include"GraphNode.h"

template<typename T>
class Graph
{
public:
	Graph() {};
	~Graph();
	void addNode(T);
	void printGraph() const;
	void printAdj() const;
	void createAdj();
	void MST_Prim();
private:
	std::vector<GraphNode<T>*>my_graph;
	std::vector<GraphNode<T>**> heap;
	void makeHeap();
	void heapDecreaseKey(int i);
	//this function was replaced by isInHeap bit 
	//in Graphnode.h and not used now
	bool isInHeap(GraphNode<T>**);
	GraphNode<T>** heap_extract_Min();
	int Left(int i)
	{
		return 2 * i + 1;
	}

	int Right(int i)
	{
		return 2 * i + 2;
	}
	int Parent(int i)
	{
		return (i + 1) / 2 - 1;
	}
	void Min_Heapify(int);
	//search in the my_graph
	GraphNode<T>* search(T);
	//search index in the heap
	int searchIndex(T);
};

template<typename T>
Graph<T>::~Graph()
{
	if (!my_graph.empty())
	{
		auto j = my_graph.begin();
		while (j != my_graph.end())
		{
			auto temp = j;
			++j;
			delete *temp;
		}
	}
}

template<typename T>
void Graph<T>::addNode(T key)
{
	GraphNode<T> *newNode = new GraphNode<T>(key);
	my_graph.push_back(newNode);
}

template<typename T>
void Graph<T>::printGraph() const
{
	if (!(my_graph.empty()))
	{
		for (auto j : my_graph)
			cout << j->getKey() << " ";
		std::cout << std::endl;
	}
}

template<typename T>
void Graph<T>::printAdj() const
{
	if (!(my_graph.empty()))
	{
		for (auto j : my_graph)
		{
			cout << j->getKey();
			for (auto i : j->adjacency)
				cout << " -> " << i.first->getKey();
			cout << std::endl;
		}

	}
}

template<typename T>
GraphNode<T>* Graph<T>::search(T val)
{
	if (!my_graph.empty())
	{
		for (auto j : my_graph)
		{
			if (j->getKey() == val)
				return j;
		}
	}
	return nullptr;
}

template<typename T>
int Graph<T>::searchIndex(T val)
{
	if (!heap.empty())
	{
		for (size_t j = 0;j < heap.size();++j)
		{
			if (((*heap[j])->getKey()) == val)
				return j;
		}
	}
	return -1;
}

template<typename T>
void Graph<T>::createAdj()
{
	T val{};
	if (!(my_graph.empty()))
	{
		for (auto j : my_graph)
		{
			val = 0;
			cout << "Enter adjacency vertexes for vertex " << j->getKey() << ":\n";
			while (val != '@')
			{
		        cin >> val;
				GraphNode<T>* found = search(val);
				if (found != nullptr)
				{
					cout << "Enter the weight of the edge(" << j->getKey() << ", " << val << ") :";
					int weight;
					cin >> weight;
					j->addToList(std::make_pair(found, weight));
				}
			}
		}
	}
}

template<typename T>
void Graph<T>::Min_Heapify(int i)
{
	int min = 0;
	unsigned int l = Left(i);
	unsigned int r = Right(i);

	if (l < heap.size() && ((*heap[l])->weight) < ((*heap[i])->weight))
		min = l;
	else
		min = i;
	if (r < heap.size() && ((*heap[r])->weight) < ((*heap[min])->weight))
		min = r;
	if (min != i)
	{
		std::swap(heap[i], heap[min]);
		Min_Heapify(min);
	}
}

template<typename T>
GraphNode<T>** Graph<T>::heap_extract_Min()
{
	if (heap.empty())
		std::cout << "Error! The queue is empty!" << std::endl;
	GraphNode<T>** min = heap[0];
	heap[0] = heap.back();
	heap.pop_back();
	Min_Heapify(0);
	((*min)->isInHeap) = false;
	return min;
}

template<typename T>
void Graph<T>::heapDecreaseKey(int i)
{
	while (i > 0 && ((*heap[Parent(i)])->weight) > ((*heap[i])->weight))
	{
		std::swap(heap[i], heap[Parent(i)]);
		i = Parent(i);
	}
}

template<typename T>
void Graph<T>::makeHeap()
{
	for (size_t j = 0; j < my_graph.size(); ++j)
	{
		GraphNode<T>**ptr = &my_graph[j];
		heap.push_back(ptr);
		((*ptr)->isInHeap) = true;
	}
	for (size_t i = heap.size() / 2; i --> 0;)
		Min_Heapify(i);
}

template<typename T>
void Graph<T>::MST_Prim()
{
	GraphNode<T> *root = *(my_graph.begin());
root->weight = 0;
makeHeap();
while (!heap.empty())
{
	GraphNode<T>**node = heap_extract_Min();
	cout << (*node)->getKey() << " ";
	for(auto j : (*node)->adjacency)
		//if (isInHeap(&(j.first)) && j.second < j.first->weight)
		//isInHeap function was replaced by bool isInHeap in GraphNode.h
		//to minimize time overheads
		if(j.first->isInHeap && (j.second < j.first->weight))
			//if (weight of edge < weight of vertex)
		{
			j.first->parent = *node;
			//assign the weight of edge to the weight of vertex
			j.first->weight = j.second;
			int index = searchIndex(j.first->getKey());
			heapDecreaseKey(index);
		}
}
}
//not used
template<typename T>
bool Graph<T>::isInHeap( GraphNode<T>**ptr)
{
	for (auto j : heap)
		if ((*ptr)->getKey() == (*j)->getKey())
			return true;
	return false;
}


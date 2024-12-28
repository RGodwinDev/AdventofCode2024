#pragma once
#include "Day18Vertex.h"

class Day18Graph {
private:

public:
	Day18Graph();
	void add_vertex(Day18Vertex v);
	void add_directed_edge(Day18Vertex from, Day18Vertex to, int weight);
	void add_undirected_edge(Day18Vertex from, Day18Vertex to, int weight);
};
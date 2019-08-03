/* 
 * File: graph.h
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 4
 * Purpose: Weighted undirected graph, minimum spanning tree
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// Enum of colors to determine discovery status of vertices
enum 
{
    WHITE, 
    GRAY, 
    BLACK
} color;

// Nodes containing the vertices of adjacency list
typedef struct adjListNode {
    int vertex;
    int weight;
    int color;
    struct adjListNode* next;
    
} adjListNode;

adjListNode *adjListNodeArray[];

// Adjacency list of each vertex 
typedef struct adjList {
    adjListNode* head;
} adjList;

// Graph array of each adjacency list
typedef struct graph { 
    int vertices;
    adjList* lists;
} graph;

//  Edge between vertices
typedef struct edge{
    int vertexU;
    int vertexV;
    int weight;
    int color;
} edge;

// Creates a node of the vertex
adjListNode* createNode(int vertex, int weight, int color); 
// Creates an array graph of the adjacency lists 
graph* createGraph(int vertices); 
// Creates an edge between source vertex and destination vertex - undirected graph
void addEdge(int src, int dst, int weight, int color);
// Prints graph array
void printGraph(graph *graph);
// Perform depth first search to determine if graph is connected
void DFS(adjListNode *adjListNodeArray[], int vertex);
// Creates an array edge from adjListNodeArray
void copyEdges(edge edge[], adjListNode *adjListNodeArray[], graph *graph);
// Exchange elements between edge array
void swap(edge edge[], int i, int j);
// Implemented by quicksort to rearrange edge array subsets
int partition(edge edge[], int start, int edges);
// Sorts edge array by ascending weight
void quicksort(edge edge[], int start, int edges);
// Find parent subset of vertex
int find(int parent[], int vertex);
// Connect subsets to parent subset
void Union(int parent[], int x, int y);
// Create parent subset of graph array
void makeSet(int parent[], graph *graph);
// Creates a minimum spanning tree
int kruskal(adjListNode *adjListNodeArray[], int edges, graph *graph, int *startArray, int *endArray, int *weightArray);
// Free memory of the graph, adjLists, and adjListNodes
void freeGraph(adjListNode *adjListNodeArray[], graph *graph);
#endif


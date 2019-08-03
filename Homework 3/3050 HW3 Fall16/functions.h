/* 
 * File: functions.h
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 3
 * Purpose: Adjacency, DFS, and topological sort
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

// Nodes containing the vertices of adjacency list
typedef struct adjListNode {
    int vertex;
    struct adjListNode* next;
} adjListNode;

// The adjacency list of each vertex 
typedef struct adjList {
    adjListNode* head;
} adjList;

// Graph array of each adjacency list
typedef struct graph { 
    int vertices;
    adjList* lists;
} graph;

// Creates a new adjListNode for vertex value
adjListNode* createNode(int vertex); 
// Creates an array of the adjLists 
graph* createGraph(int vertices); 
// Determines the number of edges the graph contains
int countEdges(const char *filename);
// Creates the edges from the source vertex to the destination vertex
int createEdge(graph* graph, int src, int dst);
// Add vertices to their respective adjListNode
adjListNode* add(adjListNode* head, int num);
// Makes adjLists in ascending order so the lesser vertices are read first
void reverse(adjListNode** head);
// performs DFS to determine edges and run times of vertices
int dfsEdges(adjListNode *list[], int vertex, int *visited, int *startTime, int *endTime);
// Free memory of the graph, adjLists, and adjListNodes
void freeGraph(graph* graph);
#endif /* FUNCTIONS_H */


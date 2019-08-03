/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.c
 * Author: bruce
 *
 * Created on November 11, 2016, 12:39 PM
 */

#include "graph.h"

adjListNode* createNode(int vertex) 
{
    adjListNode* newNode = malloc(sizeof(adjListNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    
    return newNode;
}

graph* createGraph(int vertices) 
{    
    int i = 0;
    graph* newGraph = malloc(sizeof(graph));
    newGraph->vertices = vertices;
    newGraph->lists = malloc(sizeof(adjList) * vertices);
    
    // Creates adjLists
    for(i = 0; i < vertices; i++) 
    {
        newGraph->lists[i].head = NULL;
    }
    
    return newGraph;
}

void addEdge(graph *graph, int src, int dest)
{
    /* Add an edge from src to dst in the adjacency list*/
    adjListNode *newNode = createNode(dest);
    newNode->next = graph->lists[src].head;
    graph->lists[src].head = newNode;
 
    
    /* Add an edge from dest to src also*/
    newNode = createNode(src);
    newNode->next = graph->lists[dest].head;
    graph->lists[dest].head = newNode;
}

void printGraph(graph *graph)
{
    int i = 1;
    printf("\nAdjacency List:\n");
    for (i = 1; i <= graph->vertices; i++) 
    {
        adjListNode *temp = graph->lists[i].head;
        printf("adjacency list of vertex (%d) = ", i);
        while (temp != NULL) 
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
 
            printf("NULL\n");
    }
}

void reverse(adjListNode** head)
{
    adjListNode* prev = NULL;
    adjListNode* current = *head;
    adjListNode* next = NULL;
    
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    
    *head = prev;
}
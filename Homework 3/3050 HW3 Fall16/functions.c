/* 
 * File: functions.c
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 3
 * Purpose: Adjacency, DFS, and topological sort
 */

#include "functions.h"

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

// count newline characters of file starting from 0 so the total vertices are omitted
int countEdges(const char *filename)
{
    char ch;
    int edges = 0;
    FILE *inputFp = fopen(filename, "r");

    while(!feof(inputFp))
    {
        ch = fgetc(inputFp);
        
        if(ch == '\n')
        {
            edges++;
        }
    }
    fclose(inputFp);
  
    return edges;
}

// Creates edges from source to destination in order to create a directed graph
int createEdge(graph* graph, int src, int vertex) 
{
    adjListNode* newNode = createNode(vertex);
    newNode->next = graph->lists[src-1].head;
    graph->lists[src-1].head = newNode;
}

adjListNode* add(adjListNode* head, int num)
{
    adjListNode* i = (adjListNode *)malloc(sizeof(adjListNode));
    
    i->vertex = num;
    i->next = head;
    
    return i;
}

// adjLists are read out in ascending order so the lesser vertex is chosen first
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

// DFS is utilized in order to find running times and to determine whether graph is cyclic or acyclic
int dfsEdges(adjListNode *list[], int vertex, int *visited, int *startTime, int *endTime)
{
    // initialize run time statically at 1 so it does not reset during recursion
    static int time = 1;
    visited[vertex] = 1;
    startTime[vertex]=time++;
    adjListNode *temp = list[vertex];
        
    while(temp!=NULL)
    {
        if(visited[temp->vertex] != 1)
	{
            dfsEdges(list,temp->vertex,visited,startTime,endTime);
	}
	else
	{
            // Cycle detection: if the timestamp is -1 then that determines a back edge
            if(endTime[temp->vertex] == -1)
            {
                printf("(%d,%d) is a back edge\n", vertex, temp->vertex);
                // Return the endTime in order to verify the graph is cyclic
                return endTime[temp->vertex];
            }
            else
            {
                if(vertex < startTime[temp->vertex])
                {
                    // startTime of vertexU is less than vertexV determines forward edge
                    printf("(%d,%d) is a forward edge\n",vertex, temp->vertex);
                }
                else
                {
                    // startTime of vertexU is greater than vertexV determines cross edge
                    printf("(%d,%d) is a cross edge\n", vertex, temp->vertex);
                }
            }
	}
		
        temp=temp->next;
	}
        
    endTime[vertex]=time++;
}

// Free memory
void freeGraph(graph* graph)
{
    if(graph)
    {
        if(graph->lists)
        {
            int v;
            // Free adjListNodes
            for (v = 0; v < graph->vertices; v++)
            {
                adjListNode* adjListPtr = graph->lists[v].head;
                while (adjListPtr)
                {
                    adjListNode* tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            //Free adjLists
            free(graph->lists);
        }
        // Free graph
        free(graph);
    }
}
/* 
 * File: graph.c
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 4
 * Purpose: Weighted undirected graph, minimum spanning tree
 */

#include "graph.h"

// Function explained in graph.h
adjListNode* createNode(int vertex, int weight, int color) 
{
    adjListNode* newNode = malloc(sizeof(adjListNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    newNode->weight = weight;
    newNode->color = color;
    
    return newNode;
}

// Function explained in graph.h
graph* createGraph(int vertices) 
{    
    int i = 0;
    
    graph* newGraph = malloc(sizeof(graph));
    newGraph->vertices = vertices;
    newGraph->lists = malloc(sizeof(adjList) * vertices);
    
    for(i = 0; i < vertices; i++) 
    {
        newGraph->lists[i].head = NULL;
    }
    
    return newGraph;
}

// Function explained in graph.h
void addEdge(int src, int dst, int weight, int color)
{ 
    adjListNode *temp = adjListNodeArray[src];
    
    if(temp == NULL)
    {
        adjListNodeArray[src] = createNode(dst, weight, color);
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        
        temp->next = createNode(dst, weight, color);
    }
}

// Function explained in graph.h
void printGraph(graph *graph)
{
    int i;
    
    for (i = 1; i <= graph->vertices; i++)
    {
        adjListNode* temp = adjListNodeArray[i];
        printf("Adjacency list of vertex ");
        while(temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;       

        }            

        printf("NULL\n");        
    }
}

void DFS(adjListNode *adjListNodeArray[], int vertex)
{
    // Vertex is partially discovered; neighbors are not yet discovered
    adjListNodeArray[vertex]->color = GRAY;

    adjListNode *temp = adjListNodeArray[vertex];
    // Traverse adjacency list of vertex while adjacencay list != NULL
    while(temp)
    {   
        // If vertices of adjacency list are undiscovered
        if(adjListNodeArray[temp->vertex]->color == WHITE)
        {
            // Update discovery status of adjaceny list vertices
            DFS(adjListNodeArray, temp->vertex);
        }            
            
        temp = temp->next;
    }
    // Vertex is fully discovered; neighbors are also discovered
    adjListNodeArray[vertex]->color = BLACK;
}

// Function explained in graph.h
void copyEdges(edge edge[], adjListNode *adjListNodeArray[], graph *graph)
{
    int i = 0, j = 0;
    for(i = 1; i <= graph->vertices; i++)
    {
        adjListNode *u = adjListNodeArray[i];
        if(u)
        {
            adjListNode *v = u->next;
            while(v)
            {
                edge[j].vertexU =  u->vertex;
                edge[j].vertexV = v->vertex;
                edge[j].weight = v->weight;
                edge[j].color = u->color;
                j++;                
                v = v->next;
            }
        }
    }
}

void swap(edge edge[], int i, int j)
{
    // Store edge[i] elements in temp variables
    int vertexUTemp = edge[i].vertexU;
    int vertexVTemp = edge[i].vertexV;
    int weightTemp = edge[i].weight;
    
    // Set edge[i] elements to edge[j] elements
    edge[i].vertexU  = edge[j].vertexU ;
    edge[i].vertexV  = edge[j].vertexV ;
    edge[i].weight  = edge[j].weight;
    // Set edge[j] elements to temp variables (edge[i])
    edge[j].vertexU  = vertexUTemp;
    edge[j].vertexV  = vertexVTemp;
    edge[j].weight  = weightTemp;
}

int partition(edge edge[], int vertexU, int edges){
    int i = 0, j = 0;
    // Initialize pivot variable to weight element
    int pivot =  edge[vertexU].weight;
    // left to right index
    i = vertexU + 1;
    // right to left index
    j = edges;
    // 
    while(i <= j)
    {
        // Look for first element greater than the pivot from the left
        while(i <= edges && edge[i].weight < pivot)
        {
            i++;
        }
        // Look for first element not greater than the pivot from the right
        while(j>vertexU && edge[j].weight >= pivot)
        {
            j--;
        }
        // Swap elements if left is less than the right
        if(i < j)
        {
            swap(edge, i, j);
        }
    }
    // Swap last element in the left partition with the pivot    
    if(j > vertexU)
    {
        swap(edge, vertexU, j);
    }
    
    return j;
}

void quicksort(edge edge[], int vertexU, int edges)
{
    if(vertexU >= edges) 
    {
        return;
    }
    
    // Store partition in pivot variable
    int pivot = partition(edge, vertexU, edges);
    
    // Quicksort left partition
    quicksort(edge, vertexU, pivot);
    // Quicksort right partition
    quicksort(edge, pivot+1, edges);
}

int find(int parent[], int vertex)
{
    if(parent[vertex] == -1)
    {
        return vertex;
    }
    else
    {
        // Find parent of vertex, and update vertices 
        find(parent, parent[vertex]);
    }
}
 
void Union(int parent[], int x, int y)
{ 
    // Initialize subsets
    int xset = find(parent, x);
    int yset = find(parent, y);
    // Update subsets
    parent[xset] = yset;
}
 
void makeSet(int parent[], graph *graph)
{
    int i = 0;
    // Create parent subset for each vertex
    for(i=0; i<= graph->vertices; i++)
    {
        parent[i] = -1;
    }
}

int kruskal(adjListNode * adjListNodeArray[], int edges, graph *graph, int *vertexUArray, int *vertexVArray, int *weightArray){
 
    // Initialize variables
    int i = 0, mstCount = 0, weight = 0;
 
    edge mst[edges];
    edge edge[edges];
    
    copyEdges(edge, adjListNodeArray, graph);
////    
    //DEBUG:
    // Print the copy of edges
    printf("-------------------------------------------------------------");
    printf("\nCopyEdges Function\n");
    printf("(Copies edge to an array to be sorted)\n");
    
    for(i = 0; i < edges; i++)
    {
        printf("Edge: (%d,%d) | weight = %d\n", edge[i].vertexU, edge[i].vertexV, edge[i].weight);
    }
////
    quicksort(edge, 0, edges-1);
////
    //DEBUG:
    // Print the sorted copy of edges by ascending weight
    printf("-------------------------------------------------------------");
    printf("\nQuicksort Function\n");
    printf("(Sorts CopyEdge array by weight)\n");
    
    for(i = 0; i < edges; i++)
    {
        printf("Edge: (%d,%d) | weight = %d\n", edge[i].vertexU, edge[i].vertexV, edge[i].weight);
    }
////
    int parent[graph->vertices + 1];
    makeSet(parent, graph);
    
    for(i = 0; i < edges; i++)
    {
        // Check if edge creates cycle in the tree; if not add edge to the MST
        if(find(parent, edge[i].vertexU) != find(parent, edge[i].vertexV))
        {
            Union(parent, edge[i].vertexU, edge[i].vertexV);
            mst[mstCount++] = edge[i];
            weight += edge[i].weight;
        }
    }

////
    //DEBUG:
    // Print the minimum spanning tree
    printf("-------------------------------------------------------------");
    printf("\nKruskal's Algorithm\n");
    printf("(minimum spanning tree)\n");
////    
    for(i = 0; i < mstCount; i++)
    {
////
        //DEBUG:
        printf("Edge: (%d,%d) | weight = %d\n", mst[i].vertexU, mst[i].vertexV, mst[i].weight);
////        
        vertexUArray[i] = mst[i].vertexU;
        vertexVArray[i] = mst[i].vertexV;
        weightArray[i] = mst[i].weight;
    }
    
    return mstCount;
}

void freeGraph(adjListNode *adjListNodeArray[], graph* graph)
{
    if(graph)
    {
        if(graph->lists)
        {
            int i;
            // Free adjacency lists nodes Array
            for (i = 0; i < graph->vertices; i++)
            {
                adjListNode* adjListPtr = adjListNodeArray[i];
                while (adjListPtr)
                {
                    adjListNode* temp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(temp);
                }
            }
            // Free adjacency lists
            free(graph->lists);
        }
        // Free graph
        free(graph);
    }
}
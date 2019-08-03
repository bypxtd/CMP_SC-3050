/* 
 * File: main.c
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 3
 * Purpose: Adjacency, DFS, and topological sort
 */

#include "input_error.h"
#include "functions.h"

int main(int argc, char** argv) 
{
    // Initialize variables
    int i = 0, vertices = 0, count = 0, vertexU = 0, vertexV = 0, j = 0, temp = 0, index = 0;
    // Read in two files in command line, input and output files respectively
    FILE* inputFp = fopen(argv[1], "r");
    FILE* outputFp = fopen(argv[2], "w");
    
    if(argc != 3) 
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    else
    {
        if(inputFp == NULL || outputFp == NULL) 
        {
            exit(FILE_FAILED_TO_OPEN);
        }
        else
        {
            // Read in the total number of vertices from the input file
            fscanf(inputFp, "%d\n", &vertices);
            // Create graph array of adjLists of vertices
            graph* g = createGraph(vertices);
    
            // initialize arrays for topological sorting later
            int array[vertices], ind[vertices], num[vertices];
            // Array size is made (vertices + 1) to use the array as 1-indexed
            graph* adjList[vertices + 1];
            // Initialize array
            for (i = 0; i <= vertices; i++)
            {
                adjList[i] = NULL;
            }
    
            // Call countEdges to determine total number of edges within the graph
            printf("Edges: %d\n",countEdges(argv[1]));
            // Create edges from vertexU to vertexV based on the number of edges
            for(i = 0; i < countEdges(argv[1]); i++)
            {   
                count = fscanf(inputFp, "(%d,%d)\n", &vertexU, &vertexV);  
                if(vertexU > vertices || vertexV > vertices)
                {
                    exit(INTEGER_IS_NOT_A_VERTEX);
                }
                if(count == 0) 
                {
                    exit(PARSING_ERROR_EMPTY_FILE);
                }    
                else if(count != 2) 
                {
                    exit(PARSING_ERROR_INVALID_FORMAT);
                }
                count++;

                // Creates edges of the graph array
                createEdge(g, vertexU, vertexV);
                // Add vertices onto their adjLists
                adjList[vertexU] = add(adjList[vertexU], vertexV);
            }
            // Make adjLists in ascending order in order to determine runtime properly
            for(i = 0; i < vertices; i++)
            {
                reverse(&adjList[i]);
            }
    
            // Print adjList after calling reverse function so it is in ascending order
            printf("\nAdjacency List:\n");
            for (i = 1; i <= vertices; i++) 
            {
                adjListNode *temp = adjList[i];
                printf("adjacency list of vertex (%d) -> ", i);
                while (temp != NULL) 
                {
                    printf("%d -> ", temp->vertex);
                    temp = temp->next;
                }
 
                printf("NULL\n");
            }
    
            printf("\nDFS:\n");
            // Initialize variables in respect to the DFS function
            int *visited = (int*)malloc(vertices * sizeof(int));
            int *startTime = (int*)malloc(vertices * sizeof(int));
            int *endTime = (int*)malloc(vertices * sizeof(int)); 
            int *parent = (int*)malloc(vertices * sizeof(int)); 
        
            // Determines timestamps of the DFS function
            for(i = 1; i <= vertices; i++)
            {
                startTime[i] = -1;
            }
            for(i = 1; i <= vertices; i++)
            {
                visited[i] = 0;
            }
            for(i = 1; i <= vertices; i++)
            { 
                endTime[i] = -1;
            }
            for(i = 1; i <= vertices; i++)
            {
                if(visited[i]!=1)
                {
                    dfsEdges(adjList, i, visited, startTime, endTime);
                }
            }
 
            // Print vertices and their respective start & end times after performing DFS of the directed graph
            printf("\nRun Time:\n");
            for(i = 1; i <= vertices; i++)
            {
                printf("vertex (%d) = [%d, %d]\n", i, startTime[i], endTime[i]);
            }
            // Print topological sorting of the directed graph (Greatest end time to least end time)
            printf("\nTopological Sort:");
            // Store endTime in two arrays, one for the elements and one for the indices
            for(i = 1; i <= vertices; i++)
            {
                array[i] = endTime[i];
                ind[i] = endTime[i];
                // printf("%d ", endTime[i]); // check for -1 endTime
                // Cycle detection: if there is an endTime of -1 then the graph is cyclic
                if(endTime[i] == -1)
                {
                    endTime[temp] = -1;
                    printf("\n");
                }
            }
            // If graph is cycle, write 0 to the output file
            if(endTime[temp] == -1)
            {
                printf("This graph is cyclic\n");            
                fprintf(outputFp, "%d\r\n", 0);
            }
            // Otherwise, sort the array of elements in order to determine their index and write the topological sort the the output file
            else
            {
                // Swaps elements around by endTime in descending order
                for(i = 1; i <= vertices; i++)
                {
                    for(j = i+1; j <= vertices; j++)
                    {
                        if(array[i] < array[j])
                        {
                            temp = array[i];
                            array[i] = array[j];
                            array[j] = temp;
                        }
                    }
                }
                // Print the sorted array of elements
                printf("\nSorted array of elements\n");
                for(i = 1; i <= vertices; i++)
                {
                    printf("%d > ", array[i]);
                }
                printf("NULL");
                
                // Print the index of the sorted array of elements
                printf("\nSorted index of array of elements\n");
                for(i = 1; i <= vertices; i++)
                {            
                    // Set index to 0 and increment index until element of ind[index] equals element of array[i]
                    index = 0;
                    while(ind[index] != array[i])
                    {
                        index++;
                        // Store index in a new array, increment i for the next element and set the index to 0 again then repeat
                        if(ind[index] == array[i])
                        {
                            num[i] = index;
                        }               
                    } 
       
                    printf("%d > ", num[i]);
                    fprintf(outputFp, "%d\r\n", num[i]);
                }
                printf("NULL");
            }
        
            // Call freeGraph to free memory of graph
            freeGraph(g); 
        }
    }
    
    if(fclose(inputFp) != 0 || fclose(outputFp) != 0) 
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    
    exit(EXIT_SUCCESS);
}

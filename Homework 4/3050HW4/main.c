/* 
 * File: main.c
 * Author: bruce yoshi phommaly
 * Pawprint: Bypxtd
 * Assignment: Computer Science 3050 Homework 4
 * Purpose: Weighted undirected graph, minimum spanning tree
 */

#include "input_error.h"
#include "graph.h"

int main(int argc, char** argv) 
{
    // Initialize variables
    // General variables
    int i = 0, j = 0, k = 0;
    // Vertex variables
    int vertices = 0, vertexU = 0, vertexV = 0, weight = 0, connectedComponents = 0;
    // Parse variables
    int linelen = 0, c = 0;
    int lineCount = 1;
    char* line = NULL;
    char **endptr=NULL; 
    size_t nbytes = 0;
    // Array pointer variables
    int *vertexUArray = NULL;
    int *vertexVArray = NULL;
    int *weightArray = NULL;
    
    // Open the input file
    FILE* inputFp = fopen(argv[1], "r");
    // Open the output file
    FILE* outputFp = fopen(argv[2], "w");
    // Checks the number of arguments
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
////////////// -----------------------------------------------------------
//////////////   Parse Function is mainly from the homework 3 solution
//////////////   Modified only slightly for the purpose of this homework
////////////// -----------------------------------------------------------
            c = fgetc(inputFp);
            if (c == EOF)
            {
                exit(PARSING_ERROR_EMPTY_FILE);
            }
            else
            {
                ungetc(c,inputFp);
                // Read the number of vertices. 
                linelen = getline(&line, &nbytes, inputFp);
                
                // EmptyLine
                if (linelen == -1) 
                {
                    exit(PARSING_ERROR_INVALID_FORMAT);
                }
                else
                {
                    // Removing the newline and adding the NULL character
                    line[linelen - 1] = '\0';
    
                    // Check that everything on the line is a digit
                    j = 1;
                    while (j < linelen - 1)
                    {
                        if (isdigit(line[j++])==0)
                        {
                            exit(PARSING_ERROR_INVALID_FORMAT);
                        }
                    }
                    // Compute the number of vertices
                    vertices = strtoumax(line,endptr,0);
    
                    // Check that number of vertices are > 0
                    if (vertices==0)
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                }
////////////    
                //DEBUG:
                printf("Parse Function\n");
                printf("Line number: %d | Vertices = %d\n", lineCount, vertices);
////////////      
                // Initialize graph array
                graph *g = createGraph(vertices);
                // Initialize adjacency list node array
                for(i = 1; i <= vertices; i++)
                {
                    adjListNodeArray[i] = (createNode(i,0, WHITE));
                }        

                // Read in the edges
                while ((linelen=getline(&line, &nbytes, inputFp)) != -1)
                {
                    lineCount++;
                    line[linelen-1] = '\0'; //removing the newline and adding the NULL character
////////////////                    
                    //DEBUG: 
                    //printf("%s\n", line);
////////////////        
                    //First character has to be a (
                    if (line[0] != '(')
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    //Second character is a digit
                    j = 1;
                    if (isdigit(line[j++])==0)
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    //Third character is a digit
                    j = 3;
                    if (isdigit(line[j++])==0)
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    // Check that everything before a , is a digit
                    while ((j < linelen - 1) && (line[j] != ','))
                    {
                        if (isdigit(line[j++])==0)
                        {
                            exit(PARSING_ERROR_INVALID_FORMAT);
                        }
                    }
                    
                    //This is the starting point of the edge
                    vertexU=strtoumax(&line[1],endptr,0);
        
                    //Check that the starting point is a legitimate vertex
                    if ((vertexU>vertices) || (vertexU==0))
                    {
                        exit(INTEGER_IS_NOT_A_VERTEX);
                    }
         
                    k=++j;
        
                    //Check if you reached the end of line and if the charatcer after the , is a digit
                    if (isdigit(line[j++])==0)
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    // Check that everything before a ) is a digit
                    while ((j< linelen -1) && line[j] != ')')
                    {
                        if (isdigit(line[j++])==0)
                        {
                            exit(PARSING_ERROR_INVALID_FORMAT);
                        }
                    }
        
                    // Check if there is a )
                    if (line[j] != ')')
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    //Check that the line ends at )
                    if (line[j+1]!='\0')
                    {
                        exit(PARSING_ERROR_INVALID_FORMAT);
                    }
                    //This is the starting point of the edge
                    vertexV=strtoumax( &line[3],endptr,0);
                    weight=strtoumax( &line[k],endptr,0);
       
                    //Check that the starting point is a legitimate vertex
                    if ((vertexV>vertices)||(vertexV==0))
                    {
                        exit(INTEGER_IS_NOT_A_VERTEX);
                    }
////////////////                    
                    //DEBUG: 
                    printf("Line number: %d | Edge: (%d,%d) | weight = %d\n", lineCount, vertexU, vertexV, weight);                    
////////////////       
                    // Creates edges to establish undirected graph
                    addEdge(vertexU,vertexV, weight, color);
                }
////////////
                //DEBUG:
                printf("Edges = %d\n", (lineCount - 1));
                printf("-------------------------------------------------------------");
                printf("\nPrintGraph Function\n");
                printf("(Graph is undirected but is displayed as directed -- REWORK)\n");
                printGraph(g);
                printf("-------------------------------------------------------------");
////////////                
                // Traverses vertices to determine graph connectivity
                for (i = 1; i <= vertices; i++)
                {                        
                    // Check undiscovered vertices to determine connected components
                    if(adjListNodeArray[i]->color == WHITE)
                    {
                        // Updates discovery status of vertices connected to adjListNodeArray[i] through traversal
                        DFS(adjListNodeArray, i);
                        connectedComponents++;
                    }
                }
////////////
                //DEBUG:
                printf("\nDFS Function");
                printf("\n(Graph is connected if connected components = 1)");
                printf("\nConnected components = %d\n", connectedComponents);
////////////                         
                // malloc space for arrays 
                vertexUArray = malloc(sizeof(int) * (vertices));
                vertexVArray = malloc(sizeof(int) * (vertices));
                weightArray = malloc(sizeof(int) * (vertices));
            
                // Unconnected graph
                if(connectedComponents != 1)
                {
                    printf("-------------------------------------------------------------");                  
                    printf("\nConnected components != 1 so graph is UNCONNECTED\n");
                    // Write 0 (newline) to output file
                    fprintf(outputFp, "%d\n", 0);
                }
                // Connected graph
                else
                {   
////////////////
                    //DEBUG:
                    printf("-------------------------------------------------------------");
                    printf("\nConnected components = 1 so graph is CONNECTED\n");
////////////////                    
                    // Initialize number of minimum spanning tree edges
                    int mstCount = kruskal(adjListNodeArray, (lineCount - 1), g, vertexUArray, vertexVArray, weightArray);
////////////////
                    //DEBUG:                    
                    printf("\nTransfer of minimum spanning tree to Main.C\n");
                    printf("(Moved MST to Main.C in order to write to output file)\n");                 
////////////////                    
                    for(i = 0; i < mstCount; i++)
                    {
//////////////////
                        //DEBUG:
                        //printf("Edge: (%d,%d) | weight = %d\n", vertexUArray[i], vertexVArray[i], weightArray[i]);
//////////////////                        
                        // Write minimum spanning tree edges (newline) to output file
                        fprintf(outputFp, "(%d,%d)\n", vertexUArray[i], vertexVArray[i]);
                    }   
                }
                // free memory of line
                free(line);                
////////////
                //REWORK freeGraph function - it is incorrect
                // free memory of graph
                freeGraph(adjListNodeArray, g);
////////////                
            }
        }
    }
    // Close the input and output files
    if(fclose(inputFp) != 0 || fclose(outputFp) != 0) 
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    
    exit(EXIT_SUCCESS);
}

/*
CS3050
Final Project
Zachary Pierucci
ZNPCP5
Bruce Phommaly
BYPXTD
Mitchell Hoffmann
MJHXW7
*/

#include "graph.h"
#include "input_error.h"


	int i;
	int length;
	int gridSize; //found in loop 0
	int startingPointXRobot; //found in loop 1
	int startingPointYRobot; //found in loop 1
	int exitPointXRobot; //found in loop 2
	int exitPointYRobot; //found in loop 2
	int startingPointXObstacle1; //foud in loop 3
	int startingPointYObstacle1; //found in loop 3
	int speedObstacle1; //found in loop 4
	int directionXObstacle1; //found in loop 5
	int directionYObstacle1; //found in loop 5
	int startingPointXObstacle2; //found in loop 6
	int startingPointYObstacle2; //found in loop 6
	int speedObstacle2; //found in loop 7
	int directionXObstacle2; //found in loop 8
	int directionYObstacle2; //found in loop 8
	char* zero = "0";
        char* one = "-1";
        char* two = "+1";
	int lineIndex = 0;
	char buff[255];
	char lineStr[255];
	char temp[255];


//Function to find the index
int findIndex(char* str, char ch)
{
	int index = 0;
	while (str != 0 && *str != 0 && *str != '\n')
	{
		int c = *str;
		if (c != ch) 
		{
			index++;
			str++;
			continue;
		}
		else 
		{
			return index;
		}
	}
	return-1;
}

//Function to check if number
bool isNumber(char* str) 
{
	bool invalidCharFound = false;

	while (str != 0 && *str != 0 && *str != '\n')
	{
		int c = *str;
		if (c >= '0' && c <= '9') 
		{
			str++;
			continue;
		}
		else 
		{
			invalidCharFound = true;
			break;
		}
	}
    	return !invalidCharFound;
}

int main(int argc, char** argv)
{
	if(argc != 2)// Reads in 3 arguments
	{
		exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
	}

	//open the input file
	FILE* input = fopen(argv[1], "r");
	if(input == NULL) 
	{
		exit(FILE_FAILED_TO_OPEN);
	}
	
	/*
	//open the output file
	FILE* output = fopen(argv[2], "w");
	if(output == NULL)
	{
		exit(FILE_FAILED_TO_OPEN);
	}
	*/
	while(fgets(buff, 255, (FILE*)input)) 
	{
		sscanf(buff, "%s\n", lineStr);
		if(lineIndex == 0)
		{
			if(isNumber(lineStr) == false) //if the first character is not a number
			{
				exit(PARSING_ERROR_INVALID_FORMAT);
			}
			if(lineStr < 0) // If there is less than 0 gridSize
			{
				exit(PARSING_ERROR_INVALID_FORMAT);
			}
			length = strlen(lineStr);
			strncpy(temp, lineStr, length); //copies the number on the first line to the temp
			temp[length] = '\0'; //Null terminate the temp char
			gridSize = atoi(temp);
			lineIndex++;

			printf("gridSize = %d\n", gridSize);
		}
		else
		{
			if(lineIndex == 1)
			{
				if(lineStr[0] != '(') //if the character is not a parenthesis
				{
					printf("function exits here because lineStr doesnt move onto next line\n");
					exit(PARSING_ERROR_INVALID_FORMAT);
				}
				int commaIndex = findIndex(&lineStr[1], ',');
				if(commaIndex == -1) //if the comma does not exist
				{
					exit(PARSING_ERROR_INVALID_FORMAT);
				}
				else
				{
					strncpy(temp, &lineStr[1], commaIndex);
					temp[commaIndex] = '\0'; //null terminate the temp char
					if(isNumber(temp) == false)
					{
						exit(PARSING_ERROR_INVALID_FORMAT);	
					}
					startingPointXRobot = atoi(temp);
					int parenIndex = findIndex(&lineStr[commaIndex], ')');
					if(parenIndex == -1) //if the parenthesis does not exist
					{
               		                 	exit(PARSING_ERROR_INVALID_FORMAT);
               	         		}
					else
					{
						strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
						temp[parenIndex - 2] = '\0'; //null terminate the temp char
						if(isNumber(temp) == false)
						{
							exit(PARSING_ERROR_INVALID_FORMAT);
						}
						startingPointYRobot = atoi(temp);
					}
				}					
				lineIndex++;
                                if(startingPointXRobot > gridSize || startingPointYRobot > gridSize)
                                {
                                        exit(PARSING_ERROR_INVALID_FORMAT);
                                }

				printf("startingPointXRobot = %d\n", startingPointXRobot);
				printf("startingPointYRobot = %d\n", startingPointYRobot);
			}
			else
			{
				if(lineIndex == 2)
               			{
					if(lineStr[0] != '(') //if the character is not a parenthesis
               	        		{       
               	                		exit(PARSING_ERROR_INVALID_FORMAT);
               	        		}
               	        		int commaIndex = findIndex(&lineStr[1], ',');
               	        		if(commaIndex == -1) //if the comma does not exist
               	        		{       
               	                		exit(PARSING_ERROR_INVALID_FORMAT);
               	        		}
               	        		else
               	        		{       
                                		strncpy(temp, &lineStr[1], commaIndex);
                                		temp[commaIndex] = '\0'; //null terminate the temp char
                                		if(isNumber(temp) == false)
                                		{	       
                                       			exit(PARSING_ERROR_INVALID_FORMAT);
                                		}
                                		exitPointXRobot = atoi(temp);
                                		int parenIndex = findIndex(&lineStr[commaIndex], ')');
                                		if(parenIndex == -1) //if the parenthesis does not exist
                                		{       
                                        		exit(PARSING_ERROR_INVALID_FORMAT);
                                		}
                                		else
                                		{
                                        		strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
                                        		temp[parenIndex - 2] = '\0'; //null terminate the temp char
                                        		if(isNumber(temp) == false)
                                        		{       
                                               			exit(PARSING_ERROR_INVALID_FORMAT);
                                        		}
                         		               	exitPointYRobot = atoi(temp);
        	                	        }
                	       		}           
                       			lineIndex++;
                                        if(exitPointXRobot > gridSize || exitPointYRobot > gridSize)
                                        {
                                            exit(PARSING_ERROR_INVALID_FORMAT);
                                        }

					printf("exitPointXRobot = %d\n", exitPointXRobot);
					printf("exitPointYRobot = %d\n", exitPointYRobot);
                		}
				else
				{
					if(lineIndex == 3)
	        	        	{
	               				if(lineStr[0] != '(') //if the character is not a parenthesis
                        			{       
                                			exit(PARSING_ERROR_INVALID_FORMAT);
	                        		}
	                        		int commaIndex = findIndex(&lineStr[1], ',');
	                        		if(commaIndex == -1) //if the comma does not exist
	                        		{       
	                               			exit(PARSING_ERROR_INVALID_FORMAT);
	                        		}
	                        		else
	                        		{       
	                                		strncpy(temp, &lineStr[1], commaIndex);
        	                        		temp[commaIndex] = '\0'; //null terminate the temp char
                	                		if(isNumber(temp) == false)
                        	        		{       
                                	       			exit(PARSING_ERROR_INVALID_FORMAT);
	                                		}
	                               			startingPointXObstacle1 = atoi(temp);
        	                        		int parenIndex = findIndex(&lineStr[commaIndex], ')');
                	                		if(parenIndex == -1) //if the parenthesis does not exist
                        	        		{       
                                		        	exit(PARSING_ERROR_INVALID_FORMAT);
                                			}
                                			else
                                			{       
                                        			strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
                                        			temp[parenIndex - 2] = '\0'; //null terminate the temp char
                                        			if(isNumber(temp) == false)
                                        			{       
                                               	 			exit(PARSING_ERROR_INVALID_FORMAT);
                                        			}
                                        			startingPointYObstacle1 = atoi(temp);
                                			}
                        			}           
	                       			lineIndex++;
                                                if(startingPointXObstacle1 > gridSize || startingPointYObstacle1 > gridSize)
                                                {
                                                    exit(PARSING_ERROR_INVALID_FORMAT);
                                                }

						printf("startingPointXObstacle1 = %d\n", startingPointXObstacle1);
						printf("startingPointYObstacle1 = %d\n", startingPointYObstacle1);
	                		}
					else
					{
						if(lineIndex == 4)
	                			{
	                       				if(isNumber(lineStr) == false) //if the first character is not a number
	                        			{      
	                        		       		exit(PARSING_ERROR_INVALID_FORMAT);
	                       				}
	                        			if(lineStr < 0) // If there is less than 0 vertices
	                        			{       
	                                			exit(PARSING_ERROR_INVALID_FORMAT);
	                       				}
							length = strlen(lineStr);
	                        			strncpy(temp, lineStr, length); //copies the number on the first line to the temp
	                        			temp[length] = '\0'; //Null terminate the temp char
							speedObstacle1 = atoi(temp);
							lineIndex++;

							printf("speedObstacle1 = %d\n", speedObstacle1);
               					}
						else
						{
							if(lineIndex == 5)
                					{
                 	       					if(lineStr[0] != '(') //if the character is not a parenthesis
    								{
        								exit(PARSING_ERROR_INVALID_FORMAT);
    								}
    								int commaIndex = findIndex(&lineStr[1], ',');
    								if(commaIndex == -1) //if the comma does not exist
    								{
        								exit(PARSING_ERROR_INVALID_FORMAT);
    								}
    								else
    								{
        								strncpy(temp, &lineStr[1], commaIndex);
        								temp[commaIndex] = '\0'; //null terminate the temp char
									if(strcmp(temp, zero) == 0)
        								{
										//0 = 0
										directionXObstacle1 = 0;
        								}
									else if(strcmp(temp, one) == 0)
        								{
										//1 = -1
           	 								directionXObstacle1 = 1;
        								}
        								else if(strcmp(temp, two) == 0)
        								{
										//2 = +1
            									directionXObstacle1 = 2;
        								}
        								else
        								{
            									exit(PARSING_ERROR_INVALID_FORMAT);
        								}
        								int parenIndex = findIndex(&lineStr[commaIndex], ')');
        								if(parenIndex == -1) //if the parenthesis does not exist
        								{
         									exit(PARSING_ERROR_INVALID_FORMAT);
        								}
     									else
        								{
         									strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
            									temp[parenIndex - 2] = '\0'; //null terminate the temp char
            									if(strcmp(temp, zero) == 0)
            									{
											//0 = 0
                									directionYObstacle1 = 0;
            									}
            									else if(strcmp(temp, one) == 0)
            									{
											//1 = -1
                									directionYObstacle1 = 1;
            									}
            									else if(strcmp(temp, two) == 0)
            									{
											//2 = +1
               		 								directionYObstacle1 = 2;
            									}
            									else
            									{
                									exit(PARSING_ERROR_INVALID_FORMAT);
            									}
        								}
    								}
   	 							lineIndex++;
								
    								printf("directionXObstacle1 = %d\n", directionXObstacle1);
								printf("directionYObstacle1 = %d\n", directionYObstacle1);
           						}
							else
							{
								if(lineIndex == 6)
                						{
                        						if(lineStr[0] != '(') //if the character is not a parenthesis
                        						{
                        					        	exit(PARSING_ERROR_INVALID_FORMAT);
                        						}
                        						int commaIndex = findIndex(&lineStr[1], ',');
                        						if(commaIndex == -1) //if the comma does not exist
                        						{
                        	        					exit(PARSING_ERROR_INVALID_FORMAT);
                        						}
                        						else
                        						{
                        	 						strncpy(temp, &lineStr[1], commaIndex);
                        	        					temp[commaIndex] = '\0'; //null terminate the temp char
                        	        					if(isNumber(temp) == false)
                        	        					{
                        	               						exit(PARSING_ERROR_INVALID_FORMAT);
                        	        					}
                        	        					startingPointXObstacle2 = atoi(temp);
                        	        					int parenIndex = findIndex(&lineStr[commaIndex], ')');
                        	        					if(parenIndex == -1) //if the parenthesis does not exist
                        	        					{
                        	                					exit(PARSING_ERROR_INVALID_FORMAT);
                        	        					}
                        	        					else
                        	        					{
                        	                					strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
                        	                					temp[parenIndex - 2] = '\0'; //null terminate the temp char
                        	                					if(isNumber(temp) == false)
                        	                					{
                        	                        					exit(PARSING_ERROR_INVALID_FORMAT);
                        	                					}
                        	                					startingPointYObstacle2 = atoi(temp);
                        	       						}
                        						}
                        						lineIndex++;
                                                                        if(startingPointXObstacle2 > gridSize || startingPointYObstacle2 > gridSize)
                                                                        {
                                                                            exit(PARSING_ERROR_INVALID_FORMAT);
                                                                        }

									printf("startingPointXObstacle2 = %d\n", startingPointXObstacle2);
                        						printf("startingPointYObstacle2 = %d\n", startingPointYObstacle2);
                						}
								else
								{
									if(lineIndex == 7)
                							{
                        							if(isNumber(lineStr) == false) //if the first character is not a number
                        							{       
                        	        						exit(PARSING_ERROR_INVALID_FORMAT);
                        							}
                        							if(lineStr < 0) // If there is less than 0 vertices
                        							{       
                        	       							exit(PARSING_ERROR_INVALID_FORMAT);
                        							}
										length = strlen(lineStr);
                       								strncpy(temp, lineStr, length); //copies the number on the first line to the temp
                       								temp[length] = '\0'; //Null terminate the temp char
										speedObstacle2 = atoi(temp);
										lineIndex++;

										printf("speedObstacle2 = %d\n", speedObstacle2);
                							}
									else
									{
										if(lineIndex == 8)
                								{
                        								if(lineStr[0] != '(') //if the character is not a parenthesis
    											{
        											exit(PARSING_ERROR_INVALID_FORMAT);
    											}
    											int commaIndex = findIndex(&lineStr[1], ',');
    											if(commaIndex == -1) //if the comma does not exist
    											{
        											exit(PARSING_ERROR_INVALID_FORMAT);
    											}
    											else
    											{
        											strncpy(temp, &lineStr[1], commaIndex);
        											temp[commaIndex] = '\0'; //null terminate the temp char
        											if(strcmp(temp, zero) == 0)
        											{
													//0 = 0
            												directionXObstacle2 = 0;
        											}
        											else if(strcmp(temp, one) == 0)
        											{
													//1 = -1
        						    						directionXObstacle2 = 1;
        											}
        											else if(strcmp(temp, two) == 0)
        											{
													//2 = +1
            												directionXObstacle2 = 2;
        											}
        											else
        											{
            												exit(PARSING_ERROR_INVALID_FORMAT);
        											}
        											int parenIndex = findIndex(&lineStr[commaIndex], ')');
        											if(parenIndex == -1) //if the parenthesis does not exist
        											{
            												exit(PARSING_ERROR_INVALID_FORMAT);
        											}
        											else
        											{
            												strncpy(temp, &lineStr[commaIndex + 2], parenIndex);
            												temp[parenIndex - 2] = '\0'; //null terminate the temp char
            												if(strcmp(temp, zero) == 0)
           	 											{
														//0 = 0
                												directionYObstacle2 = 0;
            												}
            												else if(strcmp(temp, one) == 0)
            												{
														//1 = -1
                												directionYObstacle2 = 1;
            												}
            												else if(strcmp(temp, two) == 0)
            												{
														//2 = +1
                												directionYObstacle2 = 2;
            												}
            												else
            												{
                												exit(PARSING_ERROR_INVALID_FORMAT);
            												}
        											}
    											}
    											lineIndex++;
											    
    											printf("directionXObstacle2 = %d\n", directionXObstacle2);
    											printf("directionYObstacle2 = %d\n", directionYObstacle2);
        	        							}
									}
								}
							}
						}
					}
				}
			}
		}
	}
        
        printf("\nInitial Graph\n");
        int array[gridSize][gridSize];
        int x, y;
         int currentPointXRobot = startingPointXRobot;
        int currentPointYRobot = startingPointYRobot;
        
        for(x = 0; x <= gridSize + 1; x++)
        {
            for(y = 0; y <= gridSize + 1; y++)
            {
                if(x == startingPointXRobot && y == startingPointYRobot)
                {
                    array[x][y] = 'R';
                    printf("%c", array[x][y]);
                }
                
                if(x == currentPointXRobot && y == currentPointYRobot)
                {
                    array[x][y] = 'F';
                    printf("%c", array[x][y]);
                }
                
                if(x == exitPointXRobot && y == exitPointYRobot)
                {
                    array[x][y] = 'L';
                    printf("%c", array[x][y]);
                }

                if(x == startingPointXObstacle1 && y == startingPointYObstacle1)
                {
                    array[x][y] = 'O';
                    printf("%c", array[x][y]);
                }
                
                if(x == startingPointXObstacle2 && y == startingPointYObstacle2)
                {
                    array[x][y] = 'O2';
                    printf("%c", array[x][y]);
                }
                
                // Wall
                if(x < 1 || y < 1 || y > gridSize)
                {
                    array[x][y] = 'W';
                    printf("%c", array[x][y]);
                }
                
                
//                if
//                {
                printf("(%d,%d)\t", x, y);
               // }
            }
            printf("\n\n");
        }
        
        printf("---------------------------------------------------------------------------------------------------\n");
            
        for(i = 1; i < 30; i++)
        {
            printf("\nMovement counter: %d\n\n", i);
//        while(array[startingPointXRobot][startingPointYRobot] != array[exitPointXRobot][exitPointYRobot])
//        {
            
//        if(array[currentPointXRobot][currentPointYRobot] )
//        {
//            
//        }
            //runGame();
            printf("Obstacle1 Info:\n");
            printf("------------------------------\n");
           moveObject1();
           moveObject2();
           //moveRobot();
        
           printf("Current Direction of Obstacle1: ");
           if(directionXObstacle1 != 0 && directionYObstacle1 !=0)
           {
                if(directionXObstacle1 == 1)
                {
                    printf("North-");
                }
                else
                {
                    printf("South-");
                }
                if(directionYObstacle1 == 1)
                {
                    printf("West\n");
                }
                else
                {
                    printf("East\n");
                }
           }
           else
           {
               if(directionXObstacle1 == 1 && directionYObstacle1 == 0)
               {
                   printf("North\n");
               }
               if(directionXObstacle1 == 2 && directionYObstacle1 == 0)
               {
                   printf("South\n");
               }
               if(directionXObstacle1 == 0 && directionYObstacle1 == 1)
               {
                   printf("West\n");
               }
               if(directionXObstacle1 == 0 && directionYObstacle1 == 2)
               {
                   printf("East\n");
               }
           }
        
           printf("Location of Obstacle1: (%d,%d)\n", startingPointXObstacle1, startingPointYObstacle1);
           
        for(x = 0; x <= gridSize + 1; x++)
        {
            for(y = 0; y <= gridSize + 1; y++)
            {
                if(x == startingPointXRobot && y == startingPointYRobot)
                {
                    array[x][y] = 'R';
                    printf("%c", array[x][y]);
                }
                
                if(x == currentPointXRobot && y == currentPointYRobot)
                {
                    array[x][y] = 'F';
                    printf("%c", array[x][y]);
                }
                
                if(x == exitPointXRobot && y == exitPointYRobot)
                {
                    array[x][y] = 'L';
                    printf("%c", array[x][y]);
                }

                if(x == startingPointXObstacle1 && y == startingPointYObstacle1)
                {
                    array[x][y] = 'O';
                    printf("%c", array[x][y]);
                }
                
                if(x == startingPointXObstacle2 && y == startingPointYObstacle2)
                {
                    array[x][y] = 'O2';
                    printf("%c", array[x][y]);
                }
                
                // Wall
                if(x < 1 || y < 1 || y > gridSize)
                {
                    array[x][y] = 'W';
                    printf("%c", array[x][y]);
                }
                
                
//                if
//                {
                printf("(%d,%d)\t", x, y);
               // }
            }
            printf("\n\n");
        }
       
        
        printf("---------------------------------------------------------------------------------\n");
        }
        //runGame();
        
	return 0;
}

void moveObject1()
{	
	if(directionXObstacle1 != 0 && directionYObstacle1 !=0)
	{ //If it is diagonal 
            
            	//North-East
		if (directionXObstacle1 == 1 && directionYObstacle1 == 2)
		{
                        startingPointXObstacle1 -= speedObstacle1;
                        startingPointYObstacle1 += speedObstacle1;
				//calculate the remainder of i
				if(startingPointXObstacle1 < 1 || startingPointYObstacle1 > gridSize)
				{          
                                    // Obstacle hits North wall
                                    if(startingPointXObstacle1 < 1 && startingPointYObstacle1 <= gridSize)
                                    {
                                        printf("Obstacle1 hit the North wall\n");
                                        // Change directionXObstacle1 
                                        directionXObstacle1 = 2;
                                        directionYObstacle1 = 2;
                                        
                                        int remainder = (speedObstacle1 - 1);
                                        if (remainder > 0 && (startingPointXObstacle1 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 += speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits East Wall
                                    if(startingPointXObstacle1 >= 1 && startingPointYObstacle1 > gridSize)
                                    {
                                        printf("Obstacle1 hit the East wall\n");
                                        directionXObstacle1 = 1;
                                        // Change directionYObstacle1
                                        directionYObstacle1 = 1;
                                        
                                        int remainder = (startingPointYObstacle1 - gridSize);
                                        if (remainder > 0 && (startingPointYObstacle1 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 -= (speedObstacle1 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 -= speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits North-East corner
                                    if(startingPointXObstacle1 < 1 && startingPointYObstacle1 > gridSize)
                                    {
                                        printf("Obstacle1 hit the North-East Corner");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 2;
                                        // Change DirectionYObstacle1
                                        directionYObstacle1 = 1;
                                        
                                        int remainderX = speedObstacle1 - 1;
                                        int remainderY = startingPointYObstacle1 - gridSize;
                                        
                                        if(startingPointXObstacle1 + speedObstacle1 == 1 && startingPointYObstacle1 - speedObstacle1 == gridSize)
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 + speedObstacle1);
                                        startingPointXObstacle1  += speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 - speedObstacle1);
                                        startingPointYObstacle1 -= speedObstacle1;     
                                        }
                                        else
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 + remainderX) - 1;
                                        startingPointXObstacle1  += speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 - remainderY) + 1;
                                        startingPointYObstacle1 -= speedObstacle1;  
                                        }
                                    }
       				}
		}
                
                // South-West
		else if (directionXObstacle1 == 2 && directionYObstacle1 == 1)
		{           
                        startingPointXObstacle1 += speedObstacle1;
                        startingPointYObstacle1 -= speedObstacle1;
                                    
				//calculate the remainder of i
				if(startingPointXObstacle1 > gridSize || startingPointYObstacle1 < 1)
				{                                              
                                    // Obstacle1 hits South wall
                                    if(startingPointXObstacle1 > gridSize && startingPointYObstacle1 >= 1)
                                    {
                                        printf("Obstacle1 hit the South wall\n");
                                        // Change directionXObstacle1 
                                        directionXObstacle1 = 1;
                                        directionYObstacle1 = 1;                                        
                                        
                                        int remainder = (startingPointXObstacle1 - gridSize);
                                        if (remainder > 0 && (startingPointXObstacle1 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 -= (speedObstacle1 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 -= speedObstacle1;
                                            }
                                        }
                                    }

                                    // Obstacle1 hits West wall
                                    if(startingPointXObstacle1 <= gridSize && startingPointYObstacle1 < 1)
                                    {
                                        printf("Obstacle1 hit the West wall\n");
                                        directionXObstacle1 = 2;
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 2;
                                        
                                        int remainder = (speedObstacle1 - 1);
                                        if (remainder > 0 && (startingPointYObstacle1 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 += speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits South-West corner
                                        if(startingPointXObstacle1 >= gridSize && startingPointYObstacle1 <= 1)
                                        {
                                        printf("Obstacle1 hit the South-West corner\n");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 1;
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 2;
                                                                         
                                        int remainderX = startingPointXObstacle1 - gridSize;
                                        int remainderY = speedObstacle1 - 1;
                                        
                                        if(startingPointXObstacle1 - speedObstacle1 == gridSize && startingPointYObstacle1 + speedObstacle1 == 1)
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 - speedObstacle1);
                                        startingPointXObstacle1  -= speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 + speedObstacle1);
                                        startingPointYObstacle1 += speedObstacle1;     
                                        }
                                        else
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 - remainderX) + 1;
                                        startingPointXObstacle1  -= speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 + remainderY) - 1;
                                        startingPointYObstacle1 += speedObstacle1;  
                                        }
                                        
                                        }
                                    
       				}
                }
                
                //North-West
                else if(directionXObstacle1 == 1 && directionYObstacle1 == 1)
		{   
                        startingPointXObstacle1 -= speedObstacle1;
                        startingPointYObstacle1 -= speedObstacle1;
                        
				//calculate the remainder of i
				if(startingPointXObstacle1 < 1 || startingPointYObstacle1 < 1)
				{                                                                                   
                                    // Obstacle1 hits North wall
                                    if(startingPointXObstacle1 < 1 && startingPointYObstacle1 >= 1)
                                    {
                                        printf("Obstacle1 hit the North wall\n");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 2;
                                        directionYObstacle1 = 1;
                                        
                                        int remainder = (speedObstacle1 - 1);
                                        if (remainder > 0 && (startingPointXObstacle1 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 += speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits West wall
                                    if(startingPointXObstacle1 >= 1 && startingPointYObstacle1 < 1)
                                    {
                                        printf("Obstacle1 hit the West wall\n");
                                        directionXObstacle1 = 1;
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 2;                                      
                                        
                                        int remainder = (speedObstacle1 - 1);
                                        if (remainder > 0 && (startingPointYObstacle1 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 += speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits North-West corner
                                        if(startingPointXObstacle1 <= 1 && startingPointYObstacle1 <= 1)
                                        {
                                        printf("Obstacle1 hit the North-West corner\n");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 2;
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 2;
                                        
                                        int remainderX = speedObstacle1 - 1;
                                        int remainderY = speedObstacle1 - 1;
                                        
                                        if(startingPointXObstacle1 + speedObstacle1 == 1 && startingPointYObstacle1 + speedObstacle1 == 1)
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 + speedObstacle1);
                                        startingPointXObstacle1  += speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 + speedObstacle1);
                                        startingPointYObstacle1 += speedObstacle1;      
                                        }
                                        else 
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 + remainderX) - 1;
                                        startingPointXObstacle1  += speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 + remainderY) - 1;
                                        startingPointYObstacle1 += speedObstacle1;    
                                        }
                                        }
       				}                  
		}
        
                // South-East
                else if (directionXObstacle1 == 2 && directionYObstacle1 == 2)
                {
                        startingPointXObstacle1 += speedObstacle1;
                        startingPointYObstacle1 += speedObstacle1;  
                                    
				//calculate the remainder of i
				if(startingPointXObstacle1 > gridSize || startingPointYObstacle1 > gridSize)
				{                                               
                                    // Obstacle1 hits South wall
                                    if(startingPointXObstacle1 > gridSize && startingPointYObstacle1 <= gridSize)
                                    {
                                        printf("Obstacle1 hit the South wall\n");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 1;

                                        int remainder = (startingPointXObstacle1 - gridSize);
                                        if (remainder > 0 && (startingPointXObstacle1 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 -= (speedObstacle1 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle1 -= speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits East wall
                                    if(startingPointXObstacle1 <= gridSize && startingPointYObstacle1 > gridSize)
                                    {
                                        printf("Obstacle1 hit the East wall\n");
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 1;                                       
                                        
                                        int remainder = (startingPointYObstacle1 - gridSize);
                                        if (remainder > 0 && (startingPointYObstacle1 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 -= (speedObstacle1 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle1 -= speedObstacle1;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle1 hits South-East corner
                                        if(startingPointXObstacle1 >= gridSize && startingPointYObstacle1 >= gridSize)
                                        {
                                        printf("Obstacle1 hit the South-East corner\n");
                                        // Change directionXObstacle1
                                        directionXObstacle1 = 1;
                                        // Change directionYObstacle1                                         
                                        directionYObstacle1 = 1;
                                        
                                        int remainderX = startingPointXObstacle1 - gridSize;
                                        int remainderY = startingPointYObstacle1 - gridSize;
                                        
                                        if(startingPointXObstacle1 - speedObstacle1 == gridSize && startingPointYObstacle1 - speedObstacle1 == gridSize)
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 - speedObstacle1);
                                        startingPointXObstacle1  -= speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 - speedObstacle1);
                                        startingPointYObstacle1 -= speedObstacle1;      
                                        }
                                        else 
                                        {
                                        startingPointXObstacle1 = (startingPointXObstacle1 - remainderX) + 1;
                                        startingPointXObstacle1  -= speedObstacle1;
                                        
                                        startingPointYObstacle1 = (startingPointYObstacle1 - remainderY) + 1;
                                        startingPointYObstacle1 -= speedObstacle1;    
                                        }
                                        
                                        }
       				}                                        
                }
                
        }
        
        
	else
	{//if not diagonal
	 
            	if(directionXObstacle1 == 1 && directionYObstacle1 == 0)
		{
		//north
                        //check to see if it will hit wall 
			if(startingPointXObstacle1 - speedObstacle1 < 1 )
			{
				int holder = (startingPointXObstacle1 - speedObstacle1) -1;
				startingPointXObstacle1 = 1 + (holder * -1); 

                                directionXObstacle1 = 2;
			}
			else
			{
				startingPointXObstacle1 -= speedObstacle1;
			}

	
		}
		
                else if(directionXObstacle1 == 2 && directionYObstacle1 == 0)
		{
		//south
		
			//check to see if it will hit wall 
			if(startingPointXObstacle1 + speedObstacle1 > gridSize )
			{
				int holder = startingPointXObstacle1 + speedObstacle1 - gridSize;
			
				startingPointXObstacle1 = gridSize - holder; 
				directionXObstacle1 = 1;
			}
		else
		{
			startingPointXObstacle1 += speedObstacle1;
		}


		}
		
		else if(directionXObstacle1 == 0 && directionYObstacle1 == 2)
		{
		//east
			//check to see if it will hit wall 
			if(startingPointYObstacle1 + speedObstacle1 > gridSize )
			{
				int holder = startingPointYObstacle1 + speedObstacle1 - gridSize;
			
				startingPointYObstacle1 = gridSize - holder; 
				directionYObstacle1 = 1;
			}
			else
			{
				startingPointYObstacle1 += speedObstacle1;
				
				
			}
		}
		else if( directionXObstacle1 == 0 && directionYObstacle1 == 1)
		{
		//west
		if(startingPointYObstacle1 - speedObstacle1 < 1 )
			{
				int holder = (startingPointYObstacle1 - speedObstacle1) -1;
				
                                startingPointYObstacle1 = 1 + (holder * -1); 
      				directionYObstacle1 = 2;
			
			}
			else
			{
				startingPointYObstacle1 -= speedObstacle1;
			}
		}

	}
}

void moveObject2()
{
	if(directionXObstacle2 != 0 && directionYObstacle2 !=0)
	{ //If it is diagonal 
            
            	//North-East
		if (directionXObstacle2 == 1 && directionYObstacle2 == 2)
		{
                        startingPointXObstacle2 -= speedObstacle2;
                        startingPointYObstacle2 += speedObstacle2;
				//calculate the remainder of i
				if(startingPointXObstacle2 < 1 || startingPointYObstacle2 > gridSize)
				{          
                                    // Obstacle hits North wall
                                    if(startingPointXObstacle2 < 1 && startingPointYObstacle2 <= gridSize)
                                    {
                                        printf("Obstacle2 hit the North wall\n");
                                        // Change directionXObstacle2 
                                        directionXObstacle2 = 2;
                                        directionYObstacle2 = 2;
                                        
                                        int remainder = (speedObstacle2 - 1);
                                        if (remainder > 0 && (startingPointXObstacle2 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 += speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits East Wall
                                    if(startingPointXObstacle2 >= 1 && startingPointYObstacle2 > gridSize)
                                    {
                                        printf("Obstacle2 hit the East wall\n");
                                        directionXObstacle2 = 1;
                                        // Change directionYObstacle2
                                        directionYObstacle2 = 1;
                                        
                                        int remainder = (startingPointYObstacle2 - gridSize);
                                        if (remainder > 0 && (startingPointYObstacle2 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 -= (speedObstacle2 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 -= speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits North-East corner
                                    if(startingPointXObstacle2 < 1 && startingPointYObstacle2 > gridSize)
                                    {
                                        printf("Obstacle2 hit the North-East Corner");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 2;
                                        // Change DirectionYObstacle2
                                        directionYObstacle2 = 1;
                                        
                                        int remainderX = speedObstacle2 - 1;
                                        int remainderY = startingPointYObstacle2 - gridSize;
                                        
                                        if(startingPointXObstacle2 + speedObstacle2 == 1 && startingPointYObstacle2 - speedObstacle2 == gridSize)
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 + speedObstacle2);
                                        startingPointXObstacle2  += speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 - speedObstacle2);
                                        startingPointYObstacle2 -= speedObstacle2;     
                                        }
                                        else
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 + remainderX) - 1;
                                        startingPointXObstacle2  += speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 - remainderY) + 1;
                                        startingPointYObstacle2 -= speedObstacle2;  
                                        }
                                    }
       				}
		}
                
                // South-West
		else if (directionXObstacle2 == 2 && directionYObstacle2 == 1)
		{           
                        startingPointXObstacle2 += speedObstacle2;
                        startingPointYObstacle2 -= speedObstacle2;
                                    
				//calculate the remainder of i
				if(startingPointXObstacle2 > gridSize || startingPointYObstacle2 < 1)
				{                                              
                                    // Obstacle2 hits South wall
                                    if(startingPointXObstacle2 > gridSize && startingPointYObstacle2 >= 1)
                                    {
                                        printf("Obstacle2 hit the South wall\n");
                                        // Change directionXObstacle2 
                                        directionXObstacle2 = 1;
                                        directionYObstacle2 = 1;                                        
                                        
                                        int remainder = (startingPointXObstacle2 - gridSize);
                                        if (remainder > 0 && (startingPointXObstacle2 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 -= (speedObstacle2 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 -= speedObstacle2;
                                            }
                                        }
                                    }

                                    // Obstacle2 hits West wall
                                    if(startingPointXObstacle2 <= gridSize && startingPointYObstacle2 < 1)
                                    {
                                        printf("Obstacle2 hit the West wall\n");
                                        directionXObstacle2 = 2;
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 2;
                                        
                                        int remainder = (speedObstacle2 - 1);
                                        if (remainder > 0 && (startingPointYObstacle2 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 += speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits South-West corner
                                        if(startingPointXObstacle2 >= gridSize && startingPointYObstacle2 <= 1)
                                        {
                                        printf("Obstacle2 hit the South-West corner\n");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 1;
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 2;
                                                                         
                                        int remainderX = startingPointXObstacle2 - gridSize;
                                        int remainderY = speedObstacle2 - 1;
                                        
                                        if(startingPointXObstacle2 - speedObstacle2 == gridSize && startingPointYObstacle2 + speedObstacle2 == 1)
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 - speedObstacle2);
                                        startingPointXObstacle2  -= speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 + speedObstacle2);
                                        startingPointYObstacle2 += speedObstacle2;     
                                        }
                                        else
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 - remainderX) + 1;
                                        startingPointXObstacle2  -= speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 + remainderY) - 1;
                                        startingPointYObstacle2 += speedObstacle2;  
                                        }
                                        
                                        }
                                    
       				}
                }
                
                //North-West
                else if(directionXObstacle2 == 1 && directionYObstacle2 == 1)
		{   
                        startingPointXObstacle2 -= speedObstacle2;
                        startingPointYObstacle2 -= speedObstacle2;
                        
				//calculate the remainder of i
				if(startingPointXObstacle2 < 1 || startingPointYObstacle2 < 1)
				{                                                                                   
                                    // Obstacle2 hits North wall
                                    if(startingPointXObstacle2 < 1 && startingPointYObstacle2 >= 1)
                                    {
                                        printf("Obstacle2 hit the North wall\n");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 2;
                                        directionYObstacle2 = 1;
                                        
                                        int remainder = (speedObstacle2 - 1);
                                        if (remainder > 0 && (startingPointXObstacle2 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 += speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits West wall
                                    if(startingPointXObstacle2 >= 1 && startingPointYObstacle2 < 1)
                                    {
                                        printf("Obstacle2 hit the West wall\n");
                                        directionXObstacle2 = 1;
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 2;                                      
                                        
                                        int remainder = (speedObstacle2 - 1);
                                        if (remainder > 0 && (startingPointYObstacle2 + remainder) != 1)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 += remainder ;
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 += speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits North-West corner
                                        if(startingPointXObstacle2 <= 1 && startingPointYObstacle2 <= 1)
                                        {
                                        printf("Obstacle2 hit the North-West corner\n");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 2;
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 2;
                                        
                                        int remainderX = speedObstacle2 - 1;
                                        int remainderY = speedObstacle2 - 1;
                                        
                                        if(startingPointXObstacle2 + speedObstacle2 == 1 && startingPointYObstacle2 + speedObstacle2 == 1)
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 + speedObstacle2);
                                        startingPointXObstacle2  += speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 + speedObstacle2);
                                        startingPointYObstacle2 += speedObstacle2;      
                                        }
                                        else 
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 + remainderX) - 1;
                                        startingPointXObstacle2  += speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 + remainderY) - 1;
                                        startingPointYObstacle2 += speedObstacle2;    
                                        }
                                        }
       				}                  
		}
        
                // South-East
                else if (directionXObstacle2 == 2 && directionYObstacle2 == 2)
                {
                        startingPointXObstacle2 += speedObstacle2;
                        startingPointYObstacle2 += speedObstacle2;  
                                    
				//calculate the remainder of i
				if(startingPointXObstacle2 > gridSize || startingPointYObstacle2 > gridSize)
				{                                               
                                    // Obstacle2 hits South wall
                                    if(startingPointXObstacle2 > gridSize && startingPointYObstacle2 <= gridSize)
                                    {
                                        printf("Obstacle2 hit the South wall\n");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 1;

                                        int remainder = (startingPointXObstacle2 - gridSize);
                                        if (remainder > 0 && (startingPointXObstacle2 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 -= (speedObstacle2 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointXObstacle2 -= speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits East wall
                                    if(startingPointXObstacle2 <= gridSize && startingPointYObstacle2 > gridSize)
                                    {
                                        printf("Obstacle2 hit the East wall\n");
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 1;                                       
                                        
                                        int remainder = (startingPointYObstacle2 - gridSize);
                                        if (remainder > 0 && (startingPointYObstacle2 - remainder) != gridSize)
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 -= (speedObstacle2 - remainder);
                                            }
                                        }
                                        else
                                        {
                                            int j = 0;
                                            for(j; j < remainder; j++)
                                            {
                                                startingPointYObstacle2 -= speedObstacle2;
                                            }
                                        }
                                    }
                                    
                                    // Obstacle2 hits South-East corner
                                        if(startingPointXObstacle2 >= gridSize && startingPointYObstacle2 >= gridSize)
                                        {
                                        printf("Obstacle2 hit the South-East corner\n");
                                        // Change directionXObstacle2
                                        directionXObstacle2 = 1;
                                        // Change directionYObstacle2                                         
                                        directionYObstacle2 = 1;
                                        
                                        int remainderX = startingPointXObstacle2 - gridSize;
                                        int remainderY = startingPointYObstacle2 - gridSize;
                                        
                                        if(startingPointXObstacle2 - speedObstacle2 == gridSize && startingPointYObstacle2 - speedObstacle2 == gridSize)
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 - speedObstacle2);
                                        startingPointXObstacle2  -= speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 - speedObstacle2);
                                        startingPointYObstacle2 -= speedObstacle2;      
                                        }
                                        else 
                                        {
                                        startingPointXObstacle2 = (startingPointXObstacle2 - remainderX) + 1;
                                        startingPointXObstacle2  -= speedObstacle2;
                                        
                                        startingPointYObstacle2 = (startingPointYObstacle2 - remainderY) + 1;
                                        startingPointYObstacle2 -= speedObstacle2;    
                                        }
                                        
                                        }
       				}                                        
                }
                
        }
        
        
	else
	{//if not diagonal
	 
            	if(directionXObstacle2 == 1 && directionYObstacle2 == 0)
		{
		//north
                        //check to see if it will hit wall 
			if(startingPointXObstacle2 - speedObstacle2 < 1 )
			{
				int holder = (startingPointXObstacle2 - speedObstacle2) -1;
				startingPointXObstacle2 = 1 + (holder * -1); 

                                directionXObstacle2 = 2;
			}
			else
			{
				startingPointXObstacle2 -= speedObstacle2;
			}

	
		}
		
                else if(directionXObstacle2 == 2 && directionYObstacle2 == 0)
		{
		//south
		
			//check to see if it will hit wall 
			if(startingPointXObstacle2 + speedObstacle2 > gridSize )
			{
				int holder = startingPointXObstacle2 + speedObstacle2 - gridSize;
			
				startingPointXObstacle2 = gridSize - holder; 
				directionXObstacle2 = 1;
			}
		else
		{
			startingPointXObstacle2 += speedObstacle2;
		}


		}
		
		else if(directionXObstacle2 == 0 && directionYObstacle2 == 2)
		{
		//east
			//check to see if it will hit wall 
			if(startingPointYObstacle2 + speedObstacle2 > gridSize )
			{
				int holder = startingPointYObstacle2 + speedObstacle2 - gridSize;
			
				startingPointYObstacle2 = gridSize - holder; 
				directionYObstacle2 = 1;
			}
			else
			{
				startingPointYObstacle2 += speedObstacle2;
				
				
			}
		}
		else if( directionXObstacle2 == 0 && directionYObstacle2 == 1)
		{
		//west
		if(startingPointYObstacle2 - speedObstacle2 < 1 )
			{
				int holder = (startingPointYObstacle2 - speedObstacle2) -1;
				
                                startingPointYObstacle2 = 1 + (holder * -1); 
      				directionYObstacle2 = 2;
			
			}
			else
			{
				startingPointYObstacle2 -= speedObstacle2;
			}
		}

	}
}
    
void moveRobot()
{
   
 // 0 - 3
 
    int run = 0;
    while(run == 0)
    {
         int x = rand() % 3;
     switch(x) {
      case 0 :
      {
       if(moveRobotNorth() == 1)
            {
            startingPointXRobot++;
            run = 1;
            }
        break;
      }
      case 1 :
      {
          if (moveRobotSouth() == 1)
            {
            startingPointXRobot--;
        run = 1 ;
            }
        break;
         
      }
     
      case 2 :
      {
          if( moveRobotEast() == 1)
            {
            startingPointYRobot++;
            run = 1;
            }
         break;
      }
      case 3 :
      {
          if(moveRobotWest() == 1)
            {
            startingPointYRobot--; 
            run = 1;
            }
         break;
      }
 
      default :
      run = 0;
         
         
         
 
}
    }
}
 
 
int moveRobotNorth()
{
    if((startingPointXRobot - 1 == startingPointXObstacle1 && startingPointYRobot == startingPointYObstacle1) || (startingPointXRobot - 1 == startingPointXObstacle2 && startingPointYRobot == startingPointYObstacle2))
    {
        return 0;
       
    }
    else if(startingPointXRobot - 1 < 1 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
 
int moveRobotSouth()
{
        if((startingPointXRobot + 1 == startingPointXObstacle1 && startingPointYRobot == startingPointYObstacle1) || (startingPointXRobot + 1 == startingPointXObstacle2 && startingPointYRobot == startingPointYObstacle2))
    {
        return 0;
       
    }
    else if(startingPointXRobot + 1 > gridSize )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
 
int moveRobotEast()
{
        if((startingPointYRobot + 1 == startingPointYObstacle1 && startingPointXRobot == startingPointXObstacle1) || (startingPointYRobot + 1 == startingPointYObstacle2 && startingPointXRobot == startingPointXObstacle2))
    {
        return 0;
       
    }
    else if(startingPointYRobot + 1 > gridSize )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
 
int moveRobotWest()
{
        if((startingPointYRobot - 1 == startingPointYObstacle1 && startingPointXRobot == startingPointXObstacle1) || (startingPointYRobot - 1 == startingPointYObstacle2 && startingPointXRobot == startingPointXObstacle2))
    {
        return 0;
       
    }
    else if(startingPointYRobot - 1 < 1 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
 
 
void runGame()
{
    int gameOver = 0;
    while(gameOver == 0)
    {
        moveRobot();
        moveObject1();
        moveObject2();
 
        //printGraph();
            int x, y, array[gridSize][gridSize], currentPointXRobot = startingPointXRobot, currentPointYRobot = startingPointYRobot;
    
        for(x = 0; x <= gridSize + 1; x++)
        {
            for(y = 0; y <= gridSize + 1; y++)
            {
                if(x == startingPointXRobot && y == startingPointYRobot)
                {
                    array[x][y] = 'R';
                    printf("%c", array[x][y]);
                }
                
                if(x == currentPointXRobot && y == currentPointYRobot)
                {
                    array[x][y] = 'F';
                    printf("%c", array[x][y]);
                }
                
                if(x == exitPointXRobot && y == exitPointYRobot)
                {
                    array[x][y] = 'L';
                    printf("%c", array[x][y]);
                }

                if(x == startingPointXObstacle1 && y == startingPointYObstacle1)
                {
                    array[x][y] = 'O';
                    printf("%c", array[x][y]);
                }
                
                if(x == startingPointXObstacle2 && y == startingPointYObstacle2)
                {
                    array[x][y] = 'O2';
                    printf("%c", array[x][y]);
                }
                
                // Wall
                if(x < 1 || y < 1 || y > gridSize)
                {
                    array[x][y] = 'W';
                    printf("%c", array[x][y]);
                }
                
                
//                if
//                {
                printf("(%d,%d)\t", x, y);
               // }
            }
            printf("\n\n");
        }
    
       
    if(checkRobotObject() == 1)
    {
        // we lose
        gameOver = 1;
    }
    else if( checkRobotWin() == 1)
    {
           
    gameOver = 2;
    }
    }
    if(gameOver == 1)
    {
        printf("YOU LOSE YA LOSER");
    }
    else
    {
        printf("YOU WIN YA BEAUTY");
    }
   
   
}
 
 
 int checkRobotObject()
 {
     if((startingPointXObstacle1 == startingPointXRobot && startingPointYRobot == startingPointYObstacle1)||(startingPointXObstacle2 == startingPointXRobot && startingPointYRobot == startingPointYObstacle2) )
     {
         return 1;
     }
     else
         return 0;
 
         
 }
 int checkRobotWin()
 {
     if(startingPointXRobot == exitPointXRobot && startingPointYRobot == exitPointYRobot)
     {return 1;}
     else
     {
         return 0;
     }
 }


//void printGraph()
//{
//    
//    int x, y, array[gridSize][gridSize], currentPointXRobot, currentPointYRobot;
//    
//        for(x = 0; x <= gridSize + 1; x++)
//        {
//            for(y = 0; y <= gridSize + 1; y++)
//            {
//                if(x == startingPointXRobot && y == startingPointYRobot)
//                {
//                    array[x][y] = 'R';
//                    printf("%c", array[x][y]);
//                }
//                
//                if(x == currentPointXRobot && y == currentPointYRobot)
//                {
//                    array[x][y] = 'F';
//                    printf("%c", array[x][y]);
//                }
//                
//                if(x == exitPointXRobot && y == exitPointYRobot)
//                {
//                    array[x][y] = 'L';
//                    printf("%c", array[x][y]);
//                }
//
//                if(x == startingPointXObstacle1 && y == startingPointYObstacle1)
//                {
//                    array[x][y] = 'O';
//                    printf("%c", array[x][y]);
//                }
//                
//                if(x == startingPointXObstacle2 && y == startingPointYObstacle2)
//                {
//                    array[x][y] = 'O2';
//                    printf("%c", array[x][y]);
//                }
//                
//                // Wall
//                if(x < 1 || y < 1 || y > gridSize)
//                {
//                    array[x][y] = 'W';
//                    printf("%c", array[x][y]);
//                }
//                
//                
////                if
////                {
//                printf("(%d,%d)\t", x, y);
//               // }
//            }
//            printf("\n\n");
//        }
//}
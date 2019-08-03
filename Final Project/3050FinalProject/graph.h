/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: bruce
 *
 * Created on November 30, 2016, 3:37 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findIndex(char* str, char ch);
bool isNumber(char* str);
void moveObject1();
void moveObject2();

 void moveRobot();
 int moveRobotNorth();
 int moveRobotSouth();
 int moveRobotEast();
 int moveRobotWest();
 void runGame();
 int checkRobotObject();
 int checkRobotWin();
 
 void printGraph();

#endif /* GRAPH_H */


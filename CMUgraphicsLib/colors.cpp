/*
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"
#include <fstream>
#include <string>
using namespace std;

ofstream& operator<(ofstream& output, const color& currentcolor)
{
    if (currentcolor == GREEN) output << "GREEN";
    else if (currentcolor == RED) output << "RED";
    else if (currentcolor == ORANGE) output << "ORANGE";
    else if (currentcolor == YELLOW) output << "YELLOW";
    else if (currentcolor == BLUE) output << "BLUE";
    else if (currentcolor == BLACK) output << "BLACK";
    return output;
}

color StringToColor(string currentcolor) 
{
    if (!currentcolor.compare("GREEN")) return GREEN;
    else if (!currentcolor.compare("RED")) return RED;
    else if (!currentcolor.compare("ORANGE")) return ORANGE;
    else if (!currentcolor.compare("YELLOW")) return YELLOW; 
    else if (!currentcolor.compare("BLUE")) return BLUE; 
    else if (!currentcolor.compare("BLACK")) return BLACK; 
}

bool operator==(color a, color b) {

    return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

    return !(a == b);

}


/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"
#include <fstream>
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

bool operator==(color a, color b) {

  return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

  return !(a == b);
  
}

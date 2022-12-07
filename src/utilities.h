//////////////////////////////////////////
//
// utilities.h
//
// Written by Edward H. Trager
//
// (c) 2022 by the Regents of the 
// University of Michigan.
// All Rights Reserved
//
// init: 2022.11.14.et
//
//////////////////////////////////////////

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "VT100.h"

// printBoxedText
void printBoxedText(std::ostream & ost, std::string & text, vt100::command color=vt100::startBlue);

// englishSingularPlural
const char* englishSingularPlural(int val,const char* singular,const char *plural);

// timeDuration
std::string timeDuration(std::chrono::steady_clock::time_point startTime,std::chrono::steady_clock::time_point endTime);

// determineDelimiter
char determineDelimiter(std::string & firstLine);

// printEnumerationDigits
std::string printEnumerationDigits(unsigned int value,unsigned int width=3);


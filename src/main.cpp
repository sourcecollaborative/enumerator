/////////////////////////
//
// MAIN
//
/////////////////////////
#include <iostream>     // std::cout, std::ios
#include <string>       // std::string
#include <string.h>     // for strncpy and strchr
#include <sstream>      // stringstream
#include <fstream>      // file io
#include <ostream>      // output stream
#include <vector>

#include "VT100.h"
#include "utilities.h"
#include "Warning.h"
#include "Message.h"

//////////////////////////////
//
// UTILITY FUNCTIONS
//
//////////////////////////////

//
// splashScreen
//
void splashScreen(std::ostream &fs){

	std::string welcome("Welcome to enumerator!");
	printBoxedText(fs,welcome);
	fs << vt100::startBlue << "   by Edward H. Trager    " << vt100::stopColor << std::endl;
	fs << vt100::startBlue << " (c) 2022 Regents of the  " << vt100::stopColor << std::endl;
	fs << vt100::startBlue << "  University of Michigan  " << vt100::stopColor << std::endl;
	fs << vt100::startBlue << "   All Rights Reserved    " << vt100::stopColor << std::endl;
}

//////////////////////////////
//
// split
//
//////////////////////////////
void split(std::vector<char *> & column,char *buffer,size_t bufferSize,const char delimiter,const std::string &line,bool override=false){
	
	column.clear();
	
	// Put line into buffer:
	strncpy(buffer,line.c_str(),bufferSize);
	
	bool enforceDoubleQuote=false;
	if(delimiter==','){
		enforceDoubleQuote=true;
	}

	bool nested=false;
	const char nestingDelimiter='"';
	char *stt=buffer;
	for(char *c=buffer;*c;c++){
		
		// Check if nested:
		if(enforceDoubleQuote && *c==nestingDelimiter){
			nested=!nested;
		}else if( *c==delimiter && !nested ){
			column.emplace_back(stt);
			*c='\0';
			stt=c+1;
		}
	}
	// Capture the final column too:
	column.emplace_back(stt);
	
}

//////////////////////////
//
// process
//
//////////////////////////
void process(std::string & filePath){

	// Buffer for doing the work in:
	const size_t bufferSize = 20000;
	char *buffer = new char[bufferSize];
	std::vector<char *> column;
	column.reserve(200);
	
	std::string firstLine;
	std::string line;

	// Open the input file stream:
	std::ifstream file(filePath);
	if (file.is_open()) {
		
		// Save firstLine:
		std::getline(file,firstLine);
		
		// Determine column delimiter:
		char delimiter = determineDelimiter(firstLine);
		
		//output << firstLine << std::endl;
		
		////////////////////////////////////////////////
		//
		// PROCESS DATA LINES:
		//
		////////////////////////////////////////////////
		//unsigned lc=0;
		
		const unsigned limit=101;
		const char* numeral[] = {
			"⓪",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉈",
			"⑪","⑫","⑬","⑭","⑮","⑯","⑰","⑱","⑲","㉉",
			"㉑","㉒","㉓","㉔","㉕","㉖","㉗","㉘","㉙","㉊",
			"㉛","㉜","㉝","㉞","㉟","㊱","㊲","㊳","㊴","㉋",
			"㊶","㊷","㊸","㊹","㊺","㊻","㊼","㊽","㊾","㉌",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉍",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉎",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉏",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐙",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟",
		};

		while (std::getline(file, line)) {
		
			// DEBUGGING / TESTING OUTPUT
			//output << "<< -----" << (++lc) << "----- >>" << std::endl;
			split(column,buffer,bufferSize,delimiter,line);
			unsigned cc=0;
			for(auto i=column.begin();i<column.end();i++){
				++cc;
				if(cc<limit){
					std::cout << numeral[cc];
				}else{
					// Random sentinel in case we really
					// have too many columns to deal with:
					std::cout << "✿";
				}
				std::cout << *i;
				std::cout << delimiter ;
			}
			std::cout << std::endl;
		}
	}
}

///////////////////////////////////////
//
// MAIN
//
///////////////////////////////////////
int main(int argc,char *argv[]){

	if(argc < 2 ){
		Warning("main","Specify at least one file for processing");
		exit(1);
	}

  	for(unsigned i=1;i<(unsigned)argc;i++){
		//
		std::string filePath = argv[i];
    		process(filePath);
  	}
  	return 0;
}



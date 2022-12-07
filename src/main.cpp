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

#include <random>	// For random integers


#include "CLP.h"
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
void process(std::string & filePath,unsigned rowStart=1,unsigned rowEnd=100){

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

		// Start at the beginning:	
		file.seekg(0, file.beg);

		//unsigned int beginning = file.gtell();	
		// Save firstLine:
		std::getline(file,firstLine);
		
		// Determine column delimiter:
		char delimiter = determineDelimiter(firstLine);
		
		// Go back to the first line so that it will be
		// included in the processing loop:
		file.seekg(0, file.beg);

		//output << firstLine << std::endl;
		
		////////////////////////////////////////////////
		//
		// PROCESS DATA LINES:
		//
		////////////////////////////////////////////////
		
		const unsigned limit=151;
		const unsigned symbolsLimit=51;
		const char* numeral[] = {
			"⓪",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","⑩",
			"⑪","⑫","⑬","⑭","⑮","⑯","⑰","⑱","⑲","⑳",
			"㉑","㉒","㉓","㉔","㉕","㉖","㉗","㉘","㉙","㉚",
			"㉛","㉜","㉝","㉞","㉟","㊱","㊲","㊳","㊴","㊵",
			"㊶","㊷","㊸","㊹","㊺","㊻","㊼","㊽","㊾","㊿",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉍",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉎",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","㉏",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐙",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟⑩",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟⑳",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟㉚",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟㊵",
			"①","②","③","④","⑤","⑥","⑦","⑧","⑨","🐟㊿"
		};

		unsigned lc=0; // line counter
		while (std::getline(file, line)) {
			++lc;
			
			// ALWAYS ALLOW ROW ONE (ASSUMED HEADER ROW) TO BE PROCESSED:
			if(lc!=1 && lc<rowStart){
				continue;
			}
			if(lc>rowEnd){
				return;
			}

			split(column,buffer,bufferSize,delimiter,line);
			unsigned cc=0;
			
			// PRINT ROW NUMBER:
			std::cout << vt100::startCyan << lc << ": " << vt100::stopColor ;

			// NOW PRINT COLUMNS:
			for(auto i=column.begin();i<column.end();i++){
				++cc;

				// SHOW EVERY TENTH COLUMN IN GREEN, OTHERWISE MAGENTA:
				// THESE COLORS SHOULD BE EASY ENOUGH TO SEE ON ALL COLOR TERMINALS:
				std::cout << (cc%10==0 ? vt100::startGreen : vt100::startMagenta);
				// USE THE CIRCLED SYMBOLS WHILE THEY LAST ... THEN SWITCH TO
				// THE DOUBLE-STRUCK SYMBOLS PROVIDED BY printEnumerationDigits:
				if(cc<symbolsLimit){
					// ENCIRCLED DIGITS:
					std::cout << numeral[cc];
				}else{
					// DOUBLE-STRUCK DIGITS:
					std::cout << printEnumerationDigits(cc,cc<100?2:3);
				}
				std::cout << vt100::stopColor;

				// Print column content:
				std::cout << *i;
				// Print delimiter:
				if(i+1 != column.end()){
					std::cout << delimiter;
				}
			}

			// FINALLY PRINT END OF THE LINE:
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

	//
	// Set up the command-line argument parser:
	//
	CLP clp;
	//clp.addSwitch("--fix","-f","Fix file by continuing to read subsequent lines, removing CR/LFs, until the correct number of columns is achieved. **NOT IMPLEMENTED YET**");
	clp.addSwitch("--help","-h","Print this help and exit");
	clp.addSwitch("--start","-s","Specify a starting row to display",1);
	clp.addSwitch("--count","-c","Specify the number of rows to display",1);
	clp.addSwitch("--end","-e","Specify an ending row to display",1);
	//clp.addSwitch("--all","-a","Display all rows from a file");
	// Example of a switch that requires a parameter to follow after it:
	//clp.addSwitch("--font","-f","Font to be used",1);
	clp.addUsage("enumerator [options] [csv_file_paths]\n\nThis tool displays an enumeration of columns on the terminal.\nBy default, lines 1 to 100 are shown. (Use options to specify a different range).");

	if(!clp.parse(argc,argv)){
		exit(1);
	}

	if(!clp.getArguments().size()){
		Warning("main","Specify at least one file for processing");
		clp.printHelp();
		exit(1);
	}

	unsigned rowStart = 0;
	unsigned rowEnd   = 0;
	unsigned rowCount = 0;

	if(clp.hasSwitchSet("--start")){
		rowStart = std::stoi(clp.getSwitchArgument("--start",1));
	}
	if(clp.hasSwitchSet("--count")){
		rowCount = std::stoi(clp.getSwitchArgument("--count",1));
		rowEnd   = rowStart + rowCount - 1;
	}
	if(clp.hasSwitchSet("--end")){
		if(rowCount){
			std::cerr << "NOTA BENE: Specified row END will take precedence over row COUNT." << std::endl;
		}
		rowEnd   = std::stoi(clp.getSwitchArgument("--end",1));
	}

	if(!rowStart){
		//std::random_device rd;     // Only used once to initialise (seed) engine
		//std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
		//std::uniform_int_distribution<unsigned> uni(1,1000); // Guaranteed unbiased
		//rowStart = uni(rng);
		rowStart=1;
	}
	if(!(rowCount || rowEnd)){
		rowCount = 100;
		rowEnd   = rowStart + rowCount - 1;
	}

	std::cerr << vt100::startBlue << "Showing rows " << vt100::startOrange << rowStart << vt100::startBlue << " to " << vt100::startOrange << rowEnd << vt100::startBlue << " (" << vt100::startOrange << rowCount << vt100::startBlue << " rows)." << vt100::stopColor << std::endl;

	for(unsigned i=1;i<(unsigned)argc;i++){
		//

		std::string filePath = argv[i];
    		process(filePath,rowStart,rowEnd);
  	}
  	return 0;
}



//////////////////////////////////////////
//
// utilities.cpp
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

#include "utilities.h"

//
// printBoxedText
//
void printBoxedText(std::ostream & ost, std::string & text, vt100::command color){
  size_t textLength = text.length();
  std::string horizontalBar;
  for(unsigned i=0;i<textLength;i++){ horizontalBar += "─"; }
  ost << color << "┌─" << horizontalBar << "─┐" << vt100::stopColor << std::endl;
  ost << color << "│ " << text << " │" << vt100::stopColor << std::endl;
  ost << color << "└─" << horizontalBar << "─┘" << vt100::stopColor << std::endl;
  return;
}

//
// englishSingularPlural
//
// The following function is actually 
// enough for a subset of other non-English
// languages (like Spanish ... but not French!).
// See: https://unicode-org.github.io/cldr-staging/charts/37/supplemental/language_plural_rules.html
// for rules recorded in the CLDR project.
//
const char* englishSingularPlural(int val,const char* singular,const char *plural){
  return val==1 ? singular : plural;
}

//
// timeDuration
//
std::string timeDuration(std::chrono::steady_clock::time_point startTime,std::chrono::steady_clock::time_point endTime){
  std::chrono::duration<double> elapsed_time = endTime - startTime;
  double execution_time = elapsed_time.count();

  // NOTA BENE: The result will always be in English PLURAL form because we are
  // showing fractional digits after the decimal point, e.g. "1.0000 seconds" 
  // is the grammatically correct form:
  std::stringstream stream;
  stream << std::fixed << std::setprecision(6) << execution_time 
    << " seconds" ;
  return stream.str();
}


/////////////////////////////////////////////////////////////////////
//
// determineDelimiter
//
//
/////////////////////////////////////////////////////////////////////
char determineDelimiter(std::string & firstLine){
  
	unsigned columnCount   =0; unsigned delimiterType=0;
	unsigned commaCount    =0; constexpr unsigned     commaMask=1;
	unsigned tabCount      =0; constexpr unsigned       tabMask=2;
	unsigned pipeCount     =0; constexpr unsigned      pipeMask=4;
	unsigned colonCount    =0; constexpr unsigned     colonMask=8;
	unsigned semicolonCount=0; constexpr unsigned semicolonMask=16;
	for(const char* c = firstLine.c_str(); *c ; c++ ){
		switch(*c){
			case ',':
				commaCount++;
				delimiterType |= commaMask;
				break;
			case '\t':
				tabCount++;
				delimiterType |= tabMask;
				break;
			case '|':
				pipeCount++;
				delimiterType |= pipeMask;
				break;
			case ':':
				colonCount++;
				delimiterType |= colonMask;
				break;
			case ';':
				semicolonCount++;
				delimiterType |= semicolonMask;
				break;
		}
	}
	char columnDelimiter;
	std::string dType;
	switch(delimiterType){
		case commaMask:
			columnDelimiter=',';
			columnCount = ++commaCount;
			dType="COMMA";
			break;
		case tabMask:
			columnDelimiter='\t';
			columnCount = ++tabCount;
			dType="TAB";
			break;
		case pipeMask:
			columnDelimiter='|';
			columnCount = ++pipeCount;
			dType="PIPE";
			break;
		case colonMask:
			columnDelimiter=':';
			columnCount = ++colonCount;
			dType="COLON";
			break;
		case semicolonMask:
			columnDelimiter=';';
			columnCount = ++semicolonCount;
			dType="SEMICOLON";
			break;
		default:
			columnDelimiter='\0';
			dType="INDETERMINATELY";
			break;		
	}
	if(columnDelimiter){
		// REPORT ON DELIMITER TYPE:
		std::cerr << vt100::startBlue << "File appears to be " << vt100::startOrange << dType << vt100:: startBlue << " delimited with " << vt100::startOrange << columnCount << vt100::startBlue << " columns." << vt100::stopColor << std::endl;
	}else{
		std::cerr << vt100::startRed << "Error: Unable to determine a unique delimiter in the first line:" << vt100::stopColor << std::endl;

		std::cerr << "┌──────────── COUNTS OF ────────────┐" << std::endl;
		std::cerr << "│COMMAS│TABS│PIPES│COLONS│SEMICOLONS│" << std::endl;
		std::cerr << "│" << std::setw(5) << commaCount << " │" << std::setw(3) << tabCount << " │" << std::setw(4) << pipeCount << " │" << std::setw(5) << colonCount << " │" << std::setw(9) << semicolonCount << " │" << std::endl;
		std::cerr << "└───────────────────────────────────┘" << std::endl;
	}
	// RETURN DELIMITER VALUE:
	return columnDelimiter;
}


//
// printEnumerationDigits
//
std::string printEnumerationDigits(unsigned int value,unsigned int width){
	// DEFAULT DOUBLE STRUCK SET:
	const char * enumerationDigits[10]={
		"𝟘","𝟙","𝟚","𝟛","𝟜","𝟝","𝟞","𝟟","𝟠","𝟡"
	};
	
	// Break the value apart into power-of-ten components:
	unsigned int digit[width];
	// Initialize vector to zeros:
	for(unsigned i=0;i<width;digit[i++]=0);
	// Store the power-of-ten values in each slot:
	for(int v=value, w=width-1 ; w>=0 && v ; --w,v/=10){
		digit[w]=v%10;
	}
	// Prepare output:
	std::string s;
	for(unsigned i=0;i<width;i++){
		s += enumerationDigits[ digit[i] ];
	}
	
	return s;
}

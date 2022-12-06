/////////////////////////////////////////////////////////
//
// This file is part of the MADELINE 2 program 
// written by Edward H. Trager and Ritu Khanna
// Copyright (c) 2005 by the
// Regents of the University of Michigan.
// All Rights Reserved.
// 
// The latest version of this program is available from:
// 
//   http://eyegene.ophthy.med.umich.edu/madeline/
//   
// Released under the GNU General Public License.
// A copy of the GPL is included in the distribution
// package of this software, or see:
// 
//   http://www.gnu.org/copyleft/
//   
// ... for licensing details.
// 
/////////////////////////////////////////////////////////
//
// 2005.03.14.ET
//

//
// Message.cpp
//

#include "Message.h"
#include <string.h>
#include "VT100.h"

//
// Static and Const Members:
//

const char *Message::_defaultSalutation="Message";
MessageInitializer MessageInitializer::messageInitializer;

//
// Constructor
//
Message::Message(const char *const methodName, const char *format,...){
	
	//
	// The Message base class uses the default salutation:
	//
	_salutation = _defaultSalutation;
	_methodName = methodName;
	int n;
	va_list args;
	if(strlen(format) > 0){
		va_start(args,format);
		n=vsnprintf(_message,GENERAL_STRING_BUFFER_SIZE,format,args);
		va_end(args);
		_truncated=(n==GENERAL_STRING_BUFFER_SIZE);
	}
	//
	// Call print method:
	//
	print();
}

//
// print()
//
void Message::print(void){
	
	std::cerr << vt100::startRed;
	std::cerr << _salutation << ": ";
	std::cerr << vt100::stopColor;
	std::cerr << vt100::startGreen;
	std::cerr << _methodName << ": ";
	std::cerr << vt100::stopColor;
	std::cerr << _message << std::endl;
	if(_truncated){
		std::cerr << "(Message has been truncated)" << std::endl;
	}
}

//
// _initialize(): 
//
// => Initializes gettext NLS system
//    by loading the message catalog for the program:
//
// => Called by MessageInitializer loader class
//
void Message::_initialize( void){
	
	//setlocale (LC_ALL, "");
	// PACKAGE and LOCALEDIR from config.h:
	//bindtextdomain (PACKAGE, LOCALEDIR);
	//textdomain (PACKAGE);
	
}

//
// get():
//               
std::string Message::get(void) const{
	
	std::string s;
	s += _salutation;
	s += ": ";
	s += _methodName;
	s += ": ";
	s += _message;
	s += '\n';
	return s;
	
}

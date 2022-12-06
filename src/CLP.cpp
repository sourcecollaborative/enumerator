/////////////////////////////////////////////////////////
//
// CLP.cpp
//
// This file is a modified version of CLP.cpp from the
//  MADELINE 2 program written by Edward H. Trager, 
// Ritu Khanna and Adrian Marrs and Copyright (c) 2005 
// by the Regents of the University of Michigan.
// All Rights Reserved.
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
// CLP.cpp
// 

#include "CLP.h"
#include "Warning.h"
#include "VT100.h"
#include <iomanip>

///////////////////////////////////
//
// CONST STATIC MEMBERS:
//
///////////////////////////////////

///////////////////////////////////
//
// PRIVATE METHODS:
//
///////////////////////////////////

//
// _getShortSwitchNameMapping: returns the long  name corresponding to the short switch name
//
std::string CLP::_getShortSwitchNameMapping(const std::string& shortName){
	
	std::string switchName=".";
	std::map<std::string,std::string>::iterator it = _shortSwitchMapping.find(shortName);
	if(it != _shortSwitchMapping.end()) switchName= it->second;
	return switchName;
	
}

//
// _shortNameExists:
//
bool CLP::_shortNameExists(const std::string& shortName){
	
	std::map<std::string,std::string>::iterator it = _shortSwitchMapping.find(shortName);
	if(it != _shortSwitchMapping.end()) return true;
	return false;
	
}

//
// _setSwitchArguments: Some of the switches require arguments. This method saves the arguments passed to a switch in a map.
//
void CLP::_setSwitchArguments(std::string currentSwitch,unsigned int argc,char* argv[],int& currentIndex, CLS& cls){
	
	std::vector<std::string> tempArgs;
	unsigned switchArgumentSize =cls.getNumberOfSwitchArguments();
	for(unsigned k=0;k<switchArgumentSize;k++){
		if((currentIndex+k+1) < argc && argv[currentIndex+k+1][0] != '-'){
			std::string temp = argv[currentIndex+k+1];
			tempArgs.push_back(temp);
		}else{
			
			Warning("CLP::_setSwitchArguments()",
			        "Insufficient arguments provided for switch %1$s. The switch will be ignored",
			        currentSwitch.c_str()
			);
			currentIndex += k;
			cls.resetSwitch();
			return;
		}
	}
	if(tempArgs.size() == switchArgumentSize){
		for(unsigned cnt=0;cnt<tempArgs.size();cnt++) cls.addSwitchArgument(tempArgs[cnt]);
		currentIndex += switchArgumentSize;
		cls.setSwitch();
	}
	
}


///////////////////////////////////
//
// PUBLIC METHODS:
//
///////////////////////////////////

//
// printHelp:
//
void CLP::printHelp(){
	
	std::cerr << vt100::startBlue << "USAGE:  " << vt100::stopColor << _usage << std::endl << std::endl;
	std::cerr << vt100::startBlue << "OPTIONS:" << vt100::stopColor ;
        std::cerr << std::endl << vt100::startCornflowerBlue << "----------------" << vt100::stopColor;
	for(auto mit = _switches.begin() ; mit != _switches.end() ; mit++ ){
		std::cerr << std::endl << std::setw(16) << mit->first << " " << mit->second.getDescription();
		std::cerr << std::endl << std::setw(16) << mit->second.getShortName();
                std::cerr << std::endl << vt100::startCornflowerBlue << "----------------" << vt100::stopColor;
	}
	std::cerr << std::endl;
	
}

//
// addUsage:
//
void CLP::addUsage(const std::string usage){
	
	_usage = usage;
	
}

//
// addSwitch:
//
void CLP::addSwitch(std::string name,std::string shortName,std::string description,unsigned numberOfArguments){
	
	if(_shortNameExists(shortName)){
		Warning("CLP::addSwitch()","The shortName %s for %s is being used by another switch. Specify an alternate short name.",shortName.c_str(),name.c_str());
		return;
	}
	std::pair<std::map<std::string,CLS>::iterator,bool> p;
	p = _switches.insert(std::pair<std::string,CLS>(name,CLS(name,shortName,description,numberOfArguments)));
	if(!p.second){
		Warning("CLP::addSwitch()",
		        "Duplicate Switch %1$s not allowed.",
		        name.c_str()
		);
	}else{
		_shortSwitchMapping.insert(std::pair<std::string,std::string>(shortName,name));
	}
}

//
// hasSwitchSet:
//
bool CLP::hasSwitchSet(std::string name){
	
	std::string switchName;
	if(name[1] != '-'){
		switchName = _getShortSwitchNameMapping(name);
		if(switchName==".") return false;
	}else switchName=name;
	std::map<std::string,CLS>::iterator mit = _switches.find(switchName);
	if(mit != _switches.end()) return mit->second.isSet();
	return false;
	
}

///
/// parse: Parses the command line arguments. Returns false if there was an error encountered. 
///
bool CLP::parse(int argc,char* argv[]){
	
	if(argc < 2){
		printHelp();
		return false;
	}
	
	const char *methodName="CLP::parse()"; // used for warnings
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){ 
			if(argv[i][1] == '-'){
				// Check for switches 
				std::map<std::string,CLS>::iterator mit = _switches.find(argv[i]);
				if(mit != _switches.end()){
					// Insert this switch into the list of switches that are set
					_setSwitchArguments(argv[i],argc,argv,i,mit->second);
				}else{
					
					Warning(methodName,
					        "Undefined switch %1$s.",
					        argv[i]
					);
					
					return false;
				}
			}else{
				// Check for the switches associated with '-'
				std::string temp=argv[i];
				unsigned j=1;
				// For multiple short switches specified together
				while(j < temp.length()){
					std::string shortSwitch="-"+temp.substr(j,1);
					// Find the equivalent name of the shortSwitch 
					std::string switchName = _getShortSwitchNameMapping(shortSwitch);
					if(switchName != "."){
						std::map<std::string,CLS>::iterator mit = _switches.find(switchName);
						_setSwitchArguments(shortSwitch,argc,argv,i,mit->second);
					}else{
						
						Warning(methodName,
						        "Undefined switch %1$s.",
						        shortSwitch.c_str()
						);
						
						return false;
					}
					j++;
					
				}
			}
		}else{
			std::string temp=argv[i];
			_arguments.push_back(temp);
		}
	}
	return true;
	
}

//
// getArguments:
//
const std::vector<std::string>& CLP::getArguments(){
	
	return _arguments;
	
}


///
/// getSwitchArgument: Some of the command line switches require arguments.
/// This method returns the index'th argument specified by the user for a switch.
///
std::string CLP::getSwitchArgument(std::string name,unsigned index){
	
	std::string switchName=name;
	if(name[1] != '-') switchName = _getShortSwitchNameMapping(name);
	
	std::map<std::string,CLS>::iterator mit = _switches.find(switchName);
	std::string temp=".";
	if(mit != _switches.end()){
		if(index > mit->second.getNumberOfSwitchArguments() || index <= 0){
			Warning("CLP::getSwitchArgument()","No command line argument exists for '%s' with index %d.",switchName.c_str(),index);
			return temp;
		}
		return mit->second.getSwitchArgument(index-1);
	}
	return temp;
	
}

//
// DEBUG: printArguments:
//
void CLP::printArguments(void){
	
	for(unsigned i=0;i<_arguments.size();i++) std::cout << _arguments[i] << std::endl;
	
}

//
// CLS (Command Line Switch)
//

//
// Constructor:
//
CLS::CLS(std::string name,std::string shortName,std::string description,unsigned numberOfSwitchArguments){
	
	_name=name;
	_shortName = shortName;
	_description = description;
	_numberOfSwitchArguments = numberOfSwitchArguments;
	_isSet = false;
}



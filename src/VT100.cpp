/////////////////////////////////////////////////////////
//
// This file is part of the MADELINE 2 program 
// written by Edward H. Trager, Ritu Khanna, and Adrian Marrs
// Copyright (c) 2005, 2016 by the
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
// VT100.cpp
//
// 2016.01.28.ET
// Updated: 2022.08.05.ET
//

#include "VT100.h"

VTStreamState VTStreamState::vtStreamState;
const std::streambuf *VTStreamState::coutBuf;
const std::streambuf *VTStreamState::cerrBuf;
const bool VTStreamState::coutIsATerminal=isatty(fileno(stdout));
const bool VTStreamState::cerrIsATerminal=isatty(fileno(stderr));

VTStreamState::VTStreamState(){
	
	coutBuf=std::cout.rdbuf();
	cerrBuf=std::cerr.rdbuf();
	
}

std::ostream & operator << (std::ostream &os, enum vt100::command cmd){

	//////////////////////////
	//
	// The command strings:
	//
	//////////////////////////
	static const char* const commandString[] = {
	        "\x1b[0m",    // stopColor
		"\x1b[1;30m", // startBlack
		"\x1b[1;31m", // startRed
		"\x1b[1;32m", // startGreen
		"\x1b[1;33m", // startYellow
		"\x1b[1;34m", // startBlue
		"\x1b[1;35m", // startMagenta
		"\x1b[1;36m", // startCyan
		"\x1b[1;37m", // startWhite
		"\x1b[38;2;128;0;0m", // startMaroon
		"\x1b[38;2;139;0;0m", // startDarkRed
		"\x1b[38;2;165;42;42m", // startBrown
		"\x1b[38;2;178;34;34m", // startFireBrick
		"\x1b[38;2;220;20;60m", // startCrimson
		"\x1b[38;2;255;99;71m", // startTomato
		"\x1b[38;2;255;127;80m", // startCoral
		"\x1b[38;2;205;92;92m", // startIndianRed
		"\x1b[38;2;240;128;128m", // startLightCoral
		"\x1b[38;2;233;150;122m", // startDarkSalmon
		"\x1b[38;2;250;128;114m", // startSalmon
		"\x1b[38;2;255;160;122m", // startLightSalmon
		"\x1b[38;2;255;69;0m", // startOrangeRed
		"\x1b[38;2;255;140;0m", // startDarkOrange
		"\x1b[38;2;255;165;0m", // startOrange
		"\x1b[38;2;255;215;0m", // startGold
		"\x1b[38;2;184;134;11m", // startDarkGoldenRod
		"\x1b[38;2;218;165;32m", // startGoldenRod
		"\x1b[38;2;238;232;170m", // startPaleGoldenRod
		"\x1b[38;2;189;183;107m", // startDarkKhaki
		"\x1b[38;2;240;230;140m", // startKhaki
		"\x1b[38;2;128;128;0m", // startOlive
		"\x1b[38;2;154;205;50m", // startYellowGreen
		"\x1b[38;2;85;107;47m", // startDarkOliveGreen
		"\x1b[38;2;107;142;35m", // startOliveDrab
		"\x1b[38;2;124;252;0m", // startLawnGreen
		"\x1b[38;2;127;255;0m", // startChartreuse
		"\x1b[38;2;173;255;47m", // startGreenYellow
		"\x1b[38;2;0;100;0m", // startDarkGreen
		"\x1b[38;2;34;139;34m", // startForestGreen
		"\x1b[38;2;0;255;0m", // startLime
		"\x1b[38;2;50;205;50m", // startLimeGreen
		"\x1b[38;2;144;238;144m", // startLightGreen
		"\x1b[38;2;152;251;152m", // startPaleGreen
		"\x1b[38;2;143;188;143m", // startDarkSeaGreen
		"\x1b[38;2;0;250;154m", // startMediumSpringGreen
		"\x1b[38;2;0;255;127m", // startSpringGreen
		"\x1b[38;2;46;139;87m", // startSeaGreen
		"\x1b[38;2;102;205;170m", // startMediumAquamarine
		"\x1b[38;2;60;179;113m", // startMediumSeaGreen
		"\x1b[38;2;32;178;170m", // startLightSeaGreen
		"\x1b[38;2;47;79;79m", // startDarkSlateGray
		"\x1b[38;2;0;128;128m", // startTeal
		"\x1b[38;2;0;139;139m", // startDarkCyan
		"\x1b[38;2;0;255;255m", // startAqua
		"\x1b[38;2;224;255;255m", // startLightCyan
		"\x1b[38;2;0;206;209m", // startDarkTurquoise
		"\x1b[38;2;64;224;208m", // startTurquoise
		"\x1b[38;2;72;209;204m", // startMediumTurquoise
		"\x1b[38;2;175;238;238m", // startPaleTurquoise
		"\x1b[38;2;127;255;212m", // startAquamarine
		"\x1b[38;2;176;224;230m", // startPowderBlue
		"\x1b[38;2;95;158;160m", // startCadetBlue
		"\x1b[38;2;70;130;180m", // startSteelBlue
		"\x1b[38;2;100;149;237m", // startCornflowerBlue
		"\x1b[38;2;0;191;255m", // startDeepSkyBlue
		"\x1b[38;2;30;144;255m", // startDodgerBlue
		"\x1b[38;2;173;216;230m", // startLightBlue
		"\x1b[38;2;135;206;235m", // startSkyBlue
		"\x1b[38;2;135;206;250m", // startLightSkyBlue
		"\x1b[38;2;25;25;112m", // startMidnightBlue
		"\x1b[38;2;0;0;128m", // startNavy
		"\x1b[38;2;0;0;139m", // startDarkBlue
		"\x1b[38;2;0;0;205m", // startMediumBlue
		"\x1b[38;2;65;105;225m", // startRoyalBlue
		"\x1b[38;2;138;43;226m", // startBlueViolet
		"\x1b[38;2;75;0;130m", // startIndigo
		"\x1b[38;2;72;61;139m", // startDarkSlateBlue
		"\x1b[38;2;106;90;205m", // startSlateBlue
		"\x1b[38;2;123;104;238m", // startMediumSlateBlue
		"\x1b[38;2;147;112;219m", // startMediumPurple
		"\x1b[38;2;139;0;139m", // startDarkMagenta
		"\x1b[38;2;148;0;211m", // startDarkViolet
		"\x1b[38;2;153;50;204m", // startDarkOrchid
		"\x1b[38;2;186;85;211m", // startMediumOrchid
		"\x1b[38;2;128;0;128m", // startPurple
		"\x1b[38;2;216;191;216m", // startThistle
		"\x1b[38;2;221;160;221m", // startPlum
		"\x1b[38;2;238;130;238m", // startViolet
		"\x1b[38;2;255;0;255m", // startFuchsia
		"\x1b[38;2;218;112;214m", // startOrchid
		"\x1b[38;2;199;21;133m", // startMediumVioletRed
		"\x1b[38;2;219;112;147m", // startPaleVioletRed
		"\x1b[38;2;255;20;147m", // startDeepPink
		"\x1b[38;2;255;105;180m", // startHotPink
		"\x1b[38;2;255;182;193m", // startLightPink
		"\x1b[38;2;255;192;203m", // startPink
		"\x1b[38;2;250;235;215m", // startAntiqueWhite
		"\x1b[38;2;245;245;220m", // startBeige
		"\x1b[38;2;255;228;196m", // startBisque
		"\x1b[38;2;255;235;205m", // startBlanchedAlmond
		"\x1b[38;2;245;222;179m", // startWheat
		"\x1b[38;2;255;248;220m", // startCornSilk
		"\x1b[38;2;255;250;205m", // startLemonChiffon
		"\x1b[38;2;250;250;210m", // startLightGoldenRodYellow
		"\x1b[38;2;255;255;224m", // startLightYellow
		"\x1b[38;2;139;69;19m", // startSaddleBrown
		"\x1b[38;2;160;82;45m", // startSienna
		"\x1b[38;2;210;105;30m", // startChocolate
		"\x1b[38;2;205;133;63m", // startPeru
		"\x1b[38;2;244;164;96m", // startSandyBrown
		"\x1b[38;2;222;184;135m", // startBurlyWood
		"\x1b[38;2;210;180;140m", // startTan
		"\x1b[38;2;188;143;143m", // startRosyBrown
		"\x1b[38;2;255;228;181m", // startMoccasin
		"\x1b[38;2;255;222;173m", // startNavajoWhite
		"\x1b[38;2;255;218;185m", // startPeachPuff
		"\x1b[38;2;255;228;225m", // startMistyRose
		"\x1b[38;2;255;240;245m", // startLavenderBlush
		"\x1b[38;2;250;240;230m", // startLinen
		"\x1b[38;2;253;245;230m", // startOldLace
		"\x1b[38;2;255;239;213m", // startPapayaWhip
		"\x1b[38;2;255;245;238m", // startSeaShell
		"\x1b[38;2;245;255;250m", // startMintCream
		"\x1b[38;2;112;128;144m", // startSlateGray
		"\x1b[38;2;119;136;153m", // startLightSlateGray
		"\x1b[38;2;176;196;222m", // startLightSteelBlue
		"\x1b[38;2;230;230;250m", // startLavender
		"\x1b[38;2;255;250;240m", // startFloralWhite
		"\x1b[38;2;240;248;255m", // startAliceBlue
		"\x1b[38;2;248;248;255m", // startGhostWhite
		"\x1b[38;2;240;255;240m", // startHoneyDew
		"\x1b[38;2;255;255;240m", // startIvory
		"\x1b[38;2;240;255;255m", // startAzure
		"\x1b[38;2;255;250;250m", // startSnow
		"\x1b[38;2;105;105;105m", // startDimGray
		"\x1b[38;2;128;128;128m", // startGray
		"\x1b[38;2;169;169;169m", // startDarkGray
		"\x1b[38;2;169;169;169m", // startDarkGrey
		"\x1b[38;2;192;192;192m", // startSilver
		"\x1b[38;2;211;211;211m", // startLightGray
		"\x1b[38;2;211;211;211m", // startLightGrey
		"\x1b[38;2;220;220;220m", // startGainsboro
		"\x1b[38;2;245;245;245m", // startWhiteSmoke
                "\x1b[48;2;100;149;237m"  // startBackgroundBlue
	};
	
	//
	// If the stream is cout or cerr and if it really is a terminal
	// (and not some file redirection), then print out the v100::command.
	// Otherwise, just return the reference to the ostream.
	//
	std::streambuf const *osBuf = os.rdbuf();
	if( (osBuf==VTStreamState::coutBuf && VTStreamState::coutIsATerminal)
	    || 
	    (osBuf==VTStreamState::cerrBuf && VTStreamState::cerrIsATerminal)
	){
		// Put the color command into the stream:
		os << commandString[cmd];
        	return os;
	}else{
        	return os;
	}
}


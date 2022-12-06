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
// VT100.h
//
// 2016.01.28.ET
//

#ifndef VT100_INCLUDED$
#define VT100_INCLUDED$

#include <iostream>
#include <unistd.h>
#include <stdio.h>

//
// vt100 command namespace and enum:
//
namespace vt100{
	enum command{
		// Colors supported by all essentially 
		// all terminal emulators:
		stopColor=0,
		startBlack,
		startRed,
		startGreen,
		startYellow,
		startBlue,
		startMagenta,
		startCyan,
		startWhite,
		// The following is the set of 140 
		// (minus the 8 above) named HTML
		// colors. These are a subset of the 
		// 24 bit colors which are supported 
		// by most modern terminal emulators
		// but curiously not by Apple's terminal (as of
		// this writing, 2022.08.03). On Apple, it is
		// best to install iTerm2 or similar to get
		// full color support.
		startMaroon,
		startDarkRed,
		startBrown,
		startFireBrick,
		startCrimson,
		startTomato,
		startCoral,
		startIndianRed,
		startLightCoral,
		startDarkSalmon,
		startSalmon,
		startLightSalmon,
		startOrangeRed,
		startDarkOrange,
		startOrange,
		startGold,
		startDarkGoldenRod,
		startGoldenRod,
		startPaleGoldenRod,
		startDarkKhaki,
		startKhaki,
		startOlive,
		startYellowGreen,
		startDarkOliveGreen,
		startOliveDrab,
		startLawnGreen,
		startChartreuse,
		startGreenYellow,
		startDarkGreen,
		startForestGreen,
		startLime,
		startLimeGreen,
		startLightGreen,
		startPaleGreen,
		startDarkSeaGreen,
		startMediumSpringGreen,
		startSpringGreen,
		startSeaGreen,
		startMediumAquamarine,
		startMediumSeaGreen,
		startLightSeaGreen,
		startDarkSlateGray,
		startTeal,
		startDarkCyan,
		startAqua,
		startLightCyan,
		startDarkTurquoise,
		startTurquoise,
		startMediumTurquoise,
		startPaleTurquoise,
		startAquamarine,
		startPowderBlue,
		startCadetBlue,
		startSteelBlue,
		startCornflowerBlue,
		startDeepSkyBlue,
		startDodgerBlue,
		startLightBlue,
		startSkyBlue,
		startLightSkyBlue,
		startMidnightBlue,
		startNavy,
		startDarkBlue,
		startMediumBlue,
		startRoyalBlue,
		startBlueViolet,
		startIndigo,
		startDarkSlateBlue,
		startSlateBlue,
		startMediumSlateBlue,
		startMediumPurple,
		startDarkMagenta,
		startDarkViolet,
		startDarkOrchid,
		startMediumOrchid,
		startPurple,
		startThistle,
		startPlum,
		startViolet,
		startFuchsia,
		startOrchid,
		startMediumVioletRed,
		startPaleVioletRed,
		startDeepPink,
		startHotPink,
		startLightPink,
		startPink,
		startAntiqueWhite,
		startBeige,
		startBisque,
		startBlanchedAlmond,
		startWheat,
		startCornSilk,
		startLemonChiffon,
		startLightGoldenRodYellow,
		startLightYellow,
		startSaddleBrown,
		startSienna,
		startChocolate,
		startPeru,
		startSandyBrown,
		startBurlyWood,
		startTan,
		startRosyBrown,
		startMoccasin,
		startNavajoWhite,
		startPeachPuff,
		startMistyRose,
		startLavenderBlush,
		startLinen,
		startOldLace,
		startPapayaWhip,
		startSeaShell,
		startMintCream,
		startSlateGray,
		startLightSlateGray,
		startLightSteelBlue,
		startLavender,
		startFloralWhite,
		startAliceBlue,
		startGhostWhite,
		startHoneyDew,
		startIvory,
		startAzure,
		startSnow,
		startDimGray,
		startGray,
		startDarkGray,
		startDarkGrey,
		startSilver,
		startLightGray,
		startLightGrey,
		startGainsboro,
		startWhiteSmoke,
                //////////////////////////////////////
                //
                // Definitions for background colors:
                //
                //////////////////////////////////////
		startBackgroundBlue
	};
};

//
// Static class VTStreamState
// maintains information about the
// state of the standard streams
// and whether they are really
// a terminal device or not
//
class VTStreamState{
private:
	static VTStreamState vtStreamState;
	
public:
	static const std::streambuf *coutBuf;
	static const std::streambuf *cerrBuf;
	static const bool coutIsATerminal;
	static const bool cerrIsATerminal;
	
public:
	
	// Constructor:
	VTStreamState();
	
};

//
// Stream operator << for the vt100::commands:
// 
// (This is where the actual work is done)
//
std::ostream & operator << (std::ostream &os,enum vt100::command cmd);

#endif

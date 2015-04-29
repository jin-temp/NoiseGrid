// original code written by Andreas MŸller
// https://github.com/andreasmuller
//
//https://github.com/andreasmuller/NoiseWorkshop/tree/master/NoiseGrid
//
// Modified and commented by Jinnie Templin
//
//
//

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}

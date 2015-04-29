// original code written by Andreas MŸller
// https://github.com/andreasmuller
//
//https://github.com/andreasmuller/NoiseWorkshop/tree/master/NoiseGrid
//
// Modified and commented by Jinnie Templin
//
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Utils/ofEasyCamExt.h"

class ofApp : public ofBaseApp
{
	public:
    
    //declare which functions class ofApp has
        void setup();
        void update();
        void draw();
    
        void keyPressed(int _key);

	
   //declare the global variables 
        ofEasyCamExt		camera;
    
        ofMesh				mesh;
    
        ofxPanel			gui;
    
        ofParameter<float>	frequency;
        ofParameter<float>	timeFrequency;
    
        ofParameter<float>	magnitude;
    
        ofParameter<float>	gridSize;
        ofParameter<int>	gridResolution;
    
        bool				drawGui;
    
        ofTrueTypeFont		fontSmall;
    
		
};
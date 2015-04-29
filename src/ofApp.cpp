// original code written by Andreas Müller
// https://github.com/andreasmuller
//
//https://github.com/andreasmuller/NoiseWorkshop/tree/master/NoiseGrid
//
// Modified and commented by Jinnie Templin
//
//
//

#include "ofApp.h"


void ofApp::setup(){
    //load the font
    fontSmall.loadFont("Fonts/DIN.otf", 8 );
    //tell the gui which font to use
    ofxGuiSetFont( "Fonts/DIN.otf", 8 );
    //set the width of the gui
    ofxGuiSetDefaultWidth( 260 );
    //declare a variable to call previously saved gui settings from an xml file
    string xmlSettingsPath = "Settings/NoiseGrid.xml";
    //setup the gui using information from previously saved settings saved to xml
    gui.setup( "Noise Grid", xmlSettingsPath );
    //add a gui control for frequency
    gui.add( frequency.set("Frequency",  1.0f,  0.01f,  2.0f) );
    //add a gui control for time frequency
    gui.add( timeFrequency.set("Time Frequency",  1.0f,  0.001f,  3.0f) );
    //add a gui control for magnitude
    gui.add( magnitude.set("Magnitude",  0.3f,  0.0f,  5.0f) );
    //add a gui control for grid size
    gui.add( gridSize.set("Grid Size",  6.0f,  0.01f,  20.0f) );
    //add a gui control for grid resolution
    gui.add( gridResolution.set("Grid Resolution",  20,  3,  100) );
    //load the previously saved gui settings from the xml file
    gui.loadFromFile( xmlSettingsPath );
    
    
    camera.setAutoDistance( false );
    camera.setGlobalPosition( ofVec3f(0,5,-10) );
    //determine what point the camera is looking at
    camera.lookAt( ofVec3f(0,3,0) );
    camera.setNearClip( 0.0001f );
    camera.setFarClip( 512 );
    
    //draw the gui controls
    drawGui = true;
}

void ofApp::update(){
    //update the time variable based on time elapsed
    float time = ofGetElapsedTimef();
    //update the noise time variable based on how much time has elapsed and the time frequency defined by the gui controls
    float noiseTime = time * timeFrequency;
    
    ofVec3f extentMin( gridSize * -0.5, 0,		  gridSize * -0.5 );
    ofVec3f extentMax( gridSize *  0.5, gridSize, gridSize *  0.5 );
    
    
    //clear the mesh so we can start over this frame
    mesh.clear();
    //tell the mesh to draw itself with lines
    mesh.setMode( OF_PRIMITIVE_LINES );
    
    //iterate through the y points of the grid
    for( int y = 0; y < gridResolution; y++ )
    {
        //iterate through the x points of the grid
        for( int x = 0; x < gridResolution; x++ )
        {
            //iterate through the z points of the grid
            for( int z = 0; z < gridResolution; z++ )
            {
                //make a new ofVec3f called pos that represents the poisition of a point on the grid
                ofVec3f pos;
                
                //map x, y, and z position values to make sure they fit within the bounds of the grid
                pos.x = ofMap( x,  0, gridResolution-1, extentMin.x, extentMax.x );
                pos.y = ofMap( y,  0, gridResolution-1, extentMin.y, extentMax.y );
                pos.z = ofMap( z,  0, gridResolution-1, extentMin.z, extentMax.z );
                
                //make a vector to manipulate the pos based on noise calculation
                ofVec3f noisePos = pos * frequency;
                
                //give the vector velocity by manipulating the x, y, and z values
                ofVec3f vel;
                vel.x = ofSignedNoise( noisePos.x, noisePos.y, noisePos.z, noiseTime );
                vel.y = ofSignedNoise( noiseTime,  noisePos.z, noisePos.y, noisePos.x );
                vel.z = ofSignedNoise( noisePos.z, noiseTime,  noisePos.y, noisePos.x );
                
                ofVec3f normVel = vel.getNormalized();
                ofVec3f velAsCol = (normVel + ofVec3f(1)) * 0.5;
                
                // set color based on direction of vector's normals
                ofFloatColor tmpCol( velAsCol.x, velAsCol.y, velAsCol.z );
                
                //add a vertext to the mesh at the pos
                mesh.addVertex( pos );
                //set the color of the point/line
                mesh.addColor( tmpCol );
                //add another vertex to "animate" the vertex lines
                mesh.addVertex( pos + (vel * magnitude));
                mesh.addColor( ofFloatColor(tmpCol, 0.0) );
            }
        }
    }
}
void ofApp::draw(){
    
    //draw a gradient background
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    //prepare the gl world by enable depth testing and beginning the camera
    ofEnableDepthTest();
    camera.begin();
    
    // draw a grid on the floor
    //set the color of the grid
    ofSetColor( ofColor(60) );
    ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofDrawGridPlane( 10, 10, false );
    ofPopMatrix();
    
	//reset the color to white
    ofSetColor( ofColor::white );
				//ofDrawBox( 1.0f );
	//draw the mesh
    mesh.draw();
    //"close" the gl world
    camera.end();
    ofDisableDepthTest();
    //draw the gui if the drawGui bool is true
    if( drawGui ) { gui.draw(); }
    
    //set the color to black for the text
    ofSetColor( ofColor::white );
    //write the frame rate in the bottom right corner of the screen
    fontSmall.drawString( ofToString(ofGetFrameRate(), 1), ofGetWidth() - 25, ofGetHeight() - 5 );



}
void ofApp::keyPressed( int _key ) {
    if( _key == ' ' )			  { }
    //if the tab key is pressed, hide or display the gui controls
    else if( _key == OF_KEY_TAB ) { drawGui = !drawGui; }
    // if f is pressed, we toggle in and out of full screen
    else if( _key == 'f' )		  { ofToggleFullscreen(); }
    
}


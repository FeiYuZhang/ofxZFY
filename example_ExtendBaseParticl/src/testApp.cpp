#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	int	iPicImgNum = 10;
	starImgList.resize(iPicImgNum);
	for (int i=0;i<starImgList.size();i++)
	{
		starImgList[i].loadImage("photo/"+ofToString(i+1)+".png");
	}	
}

//--------------------------------------------------------------
void testApp::update(){
	if(ofRandom(0,100)<10)
	{
		star.addStarParticle(&starImgList[ofRandom(0,starImgList.size())], ofPoint(ofRandomWidth(),ofRandomHeight()), ofPoint(ofRandom(-5,5),ofRandom(-5,5)));
	}
	star.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackgroundGradient(ofColor(0, 135, 188), ofColor(1, 52, 103));

	star.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
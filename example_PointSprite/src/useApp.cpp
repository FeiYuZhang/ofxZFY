#include "useApp.h"


useApp::useApp(void)
{
}


useApp::~useApp(void)
{
}

void useApp::setup()
{
	ofDirectory	dir("tex/");	
	int		iTexImgNum = dir.listDir();
	texImgList.resize(iTexImgNum);
	pointSpriteList.resize(iTexImgNum);
	ofDisableArbTex();
	for (int i=0;i<iTexImgNum;i++)
	{
		texImgList[i].loadImage("tex/"+ofToString(i)+".png");
		pointSpriteList[i].setup(&texImgList[i]);
	}
	ofEnableArbTex();

	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofSetWindowPosition(0,0);
}

void useApp::update()
{
	for (int i=0;i<pointSpriteList.size();i++)
	{
		pointSpriteList[i].update();
	}
}

void useApp::draw()
{
	ofBackgroundGradient(ofColor(0, 135, 188), ofColor(1, 52, 103));
	
	//ofSetColor(255);

	for (int i=0;i<pointSpriteList.size();i++)
	{
		pointSpriteList[i].begin();
		pointSpriteList[i].draw();
		pointSpriteList[i].end();
	}

	string info = "FPS: "+ofToString(ofGetFrameRate(), 2)+"\n";
	info += "NUM: "+ofToString(NUM_BILLBOARDS*pointSpriteList.size())+"\n";
	info += "zoom: "+ofToString(pointSpriteList[1].zoom)+"\n";
	info += "zoomTarget: "+ofToString(pointSpriteList[1].zoomTarget);
	ofDrawBitmapStringHighlight(info, 30, 30);
}

void useApp::keyPressed(int key)
{
	switch (key)
	{
	case OF_KEY_LEFT:
		ofSetWindowPosition(ofGetWindowPositionX()-5, ofGetWindowPositionY());
		break;
	case OF_KEY_RIGHT:
		ofSetWindowPosition(ofGetWindowPositionX()+5, ofGetWindowPositionY());
		break;
	default:
		break;
	}
	for (int i=0;i<pointSpriteList.size();i++)
	{
		pointSpriteList[i].keyPressed(key);
	}
}

void useApp::mousePressed(int x, int y)
{

}
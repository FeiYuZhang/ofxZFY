#pragma once

#include "ofMain.h"

#include "zfyPointSprite.h"

class useApp : public ofBaseApp
{
public:
	useApp(void);
	~useApp(void);

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y);

	vector<ofImage>	texImgList;

	vector<zfyPointSprite>	pointSpriteList;
};


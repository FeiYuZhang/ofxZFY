#pragma once

#include "ofMain.h"
#include "ofVbo.h"

#define NUM_BILLBOARDS 2500

class zfyPointSprite
{
public:
	zfyPointSprite(void);
	~zfyPointSprite(void);

	void setup(ofImage* texture);
	void update();
	void draw();

	void begin();
	void end();

	void keyPressed(int key);
	void mousePressed(int x, int y);

	float zoom, zoomTarget;

	ofImage* texture;
	// billboard particles
	ofShader billboardShader;
	ofVboMesh billboards;
	float billboardSizeTarget[NUM_BILLBOARDS];
	ofVec3f billboardVels[NUM_BILLBOARDS];
};

